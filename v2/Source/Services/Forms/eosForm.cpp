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
    service(nullptr),
    parent(_parent),
    paintPending(true),
    evSelectorPress(nullptr) {

    if (_service != nullptr)
        _service->add(this);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
Form::~Form() {
    
    if (service != nullptr)
        service->remove(this);
    
    if (evSelectorPress != nullptr)
        delete evSelectorPress;
}


/// ----------------------------------------------------------------------
/// \brief Refresca un formulari.
///
void Form::refresh() {
    
    paintPending = true;   
}


/// ----------------------------------------------------------------------
/// \brief Procesa un missatge.
/// \param message: El missatge a procesar.
///
void Form::dispatchMessage(
    Message &message) {
    
    switch (message.id) {
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
            
        case MSG_KEYBOARD:
            onKeyPress(message.msgKeyboard.event);
            break;

        default:
            break;
    }
}


/// ----------------------------------------------------------------------
/// |brief Es crida quant s'activa el form
///
void Form::onActivate(FormHandle deactivateForm) {
    
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant el selector es mou.
/// \param position: Posicio del selector.
/// \param direction: Direccio del moviment.
///
void Form::onSelectorMove(
    int position,
    SelectorDirection direction) {
    
}
    

/// ----------------------------------------------------------------------
/// \brief Es crida quant el boto del selector es prem.
/// 
void Form::onSelectorPress() {
    
    if (evSelectorPress != nullptr)
        evSelectorPress->execute(this);
}
    

/// ----------------------------------------------------------------------
/// \brief Es crida quant el boto del selector es deixa anar.
///
void Form::onSelectorRelease() {
    
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant es prem una tecla.
/// \param keyCode: Codi de la tecla.
///
void Form::onKeyPress(
    unsigned key) {
    
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant es deina anar una tecla.
/// \param keyCode: El codi de la tecla.
///
void Form::onKeyRelease(
    unsigned keyCode) {
    
}
