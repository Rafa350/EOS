#include "eos.hpp"
#include "System/eosTimer.hpp"
#include "System/eosList.hpp"
#include "System/eosCallbacks.hpp"
#include "System/eosApplication.hpp"
#include "Services/eosDigOutput.hpp"
#include "Services/eosDigInput.hpp"
#include "Services/Fsm/eosFSM.hpp"
#include "Services/eosI2CMaster.hpp"
#include "Services/Forms/eosForms.hpp"
#include "Services/Forms/eosSelector.hpp"
#include "Services/Forms/eosDisplay.hpp"
#include "Services/Forms/eosFormsMenus.hpp"
#include "fsmDefines.hpp"
#include "fsmStates.hpp"
#include "fsmMachine.hpp"
#include "../../../MD-SEL01/SEL01Messages.h"
#include "../../../MD-DSP04/DSP04Messages.h"
#include <stdlib.h>


class MyApplication: public eos::Application {
    private:
        eos::DigInputServiceHandle digInputService;
        eos::DigOutputServiceHandle digOutputService;
        eos::I2CMasterServiceHandle i2cMasterService;
        eos::FormsServiceHandle formsService;
        eos::SelectorServiceHandle selectorService;
        eos::DisplayServiceHandle displayService;
        eos::DigOutputHandle ledRED;
        eos::DigOutputHandle ledAMBER;
        eos::DigOutputHandle ledGREEN;
        eos::DigInputHandle swRED;
        eos::DigInputHandle swAMBER;
        eos::DigInputHandle swGREEN;
        eos::TimerHandle timer;        
        eos::StateMachineService* stateMachineService;
        eos::MessageQueue *messageQueue;
        eos::FormHandle menuForm;
        eos::FormHandle mainForm;

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
        
        void onSelector(int16_t position, uint8_t status);
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
    swRED->setChangeEvent(EV_DigInput_onChange(MyApplication, this, &MyApplication::onSwRED));
   
    swAMBER = new eos::DigInput(digInputService, pinSW2, true);
    swAMBER->setChangeEvent(EV_DigInput_onChange(MyApplication, this, &MyApplication::onSwAMBER));
    
    swGREEN = new eos::DigInput(digInputService, pinSW3, true);    
    swGREEN->setChangeEvent(EV_DigInput_onChange(MyApplication, this, &MyApplication::onSwGREEN));
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
    
    timer = new eos::Timer(true);
    timer->setOnTimeout(EV_Timer_onTimeout(MyApplication, this, &MyApplication::onTimeout));
    timer->start(1000, 100);
}


void MyApplication::setupStateMachineService() {
    
    stateMachineService = new eos::StateMachineService(nullptr);
}


void MyApplication::setupFormsService() {
    
    extern const uint8_t menuMnuMain[];
    
    selectorService = new eos::SelectorService(i2cMasterService, SEL_ADDRESS);
    displayService = new eos::DisplayService(i2cMasterService, DSP_ADDRESS);
    
    messageQueue = new eos::MessageQueue();
    formsService = new eos::FormsService(messageQueue, displayService);
    menuForm = new eos::MenuForm(formsService, nullptr, nullptr, (uint8_t*) menuMnuMain);
    formsService->activate(menuForm);

    selectorService->setChangeEvent(EV_SelectorService_onChange(MyApplication, this, &MyApplication::onSelector));
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
    
    ledRED->pulse(100);
}


void MyApplication::onSelector(int16_t position, uint8_t state) {
    
    static int16_t oldPosition = 0;
    static uint8_t oldState = 0;
    eos::Message message;
    
    if (formsService != nullptr) {
        eos::Form *form = formsService->getActiveForm();
        if (form != nullptr) {
            int16_t delta = position - oldPosition;
            if (delta != 0) {
                message.id = MSG_SELECTOR;
                message.target = form;
                message.msgSelector.event = delta < 0 ? EV_SELECTOR_DEC : EV_SELECTOR_INC;
                message.msgSelector.position = abs(position);
                message.msgSelector.state = state;
                messageQueue->send(message, (unsigned) -1);
                oldPosition = position;
            }
            
            if (state != oldState) {            
                if ((state & 0x0001) != 0) {
                    message.id = MSG_SELECTOR;
                    message.target = form;
                    message.msgSelector.event = EV_SELECTOR_CLICK;
                    message.msgSelector.position = position;
                    message.msgSelector.state = state;
                    messageQueue->send(message, (unsigned) -1);
                }
                oldState = state;
            }
        }
    }
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
