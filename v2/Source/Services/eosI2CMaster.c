#include "eos.h"

#if eosOPTIONS_UseI2CMasterService == 1

#include "System/eosMemory.h"
#include "System/eosInterrupts.h"
#include "System/eosTask.h"
#include "System/eosQueue.h"
#include "System/eosSemaphore.h"
#include "Services/eosI2CMaster.h"

#include "sys/attribs.h"

// Harmony
#include "peripheral/int/plib_int.h"
#include "Peripheral/i2c/plib_i2c.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"


#define __intPriority                  INT_PRIORITY_LEVEL2
#define __intSubPriority               INT_SUBPRIORITY_LEVEL0


typedef enum {                         // Estat de la transaccio
    transactionIdle,                   // -En espera de iniciar
    transactionSendAddress,            // -Transmeteix l'adressa
    transactionSendLength,             // -Transmeteix el byte de longitut
    transactionSendData,               // -Transmeteix un byte de dades
    transactionSendCheck,              // -Transmeteix el byte de verificacio
    transactionSendFinished,           // -Ha finalitzat la transmissio
    transactionStartReceive,           // -Inicia la recepcio de dades
    transactionReceiveLength,          // -Rebent un byte de longitut
    transactionReceiveData,            // -Rebent un byte de dades
    transactionReceiveCheck,           // -Rebent un byte de verificacio
    transactionAck,                    // -ACK transmitit
    transactionNak,                    // -NAK transmitit
    transactionWaitStop,               // -Esperant STOP
    transactionFinished                // -Finalitzada
} eosI2CTransactionState;

typedef struct __eosI2CTransaction {   // Dades internes d'una transaccio
    bool inUse;                        // -Indica si esta en us en el pool
    I2C_MODULE_ID id;                  // -Identificador de modul i2c
    eosSemaphoreHandle hSemaphore;     // -Semafor per notificar el fi de la transaccio
    eosI2CTransactionState state;      // -Estat de la transaccio
    uint8_t address;                   // -Adressa de l'esclau
    unsigned index;                    // -Index
    unsigned maxIndex;                 // -Valor maxim per 'index'
    bool waitingSlaveACK;              // -Esperant ACK/NAK del esclau
    bool writeMode;                    // -Indica si esta en modus escriptura
    uint8_t check;                     // -Byte de verificacio
    eosI2CMasterCallback onEndTransaction;  // -Event END_TRANSACTION
    eosI2CMasterCallback onError;      // -Event ON_ERROR
    void *context;                     // -Parametres del event
    uint8_t *txBuffer;                 // -Buffer de transmissio
    unsigned txCount;                  // -Numero de bytes a transmetre
    uint8_t *rxBuffer;                 // -Buffer de recepcio
    unsigned rxCount;                  // -Numero de bytes en el buffer de recepcio
    unsigned rxSize;                   // -Tamany del buffer de recepcio en bytes
    unsigned error;                    // -Codi d'error
} eosI2CTransaction;

typedef struct __eosI2CMasterService { // Dades internes del servei
    I2C_MODULE_ID id;                  // -El identificador del modul i2c
    eosTaskHandle hTask;               // -Handler de la tasca
    eosQueueHandle hTransactionQueue;  // -Handler de la cua de transaccions
    eosSemaphoreHandle hSemaphore;     // -Semafor de fi de transaccio
    eosPoolHandle hPool;               // -Pool de memoria per les transaccions
} eosI2CMasterService;


static unsigned serviceCount = 0;
static eosI2CTransactionHandle transactionMap[I2C_NUMBER_OF_MODULES];

static void task(void *params);
static void i2cInitialize(I2C_MODULE_ID id);
static void i2cInterrupt(I2C_MODULE_ID id);

extern void __ISR(_I2C_1_VECTOR, IPL2SOFT) isrI2C1Wrapper(void);
extern void __ISR(_I2C_2_VECTOR, IPL2SOFT) isrI2C2Wrapper(void);
extern void __ISR(_I2C_3_VECTOR, IPL2SOFT) isrI2C3Wrapper(void);
extern void __ISR(_I2C_4_VECTOR, IPL2SOFT) isrI2C4Wrapper(void);
extern void __ISR(_I2C_5_VECTOR, IPL2SOFT) isrI2C5Wrapper(void);


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosI2CMasterServiceHandle eosI2CMasterServiceInitialize(
 *              eosI2CServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio del servei
 *
 *       Retorn:
 *           El handler del servei, NULL en cas d'error
 *
 *************************************************************************/

eosI2CMasterServiceHandle eosI2CMasterServiceInitialize(
    eosI2CServiceParams *params) {
    
    eosDebugVerify(params != NULL);

    eosI2CMasterServiceHandle hService = eosAlloc(sizeof(eosI2CMasterService));
    if (hService != NULL) {
        
        eosDebugVerify(serviceCount < (unsigned) I2C_NUMBER_OF_MODULES );
        eosDebugVerify(serviceCount < (unsigned) eosI2CMasterService_MaxInstances);
        
        serviceCount++;

        // -Inicialitza les dades internes del servei
        //
        hService->id = params->id;
        
        // -Crea el pool de memoria per les transaccions
        //
        hService->hPool = eosPoolCreate(sizeof(eosI2CTransaction), 
                eosI2CMasterService_MaxTransactions);
        eosDebugVerify(hService->hPool != NULL);
        
        // -Crea la tasca de gestio
        //        
        hService->hTask = eosTaskCreate(tskIDLE_PRIORITY + params->priority, 
                512, task, hService);
        eosDebugVerify(hService->hTask != NULL);
        
        // -Crea la cua de transaccions
        //
        hService->hTransactionQueue = eosQueueCreate(sizeof(eosI2CTransactionHandle), 
                eosI2CMasterService_MaxTransactions);
        eosDebugVerify(hService->hTransactionQueue != NULL);
        
        // -Crea el semaforo de final de transaccio
        //
        hService->hSemaphore = eosSemaphoreCreate();
        eosDebugVerify(hService->hSemaphore != NULL);

        // -Inicialitza el mapa de transaccions per les interrupcions
        //
        transactionMap[hService->id] = NULL;
    }
    
    return hService;
}


/*************************************************************************
 *
 *       Inicia una transaccio
 *
 *       Funcio:
 *           eosI2CTransactionHandle eosI2CMasterStartTransaction(
 *               eosI2CMasterServiceHandle hService,
 *               eosI2CTransactionParams *params)
 *
 *       Entrada:
 *           hService: El handler del servei
 *           params  : Parametres de la transaccio
 *
 *       Retorn:
 *           El handler de la transaccio. NULL en cas d'error
 *
 *************************************************************************/

eosI2CTransactionHandle eosI2CMasterStartTransaction(
    eosI2CMasterServiceHandle hService,
    eosI2CTransactionParams *params) {
    
    eosDebugVerify(hService != NULL);
    eosDebugVerify(params != NULL);

    if ((params->txBuffer == NULL || params->txCount == 0) &&
       (params->rxBuffer == NULL || params->rxSize  == 0))
        return NULL;
    
    eosI2CTransactionHandle hTransaction = eosPoolAlloc(hService->hPool);
    if (hTransaction != NULL) {

        hTransaction->id = hService->id;
        hTransaction->state = transactionIdle;
        hTransaction->address = params->address;
        hTransaction->txBuffer = params->txBuffer;
        hTransaction->txCount = params->txCount;
        hTransaction->rxBuffer = params->rxBuffer;
        hTransaction->rxSize = params->rxSize;
        hTransaction->onEndTransaction = params->onEndTransaction;
        hTransaction->context = params->context;
        hTransaction->error = 0;

        // Afegeix la transaccio a la cua
        //
        if (!eosQueuePut(hService->hTransactionQueue, &hTransaction, 5000)) {
            eosPoolFree(hTransaction);
            hTransaction = NULL;
        }
    }
    
    return hTransaction;
}


unsigned eosI2CMasterGetTransactionResult(
    eosI2CTransactionHandle hTransaction) {

    return hTransaction->error;
}


/*************************************************************************
 *
 *       Funcio ISR del modul I2C
 * 
 *       Funcio:
 *          void isrI2CxHandler(void)
 *
 *************************************************************************/

void isrI2C1Handler(void) {

    if (eosInterruptSourceFlagGet(INT_SOURCE_I2C_1_MASTER)) {
        i2cInterrupt(I2C_ID_1);
        eosInterruptSourceFlagClear(INT_SOURCE_I2C_1_MASTER);
    }
}

void isrI2C2Handler(void) {

    if (eosInterruptSourceFlagGet(INT_SOURCE_I2C_2_MASTER)) {
        i2cInterrupt(I2C_ID_2);
        eosInterruptSourceFlagClear(INT_SOURCE_I2C_2_MASTER);
    }
}

void isrI2C3Handler(void) {

    if (eosInterruptSourceFlagGet(INT_SOURCE_I2C_3_MASTER)) {
        i2cInterrupt(I2C_ID_3);
        eosInterruptSourceFlagClear(INT_SOURCE_I2C_3_MASTER);
    }
}

void isrI2C4Handler(void) {

    if (eosInterruptSourceFlagGet(INT_SOURCE_I2C_4_MASTER)) {
        i2cInterrupt(I2C_ID_4);
        eosInterruptSourceFlagClear(INT_SOURCE_I2C_4_MASTER);
    }
}

void isrI2C5Handler(void) {

    if (eosInterruptSourceFlagGet(INT_SOURCE_I2C_5_MASTER)) {
        i2cInterrupt(I2C_ID_5);
        eosInterruptSourceFlagClear(INT_SOURCE_I2C_5_MASTER);
    }
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void task(
 *               void *params)
 *
 *       Entrada:
 *           params: Parametre (hService)
 *
 *************************************************************************/

static void task(
    void *params) {

    eosI2CMasterServiceHandle hService = params;
    I2C_MODULE_ID id = hService->id;
    
    i2cInitialize(id);

    while (true) {
           
        eosI2CTransactionHandle hTransaction;
        while (eosQueueGet(hService->hTransactionQueue, &hTransaction, 0xFFFFFFFF)) {
        
            // Espera a que el bus estigui lliure
            //
            while (!PLIB_I2C_BusIsIdle(id)) 
                eosTaskDelay(20);

            // Prepara la transaccio
            //
            hTransaction->writeMode = hTransaction->txBuffer && hTransaction->txCount;
            hTransaction->state = transactionSendAddress;
            hTransaction->hSemaphore = hService->hSemaphore;

            // Inicia la comunicacio. A partir d'aquest punt es
            // generen les interrupcions del modul I2C
            //
            transactionMap[id] = hTransaction;
            PLIB_I2C_MasterStart(id);

            // Espera que finalitzi la transaccio
            //
            if (eosSemaphoreTake(hService->hSemaphore, eosI2CMasterService_TransactionTimeout)) {
                
                // Crida a la funcio callback, si esta definida
                //
                if (hTransaction->onEndTransaction != NULL)
                    hTransaction->onEndTransaction(hTransaction, hTransaction->context);
            }
            else {
                
                // Crida a la funcio callback, si esta definida
                //
                if (hTransaction->onError != NULL)
                    hTransaction->onError(hTransaction, hTransaction->context);
            }

            // Retart entre transaccions
            //
            eosTaskDelay(eosI2CMasterService_EndTransactionDelay);
            
            // Destrueix la transaccio
            //
            eosPoolFree(hTransaction);
            transactionMap[id] = NULL;
        }
    }
}


/************************************************************************
 *
 *       Inicialitza el modul I2C
 *
 *       Funcio:
 *           void i2cInitialize(
 *               I2C_MODULE_ID id)
 *
 *       Entrada:
 *           id: Identificador del modul I2C
 *
 ************************************************************************/

static void i2cInitialize(
    I2C_MODULE_ID id) {
    
    // Inicialitzacio general del modul
    //
    PLIB_I2C_SlaveClockStretchingEnable(id);
    PLIB_I2C_SMBDisable(id);
    PLIB_I2C_HighFrequencyDisable(id);
    PLIB_I2C_StopInIdleEnable(id);

    // Selecciona la frequencia de treball
    //
    PLIB_I2C_BaudRateSet(id, CLOCK_PERIPHERICAL_HZ, 100000);

    // Configura les interrupcions
    //
    switch(id) {
        case I2C_ID_1:
            PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_I2C1, __intPriority);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_I2C1, __intSubPriority);
            eosInterruptSourceEnable(INT_SOURCE_I2C_1_MASTER);
            break;

        case I2C_ID_2:
            PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_I2C2, __intPriority);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_I2C2, __intSubPriority);
            eosInterruptSourceEnable(INT_SOURCE_I2C_2_MASTER);
            break;

        case I2C_ID_3:
            PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_I2C3, __intPriority);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_I2C3, __intSubPriority);
            eosInterruptSourceEnable(INT_SOURCE_I2C_3_MASTER);
            break;

        case I2C_ID_4:
            PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_I2C4, __intPriority);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_I2C4, __intSubPriority);
            eosInterruptSourceEnable(INT_SOURCE_I2C_4_MASTER);
            break;

        case I2C_ID_5:
            PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_I2C5, __intPriority);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_I2C5, __intSubPriority);
            eosInterruptSourceEnable(INT_SOURCE_I2C_5_MASTER);
            break;
    }

    // Activa el modul
    //
    PLIB_I2C_Enable(id);
}


/*************************************************************************
 *
 *       Procesa els events de la comunicacio I2C
 *
 *       Funcio:
 *           void i2cInterrupt(
 *              I2C_MODULE_ID id)
 *
 *       Entrada:
 *           id: Identificador del module I2C
 *
 *       Notes:
 *           Transmissio/Recepcio en format de trama
 *           |LENGTH|DATA-1|DATA-2| . . . |DATA-n|CHECK|
 *
 *************************************************************************/

static void i2cInterrupt(
    I2C_MODULE_ID id) {

    eosI2CTransactionHandle hTransaction = transactionMap[id];
    if (hTransaction != NULL) {

        switch (hTransaction->state) {

            case transactionSendAddress:

                // Si hi ha colissio, reinicia la transmissio
                //
                if (PLIB_I2C_ArbitrationLossHasOccurred(id)) {
                    PLIB_I2C_ArbitrationLossClear(id);
                    while (!PLIB_I2C_BusIsIdle(id))
                        continue;
                    PLIB_I2C_MasterStart(id);
                }

                else {

                    // Envia l'adressa del esclau
                    //
                    I2C_7_BIT_ADDRESS addr;
                    PLIB_I2C_ADDRESS_7_BIT_FORMAT(
                        addr, 
                        hTransaction->address, 
                        hTransaction->writeMode ? I2C_WRITE : I2C_READ);
                    PLIB_I2C_TransmitterByteSend(id, addr.byte);

                    hTransaction->index = 0;
                    hTransaction->check = addr.byte;

                    if (hTransaction->writeMode)
                        hTransaction->state = transactionSendLength;
                    else
                        hTransaction->state = transactionStartReceive;
                }
                break;

            case transactionSendLength:
            case transactionSendData:
            case transactionSendCheck:
            case transactionSendFinished:

                // Si hi ha colissio, reinicia la transmissio
                //
                if (PLIB_I2C_ArbitrationLossHasOccurred(id)) {
                    PLIB_I2C_ArbitrationLossClear(id);
                    while (!PLIB_I2C_BusIsIdle(id))
                        continue;
                    PLIB_I2C_MasterStart(id);
                    hTransaction->state = transactionSendAddress;
                }
            
                else {
                
                    // Si l'esclau ha respos ACK, continua amb els bytes pendents
                    //
                    if (PLIB_I2C_TransmitterByteWasAcknowledged(id) && 
                        (hTransaction->state != transactionSendFinished)) {

                        switch (hTransaction->state) {
                            case transactionSendLength:
                                hTransaction->check += hTransaction->txCount;
                                PLIB_I2C_TransmitterByteSend(id, hTransaction->txCount);
                                if (hTransaction->txCount > 0)
                                    hTransaction->state = transactionSendData;
                                else
                                    hTransaction->state = transactionSendCheck;
                                break;

                            case transactionSendData: {
                                uint8_t data = hTransaction->txBuffer[hTransaction->index++];
                                hTransaction->check += data;
                                PLIB_I2C_TransmitterByteSend(id, data);
                                if (hTransaction->index == hTransaction->txCount) 
                                    hTransaction->state = transactionSendCheck;
                                break;
                            }

                            case transactionSendCheck:
                                PLIB_I2C_TransmitterByteSend(id, hTransaction->check);
                                hTransaction->state = transactionSendFinished;
                                break;
                        }
                    }
                    
                    // En cas contrari finalitza la transmissio o continua
                    // la amb recepcio de dades desde l'esclau
                    //
                    else {

                        // Si s'ha definit el buffer de recepcio, es posa en modus lectura
                        // i inicia la transaccio de nou per rebre la resposta de l'esclau
                        //
                        if (hTransaction->rxBuffer && hTransaction->rxSize) {
                            PLIB_I2C_MasterStartRepeat(id);
                            hTransaction->writeMode = false;
                            hTransaction->state = transactionSendAddress;
                        }

                        // En cas contrari finalitza
                        //
                        else {
                            PLIB_I2C_MasterStop(id);
                            hTransaction->state = transactionWaitStop;
                        }
                    }
                }
                break;

            case transactionStartReceive:

                // Si l'escau ha respos ACK, llegeix un byte
                //
                if (PLIB_I2C_TransmitterByteWasAcknowledged(id)) {
                    PLIB_I2C_MasterReceiverClock1Byte(id);
                    hTransaction->state = transactionReceiveLength;
                }

                // En cas contrari finalitza la transmissio
                //
                else {
                    PLIB_I2C_MasterStop(id);
                    hTransaction->state = transactionWaitStop;
                }
                break;

            case transactionReceiveLength: {
                uint8_t data = PLIB_I2C_ReceivedByteGet(id);
                hTransaction->maxIndex = min(hTransaction->rxSize, data);
                hTransaction->check += data;
                PLIB_I2C_ReceivedByteAcknowledge(id, true);
                hTransaction->waitingSlaveACK = true;
                if (hTransaction->maxIndex > 0)
                    hTransaction->state = transactionReceiveData;
                else
                    hTransaction->state = transactionReceiveCheck;
                break;
            }

            case transactionReceiveData:
                if (hTransaction->waitingSlaveACK) {
                    PLIB_I2C_MasterReceiverClock1Byte(id);
                    hTransaction->waitingSlaveACK = false;
                }
                else {
                    uint8_t data = PLIB_I2C_ReceivedByteGet(id);
                    hTransaction->rxBuffer[hTransaction->index++] = data;
                    hTransaction->check += data;
                    PLIB_I2C_ReceivedByteAcknowledge(id, true);
                    hTransaction->waitingSlaveACK = true;
                    if (hTransaction->index == hTransaction->maxIndex)
                        hTransaction->state = transactionReceiveCheck;
                }
                break;

            case transactionReceiveCheck:
                if (hTransaction->waitingSlaveACK) {
                    PLIB_I2C_MasterReceiverClock1Byte(id);
                    hTransaction->waitingSlaveACK = false;
                }
                else  {
                    uint8_t data = PLIB_I2C_ReceivedByteGet(id);
                    if (data != hTransaction->check)
                        hTransaction->error = 1;
                    hTransaction->rxCount = hTransaction->index;
                    PLIB_I2C_MasterStop(id);
                    hTransaction->state = transactionWaitStop;
                }
                break;

            case transactionWaitStop:
                hTransaction->state = transactionFinished;
                eosSemaphoreISRGive(hTransaction->hSemaphore);
                break;
        }
    }
}


#endif
