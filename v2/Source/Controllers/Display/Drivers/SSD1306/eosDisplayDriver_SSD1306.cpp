#include "eos.h"
#include "eosAssert.h"
#include "HAL/halGPIO.h"
#include "HAL/halSPI.h"
#include "HAL/halTMR.h"
#include "Controllers/Display/eosMonoFrameBuffer.h"
#include "Controllers/Display/Drivers/SSD1306/eosDisplayDriver_SSD1306.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
DisplayDriver_SSD1306::DisplayDriver_SSD1306() {

	_frameBuffer = new MonoFrameBuffer(
		_displayWidth,
		_displayHeight,
		DisplayOrientation::normal,
		(void*) DISPLAY_IMAGE_BUFFER,
        _displayWidth);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void DisplayDriver_SSD1306::initialize() {

	initializeInterface();
	initializeController();
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el driver.
///
void DisplayDriver_SSD1306::shutdown() {

	displayOff();
}


/// ----------------------------------------------------------------------
/// \brief    Encen el display
///
void DisplayDriver_SSD1306::displayOn() {

	writeCommand(0xAF);
}


/// ----------------------------------------------------------------------
/// \brief    Apaga el display
///
void DisplayDriver_SSD1306::displayOff() {

	writeCommand(0xAE);
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona l'orientacio.
/// \param    orientation: L'orientacio.
///
void DisplayDriver_SSD1306::setOrientation(
    DisplayOrientation orientation) {

	_frameBuffer->setOrientation(orientation);
}


/// ----------------------------------------------------------------------
/// \brief    Borra la pantalla.
/// \param    color: Color de borrat.
///
void DisplayDriver_SSD1306::clear(
    Color color) {

	_frameBuffer->clear(color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un pixel.
/// \param    x: Coordinada x.
/// \param    y: Coordinada x.
/// \param    color: Color del pixel.
/// \remarks  Si esta fora de limits no dibuixa res.
///
void DisplayDriver_SSD1306::setPixel(
    int x,
    int y,
    Color color) {

	_frameBuffer->setPixel(x, y, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia de pixels horitzontals.
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \param    length: Longitut de la linia.
/// \param    color: Color dels pixels.
/// \remarks  Si esta fora de limits no dibuixa res.
///
void DisplayDriver_SSD1306::setHPixels(
    int x,
    int y,
    int size,
    Color color) {

	_frameBuffer->setPixels(x, y, size, 1, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia de pixels en vertical.
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \param    length: Longitut de la linia.
/// \param    color: Color dels pixels.
/// \remarks  Si esta fora de limits no dibuixa res.
///
void DisplayDriver_SSD1306::setVPixels(
    int x,
    int y,
    int size,
    Color color) {

	_frameBuffer->setPixels(x, y, 1, size, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una regio rectangular.
/// \param    x: Posicio x de la regio.
/// \param    y: Posicio y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    color: Color.
///
void DisplayDriver_SSD1306::setPixels(
    int x,
    int y,
    int width,
    int height,
    Color color) {

	_frameBuffer->setPixels(x, y, width, height, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una regio rectangular.
/// \param    x: Posicio x de la regio.
/// \param    y: Posicio y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    color: Punter als colors.
/// \param    pitch: Pitch dels colors.
///
void DisplayDriver_SSD1306::setPixels(
    int x,
    int y,
    int width,
    int height,
    const Color* color,
	int pitch) {

	_frameBuffer->setPixels(x, y, width, height, color, pitch);
}


void DisplayDriver_SSD1306::writePixels(
    int x,
    int y,
    int width,
    int height,
    const void *pixels,
    ColorFormat format,
    int pitch) {

}


void DisplayDriver_SSD1306::readPixels(
    int x,
    int y,
    int width,
    int height,
    void *pixels,
    ColorFormat format,
    int pitch) {

}

void DisplayDriver_SSD1306::vScroll(
    int delta,
    int x,
    int y,
    int width,
    int height) {

}

void DisplayDriver_SSD1306::hScroll(
    int delta,
    int x,
    int y,
    int width,
    int height) {

}


/// ----------------------------------------------------------------------
/// \brief    Transfereix el buffer d'imatge al controlador
///
void DisplayDriver_SSD1306::refresh() {

    for (int page = 0; page < _displayHeight / 8; page++) {

    	writeCommand(0xB0 + page); // Set the current page.
        writeCommand(0x00);        // Set first column (LO nibble)
        writeCommand(0x10);        // Sit first column (HI nibble)

        const uint8_t* buffer = (const uint8_t*) DISPLAY_IMAGE_BUFFER;
        writeData(&buffer[page * _displayWidth], _displayWidth);
    }
}


/// ----------------------------------------------------------------------
/// \brief     Inicialitza l'interficie amb el controlador.
///
void DisplayDriver_SSD1306::initializeInterface() {

	// Inicialitza modul GPIO
	//
	static const GPIOPinSettings gpioSettings[] = {
#ifdef DISPLAY_RST_PIN
		{ DISPLAY_RST_PORT,    DISPLAY_RST_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_PULL_NONE | HAL_GPIO_INIT_CLR, 0 },
#endif
		{ DISPLAY_CS_PORT,     DISPLAY_CS_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_FAST | HAL_GPIO_INIT_SET, 0 },
		{ DISPLAY_DC_PORT,     DISPLAY_DC_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_FAST | HAL_GPIO_INIT_CLR, 0 },
		{ DISPLAY_CLK_PORT,    DISPLAY_CLK_PIN,
			HAL_GPIO_MODE_ALT_PP | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_FAST, DISPLAY_CLK_AF },
		{ DISPLAY_MOSI_PORT,   DISPLAY_MOSI_PIN,
			HAL_GPIO_MODE_ALT_PP | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_FAST, DISPLAY_MOSI_AF},
	};
	halGPIOInitializePins(gpioSettings, sizeof(gpioSettings) / sizeof(gpioSettings[0]));

#if (DISPLAY_SSD1306_INTERFACE == DISPLAY_SSD1306_INTERFACE_SPI)

	// Inicialitza el modul SPI
	//
	static const SPISettings spiSettings = {
		DISPLAY_SPI_CHANNEL,
			HAL_SPI_MODE_0 | HAL_SPI_SIZE_8 | HAL_SPI_MS_MASTER |
			HAL_SPI_FIRSTBIT_MSB | HAL_SPI_CLOCKDIV_128, 0, 0
	};
	_hSpi = halSPIInitialize(&_spiData, &spiSettings);

#else
#error "DISPLAY_SSD1306_INTERFACE"
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el controlador.
///
void DisplayDriver_SSD1306::initializeController() {

#ifdef DISPLAY_RST_PORT

	// Reseteja el controlador
	//
    halGPIOClearPin(DISPLAY_RST_PORT, DISPLAY_RST_PIN);
    halTMRDelay(10);
    halGPIOSetPin(DISPLAY_RST_PORT, DISPLAY_RST_PIN);
    halTMRDelay(150);

#endif

    // Inicialitza el controlador
    //
    static const uint8_t initSequence[] = {
		// Turn off display
		0xAE,

		// Set addrerssing mode
		0x20, 0x00,

		// Set display clock divider
		0xD5, 0x80,

		// Set multiplex ratio
		0xA8, 0x3F,

		// Set charge pump
		0x8D, 0x14,

		// Set start line address
		0x40,

		// Set display offset
		0xD3, 0x00,

		// Set normal/inverted display
		0xA6,

		// Set entire display enable
		0xA4,

		// Set column address remap
		//
		0xA1,

		// Set COM Output Scan Direction 64 to 0
		0xC8,

		// Set com pins hardware configuration
		0xDA, 0x12,

		// Set contrast control register
		0x81, 0xCF,

		// Set pre-charge period
		0xD9, 0xF1,

		// Set VCOMH
		0xDB, 0x40,

		// Turn ON display
		0xAF
	};
	for (int i = 0; i < (int)(sizeof(initSequence) / sizeof(initSequence[0])); i++)
		writeCommand(initSequence[i]);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte de comanda en el display.
/// \param    cmd: La comanda.
///
void DisplayDriver_SSD1306::writeCommand(
    uint8_t cmd) {

#if (DISPLAY_SSD1306_INTERFACE == DISPLAY_SSD1306_INTERFACE_SPI)
	halGPIOClearPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
	halGPIOClearPin(DISPLAY_DC_PORT, DISPLAY_DC_PIN);
	halSPISendBuffer(_hSpi, &cmd, sizeof(cmd));
	halGPIOSetPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
#else
#error "DISPLAY_SSD1306_INTERFACE"
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Escriu una sequencia de bytes de dades en el display.
/// \param    data: Buffer de dades.
/// \param    length: Longitut de les dades en bytes.
///
void DisplayDriver_SSD1306::writeData(
    const uint8_t* data,
	int length) {

#if (DISPLAY_SSD1306_INTERFACE == DISPLAY_SSD1306_INTERFACE_SPI)
	halGPIOClearPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
	halGPIOSetPin(DISPLAY_DC_PORT, DISPLAY_DC_PIN);
	halSPISendBuffer(_hSpi, data, length);
	halGPIOSetPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
#else
#error "DISPLAY_SSD1306_INTERFACE"
#endif
}

