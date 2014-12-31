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


typedef enum {                         // Estats del servei
    serviceInitializing,               // -Inicialitzant
    serviceProcessQueue,               // -Procesa la cua de transaccions
    serviceWaitEndTransaction,         // -Espera el final de la transaccio
    serviceWaitEndDelay                // -Espera el final del retard
} ServiceStates;

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
} TransactionStates;

typedef struct __eosI2CTransaction {   // Dades internes d'una transaccio
    bool inUse;                        // -Indica si esta en us en el pool
    I2C_MODULE_ID id;                  // -Identificador de modul i2c
    TransactionStates state;           // -Estat de la transaccio
    BYTE address;                      // -Adressa de l'esclau
    unsigned index;                    // -Index
    unsigned maxIndex;                 // -Valor maxim per 'index'
    bool waitingSlaveACK;              // -Esperant ACK/NAK del esclau
    bool writeMode;                    // -Indica si esta en modus escriptura
    BYTE check;                        // -Byte de verificacio
    eosCallback onEndTransaction;      // -Event END_TRANSACTION
    void *context;                     // -Parametres del event
    BYTE *txBuffer;                    // -Buffer de transmissio
    unsigned txCount;                  // -Numero de bytes a transmetre
    BYTE *rxBuffer;                    // -Buffer de recepcio
    unsigned rxCount;                  // -Numero de bytes en el buffer de recepcio
    unsigned rxSize;                   // -Tamany del buffer de recepcio en bytes
    unsigned error;                    // -Codi d'error
    eosHI2CTransaction hNextTransaction;    // -Seguent transaccio en la cua
} I2CTransaction;

typedef struct __eosI2CMasterService { // Dades internes del servei
    bool inUse;                        // -Inica si esta en un en el pool
    I2C_MODULE_ID id;                  // -El identificador del modul i2c
    ServiceStates state;               // -Estat del servei
    eosHI2CTransaction hCurrentTransaction; // -Transaccio en proces
    eosHI2CTransaction hFirstTransaction;   // -Primera transaccio de la cua
    eosHI2CTransaction hLastTransaction;    // -Ultima transaccio de la cua
    unsigned tickCount;                // -Contador de ticks
} I2CMasterService;


// Pool de memoria per transaccions
//
static bool transactionPoolInitialized = false;
static I2CTransaction transactionPool[eosOPTIONS_I2CMASTER_MAX_TRANSACTIONS];

// Pool de memoria pels serveis
//
static bool servicePoolInitialized = false;
static I2CMasterService servicePool[eosOPTIONS_I2CMASTER_MAX_INSTANCES];


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
    if (hService == NULL)
        return NULL;

    hService->id = params->id;
    hService->state = serviceInitializing;
    hService->hFirstTransaction = NULL;
    hService->hLastTransaction = NULL;
    hService->tickCount = 0;

    // Asigna la funcio d'interrupcio TICK
    //
    eosHTickService hTickService = params->hTickService;
    if (hTickService == NULL)
        hTickService = eosGetTickServiceHandle();
    if (hTickService != NULL)
        eosTickAttach(hTickService, (eosTickCallback) eosI2CMasterServiceTick, hService);

    return hService;
}


/*************************************************************************
 *
 *       Comprova si el servei esta preparat
 *
 *       Funcio:
 *           bool eosI2CMasterServiceIsReady(
 *               eosHI2CMasterService hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *       Retorn:
 *           True si el servei esta preparat, false en cas contrari
 *
 *************************************************************************/

bool eosI2CMasterServiceIsReady(
    eosHI2CMasterService hService) {

    return hService->state != serviceInitializing;
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

            // Comprova si hi ha alguna transaccio en la cua
            //
            if (hService->hFirstTransaction != NULL) {

                // Comprova si el bus esta lliure
                //
                if (PLIB_I2C_BusIsIdle(hService->id)) {

                    // Treu la primera transaccio de la cua
                    //
                    eosHI2CTransaction hTransaction = hService->hFirstTransaction;
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
                    PLIB_I2C_MasterStart(hService->id);
                }
            }
            break;

        case serviceWaitEndTransaction: {

                eosHI2CTransaction hTransaction = hService->hCurrentTransaction;
                
                // Comprova si ha finalitzat la transaccio
                //
                if (hTransaction->state == transactionFinished) {

                    // Crida a la funcio callback, si esta definida
                    //
                    if (hTransaction->onEndTransaction != NULL)
                        hTransaction->onEndTransaction(hTransaction, hTransaction->context);

                    // Destrueix la transaccio
                    //
                    freeTransaction(hTransaction);

                    // Retart entre transaccions
                    //
                    bool intState = eosGetInterruptState();
                    eosDisableInterrupts();
                    hService->tickCount = eosOPTIONS_I2CMASTER_END_TRANSACTION_DELAY;
                    if (intState)
                        eosEnableInterrupts();
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
 *       Gestiona la interrupcio TICK
 *
 *       Funcio:
 *           void eosI2CMasterServiceTick(
 *               eosHI2CMasterService hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

void eosI2CMasterServiceTick(
    eosHI2CMasterService hService) {

    if (hService->tickCount > 0)
        hService->tickCount--;
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

    if ((params->txBuffer == NULL || params->txCount == 0) &&
       (params->rxBuffer == NULL || params->rxSize  == 0))
        return NULL;

    eosHI2CTransaction hTransaction = allocTransaction();
    if (hTransaction == NULL)
        return NULL;

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

    return hTransaction;
}


unsigned eosI2CMasterGetTransactionResult(
    eosHI2CTransaction hTransaction) {

    return hTransaction->error;
}


/*************************************************************************
 *
 *       Gestiona les interrupcios dels moduls I2C
 *
 *************************************************************************/

void __ISR(I2C1_CORE_VECTOR, IPL2SOFT) __ISR_Entry(I2C1_CORE_VECTOR) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C1_INT_SOURCE_MASTER)) {
        i2cInterruptService(I2C_ID_1);
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C1_INT_SOURCE_MASTER);
    }
}

void __ISR(I2C2_CORE_VECTOR, IPL2SOFT) __ISR_Entry(I2C2_CORE_VECTOR) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C2_INT_SOURCE_MASTER)) {
        i2cInterruptService(I2C_ID_2);
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C2_INT_SOURCE_MASTER);
    }
}

void __ISR(I2C3_CORE_VECTOR, IPL2SOFT) __ISR_Entry(I2C3_CORE_VECTOR) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C3_INT_SOURCE_MASTER)) {
        i2cInterruptService(I2C_ID_3);
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C3_INT_SOURCE_MASTER);
    }
}

void __ISR(I2C4_CORE_VECTOR, IPL2SOFT) __ISR_Entry(I2C4_CORE_VECTOR) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C4_INT_SOURCE_MASTER)) {
        i2cInterruptService(I2C_ID_4);
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C4_INT_SOURCE_MASTER);
    }
}

void __ISR(I2C5_CORE_VECTOR, IPL2SOFT) __ISR_Entry(I2C5_CORE_VECTOR) {

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
 *       Notes:
 *           Transmissio/Recepcio en format de trama
 *           |LENGTH|DATA-1|DATA-2| . . . |DATA-n|CHECK|
 *
 *************************************************************************/

static void i2cInterruptService(I2C_MODULE_ID id) {

    eosHI2CTransaction hTransaction = getTransactionById(id);
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
 *       Obte la transaccio asociada al modul
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
