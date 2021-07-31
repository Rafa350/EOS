#include "eos.h"
#include "System/Core/eosTask.h"
#include "appLedService.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Contructor de l'objecte.
/// \param    application: L'aplicacio.
///
LedService::LedService(
	Application* application) :

	AppLoopService(application) {
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio de la tasca.
///
void LedService::onSetup() {

#ifdef EXIST_LEDS_LED1
	led1.initialize(HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR);
#endif
#ifdef EXIST_LEDS_LED2
	led2.initialize(HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_SET);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedService::onLoop() {

	unsigned weakTime = Task::getTickCount();

	while (true) {

		Task::delay(500, weakTime);

#ifdef EXIST_LEDS_LED1
		led1.toggle();
#endif
#ifdef EXIST_LEDS_LED2
		led2.toggle();
#endif
	}
}
