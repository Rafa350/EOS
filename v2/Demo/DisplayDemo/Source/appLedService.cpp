#include "eos.h"
#include "System/Core/eosTask.h"
#include "appLedService.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
///
LedService::LedService(
	Application *pApplication) :

	AppLoopService(pApplication) {
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio de la tasca.
///
void LedService::onSetup() {

#ifdef EXIST_LEDS_LED1
	_pinLed1.initialize(HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR);
#endif
#ifdef EXIST_LEDS_LED2
	_pinLed2.initialize(HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_SET);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedService::onLoop() {

	while (true) {

#ifdef EXIST_LEDS_LED1
		_pinLed1.toggle();
#endif
#ifdef EXIST_LEDS_LED2
		_pinLed2.toggle();
#endif

		Task::delay(500);
	}
}
