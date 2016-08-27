#include "eos.hpp"
#include "Services/Forms/eosForms.hpp"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param service: El servei de gestio dels forms.
/// \param parent: El form pare.
///
Form::Form(
    FormsServiceHandle _service,
    FormHandle _parent):
#ifdef eosFormsService_UseSelector            
    evSelectorPress(nullptr),
#endif
    service(nullptr),
    parent(_parent),
    x(0),
    y(0) {

    if (_service != nullptr)
        _service->add(this);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
Form::~Form() {
    
    if (service != nullptr)
        service->remove(this);
    
#ifdef eosFormsService_UseSelector               
    if (evSelectorPress != nullptr)
        delete evSelectorPress;
#endif    
}


/// ----------------------------------------------------------------------
/// \brief Procesa un missatge.
/// \param message: El missatge a procesar.
///
void Form::dispatchMessage(
    Message &message) {
    
    switch (message.id) {
        
        case MSG_PAINT: {
            FormsDisplayHandle display = message.msgPaint.display;
            display->beginDraw();
            onPaint(display);
            display->endDraw();
            break;
        }
        
#ifdef eosFormsService_UseSelector        
        case MSG_SELECTOR:
            switch (message.msgSelector.event) {
                case EV_SELECTOR_INC:
                    onSelectorMove(message.msgSelector.position, SelectorDirection::forward);
                    break;
                    
                case EV_SELECTOR_DEC:                    
                    onSelectorMove(message.msgSelector.position, SelectorDirection::backward);
                    break;
                    
                case EV_SELECTOR_CLICK:
                    if (message.msgSelector.state == 1)
                        onSelectorPress();
                    else
                        onSelectorRelease();
                    break;
            }
            break;
#endif            
            
#ifdef eosFormsService_UseKeyboard            
        case MSG_KEYBOARD:
            onKeyPress(message.msgKeyboard.event);
            break;
#endif            

        default:
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant s'activa el form
/// \param deactivateForm: El form que s'ha desactivat.
///
void Form::onActivate(
    FormHandle deactivateForm) {
    
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant el selector es mou.
/// \param position: Posicio del selector.
/// \param direction: Direccio del moviment.
///
#ifdef eosFormsService_UseSelector
void Form::onSelectorMove(
    int position,
    SelectorDirection direction) {
    
}
#endif
    

/// ----------------------------------------------------------------------
/// \brief Es crida quant el boto del selector es prem.
/// 
#ifdef eosFormsService_UseSelector
void Form::onSelectorPress() {
    
    if (evSelectorPress != nullptr)
        evSelectorPress->execute(this);
}
#endif
    

/// ----------------------------------------------------------------------
/// \brief Es crida quant el boto del selector es deixa anar.
///
#ifdef eosFormsService_UseSelector
void Form::onSelectorRelease() {
    
}
#endif


/// ----------------------------------------------------------------------
/// \brief Es crida quant es prem una tecla.
/// \param keyCode: Codi de la tecla.
///
#ifdef eosFormsService_UseKeyboard
void Form::onKeyPress(
    unsigned key) {
    
}
#endif


/// ----------------------------------------------------------------------
/// \brief Es crida quant es deina anar una tecla.
/// \param keyCode: El codi de la tecla.
///
#ifdef eosFormsService_UseKeyboard
void Form::onKeyRelease(
    unsigned keyCode) {
    
}
#endif
