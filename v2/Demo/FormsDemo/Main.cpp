#include "eos.hpp"
#include "System/Core/eosCallbacks.hpp"
#include "System/eosApplication.hpp"
#include "Services/eosI2CMaster.hpp"
#include "Services/Forms/eosForms.hpp"
#include "Services/Forms/eosMenuForm.hpp"
#ifdef eosFormsService_UseSelector
#include "Services/eosSelector.hpp"
#include "../../../MD-SEL01/SEL01Messages.h"
#endif
#ifdef eosFormsService_UseKeyboard
#include "Services/eosKeyboard.hpp"
#include "../../../MD-KBD01/KBD01Messages.h"
#endif
#include "Controllers/Display/eosDisplay.hpp"
#include "Controllers/Display/Drivers/eosILI9341.hpp"
#include "appMainForm.hpp"


using namespace eos;
using namespace app;


class MyApplication: public Application {
    private:
        I2CMasterServiceHandle i2cMasterService;
        FormsServiceHandle formsService;
#ifdef eosFormsService_UseSelector
        SelectorServiceHandle selectorService;
#endif
#ifdef eosFormsService_UseKeyboard        
        KeyboardServiceHandle keyboardService;
#endif        
        MessageQueue *messageQueue;
        FormHandle mainForm;

    public :
        MyApplication();
    private:
        void setupI2CMasterService();
        void setupFormsService();
                
#ifdef eosFormsService_UseSelector        
        void selectorNotifyEventHandler(SelectorNotification &notification);
#endif
#ifdef eosFormsService_UseKeyboard        
        void keyboardNotifyEventHandler(KeyboardNotification &notification);
#endif        
};


/// ----------------------------------------------------------------------
/// \brief Constructor
///
MyApplication::MyApplication() {
    
    setupI2CMasterService();
    setupFormsService();
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el servei I2C Master
///
void MyApplication::setupI2CMasterService() {

    i2cMasterService = new I2CMasterService(1);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el servei FORMS
///
void MyApplication::setupFormsService() {
    
#ifdef eosFormsService_UseSelector    
    selectorService = new SelectorService(i2cMasterService, SEL_ADDRESS);
#endif    
#ifdef eosFormsService_UseKeyboard   
    keyboardService = new KeyboardService(i2cMasterService, KBD_ADDRESS);
#endif    

    IDisplayDriver *driver = new ILI9341_DisplayDriver();
    driver->initialize();
    driver->setOrientation(Orientation::rotate180);
    
    Display *display = new Display(driver);
    display->clear(0x00000000);
    
    FormsDisplayHandle formsDisplay = new FormsDisplay(display);
    
    messageQueue = new MessageQueue(20);
    formsService = new FormsService(messageQueue, formsDisplay);
    mainForm = new MainForm(formsService);

#ifdef eosFormsService_UseSelector    
    selectorService->setNotifyEvent<MyApplication>(this, &MyApplication::selectorNotifyEventHandler);
#endif
#ifdef eosFormsService_UseKeyboard   
    keyboardService->setNotifyEvent<MyApplication>(this, &MyApplication::keyboardNotifyEventHandler);
#endif    
}


/// ----------------------------------------------------------------------
/// \brief Procesa els events del teclat.
/// \param notification: Parametres del event.
///
#ifdef eosFormsService_UseKeyboard
void MyApplication::keyboardNotifyEventHandler(
    KeyboardNotification &notification) {
    
    static uint8_t oldState = 0;
    Message message;
    
    if (formsService != nullptr) {
        FormHandle form = formsService->getActiveForm();
        if (form != nullptr) {
            if (notification.state != oldState) {
                if (notification.state != 0) {
                    message.id = MSG_KEYBOARD;
                    message.target = form;
                    if (notification.state & 0x10)
                        message.msgKeyboard.event = EV_KEYBOARD_UP;
                    else if (notification.state & 0x02) 
                        message.msgKeyboard.event = EV_KEYBOARD_RIGHT;
                    else if (notification.state & 0x04)
                        message.msgKeyboard.event = EV_KEYBOARD_DOWN;
                    else if (notification.state & 0x08)
                        message.msgKeyboard.event = EV_KEYBOARD_LEFT;
                    else
                        message.msgKeyboard.event = EV_KEYBOARD_OK;
                    messageQueue->put(message, (unsigned) -1);
                }
                oldState = notification.state;
            }
        }
    }
}
#endif


/// ----------------------------------------------------------------------
/// \brief Procesa els events del teclat.
/// \params notification: Parametres del event.
///
#ifdef eosFormsService_UseSelector    
void MyApplication::selectorNotifyEventHandler(
    SelectorNotification &notification) {
    
    static int oldPosition = 0;
    static unsigned oldState = 0;
    Message message;
    
    if (formsService != nullptr) {
        FormHandle form = formsService->getActiveForm();
        if (form != nullptr) {
            int16_t delta = notification.position - oldPosition;
            if (delta != 0) {
                message.id = MSG_SELECTOR;
                message.target = form;
                message.msgSelector.event = delta < 0 ? EV_SELECTOR_DEC : EV_SELECTOR_INC;
                message.msgSelector.position = notification.position;
                message.msgSelector.state = notification.state;
                messageQueue->put(message, (unsigned) -1);
                oldPosition = notification.position;
            }
            
            if (notification.state != oldState) {            
                if ((notification.state & 0x01) != 0x00) {
                    message.id = MSG_SELECTOR;
                    message.target = form;
                    message.msgSelector.event = EV_SELECTOR_CLICK;
                    message.msgSelector.position = notification.position;
                    message.msgSelector.state = notification.state;
                    messageQueue->put(message, (unsigned) -1);
                }
                oldState = notification.state;
            }
        }
    }
}
#endif


/// ----------------------------------------------------------------------
/// \brief Punt d'entrada a l'aplicacio.
///
int main(void) {
          
    MyApplication *app = new MyApplication();
    app->execute();

    return 0;
}
