#include "eos.hpp"
#include "System/eosApplication.hpp"
#include "Services/eosDigOutput.hpp"
//#include "Services/eosDigInput.h"
//#include "Services/eosI2CMaster.h"
//#include "Services/eosTimer.h"
//#include "Services/Forms/eosForms.h"
//#include "Services/Forms/eosFormsMenus.h"

// Harmony
//#include "peripheral/i2c/plib_i2c.h"
//#include "DisplayService.h"


//static eosI2CMasterServiceHandle hI2CMasterService;
//static eosDisplayServiceHandle hDisplayService;
//static eosFormsServiceHandle hFormsService;

//static char buffer[100];

static eos::DigOutput *ledRED;
static eos::DigOutput *ledAMBER;
static eos::DigOutput *ledGREEN;

//static eosTimerHandle hTimer;

/*static void task1(void *params) {

    while (true) {
        eosDigOutputPulse(hLedRED, 50);
        eosTaskDelay(1000);
    }
}

static void posEdgeFunction(
    eosDigInputHandle hInput, 
    void *context) {
    
    eosDigOutputToggle(hLedGREEN);        
    
    eosDisplayBeginCommand(hDisplayService);
    eosDisplayAddCommandClear(hDisplayService);
    eosDisplayAddCommandDrawText(hDisplayService, 0, 0, "Hello world", 0, -1);
    eosDisplayAddCommandDrawLine(hDisplayService, 0, 10, 127, 10);
    eosDisplayAddCommandRefresh(hDisplayService);
    eosDisplayEndCommand(hDisplayService);
}

static void setupDigInputService(void) {
    
    eosDigInputServiceParams serviceParams;
    eosDigInputParams params;

    memset(&serviceParams, 0, sizeof(serviceParams));
    serviceParams.priority = 1;
    eosDigInputServiceHandle hDigInputService = eosDigInputServiceInitialize(&serviceParams);
    
    memset(&params, 0, sizeof(params));
    params.pin = pinSW1;
    params.inverted = true;
    params.onPosEdge = posEdgeFunction;
    eosDigInputCreate(hDigInputService, &params);
}
*/

static void setupDigOutputService(void) {

    eos::DigOutputService *service = new eos::DigOutputService();
   
    ledRED = new eos::DigOutput(service, pinLED1, false);
    ledAMBER = new eos::DigOutput(service, pinLED2, false);
    ledGREEN = new eos::DigOutput(service, pinLED3, false);

    ledRED->pulse(1000);
    ledAMBER->pulse(2000);
    ledGREEN->pulse(3000);
}

/*
static void setupI2CMasterService(void) {
    
    eosI2CServiceParams serviceParams;
    
    memset(&serviceParams, 0, sizeof(serviceParams));
    serviceParams.id = I2C_ID_2;
    serviceParams.priority = 2;
    hI2CMasterService = eosI2CMasterServiceInitialize(&serviceParams);
}
*/
/*
static void setupTimerService(void) {
    
    eosTimerServiceParams serviceParams;
    eosTimerParams params;
    
    eosTimerServiceHandle hTimerService;
    
    memset(&serviceParams, 0, sizeof(serviceParams));
    hTimerService = eosTimerServiceInitialize(&serviceParams);
    
    memset(&params, 0, sizeof(params));
    params.period = 1000;
    params.autoreload = true;
    params.onTimeout = timerFunction;
    hTimer = eosTimerCreate(hTimerService, &params);
}
*/
/*
static void setupFormsService(void) {
    
    eosDisplayServiceParams displayServiceParams;

    memset(&displayServiceParams, 0, sizeof(displayServiceParams));
    displayServiceParams.hI2CMasterService = hI2CMasterService;
    displayServiceParams.i2cAddr = 0x62 >> 1;
    hDisplayService = eosDisplayServiceInitialize(&displayServiceParams);
   
    eosFormsServiceParams formsServiceParams;
    extern uint8_t menuMnuMain[];
    
    memset(&formsServiceParams, 0, sizeof(formsServiceParams));
    formsServiceParams.hDisplayService = hDisplayService;
    hFormsService = eosFormsServiceInitialize(&formsServiceParams);
    
    eosMenuParams menuParams;
    memset(&menuParams, 0, sizeof(menuParams));
    menuParams.resource = menuMnuMain;
    eosFormHandle hMenu = eosFormsCreateMenu(hFormsService, &menuParams);
    eosFormsSetActiveForm(hFormsService, hMenu);
}
*/

/*************************************************************************
 *
 *       Inicialitzacio de l'aplicacio d'usuari
 *
 *       Funcio:
 *           int main(void)
 *
 *************************************************************************/

int main(void) {
    
    setupDigOutputService();
    
    eos::Application app;
    app.execute();
    
    return 0;
}