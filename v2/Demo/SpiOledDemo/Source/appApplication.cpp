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

#if EXIST_LED1
    auto pinLED1 = LED1_Pin::pInst;
	auto ledService = new LedService(pinLED1, nullptr);
	addService(ledService);
#endif

	auto displayService = new DisplayService();
	addService(displayService);

	while (true)
		Task::delay(1000);
}
