#include "eos.hpp"
#include "System/eosList.hpp"
#include "System/eosCallbacks.hpp"
#include "System/eosApplication.hpp"
#include "Services/eosDigOutput.hpp"
#include "Services/eosDigInput.hpp"
#include "Services/Fsm/eosFSM.hpp"
#include "Services/eosTimer.hpp"
#include "Services/eosI2CMaster.hpp"
#include "Services/Forms/eosForms.hpp"
#include "Services/Forms/eosSelector.hpp"
#include "Services/Forms/eosDisplay.hpp"
//#include "Services/Forms/eosFormsMenus.h"
#include "fsmDefines.hpp"
#include "fsmStates.hpp"
#include "fsmMachine.hpp"
#include "../../../MD-SEL01/SEL01Messages.h"
#include "../../../MD-DSP04/DSP04Messages.h"


class MyApplication: public eos::Application {
    private:
        eos::DigInputService *digInputService;
        eos::DigOutputService *digOutputService;
        eos::I2CMasterService *i2cMasterService;
        eos::TimerService *timerService;
        eos::FormsService *formsService;
        eos::SelectorService *selectorService;
        eos::DisplayService *displayService;
        eos::DigOutput *ledRED;
        eos::DigOutput *ledAMBER;
        eos::DigOutput *ledGREEN;
        eos::DigInput *swRED;
        eos::DigInput *swAMBER;
        eos::DigInput *swGREEN;
        eos::Timer *timer;        
        eos::StateMachineService *stateMachineService;
        eos::Form *menuForm;
        eos::Form *mainForm;

    public :
        MyApplication();
    private:
        void setupDigInputService();
        void setupDigOutputService();
        void setupTimerService();
        void setupI2CMasterService();
        void setupFormsService();
        void setupStateMachineService();
        
        void onSwRED(eos::DigInput *input);
        void onSwAMBER(eos::DigInput *input);
        void onSwGREEN(eos::DigInput *input);
        
        void onTimeout(eos::Timer *timer);
        
        void onSelector(uint16_t position, uint8_t status);
};


/*************************************************************************
 *
 *       Constructor
 * 
 *       Funcio:
 *           MyApplication::MyApplication()
 *
 *************************************************************************/

MyApplication::MyApplication() {
    
    setupDigOutputService();
    setupDigInputService();
    setupTimerService();
    setupI2CMasterService();
    //setupStateMachineService();
    setupFormsService();
}


/*************************************************************************
 *
 *       Inicialitza el servei d'entrades digitals
 *
 *       Funcio:
 *           void MyApplication::setupDigInputService() 
 *
 *************************************************************************/

void MyApplication::setupDigInputService() {

    digInputService = new eos::DigInputService();

    swRED = new eos::DigInput(digInputService, pinSW1, true);
    swRED->setOnChange(EV_DigInput_onChange(MyApplication, this, &MyApplication::onSwRED));
   
    swAMBER = new eos::DigInput(digInputService, pinSW2, true);
    swAMBER->setOnChange(EV_DigInput_onChange(MyApplication, this, &MyApplication::onSwAMBER));
    
    swGREEN = new eos::DigInput(digInputService, pinSW3, true);    
    swGREEN->setOnChange(EV_DigInput_onChange(MyApplication, this, &MyApplication::onSwGREEN));
}


/*************************************************************************
 *
 *       Inicialitza el servei de sortides digitals
 *
 *       Funcio:
 *           void MyApplication::setupDigOutputService() 
 *
 *************************************************************************/

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

    timer = new eos::Timer(timerService, true);
    timer->setOnTimeout(EV_Timer_onTimeout(MyApplication, this, &MyApplication::onTimeout));
    timer->start(1000, 100);
}


void MyApplication::setupStateMachineService() {
    
    stateMachineService = new eos::StateMachineService(nullptr);
}


void MyApplication::setupFormsService() {
    
    selectorService = new eos::SelectorService(i2cMasterService, SEL_ADDRESS);
    selectorService->setOnChange(EV_SelectorService_onChange(MyApplication, this, &MyApplication::onSelector));
    displayService = new eos::DisplayService(i2cMasterService, DSP_ADDRESS);
    
    //formsService = new eos::FormsService();
    
    /*menuParams.resource = menuMnuMain;
    menuForm = eosFormsCreateMenu(hFormsService, &menuParams);
    formsService->activate(menuForm);*/
}


void MyApplication::onSwRED(eos::DigInput *input){

    if (input->get())
        ledRED->pulse(1000);
}


void MyApplication::onSwAMBER(eos::DigInput *input){
    
    if (input->get())
        ledAMBER->pulse(1000);
}


void MyApplication::onSwGREEN(eos::DigInput *input){
    
    if (input->get())
        ledGREEN->pulse(1000);

    displayService->beginCommand();
    displayService->addCommandClear();
    displayService->addCommandRefresh();
    displayService->endCommand();
}


void MyApplication::onTimeout(eos::Timer *timer) {
    
    ledRED->pulse(500);
}


void MyApplication::onSelector(uint16_t position, uint8_t status) {
    
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
