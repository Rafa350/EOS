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

	ledService = new LedService(this);
#ifdef USE_DISPLAY    
	displayService = new DisplayService(this);
#endif    
	httpService = new HTTPService(this);
}
