#include "eos.h"
#include "Controllers/Display/Drivers/eosST7565.h"
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


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void ST7565Driver::initialize() {

    static const halGPIOPinSettings gpioInit[] = {
        { DISPLAY_RST_PORT, DISPLAY_RST_PIN, HAL_GPIO_MODE_OUTPUT_PP },
        { DISPLAY_CS_PORT,  DISPLAY_CS_PIN,  HAL_GPIO_MODE_OUTPUT_PP },
        { DISPLAY_A0_PORT,  DISPLAY_A0_PIN,  HAL_GPIO_MODE_OUTPUT_PP }
    };

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

    // Inicialitza els pins
    //
    halGPIOInitializePins(gpioInit, sizeof(gpioInit) / sizeof(gpioInit[0]));

    // Genera la senyal de reset
    //
    halGPIOClearPin(DISPLAY_RST_PORT, DISPLAY_RST_PIN);  // RST = 0
    halGPIOSetPin(DISPLAY_RST_PORT, DISPLAY_RST_PIN);  // RST = 1

    // Envia la sequencia d'inicialitzacio al display
    //
    for (unsigned i = 0; i < sizeof(initTab) / sizeof(initTab[0]); i++)
        writeCtrlRegister(initTab[i]);

    // Inicialitza la ram de video
    //
    for (unsigned i = 0; i < screenWidth * screenHeight / 8; i++)
        vRam[i] = 0x00;
    for (unsigned i = 0; i < screenHeight / 8; i++)
        vFlags[i] = 0xFF;
}


void ST7565Driver::shutdown() {

    writeCtrlRegister(CMD_DISPLAY_OFF);
    writeCtrlRegister(CMD_ALL_ON);
    halGPIOClearPin(DISPLAY_RST_PORT, DISPLAY_RST_PIN);  // RST = 0
}


void ST7565Driver::displayOn() {

}


void ST7565Driver::displayOff() {

}


void ST7565Driver::setOrientation(
    DisplayOrientation orientation) {

    if (this->orientation != orientation) {

    }
}


/// ----------------------------------------------------------------------
/// \brief    Borrat de la pantalla.
/// \param    color: El color de borrat.
///
void ST7565Driver::clear(
    const Color& color) {

    uint8_t c = (color == (color_t)0) ? 0xFF : 0x00;

    for (unsigned i = 0; i < screenWidth * screenHeight / 8; i++)
        vRam[i] = c;
    for (unsigned i = 0; i < screenHeight / 8; i++)
        vFlags[i] = 0xFF;
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un pixel.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \param    color: Color del pixel.
///
void ST7565Driver::setPixel(
    int x,
    int y,
    const Color &color) {

	if ((x >= 0) && (x < screenWidth) && (y >= 0) && (y < screenHeight)) {

        int offset = ((y >> 3) * screenWidth) + x;
        uint8_t pix = 1 << (y & 7);
        if (color == (color_t)0)
            vRam[offset] |= pix;
        else
            vRam[offset] &= ~pix;

        vFlags[y >> 3] |= 0b10000000 >> (x >> 4);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia de pixels horitzontals.
/// \param    x : Coordinada X.
/// \param    y: Colordinada Y.
/// \param    size: Longitut de la linia.
/// \param    color: Color dels pixels.
///
void ST7565Driver::setHPixels(
	int x,
	int y,
	int size,
	const Color &color) {

    int x1 = x;
    int x2 = x + size - 1;

    if ((y >= 0) && (y < screenHeight)) {

        if (x1 > x2)
            Math::swap(x1, x2);

        if (x1 < 0)
            x1 = 0;
        else if (x1 >= screenWidth)
            x1 = screenWidth - 1;

        if (x2 < 0)
            x2 = 0;
        else if (x2 >= screenWidth)
            x2 = screenWidth - 1;


        if (color == (color_t)0) {
            while (x1 <= x2) {
                vRam[((y >> 3) * screenWidth) + x1] &= ~(1 << (y & 7));
                vFlags[y >> 3] |= 0b10000000 >> (x1 >> 4);
                x1++;
            }
        }
        else {
            while (x1 <= x2) {
                vRam[((y >> 3) * screenWidth) + x1] |= (1 << (y & 7));
                vFlags[y >> 3] |= 0b10000000 >> (x1 >> 4);
                x1++;
            }
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia de pixels en vertical.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \param    size: Longitut de la linia.
/// \param    color: Color dels pixels.
///
void ST7565Driver::setVPixels(
	int x,
	int y,
	int size,
	const Color &color) {

    int y1 = y;
    int y2 = y1 + size - 1;

    if ((x >= 0) && (x < screenWidth)) {

        // Normalitza la coordinada
        //
        if (y1 > y2)
            Math::swap(y1, y2);

        // Retalla a la pantalla
        //
        if (y1 < 0)
            y1 = 0;
        else if (y1 >= screenHeight)
            y1 = screenHeight - 1;

        if (y2 < 0)
            y2 = 0;
        else if (y2 >= screenHeight)
            y2 = screenHeight - 1;

        // Dibuixa als pixels
        //
        if (color == (color_t)0) {
            while (y1 <= y2) {
                vRam[((y1 >> 3) * screenWidth) + x] &= ~(1 << (y1 & 7));
                vFlags[y1 >> 3] |= 0b10000000 >> (x >> 4);
                y1++;
            }
        }
        else {
            while (y1 <= y2) {
                vRam[((y1 >> 3) * screenWidth) + x] |= (1 << (y1 & 7));
                vFlags[y1 >> 3] |= 0b10000000 >> (x >> 4);
                y1++;
            }
        }
    }
}


void ST7565Driver::setPixels(
    int x,
    int y,
    int width,
    int height,
    const Color &color) {

}

void ST7565Driver::writePixels(
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


void ST7565Driver::readPixels(
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


void ST7565Driver::vScroll(
    int delta,
    int x,
    int y,
    int width,
    int height) {

}


void ST7565Driver::hScroll(
    int delta,
    int x,
    int y,
    int width,
    int height) {

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
                        writeDataRegister(vRam[offset + j + i]);
                }
                mask >>= 1;
            }
            vFlags[page] = 0b00000000;
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la pagina.
/// \param    page: Numero de pagina.
///
void ST7565Driver::setPage(
    uint8_t page) {

    writeCtrlRegister((page & 0x07) | CMD_SET_PAGE);
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la columna.
/// \param    page: Numero de columna.
///
void ST7565Driver::setColumn(
    uint8_t column) {

    writeCtrlRegister((column & 0x0F) | CMD_SET_COLUMN_L);
    writeCtrlRegister((column >> 4) | CMD_SET_COLUMN_H);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte en el registre de dades.
/// \param    data: El valor a escriure.
///
void ST7565Driver::writeDataRegister(
    uint8_t data) {

    halGPIOSetPin(DISPLAY_A0_PORT, DISPLAY_A0_PIN);
    halGPIOClearPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
    writeRegister(data);
    halGPIOSetPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte en el registre de control.
/// \param    cmd: El valor a escriure.
///
void ST7565Driver::writeCtrlRegister(
    uint8_t cmd) {

    halGPIOClearPin(DISPLAY_A0_PORT, DISPLAY_A0_PIN);
    halGPIOClearPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
    writeRegister(cmd);
    halGPIOSetPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);

    // Retard per procesar la comanda
    //
    uint8_t i;
    for (i = 0; i < 10; i++)
        continue;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte en el registre del controlador.
/// \param    data: El byte a escriure.
/// \remarks  El controlador ha d'estar configurat per
///           rebre el byte en el registre correcte.
///
void ST7565Driver::writeRegister(
    uint8_t data) {

}
