#include "eos.h"
#include "System/eosTask.h"
#include "Services/eosDigOutput.h"
#include "Services/eosDigInput.h"
#include "peripheral/ports/plib_ports.h"


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

static void posEdgeFunction(eosDigInputHandle hInput) {

    eosDigOutputToggle(hLedGREEN);    
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
    
    eosDigOutputServiceHandle hDigOutputService = eosDigOutputServiceInitialize(NULL);
    eosDigOutputParams params1;
    
    memset(&params1, 0, sizeof(params1));
    params1.channel = PORT_CHANNEL_D;
    params1.position = PORTS_BIT_POS_0;
    hLedRED = eosDigOutputCreate(hDigOutputService, &params1);

    memset(&params1, 0, sizeof(params1));
    params1.channel = PORT_CHANNEL_D;
    params1.position = PORTS_BIT_POS_1;
    hLedAMBER = eosDigOutputCreate(hDigOutputService, &params1);

    memset(&params1, 0, sizeof(params1));
    params1.channel = PORT_CHANNEL_D;
    params1.position = PORTS_BIT_POS_2;
    hLedGREEN = eosDigOutputCreate(hDigOutputService, &params1);

    eosDigInputServiceHandle hDigInputService = eosDigInputServiceInitialize(NULL);
    eosDigInputParams params2;
    
    memset(&params2, 0, sizeof(params2));
    params2.channel = PORT_CHANNEL_D;
    params2.position = PORTS_BIT_POS_6;
    params2.inverted = true;
    params2.onPosEdge = posEdgeFunction;
    eosDigInputCreate(hDigInputService, &params2);
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

    eosTaskRun();
}
