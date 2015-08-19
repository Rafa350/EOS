#include "eos.h"
#include "System/eosTask.h"
#include "Services/eosDigOutput.h"
#include "Services/eosDigInput.h"
#include "Services/eosI2CMaster.h"
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
    
    eosDigInputServiceHandle hDigInputService = eosDigInputServiceInitialize(NULL);
    eosDigInputParams params;
    
    memset(&params, 0, sizeof(params));
    params.channel = PORT_CHANNEL_D;
    params.position = PORTS_BIT_POS_6;
    params.inverted = true;
    params.onPosEdge = posEdgeFunction;
    eosDigInputCreate(hDigInputService, &params);
}

static void setupDigOutputService(void) {
    
    eosDigOutputServiceHandle hDigOutputService = eosDigOutputServiceInitialize(NULL);
    eosDigOutputParams params;
    
    memset(&params, 0, sizeof(params));
    params.channel = PORT_CHANNEL_D;
    params.position = PORTS_BIT_POS_0;
    hLedRED = eosDigOutputCreate(hDigOutputService, &params);

    memset(&params, 0, sizeof(params));
    params.channel = PORT_CHANNEL_D;
    params.position = PORTS_BIT_POS_1;
    hLedAMBER = eosDigOutputCreate(hDigOutputService, &params);

    memset(&params, 0, sizeof(params));
    params.channel = PORT_CHANNEL_D;
    params.position = PORTS_BIT_POS_2;
    hLedGREEN = eosDigOutputCreate(hDigOutputService, &params);
}

static void setupI2CMasterService(void) {
    
    eosI2CServiceParams params;
    memset(&params, 0, sizeof(params));
    params.id = I2C_ID_2;
    hI2CMasterService = eosI2CMasterServiceInitialize(&params);
}


/*************************************************************************
 *
 *       Inicialitzacio de l'aplicacio d'usuari
 *
 *       Funcio:
 *           void appSetup(void)
 *
 *************************************************************************/

void appSetup(void) {
    
    eosTaskCreate(0, 512, task1, NULL);
    eosTaskCreate(0, 512, task2, NULL);
    
    setupDigInputService();
    setupDigOutputService();
    setupI2CMasterService();
}


/*************************************************************************
 *
 *       Bucle principal de l'aplicacio
 *
 *       Funcio:
 *           void usrTask(void)
 *
 *************************************************************************/

void appTask(void) {

    eosStartScheduler();
}
