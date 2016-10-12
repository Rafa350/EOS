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


void VDC_Driver::initialize() {
    
    clear(Color(0));
}


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


void VDC_Driver::setPixel(
    int16_t x, 
    int16_t y, 
    Color color) {
    
    canvas[offsetOf(x, y)] = color;
}



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
