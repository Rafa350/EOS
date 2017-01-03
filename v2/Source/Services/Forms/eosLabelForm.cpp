#include "eosmacros.h"
#include "Services/Forms/eosLabelForm.hpp"

#include <stdio.h>


using namespace eos;


static const char *emptyString = "";


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param service: El servei de gestio de forms.
/// \param parent: El form pare.
///
LabelForm::LabelForm(
    FormsService *service,
    Form *parent):
    
    Form(service, parent),
    title(emptyString),
    borderWidth(1),
    borderColor(COLOR_Red), 
    fgColor(COLOR_Yellow),
    bkColor(COLOR_Transparent) {
}



/// ----------------------------------------------------------------------
/// \brief Asigna el titol.
/// \param prefix: El text del titol.
///
void LabelForm::setTitle(
    const char *title) {

    this->title = title ? title : emptyString;
    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Notifica que cal pintar la pantalla
/// \param displayController: El handler del controlador de pantalla.
///
void LabelForm::onPaint(
    FormsDisplay *display) {
    
    int16_t width = getWidth();
    int16_t height = getHeight();
    
    display->setColor(borderColor);
    display->drawRectangle(0, 0, width, height);
    
    display->setColor(bkColor);
    display->fillRectangle(1, 1, width - 2, height - 2);

    display->setColor(fgColor);
    display->drawText(2, height - 3, title, 0, -1);
}
