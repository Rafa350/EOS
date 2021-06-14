#include "eos.h"

#if defined(DISPLAY_DRV_SSD1306)

#include "eosAssert.h"
#include "Controllers/Display/Drivers/eosSSD1306.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Obte una instancia del driver
/// º\return  La instancia.
///
IDisplayDriver* SSD1306Driver::getInstance() {

    return new SSD1306Driver();
}


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
SSD1306Driver::SSD1306Driver() {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void SSD1306Driver::initialize() {

}

void SSD1306Driver::shutdown() {

}

void SSD1306Driver::displayOn() {

}

void SSD1306Driver::displayOff() {

}

void SSD1306Driver::setOrientation(
    DisplayOrientation orientation) {

}

void SSD1306Driver::clear(
    const Color &color) {

}

void SSD1306Driver::setPixel(
    int x,
    int y,
    const Color &color) {

}


void SSD1306Driver::setHPixels(
    int x,
    int y,
    int size,
    const Color &color) {

}


void SSD1306Driver::setVPixels(
    int x,
    int y,
    int size,
    const Color &color) {

}


void SSD1306Driver::setPixels(
    int x,
    int y,
    int width,
    int height,
    const Color &color) {

}


void SSD1306Driver::writePixels(
    int x,
    int y,
    int width,
    int height,
    const uint8_t *pixels,
    ColorFormat format,
    int dx,
    int dy,
    int pitch) {

}


void SSD1306Driver::readPixels(
    int x,
    int y,
    int width,
    int height,
    uint8_t *pixels, 
    ColorFormat format,
    int dx,
    int dy,
    int pitch) {

}

void SSD1306Driver::vScroll(
    int delta,
    int x,
    int y,
    int width,
    int height) {

}

void SSD1306Driver::hScroll(
    int delta,
    int x,
    int y,
    int width,
    int height) {

}


void SSD1306Driver::refresh() {

}


#endif
