#include "eos.h"
#include "Services/eosLedService.h"
#include "appApplication.h"
#include "appDisplayService.h"


using namespace app;


///-----------------------------------------------------------------------
/// \brief Contructor.
///
MyApplication::MyApplication() {

}


void MyApplication::onExecute() {

    auto pinLED1 = LED1_Pin::pInst;
	auto ledService = new eos::LedService(pinLED1, nullptr);
	addService(ledService);

	auto displayService = new DisplayService();
	addService(displayService);

	while (true)
		eos::Task::delay(1000);
}
