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

	 AppLoopService(application),
	_pinLED1(PinLED1::instance())
#ifdef EXISTS_LEDS_LED2
	, _pinLED2(PinLED2::instance())
#endif
{
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio de la tasca.
///
void LedService::onSetup() {

#ifdef EXIST_LEDS_LED1
	_pinLED1.initialize(HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR);
#endif
#ifdef EXIST_LEDS_LED2
	_pinLED2.initialize(HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_SET);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedService::onLoop() {

	while (true) {

#ifdef EXIST_LEDS_LED1
		_pinLED1.toggle();
#endif
#ifdef EXIST_LEDS_LED2
		_pinLED2.toggle();
#endif

		Task::delay(500);
	}
}
