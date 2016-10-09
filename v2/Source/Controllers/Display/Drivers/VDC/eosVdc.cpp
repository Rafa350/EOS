#include "eos.hpp"
#include "Controllers/Display/Drivers/eosVDC.hpp"



using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
/// \param screenWidth: Amplada de la pantalla virtual.
/// \param screenHeight: Alçada de la pantalla virtual.
///
VDC_Driver::VDC_Driver(
    int16_t _screenWidth,
    int16_t _screenHeight):

    screenWidth(_screenWidth),
    screenHeight(_screenHeight),
    canvas(new Color[_screenHeight * _screenHeight]) {
    
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
VDC_Driver::~VDC_Driver() {

    delete[] canvas;    
}


void VDC_Driver::initialize() {

    clear(RGB(0, 0, 0));
}


void VDC_Driver::shutdown() {
    
}


void VDC_Driver::clear(
    Color color){
    
    for (int i = 0, ii = screenWidth * screenHeight; i < ii; i++)
        canvas[i] = color;
}