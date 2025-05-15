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
using namespace app;


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
	pinCS->initOutput(htl::gpio::OutputMode::pushPull, htl::gpio::Speed::high, true);

	auto pinDC = DISPLAY_DC_Pin::pInst;
	pinCS->initOutput(htl::gpio::OutputMode::pushPull, htl::gpio::Speed::high, false);

	auto pinRST = DISPLAY_RST_Pin::pInst;
	pinCS->initOutput(htl::gpio::OutputMode::pushPull, htl::gpio::Speed::high, false);

	auto devSPI = ARDUINO_SPI_Device::pInst;
    devSPI->initPinSCK<DISPLAY_SCK_Pin>();
    devSPI->initPinMOSI<DISPLAY_MOSI_Pin>();
    devSPI->initialize(htl::spi::Mode::master, htl::spi::ClkPolarity::high, htl::spi::ClkPhase::edge1, htl::spi::WordSize::_8, htl::spi::FirstBit::msb, htl::spi::ClockDivider::_8);

	auto device = new Device_SSD1306_SPI(pinCS, pinDC, pinRST, devSPI);

	FrameBuffer *frameBuffer = new MonoFrameBuffer(
		_displayWidth,
		_displayHeight,
		DisplayOrientation::normal,
		reinterpret_cast<uint8_t*>(_displayBuffer),
		_displayWidth,
		MonoFrameBuffer::Mapping::vertical);

	_driver = new DisplayDriver_SSD1306(device, frameBuffer);
	_driver->initialize();
	_driver->clear(Colors::black);
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
