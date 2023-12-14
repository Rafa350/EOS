#include "eos.h"
#include "HTL/htlGPIO.h"
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

}


void MyApplication::onInitialize() {

    #ifdef EXIST_LED1
    LED1_Initialize();

    auto ledService = new eos::LedService(LED1_Instance);
    addService(ledService, eos::Task::Priority::normal,
            eos::LedService::stackSize, eos::LedService::serviceName);
    #endif
    /*
    #ifdef EXIST_DISPLAY
    auto displayService = new DisplayService();
    addService(displayService, eos::Task::Priority::normal,
            DisplayService::stackSize, DisplayService::serviceName);
    #endif
    */
    auto httpService = new eos::HTTPService();
    addService(httpService, eos::Task::Priority::normal,
            eos::HTTPService::stackSize, eos::HTTPService::serviceName);
}
