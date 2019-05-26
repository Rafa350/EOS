#include "eos.h"
#include "appApplication.h"
#include "appLedService.h"
#include "appDisplayService.h"


using namespace eos;
using namespace app;


///-----------------------------------------------------------------------
/// \brief Contructor.
///
MyApplication::MyApplication() {

	ledService = new LedService(this);
	displayService = new DisplayService(this);
}
