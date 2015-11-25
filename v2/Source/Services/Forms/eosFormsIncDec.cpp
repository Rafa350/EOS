#include "Services/Forms/eosFormsIncDec.hpp"
#include "Controllers/eosDisplay.hpp"


using namespace eos;


static const char *emptyString = "";


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param service: El servei de gestio de forms.
/// \param parent: El form pare.
///
IncDecForm::IncDecForm(
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
IncDecForm::~IncDecForm() {
    
    if (evChange != nullptr)
        delete evChange;
    
    if (evSet != nullptr)
        delete evSet;
}


/// ----------------------------------------------------------------------
/// \brief Asigna el valor minim.
/// \param minValue: El valor minim.
///
void IncDecForm::setMinValue(
    int minValue) {

    this->minValue = minValue;
    value = eosMax(value, minValue);
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Asigna el valor maxim.
/// \param maxValue: El valor maxim.
//
void IncDecForm::setMaxValue(
    int maxValue) {

    this->maxValue = maxValue;
    value = eosMin(value, maxValue);
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Asigna el valor.
/// \param value: El valor a asignar.
///
void IncDecForm::setValue(
    int value) {

    this->value = eosMin(eosMax(value, minValue), maxValue);
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Asigna el increment.
/// \param delte: El valor del increment.
///
void IncDecForm::setDelta(
    int delta) {

    this->delta = delta;
}


/// ----------------------------------------------------------------------
/// \brief Asigna el prefix.
/// \param prefix: El texte del prefix.
///
void IncDecForm::setPrefix(
    const char *prefix) {

    this->prefix = prefix ? prefix : emptyString;
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Asigna el sufix.
/// \param suffix: El texte del sufix.
///
void IncDecForm::setSuffix(
    const char *suffix) {

    this->suffix = suffix ? suffix : emptyString;
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Asigna el titol.
/// \param title: El texte del titol.
///
void IncDecForm::setTitle(
    const char *title) {

    this->title = title ? title : emptyString;
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Procesa els missatges que arribin al form
/// \param message: El missatge a procesar
///
void IncDecForm::dispatchMessage(
    Message &message) {

    switch (message.id) {
        case MSG_SELECTOR:
            switch (message.msgSelector.event) {
                case EV_SELECTOR_INC:
                    incValue();
                    break;

                case EV_SELECTOR_DEC:
                    decValue();
                    break;

                case EV_SELECTOR_CLICK:
                    setValue();
                    break;
            }
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief Notifica l'activacio del form
/// \param deactivateForm: El form que s'ha desactivat
///
void IncDecForm::onActivate(
    FormHandle deactivateForm) {

    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Notifica que cal pintar la pantalla
/// \param displayController: El handler del controlador de pantalla.
///
void IncDecForm::onPaint(
    DisplayControllerHandle displayController) {

    if (displayController->beginCommand()) {

        displayController->addCommandClear();
        if (title != nullptr)
            displayController->addCommandDrawText(0, 0, title, 0, -1);
        displayController->addCommandDrawLine(0, 10, 127, 10);
        displayController->addCommandDrawLine(0, 53, 127, 53);

        char text[40];
        sprintf(text, "%s%d%s", prefix, value, suffix);

        displayController->addCommandDrawText(10, 30, text, 0, -1);
        displayController->addCommandRefresh();
        displayController->endCommand();
    }
}


/// ----------------------------------------------------------------------
/// \brief Incrementa el valor.
///
void IncDecForm::incValue() {
    
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
void IncDecForm::decValue() {

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
void IncDecForm::setValue() {
    
    if (evSet != nullptr)
        evSet->execute(value);
}

