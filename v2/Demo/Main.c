#include "eos.h"
#include "System/eosTask.h"
#include "Services/eosDigOutput.h"
#include "Services/eosDigInput.h"
#include "Services/eosI2CMaster.h"

// Harmony
#include "peripheral/ports/plib_ports.h"
#include "peripheral/i2c/plib_i2c.h"


static eosI2CMasterServiceHandle hI2CMasterService;
static char buffer[100];

static eosDigOutputHandle hLedRED;
static eosDigOutputHandle hLedAMBER;
static eosDigOutputHandle hLedGREEN;


static void task1(void *params) {

    while (true) {
        eosDigOutputPulse(hLedRED, 50);
        eosTaskDelay(5000);
    }
}

static void task2(void *params) {
   
    while (true) {
        eosDigOutputToggle(hLedAMBER);
        eosTaskDelay(500);
    }
}

static void posEdgeFunction(eosDigInputHandle hInput, void *context) {

    eosDigOutputToggle(hLedGREEN);    
    
    eosI2CTransactionParams transactionParams;
    memset(&transactionParams, 0, sizeof(transactionParams));
    transactionParams.address = 0x62 >> 1;
    buffer[0] = 0x10;
    buffer[1] = 0x30;
    transactionParams.txBuffer = buffer;
    transactionParams.txCount = 2;
    //transactionParams.onEndTransaction = onEndTransaction;
    //transactionParams.context = hService;

    // Inicia la transaccio
    //
    eosI2CMasterStartTransaction(hI2CMasterService, &transactionParams);
}


static void setupDigInputService(void) {
    
    eosDigInputServiceParams serviceParams;
    eosDigInputParams params;

    memset(&serviceParams, 0, sizeof(serviceParams));
    serviceParams.priority = 1;
    eosDigInputServiceHandle hDigInputService = eosDigInputServiceInitialize(&serviceParams);
    
    memset(&params, 0, sizeof(params));
    params.channel = SW_1_CHN;
    params.position = SW_1_POS;
    params.inverted = true;
    params.onPosEdge = posEdgeFunction;
    eosDigInputCreate(hDigInputService, &params);
}

static void setupDigOutputService(void) {
    
    eosDigOutputServiceParams serviceParams;
    eosDigOutputParams params;
    
    memset(&serviceParams, 0, sizeof(serviceParams));
    serviceParams.priority = 1;
    eosDigOutputServiceHandle hDigOutputService = eosDigOutputServiceInitialize(&serviceParams);
    
    memset(&params, 0, sizeof(params));
    params.channel = LED_1_CHN;
    params.position = LED_1_POS;
    hLedRED = eosDigOutputCreate(hDigOutputService, &params);

    memset(&params, 0, sizeof(params));
    params.channel = LED_2_CHN;
    params.position = LED_2_POS;
    hLedAMBER = eosDigOutputCreate(hDigOutputService, &params);

    memset(&params, 0, sizeof(params));
    params.channel = LED_3_CHN;
    params.position = LED_3_POS;
    hLedGREEN = eosDigOutputCreate(hDigOutputService, &params);
}

static void setupI2CMasterService(void) {
    
    eosI2CServiceParams serviceParams;
    
    memset(&serviceParams, 0, sizeof(serviceParams));
    serviceParams.id = I2C_ID_2;
    serviceParams.priority = 2;
    hI2CMasterService = eosI2CMasterServiceInitialize(&serviceParams);
}


/*************************************************************************
 *
 *       Inicialitzacio de l'aplicacio d'usuari
 *
 *       Funcio:
 *           void main(void)
 *
 *************************************************************************/

void main(void) {
    
    eosInitialize();
    
    eosTaskCreate(0, 512, task1, NULL);
    eosTaskCreate(0, 512, task2, NULL);
    
    setupDigInputService();
    setupDigOutputService();
    setupI2CMasterService();
    
    eosStartScheduler();
}
