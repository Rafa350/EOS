#include "eos.h"
#include "Services/eosLedService.h"
#include "appApplication.h"
#include "appDisplayService.h"


using namespace app;


///-----------------------------------------------------------------------
/// \brief Contructor.
///
MyApplication::MyApplication():

	eos::RTOSApplication() {

    auto pinLED1 = LED1_Pin::pInst;
	auto ledService = new eos::LedService(pinLED1, nullptr);
	addService(ledService, eos::Task::Priority::normal, 128, "LED");

	auto displayService = new DisplayService();
	addService(displayService, eos::Task::Priority::normal, 128, "DISPLAY");
}
