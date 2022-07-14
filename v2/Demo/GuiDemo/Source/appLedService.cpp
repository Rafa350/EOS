#include "eos.h"
#include "HTL/htlGPIO.h"
#include "System/Core/eosTask.h"
#include "appLedService.h"


using namespace eos;
using namespace htl;
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
		GPIO_LED1::initOutput(GPIODriver::pushPull, GPIOSpeed::low);
	#endif
	#ifdef EXIST_LEDS_LED2
		GPIO_LED2::initOutput(GPIODriver::pushPull, GPIOSpeed::low);
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
