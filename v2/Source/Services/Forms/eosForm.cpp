#include "eos.h"
#include "Controllers/Display/eosColor.h"
#include "Services/Forms/eosForms.h"


using namespace eos;


VisualScheme visualScheme = {
    .labelNormalTextColor = COLOR_White,
    .labelActiveTextColor = COLOR_Yellow,
    .labelDisabledTextColor = COLOR_Gray,
    .labelBorderColor = COLOR_White,
    .labelBackgroundColor = COLOR_Black,
    .labelBorderThickness = 1,

    .editorNormalTextColor = COLOR_Yellow,
    .editorActiveTextColor = COLOR_Yellow,
    .editorDisabledTextColor = COLOR_Gray,
    .editorBorderColor = COLOR_Yellow,
    .editorBackgroundColor = COLOR_Black,
    .editorBorderThickness = 1,
            
    .menuBorderColor = COLOR_Red,
    .menuSelectedBorderColor = COLOR_Yellow,
    .menuTitleTextColor = COLOR_Red,
    .menuTitleBackgroundColor = COLOR_Orange,
    .menuNormalTextColor = COLOR_Yellow,
    .menuSelectedTextColor = COLOR_Yellow,
    .menuDisabledTextColor = COLOR_Gray,
    .menuBackgroundColor = COLOR_Black,
    .menuSelectedBackgroundColor = COLOR_Blue,
    .menuBorderThickness = 1,
    .menuItemHeight = 20
};


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param service: El servei de gestio dels forms.
/// \param parent: El form pare.
///
Form::Form(
    FormsService *_service,
    Form *_parent):

#ifdef eosFormsService_UseKeyboard
    evKeyboardPress(nullptr),
    evKeyboardRelease(nullptr),
#endif    
#ifdef eosFormsService_UseSelector            
    evSelectorPress(nullptr),
    evSelectorRelease(nullptr),
#endif
    service(nullptr),
    parent(_parent),
    x(0),
    y(0),
    width(-1),
    height(-1),
    visible(false) {

    if (_service != nullptr)
        _service->add(this);
    
    if (_parent != nullptr)
        _parent->add(this);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
Form::~Form() {
    
    if (parent != nullptr)
        parent->remove(this);
    
    if (service != nullptr)
        service->remove(this);
    
#ifdef eosFormsService_UseKeyboard
    if (evKeyboardPress != nullptr)
        delete evKeyboardPress;

    if (evKeyboardRelease != nullptr)
        delete evKeyboardRelease;
#endif    
    
#ifdef eosFormsService_UseSelector               
    if (evSelectorPress != nullptr)
        delete evSelectorPress;
    
    if (evSelectorRelease != nullptr)
        delete evSelectorRelease;
#endif    
}


/// ----------------------------------------------------------------------
/// \brief Canvia la posicio del form.
/// \param x: Posicio X.
/// \param y: Posicio Y.
///
void Form::setPosition(
    int16_t x, 
    int16_t y) {
    
    this->x = x;
    this->y = y;
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Canvia el tamany del form.
/// \param width: Amplada del form.
/// \param height: Alçada del form.
///
void Form::setSize(
    int16_t width, 
    int16_t height) {
    
    this->width = width;
    this->height = height;
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Canvia la visibilitat del form.
/// \param visible: True per fer visible el form, false en cas contrari.
///
void Form::setVisibility(
    bool visible) {
    
    this->visible = visible;
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Comprova si el form es visible, explorant tota la cadena de
///        contenidors.
/// \return True si es visible.
///
bool Form::isVisible() const {
    
    const Form *form = this;
    
    while (form != nullptr) {
        if (!form->visible)
            return false;
        form = form->parent;
    }
    
    return true;
}

/// ----------------------------------------------------------------------
/// \brief Procesa un missatge.
/// \param message: El missatge a procesar.
///
void Form::dispatchMessage(
    const Message &message) {
    
    switch (message.id) {
        
        case MSG_PAINT:
            if (isVisible())
                dispatchPaintMessage(message);
            break;
        
#ifdef eosFormsService_UseSelector        
        case MSG_SELECTOR:
            switch (message.msgSelector.event) {
                case SelectorEvent::inc:
                    onSelectorInc(message.msgSelector.delta);
                    break;
                    
                case SelectorEvent::dec:                    
                    onSelectorDec(message.msgSelector.delta);
                    break;
                    
                case SelectorEvent::press:
                    onSelectorPress();
                    break;
                
                case SelectorEvent::release:
                    onSelectorRelease();
                    break;
            }
            break;
#endif            
            
#ifdef eosFormsService_UseKeyboard            
        case MSG_KEYBOARD:
            switch (message.msgKeyboard.event) {
                case KeyboardEvent::press:
                    onKeyPress(message.msgKeyboard.keyCode);
                    break;
                    
                case KeyboardEvent::release:
                    onKeyRelease(message.msgKeyboard.keyCode);
                    break;
            }
            break;
#endif            

        default:
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief Procesa el missatge MSG_PAINT
/// \param message: El missatge a procesar.
///
void Form::dispatchPaintMessage(
    const Message& message) {

    FormsDisplay *display = message.msgPaint.display;

    // Primer es redibuixa el propi form
    //
    display->beginDraw(x, y, width, height);
    onPaint(display);
    display->endDraw();

    // Despres es redibuixen el fills
    //
    ChildListIterator iterator(childs);
    while (iterator.hasNext()) {
        Form *child = iterator.current();
        if (child->visible)
            child->dispatchPaintMessage(message);
        iterator.next();
    }
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant s'activa el form
/// \param deactivateForm: El form que s'ha desactivat.
///
void Form::onActivate(
    Form *deactivateForm) {
    
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant el selector es mou en devant.
/// \param delta: Desplaçament desde l'ultima notificacio.
///
#ifdef eosFormsService_UseSelector
void Form::onSelectorInc(
    uint16_t delta) {
    
}
#endif
    
/// ----------------------------------------------------------------------
/// \brief Es crida quant el selector es en darrera.
/// \param delta: Desplaçament desde l'ultima notificacio.
///
#ifdef eosFormsService_UseSelector
void Form::onSelectorDec(
    uint16_t delta) {
    
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
    
    if (evSelectorRelease != nullptr)
        evSelectorRelease->execute(this);
}
#endif


/// ----------------------------------------------------------------------
/// \brief Es crida quant es prem una tecla.
/// \param keyCode: Codi de la tecla.
///
#ifdef eosFormsService_UseKeyboard
void Form::onKeyPress(
    KeyCode keyCode) {
    
    if (evKeyboardPress != nullptr)
        evKeyboardPress->execute(this, keyCode);
}
#endif


/// ----------------------------------------------------------------------
/// \brief Es crida quant es deina anar una tecla.
/// \param keyCode: El codi de la tecla.
///
#ifdef eosFormsService_UseKeyboard
void Form::onKeyRelease(
    KeyCode keyCode) {
    
    if (evKeyboardRelease != nullptr)
        evKeyboardRelease->execute(this, keyCode);
}
#endif
