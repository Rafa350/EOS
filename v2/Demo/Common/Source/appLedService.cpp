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
		LED1_Pin::pInst->initOutput(gpio::OutputMode::pushPull, gpio::Speed::low, LED1_StateON);
	#endif

	#ifdef EXIST_LED2
		LED2_Pin::pInst->initOutput(gpio::OutputMode::pushPull, gpio::Speed::low, LED1_StateOFF);
	#endif
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedService::onTask() {

	Task::delay(500);

	#ifdef EXIST_LED1
	LED1_Pin::pInst->toggle();
	#endif
	#ifdef EXIST_LED2
	LED2_Pin::pInst->toggle();
	#endif
}
