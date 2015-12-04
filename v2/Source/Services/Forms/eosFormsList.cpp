#include "Services/Forms/eosFormsList.hpp"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructior.
/// \param service: El servei de gestio de forms
/// \prasm parent: El form pare
///
ListForm::ListForm(
    FormsServiceHandle service, 
    FormHandle parent):
    Form(service, parent) {
}


/// ----------------------------------------------------------------------
/// \brief Notifica l'activacio del form
/// \param deactivateForm: El form que s'ha desactivat
///
void ListForm::onActivate(
    FormHandle deactivateForm) {

    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Notifica que cal pintar la pantalla
/// \param displayController: El handler del controlador de pantalla.
///
void ListForm::onPaint(
    DisplayControllerHandle displayController) {

    displayController->addCommandClear();
    if (title != NULL)
        displayController->addCommandDrawText(0, 0, title, 0, -1);
    displayController->addCommandDrawLine(0, 10, 127, 10);
    displayController->addCommandDrawLine(0, 53, 127, 53);

    if (currentItem != (unsigned) -1) {
        const char *text = items[currentItem];
        displayController->addCommandDrawText(10, 30, text, 0, -1);
    }
}


/// ----------------------------------------------------------------------
/// Procesa els missatges que arribin al form.
/// /param message: El missatge a procesar.
///
void ListForm::dispatchMessage(Message& message) {

    switch (message.id) {
        case MSG_KEYBOARD:
            switch (message.msgKeyboard.event) {
                case EV_KEYBOARD_LEFT:
                case EV_KEYBOARD_UP:
                    prevItem();
                    break;
                    
                case EV_KEYBOARD_RIGHT:
                case EV_KEYBOARD_DOWN:
                    nextItem();
                    break;
                    
                case EV_KEYBOARD_OK:
                    selectItem();
                    break;
            }
            break;
            
        case MSG_SELECTOR:
            switch (message.msgSelector.event) {
                case EV_SELECTOR_CLICK:
                    selectItem();
                    break;
    
                case EV_SELECTOR_INC:
                    nextItem();
                    break;

                case EV_SELECTOR_DEC:
                    prevItem();
                    break;
            }
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief Avança al seguent itrm
///
void ListForm::nextItem() {

    if (currentItem < numItems - 1) {
        currentItem++;
        refresh();
    }
}


/// ----------------------------------------------------------------------
/// \brief Retrocedeix fins a l'anterior item
///
void ListForm::prevItem() {

    if (currentItem > 0) {
        currentItem--;
        refresh();
    }
}


/// ----------------------------------------------------------------------
/// \brief Selecciona el item actual
///
void ListForm::selectItem() {
}
