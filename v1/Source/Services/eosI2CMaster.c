#include "System/eosMemory.h"
#include "Services/eosI2CMaster.h"
#include "Services/eosTick.h"
#include "sys/attribs.h"
#include "peripheral/i2c/plib_i2c.h"
#include "peripheral/int/plib_int.h"


#define __intPriority                  INT_PRIORITY_LEVEL2
#define __intSubPriority               INT_SUBPRIORITY_LEVEL0


typedef enum {                         // Estats del servei
    serviceInitializing,               // -Inicialitzant
    serviceProcessQueue,               // -Procesa la cua de transaccions
    serviceWaitEndTransaction,         // -Espera el final de la transaccio
    serviceWaitEndDelay                // -Espera el final del retard
} eosI2CMasterServiceState;

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
    eosI2CTransactionState state;      // -Estat de la transaccio
    BYTE address;                      // -Adressa de l'esclau
    unsigned index;                    // -Index
    unsigned maxIndex;                 // -Valor maxim per 'index'
    bool waitingSlaveACK;              // -Esperant ACK/NAK del esclau
    bool writeMode;                    // -Indica si esta en modus escriptura
    BYTE check;                        // -Byte de verificacio
    eosI2CMasterCallback onEndTransaction;  // -Event END_TRANSACTION
    void *context;                     // -Parametres del event
    BYTE *txBuffer;                    // -Buffer de transmissio
    unsigned txCount;                  // -Numero de bytes a transmetre
    BYTE *rxBuffer;                    // -Buffer de recepcio
    unsigned rxCount;                  // -Numero de bytes en el buffer de recepcio
    unsigned rxSize;                   // -Tamany del buffer de recepcio en bytes
    unsigned error;                    // -Codi d'error
    eosI2CTransactionHandle hNextTransaction;    // -Seguent transaccio en la cua
} eosI2CTransaction;

typedef struct __eosI2CMasterService { // Dades internes del servei
    I2C_MODULE_ID id;                  // -El identificador del modul i2c
    eosI2CMasterServiceState state;    // -Estat del servei
    eosI2CTransactionHandle hCurrentTransaction; // -Transaccio en proces
    eosI2CTransactionHandle hFirstTransaction;   // -Primera transaccio de la cua
    eosI2CTransactionHandle hLastTransaction;    // -Ultima transaccio de la cua
    eosI2CTransactionHandle hTransactionPool;    // -Pool de transaccions
    unsigned tickCount;                // -Contador de ticks
} eosI2CMasterService;

static eosI2CTransactionHandle transactionMap[I2C_NUMBER_OF_MODULES];


// Pool de memoria per transaccions
//
static bool transactionPoolInitialized = false;
static eosI2CTransaction transactionPool[eosOPTIONS_I2CMASTER_MAX_TRANSACTIONS];

static void tickFunction(eosI2CMasterServiceHandle hService);
static void i2cInitialize(I2C_MODULE_ID id);
static void i2cInterruptService(I2C_MODULE_ID id);

static eosI2CTransactionHandle allocTransaction(void);
static void freeTransaction(eosI2CTransactionHandle hTransaction);


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

    unsigned transactionPoolSize = sizeof(eosI2CTransaction) * eosOPTIONS_I2CMASTER_MAX_TRANSACTIONS;

    // Crea el bloc de memoria complert per servei. Inclueix el propi
    // servei i el pool de transaccions
    //
    eosI2CMasterServiceHandle hService = (eosI2CMasterServiceHandle) eosAlloc(
        sizeof(eosI2CMasterService) + transactionPoolSize);
    if (hService != NULL) {

        // -Inicialitza les dades internes del servei
        //
        hService->id = params->id;
        hService->state = serviceInitializing;
        hService->hTransactionPool = (eosI2CTransactionHandle)((BYTE*) hService + sizeof(eosI2CMasterService));
        hService->hFirstTransaction = NULL;
        hService->hLastTransaction = NULL;
        hService->tickCount = 0;

        // -Inicialitza el mapa de transaccions per les interrupcions
        //
        transactionMap[hService->id] = NULL;

        // Asigna la funcio d'interrupcio TICK
        //
        eosTickRegisterCallback(NULL, (eosTickCallback) tickFunction, hService, false);
    }
    
    return hService;
}


/*************************************************************************
 *
 *       Comprova si el servei esta preparat
 *
 *       Funcio:
 *           bool eosI2CMasterServiceIsReady(
 *               eosI2CMasterServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *       Retorn:
 *           True si el servei esta preparat, false en cas contrari
 *
 *************************************************************************/

bool eosI2CMasterServiceIsReady(
    eosI2CMasterServiceHandle hService) {

    return hService->state != serviceInitializing;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosI2CMasterServiceTask(
 *               eosI2CMasterServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

void eosI2CMasterServiceTask(
    eosI2CMasterServiceHandle hService) {

    switch (hService->state) {
        case serviceInitializing:
            i2cInitialize(hService->id);
            hService->state = serviceProcessQueue;
            break;

        case serviceProcessQueue:

            // Comprova si hi ha alguna transaccio en la cua
            //
            if (hService->hFirstTransaction != NULL) {

                // Comprova si el bus esta lliure
                //
                if (PLIB_I2C_BusIsIdle(hService->id)) {

                    // Treu la primera transaccio de la cua
                    //
                    eosI2CTransactionHandle hTransaction = hService->hFirstTransaction;
                    hService->hFirstTransaction = hService->hFirstTransaction->hNextTransaction;

                    // Prepara la transaccio
                    //
                    hTransaction->writeMode = hTransaction->txBuffer && hTransaction->txCount;
                    hTransaction->state = transactionSendAddress;

                    hService->state = serviceWaitEndTransaction;
                    hService->hCurrentTransaction = hTransaction;

                    // Inicia la comunicacio. A partir d'aquest punt es
                    // generen les interrupcions del modul I2C
                    //
                    transactionMap[hService->id] = hTransaction;
                    PLIB_I2C_MasterStart(hService->id);
                }
            }
            break;

        case serviceWaitEndTransaction: {

                eosI2CTransactionHandle hTransaction = hService->hCurrentTransaction;
                
                // Comprova si ha finalitzat la transaccio
                //
                if (hTransaction->state == transactionFinished) {

                    // Crida a la funcio callback, si esta definida
                    //
                    if (hTransaction->onEndTransaction != NULL)
                        hTransaction->onEndTransaction(hTransaction);

                    // Destrueix la transaccio
                    //
                    freeTransaction(hTransaction);
                    transactionMap[hService->id] = NULL;

                    // Retart entre transaccions
                    //
                    hService->tickCount = eosOPTIONS_I2CMASTER_END_TRANSACTION_DELAY;
                    hService->state = serviceWaitEndDelay;
                }
            }
            break;

        case serviceWaitEndDelay:
            if (!hService->tickCount)
                hService->state = serviceProcessQueue;
            break;
    }
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

    if ((params->txBuffer == NULL || params->txCount == 0) &&
       (params->rxBuffer == NULL || params->rxSize  == 0))
        return NULL;

    eosI2CTransactionHandle hTransaction = allocTransaction();
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
        hTransaction->hNextTransaction = NULL;
        if (hService->hFirstTransaction == NULL) {
            hService->hFirstTransaction = hTransaction;
            hService->hLastTransaction = hTransaction;
        }
        else {
            hService->hFirstTransaction->hNextTransaction = hTransaction;
            hService->hLastTransaction = hTransaction;
        }
    }
    
    return hTransaction;
}


unsigned eosI2CMasterGetTransactionResult(
    eosI2CTransactionHandle hTransaction) {

    return hTransaction->error;
}

void *eosI2CMasterGetTransactionContext(
    eosI2CTransactionHandle hTransaction) {

    return hTransaction->context;
}


/*************************************************************************
 *
 *       Gestiona la interrupcio TICK
 *
 *       Funcio:
 *           void tickFuncion(
 *               eosI2CMasterServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

static void tickFunction(
    eosI2CMasterServiceHandle hService) {

    if (hService->tickCount > 0)
        hService->tickCount--;
}


/*************************************************************************
 *
 *       Funcio ISR del modul I2C
 * 
 *       Funcio:
 *          void eosI2CMasterServiceISRx(void)
 *
 *************************************************************************/

void __ISR(_I2C_1_VECTOR, IPL2SOFT) eosI2CMasterServiceISR1(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_I2C_1_MASTER)) {
        i2cInterruptService(I2C_ID_1);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_2_MASTER);
    }
}

void __ISR(_I2C_2_VECTOR, IPL2SOFT) eosI2CMasterServiceISR2(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_I2C_2_MASTER)) {
        i2cInterruptService(I2C_ID_2);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_2_MASTER);
    }
}

void __ISR(_I2C_3_VECTOR, IPL2SOFT) eosI2CMasterServiceISR3(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_I2C_3_MASTER)) {
        i2cInterruptService(I2C_ID_3);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_3_MASTER);
    }
}

void __ISR(_I2C_4_VECTOR, IPL2SOFT) eosI2CMasterServiceISR4(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_I2C_4_MASTER)) {
        i2cInterruptService(I2C_ID_4);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_4_MASTER);
    }
}

void __ISR(_I2C_5_VECTOR, IPL2SOFT) eosI2CMasterServiceISR5(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_I2C_5_MASTER)) {
        i2cInterruptService(I2C_ID_5);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_5_MASTER);
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
 *           void i2cInterruptService(
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

static void i2cInterruptService(
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
                                BYTE data = hTransaction->txBuffer[hTransaction->index++];
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
                BYTE data = PLIB_I2C_ReceivedByteGet(id);
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
                    BYTE data = PLIB_I2C_ReceivedByteGet(id);
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
                    BYTE data = PLIB_I2C_ReceivedByteGet(id);
                    if (data != hTransaction->check)
                        hTransaction->error = 1;
                    hTransaction->rxCount = hTransaction->index;
                    PLIB_I2C_MasterStop(id);
                    hTransaction->state = transactionWaitStop;
                }
                break;

            case transactionWaitStop:
                hTransaction->state = transactionFinished;
                break;
        }
    }
}


/*************************************************************************
 *
 *       Crea una objecte I2CTransaction
 *
 *       Funcio:
 *           eosI2CTransactionHandle allocTransaction(void)
 *
 *       Retorn:
 *           El handler del objecte creat. NULL en cas d'error
 *
 *************************************************************************/

static eosI2CTransactionHandle allocTransaction(void) {

    int i = 0;

    if (!transactionPoolInitialized) {
        for (i = 0; i < sizeof(transactionPool) / sizeof(transactionPool[0]); i++)
            transactionPool[i].inUse = false;
        transactionPoolInitialized = true;
    }

    for (i = 0; i < sizeof(transactionPool) / sizeof(transactionPool[0]); i++) {
        eosI2CTransactionHandle hTransaction = &transactionPool[i];
        if (!hTransaction->inUse) {
            hTransaction->inUse = true;
            return hTransaction;
        }
    }
    
    return NULL;
}


/*************************************************************************
 *
 *       Destrueix un objecte I2Ctransaction
 *
 *       Funcio:
 *           void freeTransaction(
 *               eosI2CTransactionHandle hTransaction)
 *
 *       Entrada:
 *           hTransaction: El objecte a destruir
 *
 *************************************************************************/

static void freeTransaction(
    eosI2CTransactionHandle hTransaction) {

    hTransaction->inUse = false;
}
