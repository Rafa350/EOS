#include "eos.h"
#include "Controllers/Display/Drivers/SSD1306/eosDevice_SSD1306.h"
#include "Controllers/Display/Drivers/SSD1306/eosDisplayDriver_SSD1306.h"
#include "Controllers/Display/eosMonoFrameBuffer.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"
#include "appDisplayService.h"


using namespace eos;
using namespace htl;
using namespace app;


static const uint8_t __displayInitScript[] = {
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


/// ----------------------------------------------------------------------
/// \brief    Constructor:
/// \param    application: L'aplicacio.
///
DisplayService::DisplayService() {
}


/// ----------------------------------------------------------------------
/// \brief    : Inicialitza el servei.
///
void DisplayService::onExecute() {

	auto pinCS = DISPLAY_CS_Pin::pInst;
	pinCS->initOutput(gpio::OutputType::pushPull, gpio::PullUpDown::none, gpio::Speed::high, true);

	auto pinDC = DISPLAY_DC_Pin::pInst;
	pinCS->initOutput(gpio::OutputType::pushPull, gpio::PullUpDown::none, gpio::Speed::high, false);

	auto pinRST = DISPLAY_RST_Pin::pInst;
	pinCS->initOutput(gpio::OutputType::pushPull, gpio::PullUpDown::none, gpio::Speed::high, false);

	auto devSPI = ARDUINO_SPI_Device::pInst;
    devSPI->initPinSCK<DISPLAY_SCK_Pin>();
    devSPI->initPinMOSI<DISPLAY_MOSI_Pin>();
    devSPI->initialize(spi::Mode::master, spi::ClkPolarity::low, spi::ClkPhase::edge1,
    	spi::WordSize::ws8, spi::FirstBit::msb, spi::ClockDivider::div128);

	auto device = new Device_SSD1306_SPI(pinCS, pinDC, pinRST, devSPI);
	device->initialize(__displayInitScript, sizeof(__displayInitScript));

	FrameBuffer *frameBuffer = new MonoFrameBuffer(
		_displayWidth,
		_displayHeight,
		DisplayOrientation::normal,
		reinterpret_cast<uint8_t*>(_displayBuffer),
		_displayWidth,
		MonoFrameBuffer::Mapping::vertical);

	_driver = new DisplayDriver_SSD1306(device, frameBuffer);
	_driver->initialize();
	_driver->clear(Colors::white);
	_driver->enable();

	_graphics = new Graphics(_driver);

	static int count = 0;

	while (!stopSignal()) {

		Task::delay(500);

		_graphics->clear(Colors::black);

		switch (count & 0x3) {
			case 0:
				_graphics->drawRectangle(0, 0, 127, 63, Colors::white);
				_graphics->fillEllipse(10, 10, 20, 20, Colors::white);
				_graphics->fillEllipse(107, 43, 117, 53, Colors::white);
				break;
			case 1:
				_graphics->drawEllipse(20, 20, 118, 54, Colors::white);
				break;
			case 2:
				_graphics->drawEllipse(30, 30, 118, 54, Colors::white);
				break;
			case 3:
				_graphics->drawEllipse(40, 40, 118, 54, Colors::white);
				break;
		}

		_driver->refresh();

		count++;
	}
}
