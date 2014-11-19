#define __EOS_I2CMASTER_INTERNAL
#include "HardwareProfile.h"
#include "Services/eosI2CMaster.h"
#include "System/eosMemory.h"
#include "System/eosQueue.h"
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


typedef enum {                    // Codis d'operacio
    opStartTransaction            // -Inicia una transaccio
} OpCodes;

typedef enum {                    // Estats del servei
    ssInitializing,               // -Inicialitzant
    ssWaitCommand,                // -Esperant comanda
    ssWaitBeginTransaction,       // -Espera el inici de la transaccio
    ssWaitEndTransaction          // -Espera el final de la transaccio
} ServiceStates;

typedef enum {                    // Estat de la transaccio
    tsWaitStart,                  // -Esperant START
    tsWaitRestart,                // -Esperant RESTART
    tsSendData,                   // -Transmetent dades
    tsReceiveData,                // -Rebent dades
    tsWaitStop,                   // -Esperant STOP
    tsFinished                    // -Finalitzada
} TransactionStates;

typedef struct {                       // Comanda
    OpCodes opCode;                    // -Codi d'operacio
    eosHI2CTransaction hTransaction;   // -Transaccio
} Command;

typedef struct __I2CTransaction {      // Dades internes d'una transaccio
    I2C_MODULE_ID id;                  // -Identificador de modul i2c
    TransactionStates state;           // -Estat de la transaccio
    BYTE address;                      // -Adressa de l'esclau
    TransactionType type;              // -Tipus de transaccio
    BYTE *txBuffer;                    // -Buffer de transmissio
    unsigned txCount;                  // -Numero de bytes a transmetre
    unsigned txIndex;                  // -Index al buffer de transmissio
} Transaction;

typedef struct __I2CMasterService {    // Dades internes del servei
    I2C_MODULE_ID id;                  // -El identificador del modul i2c
    ServiceStates state;               // -Estat del servei
    eosHQueue hCommandQueue;           // -Cua de comandes
    eosHI2CTransaction hCurrentTransaction;      // Transaccio actual
    eosHI2CMasterService hNextService; // -Seguent servei
} I2CMasterService;

static eosHI2CMasterService hFirstService = NULL;     // Primer servei


static void i2cInitialize(I2C_MODULE_ID id);
static eosHI2CMasterService i2cLocateService(I2C_MODULE_ID id);
static void i2cInterruptService(I2C_MODULE_ID id);


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

    // Inicialitza la cua de commandes
    //
    eosHQueue hQueue;
    eosQueueParams queueParams;
    queueParams.itemSize = sizeof(Command);
    queueParams.maxItems = 10;
    if (eosQueueCreate(&queueParams, &hQueue) != eos_RESULT_SUCCESS) {
        eosFree(hService);
        return eos_ERROR_ALLOC;
    }

    hService->id = params->id;
    hService->state = ssInitializing;
    hService->hCommandQueue = hQueue;
    hService->hCurrentTransaction = NULL;

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

                // Procesa les comandes pendents
                //
                Command command;
                if (eosQueueGet(hService->hCommandQueue, &command) == eos_RESULT_SUCCESS) {
                    switch (command.opCode) {
                        case opStartTransaction:
                            hService->hCurrentTransaction = command.hTransaction;
                            hService->state = ssWaitBeginTransaction;
                            break;
                    }
                }
            }
            break;

        case ssWaitBeginTransaction:
            if (PLIB_I2C_BusIsIdle(hService->id)) {
                PLIB_I2C_MasterStart(hService->id);
                hService->state = ssWaitEndTransaction;
            }
            break;

        case ssWaitEndTransaction:
            if (hService->hCurrentTransaction == NULL)
                hService->state = ssWaitCommand;
            break;
    }
}


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
    
    eosHI2CTransaction hTransaction = eosAlloc(sizeof(Transaction));
    if (hTransaction == NULL)
        return eos_ERROR_ALLOC;

    hTransaction->id = hService->id;
    hTransaction->state = tsWaitStart;
    hTransaction->address = params->address;
    hTransaction->type = params->type;
    hTransaction->txBuffer = params->txBuffer;
    hTransaction->txCount = params->txCount;

    Command command;
    command.opCode = opStartTransaction;
    command.hTransaction = hTransaction;
    eosQueuePut(hService->hCommandQueue, &command);

    *_hTransaction = hTransaction;

    return eos_RESULT_SUCCESS;
}


BOOL eosI2CMasterTransactionIsPending(
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


/************************************************************************
 *
 *       Localitza el servei que gestiona el modul especificat
 *
 *       Funcio:
 *           eosHI2CMasterService i2cLocateService(
 *               I2C_MODULE_ID id)
 *
 *       Entrada:
 *           id: Identificador del modul
 *
 *       Retorn:
 *           El handler del servei o NULL en cas d'error
 *
 ************************************************************************/

static eosHI2CMasterService i2cLocateService(I2C_MODULE_ID id) {

    eosHI2CMasterService hService = hFirstService;
    while (hService) {
        if (hService->id == id)
            return hService;
        else
            hService = hService->hNextService;
    }

    return NULL;
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

    eosHI2CMasterService hService = i2cLocateService(id);
    if (hService && hService->hCurrentTransaction) {
        
        eosHI2CTransaction hTransaction = hService->hCurrentTransaction;

        switch (hTransaction->state) {
            case tsWaitStart:

                // Si hi ha colissio, reinicia la transmissio
                //
                if (PLIB_I2C_ArbitrationLossHasOccurred(id)) {
                    PLIB_I2C_ArbitrationLossClear(id);
                    while (PLIB_I2C_BusIsIdle(id))
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
                    hTransaction->txIndex = 0;
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
                    while (PLIB_I2C_BusIsIdle(id))
                        continue;
                    PLIB_I2C_MasterStart(id);
                    hTransaction->state = tsWaitStart;
                }
            
                else {
                    // Si l'esclau ha respos ACK, continua els bytes pendents
                    //
                    if (PLIB_I2C_TransmitterByteWasAcknowledged(id) &&
                        (hTransaction->txIndex < hTransaction->txCount))
                        PLIB_I2C_TransmitterByteSend(id, hTransaction->txBuffer[hTransaction->txIndex++]);

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
                hService->hCurrentTransaction = NULL;
                break;
        }
    }
}