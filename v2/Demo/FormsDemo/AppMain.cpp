#include "eos.h"
#include "System/Core/eosCallbacks.h"
#include "System/eosApplication.h"
#include "Services/eosI2CMaster.h"
#include "Services/Forms/eosForms.h"
#include "Services/Forms/eosMenuForm.h"
#ifdef eosFormsService_UseSelector
#include "Services/eosSelector.h"
#include "../../../MD-SEL01/SEL01Messages.h"
#endif
#ifdef eosFormsService_UseKeyboard
#include "Services/eosKeyboard.h"
#include "../../../MD-KBD01/KBD01Messages.h"
#endif
#include "Controllers/Display/eosDisplay.h"
#include "Controllers/Display/Drivers/eosILI9341.h"
#include "appMainForm.h"


using namespace eos;
using namespace app;


class MyApplication: public Application {
    private:
#if defined(eosFormsService_UseSelector) || defined(eosFormsService_UseKeyboard)
        I2CMasterService *i2cMasterService;
#endif
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
#if defined(eosFormsService_UseSelector) || defined(eosFormsService_UseKeyboard)
    i2cMasterService = new I2CMasterService(this, 0);
#endif

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
    selectorService->setNotifyEventHandler<MyApplication>(this, &MyApplication::selectorNotifyEventHandler);
#endif
#ifdef eosFormsService_UseKeyboard
    keyboardService->setNotifyEventHandler<MyApplication>(this, &MyApplication::keyboardNotifyEventHandler);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Procesa els events del teclat.
/// \param state: Estat del teclat.
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
/// \brief Procesa els events del selector.
/// \param position: Posicio del selector.
/// \param state: Estat del boto.
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
                message.msgSelector.delta = delta < 0 ? -delta : delta;
                messageQueue->put(message, (unsigned) -1);
                oldPosition = position;
            }

            if (state != oldState) {
                message.id = MSG_SELECTOR;
                message.target = form;
                message.msgSelector.event = state == 1 ? SelectorEvent::press : SelectorEvent::release;
                message.msgSelector.delta = 0;
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
void AppMain() {

    MyApplication *app = new MyApplication();
    app->execute();
    delete app;
}
