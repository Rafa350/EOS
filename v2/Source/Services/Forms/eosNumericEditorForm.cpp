#include "Services/Forms/eosNumericEditorForm.hpp"


using namespace eos;


static const char *emptyString = "";


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param service: El servei de gestio de forms.
/// \param parent: El form pare.
///
NumericEditorForm::NumericEditorForm(
    FormsServiceHandle service,
    FormHandle parent):
    Form(service, parent),
    prefix(emptyString),
    suffix(emptyString),
    evChange(nullptr),
    evSet(nullptr) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
NumericEditorForm::~NumericEditorForm() {
    
    if (evChange != nullptr)
        delete evChange;
    
    if (evSet != nullptr)
        delete evSet;
}


/// ----------------------------------------------------------------------
/// \brief Asigna el valor minim.
/// \param minValue: El valor minim.
///
void NumericEditorForm::setMinValue(
    int minValue) {

    this->minValue = minValue;
    value = eosMax(value, minValue);
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Asigna el valor maxim.
/// \param maxValue: El valor maxim.
//
void NumericEditorForm::setMaxValue(
    int maxValue) {

    this->maxValue = maxValue;
    value = eosMin(value, maxValue);
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Asigna el valor.
/// \param value: El valor a asignar.
///
void NumericEditorForm::setValue(
    int value) {

    this->value = eosMin(eosMax(value, minValue), maxValue);
    refresh();
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
/// \brief Asigna el titol.
/// \param title: El texte del titol.
///
void NumericEditorForm::setTitle(
    const char *title) {

    this->title = title ? title : emptyString;
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Notifica l'activacio del form
/// \param deactivateForm: El form que s'ha desactivat
///
void NumericEditorForm::onActivate(
    FormHandle deactivateForm) {

    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Notifica que cal pintar la pantalla
/// \param displayController: El handler del controlador de pantalla.
///
void NumericEditorForm::onPaint(
    FormsDisplayHandle display) {

    display->clear();
    if (title != nullptr)
        display->drawText(0, 0, title, 0, -1);
    
    display->drawLine(0, 10, 127, 10);
    display->drawLine(0, 53, 127, 53);

    char text[40];
    sprintf(text, "%s%d%s", prefix, value, suffix);

    display->drawText(10, 30, text, 0, -1);
}

     
/// ----------------------------------------------------------------------
/// \brief Es crida quant canvia la posicio del selector.
/// \param position: Posicio del selector.
/// \param direction: Direccio del moviment.
///
void NumericEditorForm::onSelectorMove(
    int position, 
    SelectorDirection direction) {
    
    if (direction == SelectorDirection::forward)
        incValue();
    else
        decValue();
    
    Form::onSelectorMove(position, direction);
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant es prem el boto del selector.
//
void NumericEditorForm::onSelectorPress() {
    
    setValue();
    
    Form::onSelectorPress();
}


/// ----------------------------------------------------------------------
/// \brief Incrementa el valor.
///
void NumericEditorForm::incValue() {
    
    if (value + delta <= maxValue) {
        value += delta;
        if (evChange != nullptr)
            evChange->execute(value);
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
            evChange->execute(value);
        refresh();
    }
}


/// ----------------------------------------------------------------------
/// \brief Asigna el valor.
///
void NumericEditorForm::setValue() {
    
    if (evSet != nullptr)
        evSet->execute(value);
}

