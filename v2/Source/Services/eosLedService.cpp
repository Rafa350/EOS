#include "eos.h"
#include "htl/htlGPIO.h"
#include "Services/eosLedService.h"
#include "System/Core/eosTask.h"
#include "System/Core/eosKernel.h"


using namespace eos;
using namespace htl;


constexpr const char *serviceName = "Led";
constexpr unsigned serviceStackSize = 96;
constexpr Task::Priority servicePriority = Task::Priority::low;


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
	params.stackSize = serviceStackSize;
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

    auto weakTime = Kernel::pInst->getTickCount();

    while (!stopSignal()) {

		if (_pinLED1 != nullptr)
			_pinLED1->toggle();

		if (_pinLED2 != nullptr)
			_pinLED2->toggle();

		Task::delay(500, weakTime);
	}
}
