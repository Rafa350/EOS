#include "eos.hpp"
#include "Services/Forms/eosForms.hpp"
#include "Controllers/Display/eosDisplay.hpp"


using namespace eos;


/// ---------------------------------------------------------------------
/// \brier Contructor.
/// \param display: Handler del controlador del display.
///
FormsDisplay::FormsDisplay(
    Display *_display):
    display(_display) {
    
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
    
    display->setColor(color);
}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla.
/// \param color: Color
///
void FormsDisplay::clear(
    Color color) {
    
    display->clear(color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia.
/// \param x1: Coordinada x inicial.
/// \param y1: Coordinada y inicial.
/// \param x2: Coordinada x final.
/// \param y2: Coordinada y final.
///
void FormsDisplay::drawLine(
    int16_t x1, 
    int16_t y1, 
    int16_t x2, 
    int16_t y2) {
    
    display->drawLine(x1, y1, x2, y2);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un rectangle.
/// \param x: Coordinada x de la posicio.
/// \param y: Coordinada y de la posicio.
/// \param width: Amplada.
/// \param height: Alçada.
///
void FormsDisplay::drawRectangle(
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height) {
    
    display->drawRectangle(x, y, x + width - 1, y + height - 1);
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
    int16_t x, 
    int16_t y, 
    const char* text, 
    int16_t offset,
    int16_t length) {
    
    display->drawText(x, y, text, offset, length);    
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un rectangle ple.
/// \param x: Coordinada x de la posicio.
/// \param y: Coordinada y de la posicio.
/// \param width: Amplada.
/// \param height: Alçada.
///
void FormsDisplay::fillRectangle(
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height) {
    
    display->fillRectangle(x, y, x + width, y + height);
}

