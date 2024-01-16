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
/// \brief Procesa l'inici d'execucio de la tasca.
///
bool LedService::onTaskStart() {

    if (_pinLED1 != nullptr)
        _pinLED1->set();
    if (_pinLED2 != nullptr)
        _pinLED2->clear();

    _weakTime = Task::getTickCount();

    return true;
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
bool LedService::onTask() {

    if (_pinLED1 != nullptr)
        _pinLED1->toggle();

    if (_pinLED2 != nullptr)
        _pinLED2->toggle();

    Task::delay(500, _weakTime);

    return true;
}
