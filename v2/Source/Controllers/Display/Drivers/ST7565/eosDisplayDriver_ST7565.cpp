#include "eos.h"
#include "Controllers/Display/Drivers/ST7565/eosDisplayDriver_ST7565.h"
#include "System/eosMath.h"
#include "System/Graphics/eosColor.h"
#include "HAL/halGPIO.h"


// Comandes de control del controlador
//
#define CMD_DISPLAY_OFF        0xAE              // Activa el display
#define CMD_DISPLAY_ON         0xAF              // Desactiva el display
#define CMD_DISPLAY_NORMAL     0xA6              // Display normal
#define CMD_DISPLAY_REVERSE    0xA7              // Display invers
#define CMD_SET_START_LINE     0x40              // Selecciona la linia inicial
#define CMD_SET_PAGE           0xB0              // Selecciona la pagina
#define CMD_SET_COLUMN_H       0x10              // Selecciona la columna (High nibble)
#define CMD_SET_COLUMN_L       0x00              // Selecciona la columna (Low nibble)
#define CMD_ALL_ON             0xA4              // Tots els punts OFF
#define CMD_ALL_OFF            0xA5              // Tots els punts ON


using namespace eos;


static uint8_t vRam[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];
static uint8_t vFlags[DISPLAY_HEIGHT / 8];


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
DisplayDriver_ST7565::DisplayDriver_ST7565(
	FrameBuffer *frameBuffer):
	_frameBuffer(frameBuffer) {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void DisplayDriver_ST7565::initialize() {

    initializeInterface();
    initializeController();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void DisplayDriver_ST7565::deinitialize() {

    disable();
}


/// ----------------------------------------------------------------------
/// \brief    Activa el display.
///
void DisplayDriver_ST7565::enable() {

    writeCtrlRegister(CMD_DISPLAY_ON);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el display.
///
void DisplayDriver_ST7565::disable() {

    writeCtrlRegister(CMD_DISPLAY_OFF);
    writeCtrlRegister(CMD_ALL_ON);
}


/// ----------------------------------------------------------------------
/// \brief    Borrat de la pantalla.
/// \param    color: El color de borrat.
///
void DisplayDriver_ST7565::clear(
    Color color) {

	_frameBuffer->clear(color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un pixel.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \param    color: Color del pixel.
///
void DisplayDriver_ST7565::setPixel(
    int x,
    int y,
    Color color) {

	_frameBuffer->setPixel(x, y, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia de pixels horitzontals.
/// \param    x : Coordinada X.
/// \param    y: Colordinada Y.
/// \param    size: Longitut de la linia.
/// \param    color: Color dels pixels.
///
void DisplayDriver_ST7565::setHPixels(
	int x,
	int y,
	int size,
	Color color) {

	_frameBuffer->setPixels(x, y, size, 1, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia de pixels en vertical.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \param    size: Longitut de la linia.
/// \param    color: Color dels pixels.
///
void DisplayDriver_ST7565::setVPixels(
	int x,
	int y,
	int size,
	Color color) {

	_frameBuffer->setPixels(x, y, 1, size, color);

}


void DisplayDriver_ST7565::setPixels(
    int x,
    int y,
    int width,
    int height,
    Color color) {

}


void DisplayDriver_ST7565::refresh() {

	constexpr int columns = _displayWidth;
	constexpr int pages = _displayHeight / 8;

    // Transfereix les pagines modificades
    //
    for (unsigned page = 0; page < 8; page++) {

        uint8_t flags = vFlags[page];
        if (flags) {
            setPage(page);
            unsigned offset = _displayWidth * page;
            uint8_t mask = 0b10000000u;
            for (unsigned j = 0; j < 128; j += 16) {
                if ((flags & mask) != 0) {
                    setColumn(j);
                    for (unsigned i = 0; i < 16; i++)
                        writeDataRegister(vRam[offset + j + i]);
                }
                mask >>= 1;
            }
            vFlags[page] = 0b00000000;
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el controlador.
///
void DisplayDriver_ST7565::initializeController() {

    static const uint8_t initTab[] = {// Taula d'inicialitzacio del display
        CMD_SET_START_LINE | 0,       // -Inici del display a la linia 0
        0xA1,                         // -ADC invertit (Visio 6h)
        0xC0,                         // -Normal COM0..63
        CMD_DISPLAY_NORMAL,           // -Normal
        0xA2,                         // -Bias 1/9
        0x2F,                         // -Booster ON
        0xF8, 0x00,                   // -Booster x4
        0x27,                         // -Regulador de voltatge
        0x81, 0x16,                   // -Modus del regulador de voltatge
        0xAC, 0x00,                   // -Sense indicador static
        CMD_DISPLAY_ON                // -Activa el display
    };

    // Envia la sequencia d'inicialitzacio al display
    //
    for (unsigned i = 0; i < sizeof(initTab) / sizeof(initTab[0]); i++)
        writeCtrlRegister(initTab[i]);
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la pagina.
/// \param    page: Numero de pagina.
///
void DisplayDriver_ST7565::setPage(
    uint8_t page) {

    writeCtrlRegister((page & 0x07) | CMD_SET_PAGE);
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la columna.
/// \param    page: Numero de columna.
///
void DisplayDriver_ST7565::setColumn(
    uint8_t column) {

    writeCtrlRegister((column & 0x0F) | CMD_SET_COLUMN_L);
    writeCtrlRegister((column >> 4) | CMD_SET_COLUMN_H);
}


