#include "eos.h"
#include "htl/htlGPIO.h"
#include "Services/eosLedService.h"
#include "System/Core/eosTask.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
///
LedService::LedService(
     Pin *pinLED1,
     Pin *pinLED2) :

	 Service(),
	 _pinLED1 {pinLED1},
	 _pinLED2 {pinLED2} {
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio de la tasca.
///
void LedService::onInitialize() {

}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedService::onTask() {

	Task::delay(500);

	if (_pinLED1 != nullptr)
	    _pinLED1->toggle();

	if (_pinLED2 != nullptr)
	    _pinLED2->toggle();
}
