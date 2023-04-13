#include "eos.h"
#include "eosAssert.h"
#include "HAL/halTMR.h"
#include "Controllers/Display/eosMonoFrameBuffer.h"
#include "Controllers/Display/Drivers/SSD1306/eosDisplayDriver_SSD1306.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
DisplayDriver_SSD1306::DisplayDriver_SSD1306(
	FrameBuffer *frameBuffer):

	_frameBuffer(frameBuffer) {
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
void DisplayDriver_SSD1306::deinitialize() {

	disable();
}


/// ----------------------------------------------------------------------
/// \brief    Encen el display
///
void DisplayDriver_SSD1306::enable() {

	writeCommand(0xAF);
}


/// ----------------------------------------------------------------------
/// \brief    Apaga el display
///
void DisplayDriver_SSD1306::disable() {

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
    int16_t x,
    int16_t y,
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
    int16_t x,
    int16_t y,
    int16_t size,
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
    int16_t x,
    int16_t y,
    int16_t size,
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
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height,
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
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height,
    const Color *color,
	int16_t pitch) {

	_frameBuffer->setPixels(x, y, width, height, color, pitch);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una regio rectangular.
/// \param    x: Posicio x de la regio.
/// \param    y: Posicio y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    pixels: Punter als colors.
/// \param    format: Format de color
/// \param    pitch: Pitch dels colors.
///
void DisplayDriver_SSD1306::setPixels(
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height,
    const void *pixels,
    ColorFormat format,
    int16_t pitch) {

	_frameBuffer->setPixels(x, y, width, height, pixels, format, pitch);
}


/// ----------------------------------------------------------------------
/// \brief    Transfereix el buffer d'imatge al controlador
///
void DisplayDriver_SSD1306::refresh() {

    constexpr int16_t pages = _displayHeight / 8;
	const uint8_t *buffer = reinterpret_cast<const uint8_t*>(_frameBuffer->getBuffer());

    for (int16_t page = 0; page < pages; page++) {

    	writeCommand(0xB0 + page); // Set the current page.
        writeCommand(0x00);        // Set first column (LO nibble)
        writeCommand(0x10);        // Set first column (HI nibble)

        writeData(&buffer[page * _displayWidth], _displayWidth);
    }
}


/// ----------------------------------------------------------------------
/// \brief     Inicialitza l'interficie amb el controlador.
///
#ifdef DISPLAY_INTERFACE_SPI
void DisplayDriver_SSD1306::initializeInterface() {

	// Inicialitza modul GPIO
	//
	PinCS::initOutput(GPIODriver::pushPull, GPIOSpeed::fast, GPIOInitPinState::set);
	PinDC::initOutput(GPIODriver::pushPull, GPIOSpeed::fast);
	#ifdef DISPLAY_RST_GPIO
	PinRST::initOutput(GPIODriver::pushPull, GPIOSpeed::low, GPIOInitPinState::clear);
	#endif

	// Inicialitza el modul SPI
	//
	Spi::initSCKPin<PinSCK>();
	Spi::initMOSIPin<PinMOSI>();
	Spi::initialize(SPIMode::master, SPIClkPolarity::low, SPIClkPhase::edge1, SPISize::_8, SPIFirstBit::msb, SPIClockDivider::_4);
	Spi::enable();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el controlador.
///
void DisplayDriver_SSD1306::initializeController() {

	// Reseteja el controlador
	//
	#ifdef DISPLAY_RST_GPIO
	PinRST::clear();
	halTMRDelay(10);
	PinRST::set();
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
#ifdef DISPLAY_INTERFACE_SPI
void DisplayDriver_SSD1306::writeCommand(
    uint8_t cmd) {

	PinCS::clear();
	PinDC::clear();

	Spi::write8(cmd);
	while (!Spi::getFlag(SPIFlag::txEmpty))
		continue;
	while (Spi::getFlag(SPIFlag::busy))
		continue;

	PinCS::set();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Escriu una sequencia de bytes de dades en el display.
/// \param    data: Buffer de dades.
/// \param    length: Longitut de les dades en bytes.
///
#ifdef DISPLAY_INTERFACE_SPI
void DisplayDriver_SSD1306::writeData(
    const uint8_t* data,
	int length) {

	PinCS::clear();
	PinDC::set();

	while (length--) {
		Spi::write8(*data++);
		while (!Spi::getFlag(SPIFlag::txEmpty))
			continue;
	}
	while (Spi::getFlag(SPIFlag::busy))
		continue;

	PinCS::clear();
}
#endif

