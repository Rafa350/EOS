#include "eos.hpp"
#include "System/eosCallbacks.hpp"
#include "System/eosApplication.hpp"
#include "Services/eosDigOutput.hpp"
#include "Services/eosDigInput.hpp"
#include "Services/eosFSM.hpp"
#include "Services/eosTimer.hpp"
#include "Services/eosI2CMaster.hpp"
#include "fsmDefines.hpp"
#include "fsmStates.hpp"
#include "fsmMachine.hpp"
//#include "Services/eosI2CMaster.h"
//#include "Services/eosTimer.h"
//#include "Services/Forms/eosForms.h"
//#include "Services/Forms/eosFormsMenus.h"

// Harmony
//#include "peripheral/i2c/plib_i2c.h"
//#include "DisplayService.h"


//static char buffer[100];

class MyApplication: public eos::Application {
    private:
        eos::DigInputService *digInputService;
        eos::DigOutputService *digOutputService;
        eos::I2CMasterService *i2cMasterService;
        eos::TimerService *timerService;
        eos::DigOutput *ledRED;
        eos::DigOutput *ledAMBER;
        eos::DigOutput *ledGREEN;
        eos::DigInput *swRED;
        eos::DigInput *swAMBER;
        eos::DigInput *swGREEN;
        eos::Timer *timer;
        eos::StateMachineService *stateMachineService;

    public :
        MyApplication();
    private:
        void setupDigInputService();
        void setupDigOutputService();
        void setupTimerService();
        void setupI2CMasterService();
        void setupStateMachineService();
        
        void onSwRED(eos::DigInput *input);
        void onSwAMBER(eos::DigInput *input);
        void onSwGREEN(eos::DigInput *input);
        
        void onTimeout(eos::Timer *timer);
};


MyApplication::MyApplication() {
    
    setupDigOutputService();
    setupDigInputService();
    setupTimerService();
    setupI2CMasterService();
    setupStateMachineService();
}


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
*/
void MyApplication::setupDigInputService() {

    digInputService = new eos::DigInputService();

    swRED = new eos::DigInput(digInputService, pinSW1, true);
    swRED->setOnPosEdge(EV_DigInput_onPosEdge(MyApplication, this, &MyApplication::onSwRED));
   
    swAMBER = new eos::DigInput(digInputService, pinSW2, true);
    swAMBER->setOnPosEdge(EV_DigInput_onPosEdge(MyApplication, this, &MyApplication::onSwAMBER));
    
    swGREEN = new eos::DigInput(digInputService, pinSW3, true);    
    swGREEN->setOnPosEdge(EV_DigInput_onPosEdge(MyApplication, this, &MyApplication::onSwGREEN));
}


void MyApplication::setupDigOutputService() {

    digOutputService = new eos::DigOutputService();
   
    ledRED = new eos::DigOutput(digOutputService, pinLED1, false);
    ledAMBER = new eos::DigOutput(digOutputService, pinLED2, false);
    ledGREEN = new eos::DigOutput(digOutputService, pinLED3, false);

    ledRED->pulse(500);
    ledAMBER->pulse(1000);
    ledGREEN->pulse(1500);
}


void MyApplication::setupI2CMasterService() {

    i2cMasterService = new eos::I2CMasterService(1);
}


void MyApplication::setupTimerService() {
    
    timerService = new eos::TimerService();

    timer = new eos::Timer(timerService, 1000, true);
    timer->setOnTimeout(EV_Timer_onTimeout(MyApplication, this, &MyApplication::onTimeout));
    timer->start(1000);
}


void MyApplication::setupStateMachineService() {
    
    stateMachineService = new eos::StateMachineService(nullptr);
}

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

void MyApplication::onSwRED(eos::DigInput *input){

    ledRED->pulse(1000);
}

void MyApplication::onSwAMBER(eos::DigInput *input){
    
    ledAMBER->pulse(1000);
}

void MyApplication::onSwGREEN(eos::DigInput *input){
    
    ledGREEN->pulse(1000);

    const char *buffer = "\x10\x30";   
    i2cMasterService->startTransaction(0x62, (void*) buffer, 2, NULL, 0, 5000);
}

void MyApplication::onTimeout(eos::Timer *timer) {
    
    ledRED->pulse(500);
}


/*************************************************************************
 *
 *       Inicialitzacio de l'aplicacio d'usuari
 *
 *       Funcio:
 *           int main(void)
 *
 *************************************************************************/

int main(void) {
       
    MyApplication *app = new MyApplication();
    app->execute();

    return 0;
}
