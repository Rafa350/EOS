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
/// \brief Es crida quant el selector es mou.
/// \param position: Posicio del selector
/// \param forward: True si la posicio s'incrementa.
///
void ListForm::onSelectorMove(
    int position, 
    bool forward) {
    
    if (forward)
        nextItem();
    else
        prevItem();
}
    

/// ----------------------------------------------------------------------
/// \brief Es crida quant es prem el boto del selector
///
void ListForm::onSelectorPress() {
    
    selectItem();
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
