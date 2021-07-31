#include "eos.h"
#include "Controllers/Display/Drivers/SSD1306/eosDisplayDriver_SSD1306.h"
#include "HAL/halGPIO.h"
#include "HAL/halSPI.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"
#include "appDisplayService.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor:
/// \param    application: L'aplicacio.
///
DisplayService::DisplayService(
	Application* application) :

	AppLoopService(application) {

}


/// ----------------------------------------------------------------------
/// \brief    : Inicialitza el servei.
///
void DisplayService::onSetup() {

	_driver = new DisplayDriver_SSD1306();
	_driver->initialize();
	_driver->displayOn();

	_graphics = new Graphics(_driver);
	_graphics->clear(COLOR_Black);
}

/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio del servei.
///
void DisplayService::onLoop() {

	static int count = 0;

	Task::delay(1000);

	_graphics->clear(COLOR_Black);

	switch (count & 0x3) {
		case 0:
			_graphics->drawRectangle(0, 0, 127, 63, COLOR_White);
			_graphics->fillEllipse(10, 10, 20, 20, COLOR_White);
			_graphics->fillEllipse(107, 43, 117, 53, COLOR_White);
			break;
		case 1:
			_graphics->drawEllipse(20, 20, 118, 54, COLOR_White);
			break;
		case 2:
			_graphics->drawEllipse(30, 30, 118, 54, COLOR_White);
			break;
		case 3:
			_graphics->drawEllipse(40, 40, 118, 54, COLOR_White);
			break;
	}

	_driver->refresh();

	count++;
}
