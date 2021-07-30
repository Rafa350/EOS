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

	_graphics = new Graphics(_driver);
	_graphics->clear(COLOR_Black);
}

/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio del servei.
///
void DisplayService::onLoop() {

	Task::delay(1000);
	_graphics->clear(COLOR_Black);
	_graphics->drawEllipse(10, 10, 118, 54, COLOR_White);
	_driver->refresh();
}
