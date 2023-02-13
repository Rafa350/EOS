#include "eos.h"
#include "Controllers/Display/Drivers/SSD1306/eosDisplayDriver_SSD1306.h"
#include "Controllers/Display/eosMonoFrameBuffer.h"
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
void DisplayService::onSetup() {

	FrameBuffer *frameBuffer = new MonoFrameBuffer(
		_displayWidth,
		_displayHeight,
		DisplayOrientation::normal,
		(void*) _displayBuffer,
		_displayWidth);

	_driver = new DisplayDriver_SSD1306(frameBuffer);
	_driver->initialize();
	_driver->clear(Colors::black);
	_driver->enable();

	_graphics = new Graphics(_driver);
}


/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio del servei.
///
void DisplayService::onLoop() {

	static int count = 0;

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
