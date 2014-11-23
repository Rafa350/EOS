#define __EOS_I2CMASTER_INTERNAL
#include "HardwareProfile.h"
#include "Services/eosI2CMaster.h"
#include "sys/attribs.h"
#include "peripheral/i2c/plib_i2c.h"
#include "peripheral/int/plib_int.h"


#define I2C1_INT_VECTOR           INT_VECTOR_I2C1
#define I2C1_INT_SOURCE_MASTER    INT_SOURCE_I2C_1_MASTER
#define I2C1_CORE_VECTOR          _I2C_1_VECTOR

#define I2C2_INT_VECTOR           INT_VECTOR_I2C2
#define I2C2_INT_SOURCE_MASTER    INT_SOURCE_I2C_2_MASTER
#define I2C2_CORE_VECTOR          _I2C_2_VECTOR

#define I2C3_INT_VECTOR           INT_VECTOR_I2C3
#define I2C3_INT_SOURCE_MASTER    INT_SOURCE_I2C_3_MASTER
#define I2C3_CORE_VECTOR          _I2C_3_VECTOR

#define I2C4_INT_VECTOR           INT_VECTOR_I2C4
#define I2C4_INT_SOURCE_MASTER    INT_SOURCE_I2C_4_MASTER
#define I2C4_CORE_VECTOR          _I2C_4_VECTOR

#define I2C5_INT_VECTOR           INT_VECTOR_I2C5
#define I2C5_INT_SOURCE_MASTER    INT_SOURCE_I2C_5_MASTER
#define I2C5_CORE_VECTOR          _I2C_5_VECTOR


#define SERVICE_POOL_SIZE         I2C_NUMBER_OF_MODULES  // Tamany del pool de serveis
#define TRANSACTION_POOL_SIZE     20   // Tamany del pool de transaccions


typedef enum {                         // Estats del servei
    serviceInitializing,               // -Inicialitzant
    serviceProcessQueue,               // -Procesa la cua de transaccions
    serviceWaitBeginTransaction,       // -Espera el inici de la transaccio
    serviceWaitEndTransaction          // -Espera el final de la transaccio
} ServiceStates;

typedef enum {                         // Estat de la transaccio
    transactionIdle,                   // -En espera de iniciar
    transactionWaitStart,              // -Esperant START
    transactionWaitRestart,            // -Esperant RESTART
    transactionSendData,               // -Transmetent dades
    transactionStartReceiveData,       // -Inicia la recepcio de dades
    transactionReceiveData,            // -Rebent dades
    transactionAck,                    // -ACK transmitit
    transactionNak,                    // -NAK transmitit
    transactionWaitStop,               // -Esperant STOP
    transactionFinished                // -Finalitzada
} TransactionStates;

typedef struct __eosI2CTransaction {   // Dades internes d'una transaccio
    bool inUse;                        // -Indica si esta en us en el pool
    I2C_MODULE_ID id;                  // -Identificador de modul i2c
    TransactionStates state;           // -Estat de la transaccio
    BYTE address;                      // -Adressa de l'esclau
    eosI2CTransactionType type;        // -Tipus de transaccio
    unsigned index;                    // -Index per les transferencies
    eosCallback onEndTransaction;      // -Event END_TRANSACTION
    void *context;                     // -Parametres del event
    BYTE *txBuffer;                    // -Buffer de transmissio
    unsigned txCount;                  // -Numero de bytes a transmetre
    BYTE *rxBuffer;                    // -Buffer de recepcio
    unsigned rxCount;                  // -Numero de bytes en el buffer de recepcio
    unsigned rxSize;                   // -Tamany del buffer de recepcio en bytes
    eosHI2CTransaction hNextTransaction;    // -Seguent transaccio en la cua
} I2CTransaction;

typedef struct __eosI2CMasterService { // Dades internes del servei
    bool inUse;                        // -Inica si esta en un en el pool
    I2C_MODULE_ID id;                  // -El identificador del modul i2c
    ServiceStates state;               // -Estat del servei
    eosHI2CTransaction hFirstTransaction;   // -Primera transaccio de la cua
    eosHI2CTransaction hLastTransaction;    // -Ultima transaccio de la cua
} I2CMasterService;


static bool transactionPoolInitialized = false;
static I2CTransaction transactionPool[TRANSACTION_POOL_SIZE];

static bool servicePoolInitialized = false;
static I2CMasterService servicePool[SERVICE_POOL_SIZE];


static void i2cInitialize(I2C_MODULE_ID id);
static void i2cInterruptService(I2C_MODULE_ID id);

static eosHI2CTransaction getTransactionById(I2C_MODULE_ID id);

static eosHI2CMasterService allocService(void);
static eosHI2CTransaction allocTransaction(void);
static void freeTransaction(eosHI2CTransaction hTransaction);


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosHI2CMasterServicet eosI2CMasterServiceInitialize(
 *              eosI2CServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio del servei
 *
 *       Retorn:
 *           El handler del servei, NULL en cas d'error
 *
 *************************************************************************/

eosHI2CMasterService eosI2CMasterServiceInitialize(
    eosI2CServiceParams *params) {

    eosHI2CMasterService hService = allocService();
    if (!hService)
        return NULL;

    hService->id = params->id;
    hService->state = serviceInitializing;
    hService->hFirstTransaction = NULL;
    hService->hLastTransaction = NULL;

    return hService;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosI2CMasterServiceTask(
 *               eosHI2CMasterService hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

void eosI2CMasterServiceTask(
    eosHI2CMasterService hService) {

    switch (hService->state) {
        case serviceInitializing:
            i2cInitialize(hService->id);
            hService->state = serviceProcessQueue;
            break;

        case serviceProcessQueue:
            if (hService->hFirstTransaction != NULL)
                hService->state = serviceWaitBeginTransaction;
            break;

        case serviceWaitBeginTransaction:
            if (PLIB_I2C_BusIsIdle(hService->id)) {
                hService->hFirstTransaction->state = transactionWaitStart;
                hService->state = serviceWaitEndTransaction;
                PLIB_I2C_MasterStart(hService->id);
                // A partir d'aqui ja es generen interrupcions I2C
            }
            break;

        case serviceWaitEndTransaction: {
                eosHI2CTransaction hTransaction = hService->hFirstTransaction;
                if (hTransaction->state == transactionFinished) {
                    if (hTransaction->onEndTransaction != NULL)
                        hTransaction->onEndTransaction(hTransaction, hTransaction->context);
                    hService->hFirstTransaction = hTransaction->hNextTransaction;
                    freeTransaction(hTransaction);
                    hService->state = serviceProcessQueue;
                }
            }
            break;
    }
}


/*************************************************************************
 *
 *       Gestiona la interrupcio TICK
 *
 *       Funcio:
 *           void eosI2CMasterServiceISRTick(
 *               eosHI2CMasterService hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

void eosI2CMasterServiceISRTick(
    eosHI2CMasterService hService) {

}


/*************************************************************************
 *
 *       Inicia una transaccio
 *
 *       Funcio:
 *           eosHI2CTransaction eosI2CMasterStartTransaction(
 *               eosHI2CMasterService hService,
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

eosHI2CTransaction eosI2CMasterStartTransaction(
    eosHI2CMasterService hService,
    eosI2CTransactionParams *params) {

    eosHI2CTransaction hTransaction = allocTransaction();
    if (!hTransaction)
        return NULL;

    hTransaction->id = hService->id;
    hTransaction->state = transactionIdle;
    hTransaction->address = params->address;
    hTransaction->type = params->type;
    hTransaction->txBuffer = params->txBuffer;
    hTransaction->txCount = params->txCount;
    hTransaction->rxBuffer = params->rxBuffer;
    hTransaction->rxSize = params->rxSize;
    hTransaction->onEndTransaction = params->onEndTransaction;
    hTransaction->context = params->context;

    hTransaction->hNextTransaction = NULL;
    if (hService->hFirstTransaction == NULL) {
        hService->hFirstTransaction = hTransaction;
        hService->hLastTransaction = hTransaction;
    }
    else {
        hService->hFirstTransaction->hNextTransaction = hTransaction;
        hService->hLastTransaction = hTransaction;
    }

    return hTransaction;
}


/*************************************************************************
 *
 *       Gestiona les interrupcios dels moduls I2C
 *
 *************************************************************************/

void __ISR(I2C1_CORE_VECTOR, ipl2) __ISR_Entry(I2C1_CORE_VECTOR) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C1_INT_SOURCE_MASTER)) {
        i2cInterruptService(I2C_ID_1);
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C1_INT_SOURCE_MASTER);
    }
}

void __ISR(I2C2_CORE_VECTOR, ipl2) __ISR_Entry(I2C2_CORE_VECTOR) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C2_INT_SOURCE_MASTER)) {
        i2cInterruptService(I2C_ID_2);
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C2_INT_SOURCE_MASTER);
    }
}

void __ISR(I2C3_CORE_VECTOR, ipl2) __ISR_Entry(I2C3_CORE_VECTOR) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C3_INT_SOURCE_MASTER)) {
        i2cInterruptService(I2C_ID_3);
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C3_INT_SOURCE_MASTER);
    }
}

void __ISR(I2C4_CORE_VECTOR, ipl2) __ISR_Entry(I2C4_CORE_VECTOR) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C4_INT_SOURCE_MASTER)) {
        i2cInterruptService(I2C_ID_4);
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C4_INT_SOURCE_MASTER);
    }
}

void __ISR(I2C5_CORE_VECTOR, ipl2) __ISR_Entry(I2C5_CORE_VECTOR) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C5_INT_SOURCE_MASTER)) {
        i2cInterruptService(I2C_ID_5);
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C5_INT_SOURCE_MASTER);
    }
}


/************************************************************************
 *
 *       Inicialitza el modul I2C
 *
 *       Funcio:
 *           void i2cInitialize(I2C_MODULE_ID id)
 *
 *       Entrada:
 *           id Identificador del modul I2C
 *
 ************************************************************************/

static void i2cInitialize(I2C_MODULE_ID id) {

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
            PLIB_INT_VectorPrioritySet(INT_ID_0, I2C1_INT_VECTOR, INT_PRIORITY_LEVEL2);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, I2C1_INT_VECTOR, INT_SUBPRIORITY_LEVEL0);
            PLIB_INT_SourceEnable(INT_ID_0, I2C1_INT_SOURCE_MASTER);
            break;

        case I2C_ID_2:
            PLIB_INT_VectorPrioritySet(INT_ID_0, I2C2_INT_VECTOR, INT_PRIORITY_LEVEL2);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, I2C2_INT_VECTOR, INT_SUBPRIORITY_LEVEL0);
            PLIB_INT_SourceEnable(INT_ID_0, I2C2_INT_SOURCE_MASTER);
            break;

        case I2C_ID_3:
            PLIB_INT_VectorPrioritySet(INT_ID_0, I2C3_INT_VECTOR, INT_PRIORITY_LEVEL2);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, I2C3_INT_VECTOR, INT_SUBPRIORITY_LEVEL0);
            PLIB_INT_SourceEnable(INT_ID_0, I2C3_INT_SOURCE_MASTER);
            break;

        case I2C_ID_4:
            PLIB_INT_VectorPrioritySet(INT_ID_0, I2C4_INT_VECTOR, INT_PRIORITY_LEVEL2);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, I2C4_INT_VECTOR, INT_SUBPRIORITY_LEVEL0);
            PLIB_INT_SourceEnable(INT_ID_0, I2C4_INT_SOURCE_MASTER);
            break;

        case I2C_ID_5:
            PLIB_INT_VectorPrioritySet(INT_ID_0, I2C5_INT_VECTOR, INT_PRIORITY_LEVEL2);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, I2C5_INT_VECTOR, INT_SUBPRIORITY_LEVEL0);
            PLIB_INT_SourceEnable(INT_ID_0, I2C5_INT_SOURCE_MASTER);
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
 *           void i2cInterruptService() 
 *
 *************************************************************************/

static void i2cInterruptService(I2C_MODULE_ID id) {

    eosHI2CTransaction hTransaction = getTransactionById(id);
    if (hTransaction != NULL) {

        switch (hTransaction->state) {

            case transactionWaitStart:

                // Si hi ha colissio, reinicia la transmissio
                //
                if (PLIB_I2C_ArbitrationLossHasOccurred(id)) {
                    PLIB_I2C_ArbitrationLossClear(id);
                    while (!PLIB_I2C_BusIsIdle(id))
                        continue;
                    PLIB_I2C_MasterStart(id);
                }

                // Si tot es correcte, envia l'adressa de l'escalu
                //
                else {
                    I2C_7_BIT_ADDRESS addr;
                    PLIB_I2C_ADDRESS_7_BIT_FORMAT(
                        addr, 
                        hTransaction->address, 
                        hTransaction->type == ttRead ? I2C_READ : I2C_WRITE);
                    PLIB_I2C_TransmitterByteSend(id, addr.byte);
                    hTransaction->index = 0;
                    if (hTransaction->type == ttRead)
                        hTransaction->state = transactionStartReceiveData;
                    else
                        hTransaction->state = transactionSendData;
                }
                break;

            case transactionSendData:

                // Si hi ha colissio, reinicia la transmissio
                //
                if (PLIB_I2C_ArbitrationLossHasOccurred(id)) {
                    PLIB_I2C_ArbitrationLossClear(id);
                    while (!PLIB_I2C_BusIsIdle(id))
                        continue;
                    PLIB_I2C_MasterStart(id);
                    hTransaction->state = transactionWaitStart;
                }
            
                else {
                    // Si l'esclau ha respos ACK, continua els bytes pendents
                    //
                    if (PLIB_I2C_TransmitterByteWasAcknowledged(id) &&
                        (hTransaction->index < hTransaction->txCount))
                        PLIB_I2C_TransmitterByteSend(id, hTransaction->txBuffer[hTransaction->index++]);

                    // En cas contrari finalitza la transmissio
                    //
                    else {
                        PLIB_I2C_MasterStop(id);
                        hTransaction->state = transactionWaitStop;
                    }
                }
                break;

            case transactionStartReceiveData:

                // Si l'escau ha respos ACK, llegeix un byte
                //
                if (PLIB_I2C_TransmitterByteWasAcknowledged(id)) {
                    PLIB_I2C_MasterReceiverClock1Byte(id);
                    hTransaction->state = transactionReceiveData;
                }

                // En cas contrari finalitza la transmissio
                //
                else {
                    PLIB_I2C_MasterStop(id);
                    hTransaction->state = transactionWaitStop;
                }
                break;

            case transactionReceiveData:
                hTransaction->rxBuffer[hTransaction->index++] = PLIB_I2C_ReceivedByteGet(id);
                if (hTransaction->index < hTransaction->rxSize) {
                    PLIB_I2C_ReceivedByteAcknowledge(id, true);
                    hTransaction->state = transactionAck;
                }
                else {
                    PLIB_I2C_ReceivedByteAcknowledge(id, false);
                    hTransaction->state = transactionNak;
                }
                break;

            case transactionAck:
                PLIB_I2C_MasterReceiverClock1Byte(id);
                hTransaction->state = transactionReceiveData;
                break;

            case transactionNak:
                PLIB_I2C_MasterStop(id);
                hTransaction->state = transactionWaitStop;
                break;

            case transactionWaitStop:
                hTransaction->state = transactionFinished;
                break;
        }
    }
}


/*************************************************************************
 *
 *       Obte la transaccio asociada al mocul
 *
 *       Funcio:
 *           eosHI2CTransaction getTransactionById(I2C_MODULE_ID id)
 *
 *       Entrada:
 *           id: Identificador del modul
 *
 *       Retorn:
 *           El handler de la transaccio. NULL en cas d'error
 *
 *************************************************************************/

static eosHI2CTransaction getTransactionById(I2C_MODULE_ID id) {

    int i;

    for (i = 0; i < sizeof(transactionPool) / sizeof(transactionPool[0]); i++) {
        eosHI2CTransaction hTransaction = &transactionPool[i];
        if ((hTransaction->inUse) &&
            (hTransaction->state != transactionIdle) &&
            (hTransaction->id == id))
            return hTransaction;
    }

    return NULL;
}


/*************************************************************************
 *
 *       Crea una objecte I2CService
 *
 *       Funcio:
 *           eosHI2CMasterService allocTransaction(void)
 *
 *       Retorn:
 *           El handler del objecte creat. NULL en cas d'error
 *
 *************************************************************************/

static eosHI2CMasterService allocService(void) {

    int i;

    if (!servicePoolInitialized) {
        for (i = 0; i < sizeof(servicePool) / sizeof(servicePool[0]); i++)
            servicePool[i].inUse = false;
        servicePoolInitialized = true;
    }

    for (i = 0; i < sizeof(servicePool) / sizeof(servicePool[0]); i++) {
        eosHI2CMasterService hService = &servicePool[i];
        if (!hService->inUse) {
            hService->inUse = true;
            return hService;
        }
    }

    return NULL;
}


/*************************************************************************
 *
 *       Crea una objecte I2CTransaction
 *
 *       Funcio:
 *           eosHI2CTransaction allocTransaction(void)
 *
 *       Retorn:
 *           El handler del objecte creat. NULL en cas d'error
 *
 *************************************************************************/

static eosHI2CTransaction allocTransaction(void) {

    int i = 0;

    if (!transactionPoolInitialized) {
        for (i = 0; i < sizeof(transactionPool) / sizeof(transactionPool[0]); i++)
            transactionPool[i].inUse = false;
        transactionPoolInitialized = true;
    }

    for (i = 0; i < sizeof(transactionPool) / sizeof(transactionPool[0]); i++) {
        eosHI2CTransaction hTransaction = &transactionPool[i];
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
 *               eosHI2CTransaction hTransaction)
 *
 *       Entrada:
 *           hTransaction: El objecte a destruir
 *
 *************************************************************************/

static void freeTransaction(eosHI2CTransaction hTransaction) {

    hTransaction->inUse = false;
}
