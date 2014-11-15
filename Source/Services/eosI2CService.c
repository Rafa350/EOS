#define __EOS_I2CMASTER_INTERNAL
#include "HardwareProfile.h"
#include "Services/eosI2CService.h"
#include "System/eosMemory.h"
#include "System/eosQueue.h"
#include "sys/attribs.h"
#include "peripheral/i2c/plib_i2c.h"
#include "peripheral/int/plib_int.h"


#define I2C1_INT_VECTOR           INT_VECTOR_I2C1
#define I2C1_INT_SOURCE_MASTER    INT_SOURCE_I2C_1_MASTER
#define I2C1_INT_SOURCE_ERROR     INT_SOURCE_I2C_1_ERROR
#define I2C1_CORE_VECTOR          _I2C_1_VECTOR

#define I2C2_INT_VECTOR           INT_VECTOR_I2C2
#define I2C2_INT_SOURCE_MASTER    INT_SOURCE_I2C_2_MASTER
#define I2C2_INT_SOURCE_ERROR     INT_SOURCE_I2C_2_ERROR
#define I2C2_CORE_VECTOR          _I2C_2_VECTOR

#define I2C3_INT_VECTOR           INT_VECTOR_I2C3
#define I2C3_INT_SOURCE_MASTER    INT_SOURCE_I2C_3_MASTER
#define I2C3_INT_SOURCE_ERROR     INT_SOURCE_I2C_3_ERROR
#define I2C3_CORE_VECTOR          _I2C_3_VECTOR

#define I2C4_INT_VECTOR           INT_VECTOR_I2C4
#define I2C4_INT_SOURCE_MASTER    INT_SOURCE_I2C_4_MASTER
#define I2C4_INT_SOURCE_ERROR     INT_SOURCE_I2C_4_ERROR
#define I2C4_CORE_VECTOR          _I2C_4_VECTOR


typedef enum {                    // Codis d'operacio
    opCode_StartTransmission      // -Inicia una transmissio
} OpCodes;

typedef enum {                    // Estats del servei
    state_Initializing,           // -Inicialitzant
    state_Running                 // -En execucio
} States;

typedef enum {
    tstate_Idle,
    tstate_WaitStart,
    tstate_SendData,
    tstate_WaitStop
} TransactionStates;

typedef struct {                       // Comanda
    OpCodes opCode;                    // -Codi d'operacio
} Command;

typedef struct __I2CMasterService {    // Dades internes del servei
    I2C_MODULE_ID id;                  // -El identificador del modul i2c
    States state;                      // -Estat del servei
    eosHQueue hCommandQueue;           // -Cua de comandes
} I2CMasterService;


static void i2cInitialize(eosHI2CMasterService hService);
static void i2cInterruptService(void);


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
    hService->state = state_Initializing;
    hService->hCommandQueue = hQueue;
    *_hService = hService;

    return eos_RESULT_SUCCESS;
}


int i2cTest(eosHI2CMasterService hService) {

    I2C_MODULE_ID id = hService->id;

    while(PLIB_I2C_BusIsIdle(id) == 0);
    PLIB_I2C_MasterStart(id);
    while (1);
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
        case state_Initializing:
            i2cInitialize(hService);
            hService->state = state_Running;
            break;

        case state_Running:

            // Procesa les comandes pendents
            //
            Command command;
            while (eosQueueGet(hService->hCommandQueue, &command) == eos_RESULT_SUCCESS) {
                switch (command.opCode) {
                    case opCode_StartTransmission:
                        break;
                }
            }
            break;
    }
}


void eosI2CMasterServiceISRTick(
    eosHI2CMasterService hService) {

}


eosResult eosI2CMasterOpenTransaction(
    eosHI2CMasterService hService,
    eosHI2CTransaction *hTransaction) {

    return eos_RESULT_SUCCESS;
}


eosResult eosI2CMasterCloseTransaction(
    eosHI2CTransaction hTransaction) {

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Gestiona les interrupcios dels moduls I2C
 *
 *************************************************************************/

void __ISR(I2C1_CORE_VECTOR, ipl2) __ISR_Entry(I2C1_CORE_VECTOR) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C1_INT_SOURCE_MASTER)) {
        i2cInterruptService();
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C1_INT_SOURCE_MASTER);
    }
    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C1_INT_SOURCE_ERROR)) {
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C1_INT_SOURCE_ERROR);
    }
}

void __ISR(I2C2_CORE_VECTOR, ipl2) __ISR_Entry(I2C2_CORE_VECTOR) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C2_INT_SOURCE_MASTER)) {
        i2cInterruptService();
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C2_INT_SOURCE_MASTER);
    }
    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C2_INT_SOURCE_ERROR)) {
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C2_INT_SOURCE_ERROR);
    }
}

void __ISR(I2C3_CORE_VECTOR, ipl2) __ISR_Entry(I2C3_CORE_VECTOR) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C3_INT_SOURCE_MASTER)) {
        i2cInterruptService();
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C3_INT_SOURCE_MASTER);
    }
    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C3_INT_SOURCE_ERROR)) {
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C3_INT_SOURCE_ERROR);
    }
}

void __ISR(I2C4_CORE_VECTOR, ipl2) __ISR_Entry(I2C4_CORE_VECTOR) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C4_INT_SOURCE_MASTER)) {
        i2cInterruptService();
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C4_INT_SOURCE_MASTER);
    }
    if (PLIB_INT_SourceFlagGet(INT_ID_0, I2C4_INT_SOURCE_ERROR)) {
        PLIB_INT_SourceFlagClear(INT_ID_0, I2C4_INT_SOURCE_ERROR);
    }
}


/************************************************************************
 *
 *       Inicialitza el modul I2C
 *
 *       Funcio:
 *           void i2cInitialize(eosHI2CMasterService hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 ************************************************************************/

static void i2cInitialize(eosHI2CMasterService hService) {

    I2C_MODULE_ID id = hService->id;

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
            PLIB_INT_SourceEnable(INT_ID_0, I2C1_INT_SOURCE_ERROR);
            break;

        case I2C_ID_2:
            PLIB_INT_VectorPrioritySet(INT_ID_0, I2C2_INT_VECTOR, INT_PRIORITY_LEVEL2);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, I2C2_INT_VECTOR, INT_SUBPRIORITY_LEVEL0);
            PLIB_INT_SourceEnable(INT_ID_0, I2C2_INT_SOURCE_MASTER);
            PLIB_INT_SourceEnable(INT_ID_0, I2C2_INT_SOURCE_ERROR);
            break;

        case I2C_ID_3:
            PLIB_INT_VectorPrioritySet(INT_ID_0, I2C3_INT_VECTOR, INT_PRIORITY_LEVEL2);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, I2C3_INT_VECTOR, INT_SUBPRIORITY_LEVEL0);
            PLIB_INT_SourceEnable(INT_ID_0, I2C3_INT_SOURCE_MASTER);
            PLIB_INT_SourceEnable(INT_ID_0, I2C3_INT_SOURCE_ERROR);
            break;

        case I2C_ID_4:
            PLIB_INT_VectorPrioritySet(INT_ID_0, I2C4_INT_VECTOR, INT_PRIORITY_LEVEL2);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, I2C4_INT_VECTOR, INT_SUBPRIORITY_LEVEL0);
            PLIB_INT_SourceEnable(INT_ID_0, I2C4_INT_SOURCE_MASTER);
            PLIB_INT_SourceEnable(INT_ID_0, I2C4_INT_SOURCE_ERROR);
            break;
    }

    // Activa el modul
    //
    PLIB_I2C_Enable(id);
}

static TransactionStates tstate = tstate_WaitStart;
static BYTE address = 0x30;
static BYTE data[100];
static unsigned dataCount = 4;

static void i2cInterruptService() {

    I2C_MODULE_ID id = I2C_ID_2;

    switch (tstate) {
        case tstate_WaitStart:

            // Si hi ha colissio, cancela la transmissio
            //
            if (PLIB_I2C_ArbitrationLossHasOccurred(id))
                PLIB_I2C_ArbitrationLossClear(id);

            // Si tot es correcte, envia l'adressa de l'escalu
            //
            else {
                PLIB_I2C_TransmitterByteSend(id, address);
                tstate = tstate_SendData;
            }
            break;

        case tstate_SendData:

            // Si hi ha colissio, cancela la transmissio
            //
            if (PLIB_I2C_ArbitrationLossHasOccurred(id)) 
                PLIB_I2C_ArbitrationLossClear(id);
            
            else {
                // Si l'esclau ha respos ACK, continua els bytes pendents
                //
                if (PLIB_I2C_TransmitterByteWasAcknowledged(id) && dataCount)
                    PLIB_I2C_TransmitterByteSend(id, data[dataCount--]);                

                // En cas contrari finalitza la transmissio
                //
                else {
                    PLIB_I2C_MasterStop(id);
                    tstate = tstate_WaitStop;
                }
            }
            break;

        case tstate_WaitStop:
            tstate = tstate_Idle;
            break;
    }
}