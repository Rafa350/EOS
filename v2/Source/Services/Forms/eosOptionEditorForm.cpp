#include "Services/Forms/eosOptionEditorForm.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructior.
/// \param service: El servei de gestio de forms
/// \prasm parent: El form pare
///
OptionEditorForm::OptionEditorForm(
    FormsService *service, 
    Form *parent):
    Form(service, parent) {
}


/// ----------------------------------------------------------------------
/// \brief Notifica que cal pintar la pantalla
/// \param displayController: El handler del controlador de pantalla.
///
void OptionEditorForm::onPaint(
    FormsDisplay *display) {

    display->clear(0x00000000);
    if (title != nullptr)
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
#ifdef eosFormsService_UseSelector
void OptionEditorForm::onSelectorMove(
    int position, 
    SelectorDirection direction) {
    
    if (direction == SelectorDirection::forward)
        nextItem();
    else
        prevItem();
}
#endif
    

/// ----------------------------------------------------------------------
/// \brief Es crida quant es prem el boto del selector
///
#ifdef eosFormsService_UseSelector
void OptionEditorForm::onSelectorPress() {
    
    selectItem();
}
#endif


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
