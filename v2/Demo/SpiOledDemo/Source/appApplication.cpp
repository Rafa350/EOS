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

	_ledService = new LedService(this);
	_displayService = new DisplayService(this);
}
