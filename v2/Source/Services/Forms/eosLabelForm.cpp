#include "eosmacros.h"
#include "Services/Forms/eosLabelForm.h"

#include <stdio.h>


using namespace eos;


static const char *emptyString = "";
extern VisualScheme visualScheme;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param service: El servei de gestio de forms.
/// \param parent: El form pare.
///
LabelForm::LabelForm(
    FormsService *service,
    Form *parent):
    
    Form(service, parent),
    title(emptyString) {
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
    
    if (visualScheme.labelBorderThickness > 0) {
        display->setColor(visualScheme.labelBorderColor);
        display->drawRectangle(0, 0, width, height, visualScheme.labelBorderThickness);
    }
    
    display->setColor(visualScheme.labelBackgroundColor);
    display->fillRectangle(visualScheme.labelBorderThickness, visualScheme.labelBorderThickness, 
        width - (visualScheme.labelBorderThickness << 1), height - (visualScheme.labelBorderThickness << 1));

    display->setColor(visualScheme.labelNormalTextColor);
    display->drawText(2, height - 3, title, 0, -1);
}
