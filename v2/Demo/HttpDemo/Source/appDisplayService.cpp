#include "eos.h"
#include "Controllers/Display/Drivers/eosRGBLTDC.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"
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
	graphics(nullptr) {
}


///-----------------------------------------------------------------------
/// \brief Process la inicialitzacio de la tasca.
///
void DisplayService::onSetup() {

	driver = new RGBDirectDriver();
    driver->initialize();
    driver->displayOn();

    graphics = new eos::Graphics(driver);
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void DisplayService::onLoop() {

    Task::delay(5000);
}
