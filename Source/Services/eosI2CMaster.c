#define __EOS_I2CMASTER_INTERNAL
#include "HardwareProfile.h"
#include "Services/eosI2CMaster.h"
#include "System/eosMemory.h"
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

#define DEF_QUEUE_SIZE            10


typedef enum {                         // Estats del servei
    ssInitializing,                    // -Inicialitzant
    ssWaitCommand,                     // -Esperant comanda
    ssWaitBeginTransaction,            // -Espera el inici de la transaccio
    ssWaitEndTransaction               // -Espera el final de la transaccio
} ServiceStates;

typedef enum {                         // Estat de la transaccio
    tsWaitStart,                       // -Esperant START
    tsWaitRestart,                     // -Esperant RESTART
    tsSendData,                        // -Transmetent dades
    tsReceiveData,                     // -Rebent dades
    tsWaitStop,                        // -Esperant STOP
    tsFinished                         // -Finalitzada
} TransactionStates;

typedef struct __eosI2CTransaction {   // Dades internes d'una transaccio
    bool inUse;                        // -Indica si esta en us
    I2C_MODULE_ID id;                  // -Identificador de modul i2c
    TransactionStates state;           // -Estat de la transaccio
    BYTE address;                      // -Adressa de l'esclau
    TransactionType type;              // -Tipus de transaccio
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
    I2C_MODULE_ID id;                  // -El identificador del modul i2c
    ServiceStates state;               // -Estat del servei
    eosHI2CTransaction hCurrentTransaction; // Transaccio actual
    eosHI2CMasterService hNextService; // -Seguent servei
    eosHI2CTransaction hFirstTransaction;   // -Primera comanda de la cua
    eosHI2CTransaction hLastTransaction;    // -Ultima comanda de la cua
    I2CTransaction *transactionPool;   // -Memoria per les transaccions
    unsigned transactionPoolSize;      // -Tamany de la memoria de transaccions
} I2CMasterService;


static eosHI2CMasterService hFirstService = NULL;     // Primer servei
static eosHI2CMasterService hServiceMap[I2C_NUMBER_OF_MODULES]; // Asignacio modul <-> servei


static void i2cInitialize(I2C_MODULE_ID id);
static void i2cInterruptService(I2C_MODULE_ID id);

static eosHI2CTransaction getTransaction(eosHI2CMasterService hService);


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosResult eosI2CMasterServiceInitialize(
 *              eosI2CServiceParams *params,
 *              eosHI2CMasterService *_hService)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio del servei
 *
 *       Sortida:
 *           hService: El handler del servei
 *
 *       Retorn:
 *           EL resultat de l'operacio
 *
 *************************************************************************/

eosResult eosI2CMasterServiceInitialize(
    eosI2CServiceParams *params,
    eosHI2CMasterService *_hService) {

    eosHI2CMasterService hService = (eosHI2CMasterService) eosAlloc(sizeof(I2CMasterService));
    if (hService == NULL)
        return eos_ERROR_ALLOC;

    hService->id = params->id;
    hService->state = ssInitializing;
    hService->hFirstTransaction = NULL;
    hService->hLastTransaction = NULL;
    hService->hCurrentTransaction = NULL;

    hService->transactionPoolSize = max(DEF_QUEUE_SIZE, params->queueSize);
    hService->transactionPool = eosAlloc(sizeof(I2CTransaction) * hService->transactionPoolSize);

    int i;
    for (i = 0; i < hService->transactionPoolSize; i++)
        hService->transactionPool[i].inUse = false;

    hServiceMap[hService->id] = hService;

    // Afegeix el servei a la llista de serveis
    //
    hService->hNextService = hFirstService;
    hFirstService = hService;

    *_hService = hService;

    return eos_RESULT_SUCCESS;
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
        case ssInitializing:
            i2cInitialize(hService->id);
            hService->state = ssWaitCommand;
            break;

        case ssWaitCommand: {
                eosHI2CTransaction hTransaction = hService->hFirstTransaction;
                if (hTransaction != NULL) {
                    hService->hCurrentTransaction = hTransaction;
                    hService->state = ssWaitBeginTransaction;
                    hService->hFirstTransaction = hTransaction->hNextTransaction;
                }
            }
            break;

        case ssWaitBeginTransaction:
            if (PLIB_I2C_BusIsIdle(hService->id)) {
                PLIB_I2C_MasterStart(hService->id);
                hService->state = ssWaitEndTransaction;
            }
            break;

        case ssWaitEndTransaction: {
                eosHI2CTransaction hTransaction = hService->hCurrentTransaction;
                if (hTransaction->state == tsFinished) {
                    if (hTransaction->onEndTransaction != NULL)
                        hTransaction->onEndTransaction(hTransaction, hTransaction->context);
                    hTransaction->inUse = false;
                    hService->state = ssWaitCommand;
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
 *           eosResult eosI2CMasterStartTransaction(
 *               eosHI2CMasterService hService,
 *               eosI2CTransactionParams *params,
 *               eosHI2CTransaction *hTransaction)
 *
 *       Entrada:
 *           hService: El handler del servei
 *           params  : Parametres de la transaccio
 *
 *       Sortida:
 *           hTransaction: El handler de la transaccio
 *
 *       Retorn:
 *           El resultat de l'operacio
 *
 *************************************************************************/

eosResult eosI2CMasterStartTransaction(
    eosHI2CMasterService hService,
    eosI2CTransactionParams *params,
    eosHI2CTransaction *_hTransaction) {

    eosHI2CTransaction hTransaction = NULL;
    int i = 0;
    for (i = 0; i < hService->transactionPoolSize; i++)
        if (!hService->transactionPool[i].inUse) {
            hService->transactionPool[i].inUse = true;
            hTransaction = &hService->transactionPool[i];
            break;
        }
    if (hTransaction == NULL)
        return eos_ERROR_ALLOC;

    hTransaction->id = hService->id;
    hTransaction->state = tsWaitStart;
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

    *_hTransaction = hTransaction;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Comprova si la transaccio esta pendent de finalitzar
 *
 *       Funcio:
 *           bool eosI2CMasterTransactionIsPending(
 *               eosHI2CTransaction hTransaction)
 *
 *       Entrada:
 *           hTransaction: El handler de la transaccio
 *
 *       Retorn:
 *           true si la transaccio ha finalitzat, false en cas contrari
 *
 **************************************************************************/

bool eosI2CMasterTransactionIsPending(
    eosHI2CTransaction hTransaction) {

    return hTransaction->state != tsFinished;
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


/************************************************************************
 *
 *       Inicialitza el modul I2C
 *
 *       Funcio:
 *           void i2cInitialize(I2C_MODULE_ID id)
 *
 *       Entrada:
 *           id Identificador del modul
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

    eosHI2CMasterService hService = hServiceMap[id];
    if (hService && hService->hCurrentTransaction) {
        
        eosHI2CTransaction hTransaction = hService->hCurrentTransaction;

        switch (hTransaction->state) {
            case tsWaitStart:

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
                        hTransaction->state = tsReceiveData;
                    else
                        hTransaction->state = tsSendData;
                }
                break;

            case tsSendData:

                // Si hi ha colissio, reinicia la transmissio
                //
                if (PLIB_I2C_ArbitrationLossHasOccurred(id)) {
                    PLIB_I2C_ArbitrationLossClear(id);
                    while (!PLIB_I2C_BusIsIdle(id))
                        continue;
                    PLIB_I2C_MasterStart(id);
                    hTransaction->state = tsWaitStart;
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
                        hTransaction->state = tsWaitStop;
                    }
                }
                break;

            case tsWaitStop:
                hTransaction->state = tsFinished;
                break;
        }
    }
}

static eosHI2CTransaction getTransaction(eosHI2CMasterService hService) {

    int i = 0;
    for (i = 0; i < hService->transactionPoolSize; i++)
        if (!hService->transactionPool[i].inUse) {
            hService->transactionPool[i].inUse = true;
            return &hService->transactionPool[i];
        }

    return NULL;
}
