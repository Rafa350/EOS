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
	_gpioLED1(LEDS_LED1_PORT, LEDS_LED1_PIN)
#ifdef EXISTS_LEDS_LED2
	, _gpioLED2(LEDS_LED2_PORT, LEDS_LED2_PIN)
#endif
{
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio de la tasca.
///
void LedService::onSetup() {

#ifdef EXIST_LEDS_LED1
	_gpioLED1.setMode(hal::GPIO::OutputMode::output);
	_gpioLED1.set();
#endif
#ifdef EXIST_LEDS_LED2
	_gpioLED2.setMode(hal::GPIO::OutputMode::output);
	_gpioLED2.set();
#endif
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedService::onLoop() {

	while (true) {

#ifdef EXIST_LEDS_LED1
		_gpioLED1.toggle();
#endif
#ifdef EXIST_LEDS_LED2
		_gpioLED2.toggle();
#endif

		Task::delay(500);
	}
}
