#include "eosmacros.h"
#include "Services/Forms/eosNumericEditorForm.hpp"

#include <stdio.h>


using namespace eos;


static const char *emptyString = "";


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param service: El servei de gestio de forms.
/// \param parent: El form pare.
///
NumericEditorForm::NumericEditorForm(
    FormsService *service,
    Form *parent):
    
    Form(service, parent),
    prefix(emptyString),
    suffix(emptyString),
    evChange(nullptr),
    borderWidth(1),
    borderColor(COLOR_Blue), 
    fgColor(COLOR_Yellow),
    bkColor(COLOR_Black) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
NumericEditorForm::~NumericEditorForm() {
    
    if (evChange != nullptr)
        delete evChange;
}


/// ----------------------------------------------------------------------
/// \brief Asigna el valor minim.
/// \param minValue: El valor minim.
///
void NumericEditorForm::setMinValue(
    int minValue) {

    this->minValue = minValue;
    setValue(max(value, minValue));
}


/// ----------------------------------------------------------------------
/// \brief Asigna el valor maxim.
/// \param maxValue: El valor maxim.
//
void NumericEditorForm::setMaxValue(
    int maxValue) {

    this->maxValue = maxValue;
    setValue(min(value, maxValue));
}


/// ----------------------------------------------------------------------
/// \brief Asigna el valor.
/// \param value: El valor a asignar.
///
void NumericEditorForm::setValue(
    int value) {

    if (this->value != value) {
        this->value = min(max(value, minValue), maxValue);
        if (evChange != nullptr)
            evChange->execute(this, value);
        refresh();
    }
}


/// ----------------------------------------------------------------------
/// \brief Asigna el increment.
/// \param delte: El valor del increment.
///
void NumericEditorForm::setDelta(
    int delta) {

    this->delta = delta;
}


/// ----------------------------------------------------------------------
/// \brief Asigna el prefix.
/// \param prefix: El texte del prefix.
///
void NumericEditorForm::setPrefix(
    const char *prefix) {

    this->prefix = prefix ? prefix : emptyString;
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Asigna el sufix.
/// \param suffix: El texte del sufix.
///
void NumericEditorForm::setSuffix(
    const char *suffix) {

    this->suffix = suffix ? suffix : emptyString;
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Notifica que cal pintar la pantalla
/// \param displayController: El handler del controlador de pantalla.
///
void NumericEditorForm::onPaint(
    FormsDisplay *display) {
    
    char text[40];
    sprintf(text, "%s%d%s", prefix, value, suffix);

    if (borderWidth) {
        display->setColor(borderColor);
        display->drawRectangle(0, 0, 100, 20);
    }
    
    display->setColor(bkColor);
    display->fillRectangle(1, 1, 98, 18);

    display->setTextAlign(HorizontalTextAlign::right, VerticalTextAlign::bottom);
    display->setColor(fgColor);
    display->drawText(96, 16, text, 0, -1);
}

     
/// ----------------------------------------------------------------------
/// \brief Es crida quant canvia la posicio del selector.
/// \param position: Posicio del selector.
/// \param direction: Direccio del moviment.
///
#ifdef eosFormsService_UseSelector
void NumericEditorForm::onSelectorMove(
    int position, 
    SelectorDirection direction) {
    
    if (direction == SelectorDirection::forward)
        incValue();
    else
        decValue();
    
    Form::onSelectorMove(position, direction);
}
#endif


/// ----------------------------------------------------------------------
/// \brief Es crida quan es prem el boto del selector.
///
#ifdef eosFormsService_UseSelector
void NumericEditorForm::onSelectorPress() {
    
    Form::onSelectorPress();
}
#endif


/// ----------------------------------------------------------------------
/// \brief Es crida quant es prem una tecla.
/// \param keyCode: Codi de la tecla.
///
#ifdef eosFormsService_UseKeyboard
void NumericEditorForm::onKeyPress(
    KeyCode keyCode) {
    
    switch (keyCode) {
        case KeyCode::left:
        case KeyCode::up:
            incValue();
            break;
        
        case KeyCode::right:
        case KeyCode::down:
            decValue();
            break;
            
        case KeyCode::enter:
            break;
    }
    
    Form::onKeyPress(keyCode);
}
#endif


/// ----------------------------------------------------------------------
/// \brief Incrementa el valor.
///
void NumericEditorForm::incValue() {
    
    if (value + delta <= maxValue) {
        value += delta;
        if (evChange != nullptr)
            evChange->execute(this, value);
        refresh();
    }
}


/// ----------------------------------------------------------------------
/// \brief Decrementa el valor.
///
void NumericEditorForm::decValue() {

    if (value - delta >= minValue) {
        value -= delta;
        if (evChange != nullptr)
            evChange->execute(this, value);
        refresh();
    }
}
