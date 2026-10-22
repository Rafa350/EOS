module;

#include "eos.h"


export module App.Application;


import App.Services.Display;
import Eos.Hardware.GPIO;
import Eos.Services.LedService;
import Eos.System.Application.RTOS;
import Eos.System.Core.Task;
import Eos.System.Core.Ticks;


namespace app {

    using PinLED = eos::hardware::gpio::PinG13;

    constexpr auto pinLED = PinLED::pInst;


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

    initializeLedService();
    initializeDisplayService();

    // Executa els serveis indefinidament
    //
    while (true)
    	Task::delay(Ticks::fromMiliseconds(1000));
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei de gestio dels leds
///
void MyApplication::initializeLedService() {

    auto ledService = new LedService(pinLED1);
    addService(ledService);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei de gestio del display
///
void MyApplication::initializeDisplayService() {

    auto displayService = new DisplayService();
    addService(displayService);
}
