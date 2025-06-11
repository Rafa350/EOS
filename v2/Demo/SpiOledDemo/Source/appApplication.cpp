#include "eos.h"
#include "Services/eosLedService.h"
#include "appApplication.h"
#include "appDisplayService.h"


using namespace app;
using namespace eos;


///-----------------------------------------------------------------------
/// \brief Contructor.
///
MyApplication::MyApplication() {

}


void MyApplication::onExecute() {

    auto pinLED1 = LED11_Pin::pInst;
	auto ledService = new LedService(pinLED1, nullptr);
	addService(ledService);

	auto displayService = new DisplayService();
	addService(displayService);

	while (true)
		Task::delay(1000);
}
