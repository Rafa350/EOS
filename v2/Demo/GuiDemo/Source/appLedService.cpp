#include "eos.h"
#include "HAL/halGPIO.h"
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
	_led1.initOutput(GPIOSpeed::low, GPIODriver::pushPull);
#endif
#ifdef EXIST_LEDS_LED2
	_led2.initOutput(GPIOSpeed::low, GPIODriver::pushPull);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedService::onLoop() {

	while (true) {

#ifdef EXIST_LEDS_LED1
		_led1.toggle();
#endif
#ifdef EXIST_LEDS_LED2
		_led2.toggle();
#endif

		Task::delay(500);
	}
}
