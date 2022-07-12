#include "eos.h"
#include "System/Core/eosTask.h"
#include "appLedService.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
///
LedService::LedService(
	Application *application) :

	 AppLoopService(application) {
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio de la tasca.
///
void LedService::onSetup() {

#ifdef EXIST_LEDS_LED1
	GPIO_LED1::initOutput(htl::GPIODriver::pushPull);
	GPIO_LED1::set();
#endif
#ifdef EXIST_LEDS_LED2
	GPIO_LED2::initOutput(htl::GPIODriver::pushPull);
	GPIO_LED2::clear();
#endif
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedService::onLoop() {

	while (true) {

#ifdef EXIST_LEDS_LED1
		GPIO_LED1::toggle();
#endif
#ifdef EXIST_LEDS_LED2
		GPIO_LED2::toggle();
#endif

		Task::delay(500);
	}
}
