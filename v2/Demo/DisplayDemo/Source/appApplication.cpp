#include "eos.h"
#include "Services/eosLedService.h"

#include "appApplication.h"
#include "appDisplayService.h"


using namespace eos;
using namespace htl;
using namespace app;


///-----------------------------------------------------------------------
/// \brief Contructor.
///
MyApplication::MyApplication() {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {

    #ifdef EXIST_LED1
    LED1_Initialize();
    #endif
    #ifdef EXIST_LED2
    LED2_Initialize();
    #endif

    #if defined(EXIST_LED1) || defined(EXIST_LED2)
    configureLedService();
    #endif
    configureDisplayService();
}


#if defined(EXIST_LED1) || defined(EXIST_LED2)
void MyApplication::configureLedService() {

    #ifdef EXIST_LED1
    constexpr auto pinLED1 = LED1_Instance;
    #else
    constexpr gpio::PinDevice *pinLED1 = nullptr;
    #endif
    #ifdef EXIST_LED2
    constexpr auto pinLED2 = LED2_Instance;
    #else
    constexpr gpio::PinDevice *pinLED2 = nullptr;
    #endif

    auto ledService = new LedService(pinLED1, pinLED2);
    addService(ledService, Task::Priority::normal, 128);
}
#endif


void MyApplication::configureDisplayService() {

    auto displayService = new DisplayService();
    addService(displayService, Task::Priority::normal, 512);
}
