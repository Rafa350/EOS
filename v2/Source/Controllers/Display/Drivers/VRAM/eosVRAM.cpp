#include "Controllers/Display/Drivers/eosVRAM.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
/// \param screenWidth: Amplada de la pantalla virtual.
/// \param screenHeight: Al�ada de la pantalla virtual.
///
VRAM_Driver::VRAM_Driver(
    int16_t screenWidth,
    int16_t screenHeight):

    screenWidth(screenWidth),
    screenHeight(screenHeight),
    canvas(screenHeight * screenHeight) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
VRAM_Driver::~VRAM_Driver() {
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza la pantalla.
///
void VRAM_Driver::initialize() {
    
    clear(COLOR_Black);
}


/// ----------------------------------------------------------------------
/// \brief Desactiva la pantalla.
///
void VRAM_Driver::shutdown() {
    
}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla.
/// \param color: Color per borrar.
///
void VRAM_Driver::clear(
    Color color){
    
    for (int i = 0, ii = screenWidth * screenHeight; i < ii; i++)
        canvas.setColor(i, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un pixel.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param color: Color del pixel.
///
void VRAM_Driver::setPixel(
    int16_t x, 
    int16_t y, 
    Color color) {
    
    canvas.setColor(offsetOf(x, y), color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels horitzontals. 
/// \param x: Coordinada X.
/// \param y: Colordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void VRAM_Driver::setHPixels(
    int16_t x, 
    int16_t y, 
    int16_t size, 
    Color color) {
    
    int16_t offset = offsetOf(x, y);
    while (size--) {
        canvas.setColor(offset, color);
        offset += 1;
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels en vertical. 
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void VRAM_Driver::setVPixels(
    int16_t x, 
    int16_t y, 
    int16_t size, 
    Color color) {
    
    int16_t offset = offsetOf(x, y);
    while (size--) {
        canvas.setColor(offset, color);
        offset += screenWidth;
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una regio rectangular de pixels.
/// \param x: Posicio X.
/// \param y: Posicio Y.
/// \param width: Amplada de la regio.
/// \param height: Al�ada de la regio.
/// \param color: Color dels pixels.
///
void VRAM_Driver::setPixels(
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height, 
    Color color) {

    while (height--)
        setHPixels(x, y++, width, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una regio rectangular de pixels.
/// \param x: Posicio X.
/// \param y: Posicio Y.
/// \param width: Amplada de la regio.
/// \param height: Al�ada de la regio.
/// \param colors: Color dels pixels.
///
void VRAM_Driver::writePixels(
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height, 
    const Color* colors) {

    while (height--) {
        while (width--) {
            setPixel(x, y, *colors++);
            x += 1;
        }
        y += 1;
    }
}


/// ----------------------------------------------------------------------
/// \brief Llegeix una regio rectangular de pixels. No hi ha cap tipus de 
///        comprovacio de la validesa dels parametres.
/// \param x: Posicio X.
/// \param y: Posicio Y.
/// \param width: Amplada de la regio.
/// \param height: Al�ada de la regio.
/// \params colors: Buffer on deixar els pixels.
///
void VRAM_Driver::readPixels(
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height, 
    Color *colors) {

    while (height--) {
        while (width--) {
            *colors++ = canvas.getColor(offsetOf(x, y));
            x += 1;
        }
        y += 1;
    }
}