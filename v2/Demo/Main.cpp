#include "eos.hpp"
#include "System/Core/eosTimer.hpp"
#include "System/Core/eosCallbacks.hpp"
//#include "System/Collections/eosList.hpp"
#include "System/eosApplication.hpp"
#include "Services/eosDigOutput.hpp"
#include "Services/eosDigInput.hpp"
#include "Services/Fsm/eosFSM.hpp"
#include "Services/eosI2CMaster.hpp"
#include "Services/Forms/eosForms.hpp"
#include "Services/Forms/eosSelector.hpp"
#include "Services/Forms/eosMenuForm.hpp"
#include "Controllers/eosDisplay.hpp"
#include "appMainForm.hpp"
#include "fsmDefines.hpp"
#include "fsmStates.hpp"
#include "fsmMachine.hpp"
#include "../../../MD-SEL01/SEL01Messages.h"
#include "../../../MD-DSP04/DSP04Messages.h"


using namespace eos;
using namespace app;


class MyApplication: public Application {
    private:
        DigInputServiceHandle digInputService;
        DigOutputServiceHandle digOutputService;
        I2CMasterServiceHandle i2cMasterService;
        FormsServiceHandle formsService;
        SelectorServiceHandle selectorService;
        DigOutputHandle ledRED;
        DigOutputHandle ledAMBER;
        DigOutputHandle ledGREEN;
        DigInputHandle swRED;
        DigInputHandle swAMBER;
        DigInputHandle swGREEN;
        TimerHandle timer;        
        StateMachineService* stateMachineService;
        DisplayControllerHandle displayController;
        MessageQueue *messageQueue;
        FormHandle mainForm;

    public :
        MyApplication();
    private:
        void setupDigInputService();
        void setupDigOutputService();
        void setupTimerService();
        void setupI2CMasterService();
        void setupFormsService();
        void setupStateMachineService();
        
        void onSwRED(eos::DigInputHandle input);
        void onSwAMBER(eos::DigInputHandle input);
        void onSwGREEN(eos::DigInputHandle input);
        
        void onTimeout(eos::TimerHandle timer);
        
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

    swRED = new DigInput(digInputService, pinSW1, true);
    swRED->setChangeEvent<MyApplication>(this, &MyApplication::onSwRED);
   
    swAMBER = new DigInput(digInputService, pinSW2, true);
    swAMBER->setChangeEvent<MyApplication>(this, &MyApplication::onSwAMBER);
    
    swGREEN = new DigInput(digInputService, pinSW3, true);    
    swGREEN->setChangeEvent<MyApplication>(this, &MyApplication::onSwGREEN);
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

    digOutputService = new DigOutputService();
   
    ledRED = new DigOutput(digOutputService, pinLED1, false);
    ledAMBER = new DigOutput(digOutputService, pinLED2, false);
    ledGREEN = new DigOutput(digOutputService, pinLED3, false);

    ledRED->pulse(500);
    ledAMBER->pulse(1000);
    ledGREEN->pulse(1500);
}


void MyApplication::setupI2CMasterService() {

    i2cMasterService = new I2CMasterService(1);
}


void MyApplication::setupTimerService() {
    
    timer = new Timer(true);
    timer->setEvTimeout<MyApplication>(this, &MyApplication::onTimeout);
    timer->start(1000, 100);
}


void MyApplication::setupStateMachineService() {
    
    stateMachineService = new StateMachineService(nullptr);
}


void MyApplication::setupFormsService() {
    
    selectorService = new SelectorService(i2cMasterService, SEL_ADDRESS);
    displayController = new DisplayController(i2cMasterService, DSP_ADDRESS);
    
    messageQueue = new MessageQueue(20);
    formsService = new FormsService(messageQueue, displayController);
    mainForm = new MainForm(formsService);

    selectorService->setChangeEvent<MyApplication>(this, &MyApplication::onSelector);
}


void MyApplication::onSwRED(eos::DigInputHandle input){

    if (input->get())
        ledRED->pulse(1000);
}


void MyApplication::onSwAMBER(eos::DigInputHandle input){
    
    if (input->get()) 
        ledAMBER->pulse(1000);
}


void MyApplication::onSwGREEN(eos::DigInputHandle input){
    
    if (input->get())
        ledGREEN->pulse(1000);

    displayController->beginCommand();
    displayController->addCommandClear();
    displayController->addCommandRefresh();
    displayController->endCommand();
}


void MyApplication::onTimeout(eos::Timer *timer) {
    
    ledRED->pulse(100);
}


void MyApplication::onSelector(int16_t position, uint8_t state) {
    
    static int16_t oldPosition = 0;
    static uint8_t oldState = 0;
    Message message;
    
    if (formsService != nullptr) {
        FormHandle form = formsService->getActiveForm();
        if (form != nullptr) {
            int16_t delta = position - oldPosition;
            if (delta != 0) {
                message.id = MSG_SELECTOR;
                message.target = form;
                message.msgSelector.event = delta < 0 ? EV_SELECTOR_DEC : EV_SELECTOR_INC;
                message.msgSelector.position = position;
                message.msgSelector.state = state;
                messageQueue->put(message, (unsigned) -1);
                oldPosition = position;
            }
            
            if (state != oldState) {            
                if ((state & 0x01) != 0x00) {
                    message.id = MSG_SELECTOR;
                    message.target = form;
                    message.msgSelector.event = EV_SELECTOR_CLICK;
                    message.msgSelector.position = position;
                    message.msgSelector.state = state;
                    messageQueue->put(message, (unsigned) -1);
                }
                oldState = state;
            }
        }
    }
}


void eosTest() {

    unsigned count;
    unsigned value;
    List<unsigned> list;
    
    list.add(0);
    list.add(1);
    list.add(2);
    
    count = list.getCount();
    value = list[0];
    
    list.remove(0);
    
    count = list.getCount();
    value = list[0];

    list.remove(0);
    
    count = list.getCount();
    value = list[0];

    list.remove(0);
    
    count = list.getCount();
    value = list[0];
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
    
    //eosTest();
       
    MyApplication *app = new MyApplication();
    app->execute();

    return 0;
}
