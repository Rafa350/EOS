#include "eos.hpp"
#include "Services/Forms/eosForms.hpp"


using namespace eos;


/// ---------------------------------------------------------------------
/// \brier Contructor.
/// \param displayController: Handler del controlador del display.
///
FormsDisplay::FormsDisplay(
    DisplayControllerHandle _displayController):
    displayController(_displayController) {
    
}


/// ----------------------------------------------------------------------
/// \brief Inicia el proces de dibuix de la pantalla.
///
void FormsDisplay::beginDraw() {

    displayController->beginCommand();    
}


/// ----------------------------------------------------------------------
/// \brief Finalitza el proces de dibuix de pantalla.
///
void FormsDisplay::endDraw() {
    
    displayController->addCommandRefresh();
    displayController->endCommand();
}


/// ----------------------------------------------------------------------
/// \brief Selecciona el color per dibuixar.
/// \param color: El color.
///
void FormsDisplay::setColor(
    unsigned color) {
    
    displayController->addCommandSetColor(color, -1);
}

void FormsDisplay::clear() {
    
    displayController->addCommandClear();
}


void FormsDisplay::drawLine(
    int x1, 
    int y1, 
    int x2, 
    int y2) {
    
    displayController->addCommandDrawLine(x1, y1, x2, y2);
}


void FormsDisplay::drawRectangle(
    int x, 
    int y, 
    int width, 
    int height) {
    
    displayController->addCommandFillRectangle(x, y, x + width, y + height);
}


void FormsDisplay::drawText(
    int x, 
    int y, 
    const char* text, 
    unsigned offset,
    unsigned length) {
    
    displayController->addCommandDrawText(x, y, text, offset, length);    
}


void FormsDisplay::fillRectangle(int x, int y, int width, int height) {
    
    displayController->addCommandFillRectangle(x, y, x + width, y + height);
}

