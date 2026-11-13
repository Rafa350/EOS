module;

#include "eos.h"


export module App.Application;


import App.Hardware;
import App.Services.Display;
import Eos.Services.LedService;
import Eos.System.Application.RTOS;
import Eos.System.Core.Task;
import Eos.System.Core.Ticks;


using namespace eos;


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

    pinLed->initializeOutput();

    auto ledService = new LedService(pinLED);
    addService(ledService);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei de gestio del display
///
void MyApplication::initializeDisplayService() {

    auto displayService = new DisplayService();
    addService(displayService);
}
