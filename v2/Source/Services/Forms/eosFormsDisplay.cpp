#include "eos.hpp"
#include "Services/Forms/eosForms.hpp"


using namespace eos;


/// ---------------------------------------------------------------------
/// \brier Contructor.
/// \param displayController: Handler del controlador del display.
///
FormsDisplay::FormsDisplay(
    DisplayHandle _displayController):
    displayController(_displayController) {
    
}


/// ----------------------------------------------------------------------
/// \brief Inicia el proces de dibuix de la pantalla.
///
void FormsDisplay::beginDraw() {

}


/// ----------------------------------------------------------------------
/// \brief Finalitza el proces de dibuix de pantalla.
///
void FormsDisplay::endDraw() {
    
}


/// ----------------------------------------------------------------------
/// \brief Selecciona el color per dibuixar.
/// \param color: El color.
///
void FormsDisplay::setColor(
    unsigned color) {
    
    displayController->setColor(color);
}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla.
///
void FormsDisplay::clear() {
    
    displayController->clear(0);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia.
/// \param x1: Coordinada x inicial.
/// \param y1: Coordinada y inicial.
/// \param x2: Coordinada x final.
/// \param y2: Coordinada y final.
///
void FormsDisplay::drawLine(
    int x1, 
    int y1, 
    int x2, 
    int y2) {
    
    displayController->drawLine(x1, y1, x2, y2);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un rectangle.
/// \param x: Coordinada x de la posicio.
/// \param y: Coordinada y de la posicio.
/// \param width: Amplada.
/// \param height: Alçada.
///
void FormsDisplay::drawRectangle(
    int x, 
    int y, 
    int width, 
    int height) {
    
    displayController->drawRectangle(x, y, x + width, y + height);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un texte.
/// \param x: Coordinada x de la posicio.
/// \param y: Coordinada y de la posicio.
/// \param text: Texte a dibuixar.
/// \param offset: Posicio del primer caracter a dibuixar.
/// \param length: Numero de caracters a dibuixar.
///
void FormsDisplay::drawText(
    int x, 
    int y, 
    const char* text, 
    unsigned offset,
    unsigned length) {
    
    displayController->drawString(x, y, text);    
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un rectangle ple.
/// \param x: Coordinada x de la posicio.
/// \param y: Coordinada y de la posicio.
/// \param width: Amplada.
/// \param height: Alçada.
///
void FormsDisplay::fillRectangle(
    int x, 
    int y, 
    int width, 
    int height) {
    
    displayController->fillRectangle(x, y, x + width, y + height);
}

