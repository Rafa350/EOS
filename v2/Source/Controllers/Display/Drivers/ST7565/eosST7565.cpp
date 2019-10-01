#include "eos.h"
#include "Controllers/Display/Drivers/eosST7565.h"
#include "System/Graphics/eosColor.h"
#include "HAL/halGPIO.h"


using namespace eos;


static uint8_t vRam[DISPLAY_SCREEN_WIDTH * DISPLAY_SCREEN_HEIGHT / 8];
static uint8_t vFlags[DISPLAY_SCREEN_HEIGHT / 8];        


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
ST7565Driver::ST7565Driver():
 	screenWidth(DISPLAY_SCREEN_WIDTH),
	screenHeight(DISPLAY_SCREEN_HEIGHT),
	orientation(DisplayOrientation::normal) {
    
}


void ST7565Driver::initialize() {
    
}


void ST7565Driver::shutdown() {
    
}


void ST7565Driver::displayOn() {
    
}


void ST7565Driver::displayOff() {
    
}


void ST7565Driver::setOrientation(
    DisplayOrientation orientation) {
    
}


void ST7565Driver::clear(
    const Color& color) {
    
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un pixel.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param color: Color del pixel.
///
void ST7565Driver::setPixel(
    int x,
    int y,
    const Color &color) {

	if ((x >= 0) && (x < screenWidth) && (y >= 0) && (y < screenHeight)) {

        int offset = ((y >> 3) * screenWidth) + x;
        uint8_t pix = 1 << (y & 7);      
        if (color.isOpaque())
            vRam[offset] |= pix;
        else
            vRam[offset] &= ~pix;

        vFlags[y >> 3] |= 0b10000000 >> (x >> 4);
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels horitzontals.
/// \param x: Coordinada X.
/// \param y: Colordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void ST7565Driver::setHPixels(
	int x,
	int y,
	int size,
	const Color &color) {
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels en vertical.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void ST7565Driver::setVPixels(
	int x,
	int y,
	int size,
	const Color &color) {
}



void ST7565Driver::refresh() {
    
    // Transfereix les pagines modificades
    //
    for (unsigned page = 0; page < 8; page++) {

        uint8_t flags = vFlags[page];
        if (flags) {
            setPage(page);
            unsigned offset = screenWidth * page;
            uint8_t mask = 0b10000000u;
            for (unsigned j = 0; j < 128; j += 16) {
                if ((flags & mask) != 0) {
                    setColumn(j);
                    for (unsigned i = 0; i < 16; i++)
                        writeData(vRam[offset + j + i]);
                }
                mask >>= 1;
            }
            vFlags[page] = 0b00000000;
        }
    }   
}



void ST7565Driver::setPage(
    uint8_t page) {
    
}


void ST7565Driver::setColumn(
    uint8_t column) {
    
}


void ST7565Driver::writeData(
    uint8_t data) {
    
}