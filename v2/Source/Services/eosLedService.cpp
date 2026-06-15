#include "eos.h"
#include "HTL/htlGPIO.h"
#include "RTOS/rtosTime.h"
#include "RTOS/rtosTask.h"
#include "Services/eosLedService.h"
#include "System/eosTime.h"


using namespace eos;
using namespace htl;


constexpr const char *serviceName = "Led";
constexpr uint32_t serviceStackDepth = 96;
constexpr rtos::Task::Priority servicePriority = rtos::Task::Priority::low;


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
/// \brief    Inicialitza els parametres del servei.
///
void LedService::onInitialize(
	ServiceParams &params) {

	params.name = serviceName;
	params.stackDepth = serviceStackDepth;
	params.priority = servicePriority;
}


/// ----------------------------------------------------------------------
/// \brief 	  Tasca del servei.
///
void LedService::onExecute() {

    if (_pinLED1 != nullptr)
        _pinLED1->set();
    if (_pinLED2 != nullptr)
        _pinLED2->clear();

    while (!stopSignal()) {

		if (_pinLED1 != nullptr)
			_pinLED1->toggle();

		if (_pinLED2 != nullptr)
			_pinLED2->toggle();

		rtos::Task::delayUntil(eos::Time::fromMiliseconds(500));
	}
}
