#include "eos.h"
#include "Services/eosLedService.h"
#include "appApplication.h"
#include "appDisplayService.h"


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

    #if defined(EXIST_LED1) || defined(EXIST_LED2)
    #ifdef EXIST_LED1
    constexpr htl::gpio::Pin *pinLED1 = LED1_Instance;
    #else
    constexpr htl::gpio::Pin *pinLED1 = nullptr;
    #endif
    #ifdef EXIST_LED2
    constexpr htl::gpio::Pin *pinLED2 = LED2_Instance;
    #else
    constexpr htl::gpio::Pin *pinLED2 = nullptr;
    #endif

    #ifdef EXIST_LED1
    LED1_Initialize();
    #endif
    #ifdef EXIST_LED2
    LED2_Initialize();
    LED2_Toggle();
    #endif

	_ledService = new eos::LedService(pinLED1, pinLED2);
	addService(_ledService, eos::Task::Priority::normal, 128);
    #endif

	_displayService = new DisplayService();
	addService(_displayService, eos::Task::Priority::normal, 512);
}
