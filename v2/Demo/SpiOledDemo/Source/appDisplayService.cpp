#include "eos.h"
#include "Controllers/Display/Drivers/SSD1306/eosDisplayDriver_SSD1306.h"
#include "HAL/halGPIO.h"
#include "HAL/halSPI.h"
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
}

/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio del servei.
///
void DisplayService::onLoop() {

	_driver->refresh();
}
