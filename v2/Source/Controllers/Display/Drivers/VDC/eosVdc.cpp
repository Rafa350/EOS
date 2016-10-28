#include "eos.hpp"
#include "Controllers/Display/Drivers/eosVDC.hpp"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
/// \param screenWidth: Amplada de la pantalla virtual.
/// \param screenHeight: Alçada de la pantalla virtual.
///
VDC_Driver::VDC_Driver(
    int16_t screenWidth,
    int16_t screenHeight):

    screenWidth(screenWidth),
    screenHeight(screenHeight),
    canvas(new VDC_Pixel[screenHeight * screenHeight]) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
VDC_Driver::~VDC_Driver() {

    delete[] canvas;    
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza la pantalla.
///
void VDC_Driver::initialize() {
    
    clear(Color(0));
}


/// ----------------------------------------------------------------------
/// \brief Desactiva la pantalla.
///
void VDC_Driver::shutdown() {
    
}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla.
/// \param color: Color per borrar.
///
void VDC_Driver::clear(
    Color color){
    
    VDC_Pixel pixel(color);
    for (int i = 0, ii = screenWidth * screenHeight; i < ii; i++)
        canvas[i] = pixel;
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un pixel.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param color: Color del pixel.
///
void VDC_Driver::setPixel(
    int16_t x, 
    int16_t y, 
    Color color) {
    
    canvas[offsetOf(x, y)] = color;
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels horitzontals. 
/// \param x: Coordinada X.
/// \param y: Colordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void VDC_Driver::setHPixels(
    int16_t x, 
    int16_t y, 
    int16_t size, 
    Color color) {
    
    VDC_Pixel pixel(color);
    
    int16_t offset = offsetOf(x, y);
    while (size--) {
        canvas[offset] = pixel;
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
void VDC_Driver::setVPixels(
    int16_t x, 
    int16_t y, 
    int16_t size, 
    Color color) {
    
    VDC_Pixel pixel(color);
    
    int16_t offset = offsetOf(x, y);
    while (size--) {
        canvas[offset] = pixel;
        offset += screenWidth;
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una regio rectangular de pixels.
/// \param x: Posicio X.
/// \param y: Posicio Y.
/// \param width: Amplada de la regio.
/// \param height: Alçada de la regio.
/// \param color: Color dels pixels.
///
void VDC_Driver::setPixels(
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
/// \param height: Alçada de la regio.
/// \param colors: Color dels pixels.
///
void VDC_Driver::writePixels(
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
/// \param height: Alçada de la regio.
/// \params colors: Buffer on deixar els pixels.
///
void VDC_Driver::readPixels(
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height, 
    Color *colors) {

    while (height--) {
        while (width--) {
            VDC_Pixel *pixel = &canvas[offsetOf(x, y)];
            colors->r = pixel->r << 3;
            colors->g = pixel->g << 2;
            colors->b = pixel->b << 3;
            x += 1;
        }
        y += 1;
    }
}
