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

	_frameBuffer(frameBuffer),
    _pages(_displayHeight / 8),
	_columns(_displayWidth) {
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
    int x,
    int y,
    int width,
    int height,
    const void *pixels,
    ColorFormat format,
    int pitch) {

	_frameBuffer->setPixels(x, y, width, height, pixels, format, pitch);
}


/// ----------------------------------------------------------------------
/// \brief    Transfereix el buffer d'imatge al controlador
///
void DisplayDriver_SSD1306::refresh() {

	const uint8_t *buffer = reinterpret_cast<const uint8_t*>(_frameBuffer->getBuffer());

    for (int page = 0; page < _pages; page++) {

    	writeCommand(0xB0 + page); // Set the current page.
        writeCommand(0x00);        // Set first column (LO nibble)
        writeCommand(0x10);        // Set first column (HI nibble)

        writeData(&buffer[page * _columns], _columns);
    }
}


/// ----------------------------------------------------------------------
/// \brief     Inicialitza l'interficie amb el controlador.
///
#if defined(DISPLAY_INTERFACE_SPI)
void DisplayDriver_SSD1306::initializeInterface() {

	// Inicialitza modul GPIO
	//
	PinCS::initOutput(GPIODriver::pushPull, GPIOSpeed::fast);
	PinCS::set();
	PinDC::initOutput(GPIODriver::pushPull, GPIOSpeed::fast);
	PinRST::initOutput(GPIODriver::pushPull, GPIOSpeed::low);
	PinRST::clear();

	// Inicialitza el modul SPI
	//
	Spi::initSCKPin<PinSCK>();
	Spi::initMOSIPin<PinMOSI>();
	Spi::initialize(SPIMode::master, SPIClkPolarity::low, SPIClkPhase::edge1, SPISize::_8, SPIFirstBit::msb, SPIClockDivider::_128);
}
#else
#error "DISPLAY_INTERFACE_XXXX"
#endif


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el controlador.
///
void DisplayDriver_SSD1306::initializeController() {

	// Reseteja el controlador
	//
	PinRST::clear();
	halTMRDelay(10);
	PinRST::set();
	halTMRDelay(150);

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
#if defined (DISPLAY_INTERFACE_SPI)
void DisplayDriver_SSD1306::writeCommand(
    uint8_t cmd) {

	PinCS::clear();
	PinDC::clear();

#if 1
	Spi::send(&cmd, sizeof(cmd));
#else
	Spi::write8(cmd);
	while (!Spi::getInterruptFlag(SPIEvent::txEmpty))
		continue;
#endif

	PinCS::set();
}
#else
#error "Undefined DISPLAY_INTERFACE_XXXX"
#endif


/// ----------------------------------------------------------------------
/// \brief    Escriu una sequencia de bytes de dades en el display.
/// \param    data: Buffer de dades.
/// \param    length: Longitut de les dades en bytes.
///
#if defined(DISPLAY_INTERFACE_SPI)
void DisplayDriver_SSD1306::writeData(
    const uint8_t* data,
	int length) {

	PinCS::clear();
	PinDC::set();
#if 1
	Spi::send(data, length);
#else
	Spi::write8(cmd);
	while (!Spi::getInterruptFlag(SPIEvent::txEmpty))
		continue;
#endif
	PinCS::clear();
}
#else
#error "Undefined DISPLAY_INTERFACE_XXXX"
#endif

