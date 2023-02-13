#include "eos.h"
#include "appApplication.h"
#include "appLedService.h"
#include "appDisplayService.h"


using namespace app;


///-----------------------------------------------------------------------
/// \brief Contructor.
///
MyApplication::MyApplication():

	eos::Application() {

	_ledService = new LedService();
	addService(_ledService, eos::Task::Priority::normal, 128, "LED");

	_displayService = new DisplayService();
	addService(_displayService, eos::Task::Priority::normal, 128, "DISPLAY");
}
