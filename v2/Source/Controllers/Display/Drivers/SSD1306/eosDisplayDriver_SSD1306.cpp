#include "eos.h"
#include "eosAssert.h"
#include "HTL/htlTick.h"
#include "HTL/htlINT.h"
#include "Controllers/Display/eosMonoFrameBuffer.h"
#include "Controllers/Display/Drivers/SSD1306/eosDisplayDriver_SSD1306.h"
#include "System/Core/eosTask.h"

using namespace eos;
using namespace htl;


static void delay(
	uint32_t time) {

	if (time > 0) {
		auto tick = tick::Tick::getHandler();
		tick->wait(time);
	}
}


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

    constexpr int8_t pages = _displayHeight / 8;
	const uint8_t *buffer = _frameBuffer->getBuffer();

    for (int8_t page = 0; page < pages; page++) {

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

	// Inicialitza el pin CS
	//
	auto pinCS = PinCS::getHandler();
	pinCS->initOutput(gpio::OutDriver::pushPull, gpio::Speed::fast, true);

	// Inicialitza el pin DC
	//
	auto pinDC = PinDC::getHandler();
	pinDC->initOutput(gpio::OutDriver::pushPull, gpio::Speed::fast);

	// Inicialitza el pin RST
	//
	#ifdef DISPLAY_RST_Pin
	auto pinRST = PinRST::getHandler();
	pinRST->initOutput(gpio::OutDriver::pushPull, gpio::Speed::low, false);
	#endif

	// Inicialitza el modul SPI
	//
	auto spi = SpiDevice::getHandler();
	spi->initSCKPin<PinSCK>();
	spi->initMOSIPin<PinMOSI>();
	spi->initialize(spi::SPIMode::master, _spiClkPolarity, _spiClkPhase,
		spi::WordSize::_8, spi::FirstBit::msb, _spiClockDivider);
	spi->enable();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el controlador.
///
void DisplayDriver_SSD1306::initializeController() {

	// Reseteja el controlador
	//
	#ifdef DISPLAY_RST_Pin
	auto pinRST = PinRST::getHandler();
	pinRST->clear();
	delay(100);
	pinRST->set();
	delay(300);
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

	auto pinCS = PinCS::getHandler();
	auto pinDC = PinDC::getHandler();
	auto spi = SpiDevice::getHandler();

	pinCS->clear();
	pinDC->clear();

	spi->transmit(&cmd, 1);

	pinCS->set();
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

	auto pinCS = PinCS::getHandler();
	auto pinDC = PinDC::getHandler();
	auto spi = SpiDevice::getHandler();

	pinCS->clear();
	pinDC->set();

	spi->transmit(data, length);

	pinCS->clear();
}
#endif

