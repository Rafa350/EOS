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
	 Service() {
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio de la tasca.
///
void LedService::onInitialize() {

	#ifdef EXIST_LED1
		PinLED1::initOutput(GPIODriver::pushPull, GPIOSpeed::low, GPIOInitState::set);
	#endif
	#ifdef EXIST_LED2
		PinLED2::initOutput(GPIODriver::pushPull, GPIOSpeed::low, GPIOInitState::clear);
	#endif
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedService::onTask() {

	Task::delay(500);

	#ifdef EXIST_LED1
		PinLED1::toggle();
	#endif
	#ifdef EXIST_LED2
		PinLED2::toggle();
	#endif
}
