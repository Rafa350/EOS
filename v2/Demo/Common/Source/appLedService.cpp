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
		auto pinLED1 = LED1_Pin::getHandler();
		pinLED1->initOutput(gpio::OutDriver::pushPull, gpio::Speed::low, gpio::InitPinState::set);
	#endif

	#ifdef EXIST_LED2
		auto pinLED2 = LED2_Pin::getHandler();
		pinLED2->initOutput(GPIODriver::pushPull, GPIOSpeed::low, GPIOInitPinState::clear);
	#endif
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedService::onTask() {

	Task::delay(500);

	#ifdef EXIST_LED1
	auto pinLED1 = LED1_Pin::getHandler();
	pinLED1->toggle();
	#endif
	#ifdef EXIST_LED2
	auto pinLED2 = LED2_Pin::getHandler();
	pinLED2->toggle();
	#endif
}
