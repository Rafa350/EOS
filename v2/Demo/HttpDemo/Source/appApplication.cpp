#include "eos.h"
#include "appApplication.h"
#include "appLedService.h"
#ifdef USE_DISPLAY
#include "appDisplayService.h"
#endif
#include "Services/eosHTTPService.h"


using namespace eos;
using namespace app;


///-----------------------------------------------------------------------
/// \brief Contructor.
///
MyApplication::MyApplication() {

	_ledService = new LedService(this);
	#ifdef USE_DISPLAY
		_displayService = new DisplayService(this);
	#endif
	_httpService = new HTTPService(this);
}
