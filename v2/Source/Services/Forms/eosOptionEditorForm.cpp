#include "Services/Forms/eosOptionEditorForm.hpp"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructior.
/// \param service: El servei de gestio de forms
/// \prasm parent: El form pare
///
OptionEditorForm::OptionEditorForm(
    FormsServiceHandle service, 
    FormHandle parent):
    Form(service, parent) {
}


/// ----------------------------------------------------------------------
/// \brief Notifica l'activacio del form
/// \param deactivateForm: El form que s'ha desactivat
///
void OptionEditorForm::onActivate(
    FormHandle deactivateForm) {

    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Notifica que cal pintar la pantalla
/// \param displayController: El handler del controlador de pantalla.
///
void OptionEditorForm::onPaint(
    FormsDisplayHandle display) {

    display->clear();
    if (title != NULL)
        display->drawText(0, 0, title, 0, -1);
    display->drawLine(0, 10, 127, 10);
    display->drawLine(0, 53, 127, 53);

    if (currentItem != (unsigned) -1) {
        const char *text = items[currentItem];
        display->drawText(10, 30, text, 0, -1);
    }
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant el selector es mou.
/// \param position: Posicio del selector
/// \param direction Direccio del moviment.
///
void OptionEditorForm::onSelectorMove(
    int position, 
    SelectorDirection direction) {
    
    if (direction == SelectorDirection::forward)
        nextItem();
    else
        prevItem();
}
    

/// ----------------------------------------------------------------------
/// \brief Es crida quant es prem el boto del selector
///
void OptionEditorForm::onSelectorPress() {
    
    selectItem();
}


/// ----------------------------------------------------------------------
/// \brief Avança al seguent itrm
///
void OptionEditorForm::nextItem() {

    if (currentItem < numItems - 1) {
        currentItem++;
        refresh();
    }
}


/// ----------------------------------------------------------------------
/// \brief Retrocedeix fins a l'anterior item
///
void OptionEditorForm::prevItem() {

    if (currentItem > 0) {
        currentItem--;
        refresh();
    }
}


/// ----------------------------------------------------------------------
/// \brief Selecciona el item actual
///
void OptionEditorForm::selectItem() {
}
