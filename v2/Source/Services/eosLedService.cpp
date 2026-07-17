#include "eos.h"
#include "HTL/htlGPIO.h"
#include "RTOS/rtosTime.h"
#include "RTOS/rtosTask.h"
#include "Services/eosLedService.h"
#include "System/eosTime.h"


using namespace htl;


constexpr const char *serviceName = "Led";
constexpr uint32_t serviceStackDepth = 96;
constexpr rtos::Task::Priority servicePriority = rtos::Task::Priority::low;


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
///
eos::LedService::LedService(
     Pin *pinLED1,
     Pin *pinLED2) :

	 Service(),
	 _pinLED1 {pinLED1},
	 _pinLED2 {pinLED2},
	 _modeLED1 {LedMode::blinkSlow},
	 _modeLED2 {LedMode::blinkSlow} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els parametres del servei.
///
void eos::LedService::onInitialize(
	ServiceParams &params) {

	params.name = serviceName;
	params.stackDepth = serviceStackDepth;
	params.priority = servicePriority;
}


void eos::LedService::setLed1Mode(
	LedMode value) {

	if (_modeLED1 != value) {
		_modeLED1 = value;
	}
}


void eos::LedService::setLed2Mode(
	LedMode value) {

	if (_modeLED2 != value) {
		_modeLED2 = value;
	}
}


/// ----------------------------------------------------------------------
/// \brief 	  Tasca del servei.
///
void eos::LedService::onExecute() {

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
