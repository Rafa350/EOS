#include "eos.h"
#include "htl/htlGPIO.h"
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
		auto hPinLED1 = LED1_Pin::getHandler();
		hPinLED1->initOutput(gpio::OutputMode::pushPull, gpio::Speed::low, LED1_StateON);
	#endif

	#ifdef EXIST_LED2
		auto hPinLED2 = LED2_Pin::getHandler();
		hPinLED2->initOutput(gpio::OutputMode::pushPull, gpio::Speed::low, LED1_StateOFF);
	#endif
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedService::onTask() {

	Task::delay(500);

	#ifdef EXIST_LED1
	auto hPinLED1 = LED1_Pin::getHandler();
	hPinLED1->toggle();
	#endif
	#ifdef EXIST_LED2
	auto hPinLED2 = LED2_Pin::getHandler();
	hPinLED2->toggle();
	#endif
}
