#include "eos.h"
#include "Controllers/Display/Drivers/eosRGBLTDC.h"
#include "System/Graphics/eosDisplay.h"
#include "appDisplayService.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte
/// \param application: Aplicacio a la que pertany el servei.
///
DisplayService::DisplayService(
	eos::Application *application):

	eos::AppLoopService(application),
	driver(nullptr),
	display(nullptr) {
}


///-----------------------------------------------------------------------
/// \brief Process la inicialitzacio de la tasca.
///
void DisplayService::onSetup() {

	driver = RGBDirectDriver::getInstance();
    driver->initialize();
    driver->displayOn();

    display = new Display(driver);
    display->clear(COLOR_Blue);
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void DisplayService::onLoop() {

    Task::delay(5000);
}
