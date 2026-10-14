module;


export module App.Application;


import Eos.System.Application.RTOS;
import Eos.System.Core.Task;
import Eos.System.Core.Ticks;


namespace app {

	class MyApplication: public eos::RTOSApplication {
		protected:
			void initializeLedService();
			void initializeDisplayService();

		public :
			MyApplication();

			void onExecute() override;
	};

}


using namespace eos;
using namespace app;


///-----------------------------------------------------------------------
/// \brief Contructor.
///
MyApplication::MyApplication() {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza l'aplicacio.
///
void MyApplication::onExecute() {

    #ifdef EXIST_LED1
    LED1_Initialize();
    #endif
    #ifdef EXIST_LED2
    LED2_Initialize();
    #endif

    #if defined(EXIST_LED1) || defined(EXIST_LED2)
    initializeLedService();
    #endif
    initializeDisplayService();

    // Executa els serveis indefinidament
    //
    while (true)
    	Task::delay(Ticks::fromMiliseconds(1000));
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei de gestio dels leds
///
#if defined(EXIST_LED1) || defined(EXIST_LED2)
void MyApplication::initializeLedService() {

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
    addService(ledService);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei de gestio del display
///
void MyApplication::initializeDisplayService() {

    auto displayService = new DisplayService();
    addService(displayService);
}
