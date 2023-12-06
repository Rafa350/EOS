#include "eos.h"
#include "Services/eosHTTPService.h"
#ifdef EXIST_LED1
#include "Services/eosLedService.h"
#endif
#include "appApplication.h"

#ifdef USE_DISPLAY
#include "appDisplayService.h"
#endif


using namespace app;


///-----------------------------------------------------------------------
/// \brief Contructor.
///
MyApplication::MyApplication() {

    #ifdef EXIST_LED1
	_ledService = new eos::LedService(LED1_Pin::pInst);
	addService(_ledService, eos::Task::Priority::normal,
	        eos::LedService::stackSize, eos::LedService::serviceName);
    #endif
	#ifdef EXIST_DISPLAY
	_displayService = new DisplayService();
    addService(_displayService, eos::Task::Priority::normal,
            DisplayService::stackSize, DisplayService::serviceName);
	#endif
	_httpService = new eos::HTTPService();
	addService(_httpService, eos::Task::Priority::normal,
	        eos::HTTPService::stackSize, eos::HTTPService::serviceName);
}
