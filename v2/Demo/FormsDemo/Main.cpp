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
        I2CMasterService *i2cMasterService;
        FormsService *formsService;
#ifdef eosFormsService_UseSelector
        SelectorService *selectorService;
#endif
#ifdef eosFormsService_UseKeyboard        
        KeyboardService *keyboardService;
#endif        
        MessageQueue *messageQueue;
        Form *mainForm;

    public :
        MyApplication();
        
    protected:
        void onInitialize();
                
#ifdef eosFormsService_UseSelector        
        void selectorNotifyEventHandler(SelectorPosition position, SelectorState state);
#endif
#ifdef eosFormsService_UseKeyboard        
        void keyboardNotifyEventHandler(KeyboardState state);
#endif        
};


/// ----------------------------------------------------------------------
/// \brief Constructor
///
MyApplication::MyApplication() {
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {
    
    // Inicialitza el servei de comunicacions del bus I2C
    //
    i2cMasterService = new I2CMasterService(this, 0);
   
    // Inicia el servei de control de selector
    //
#ifdef eosFormsService_UseSelector    
    selectorService = new SelectorService(this, i2cMasterService, SEL_ADDRESS);
#endif

    // Inicialitza el servei de control del teclat
    //    
#ifdef eosFormsService_UseKeyboard   
    keyboardService = new KeyboardService(this, i2cMasterService, KBD_ADDRESS);
#endif    
    
    // Inicialitza el servei de gestio de la interficie d'usuari
    //
    IDisplayDriver *driver = new ILI9341_Driver();
    driver->initialize();
    driver->setOrientation(Orientation::rotate180);
    
    Display *display = new Display(driver);
    display->clear(RGB(0, 0, 0));
    
    FormsDisplay *formsDisplay = new FormsDisplay(display);
    
    messageQueue = new MessageQueue(20);
    formsService = new FormsService(this, messageQueue, formsDisplay);
    mainForm = new MainForm(formsService);
    mainForm->activate();

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
    KeyboardState state) {
    
    static KeyboardState oldState = 0;
    Message message;
    
    if (formsService != nullptr) {
        Form *form = formsService->getActiveForm();
        if (form != nullptr) {
            if (state != oldState) {
                message.id = MSG_KEYBOARD;
                message.target = form;
                if (state != 0) {
                    message.msgKeyboard.event = KeyboardEvent::press;
                    if (state & 0x10) 
                        message.msgKeyboard.keyCode = KeyCode::up;
                    else if (state & 0x02) 
                        message.msgKeyboard.keyCode = KeyCode::right;
                    else if (state & 0x04)
                        message.msgKeyboard.keyCode = KeyCode::down;
                    else if (state & 0x08)
                        message.msgKeyboard.keyCode = KeyCode::left;
                    else
                        message.msgKeyboard.keyCode = KeyCode::enter;
                }
                else {
                    message.msgKeyboard.event = KeyboardEvent::release;
                }
                messageQueue->put(message, (unsigned) -1);
                oldState = state;
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
    SelectorPosition position,
    SelectorState state) {
    
    static SelectorPosition oldPosition = 0;
    static SelectorState oldState = 0;
    Message message;
    
    if (formsService != nullptr) {
        Form *form = formsService->getActiveForm();
        if (form != nullptr) {
            int delta = position - oldPosition;
            if (delta != 0) {
                message.id = MSG_SELECTOR;
                message.target = form;
                message.msgSelector.event = delta < 0 ? SelectorEvent::dec : SelectorEvent::inc;
                message.msgSelector.position = position;
                message.msgSelector.state = state;
                messageQueue->put(message, (unsigned) -1);
                oldPosition = position;
            }
            
            if (state != oldState) {            
                message.id = MSG_SELECTOR;
                message.target = form;
                message.msgSelector.event = state == 1 ? SelectorEvent::press : SelectorEvent::release;
                message.msgSelector.position = position;
                message.msgSelector.state = state;
                messageQueue->put(message, (unsigned) -1);
                oldState = state;
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
