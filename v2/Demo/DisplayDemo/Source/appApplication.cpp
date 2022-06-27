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

	ledService = new LedService(this);
	displayService = new DisplayService(this);
}
