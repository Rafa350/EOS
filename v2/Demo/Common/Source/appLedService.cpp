#include "eos.h"
#include "System/Core/eosTask.h"
#include "appLedService.h"


using namespace eos;
using namespace htl;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
///
LedService::LedService() :
	 AppLoopService() {
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio de la tasca.
///
void LedService::onSetup() {

	#ifdef EXIST_LED1
		PinLED1::initOutput(GPIODriver::pushPull);
		PinLED1::write(_ledON);
	#endif
	#ifdef EXIST_LED2
		PinLED2::initOutput(GPIODriver::pushPull);
		PinLED2::write(_ledOFF);
	#endif
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedService::onLoop() {

	while (true) {

		Task::delay(500);

		#ifdef EXIST_LED1
			PinLED1::toggle();
		#endif
		#ifdef EXIST_LED2
			PinLED2::toggle();
		#endif
	}
}
