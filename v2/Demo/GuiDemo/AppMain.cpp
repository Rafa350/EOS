#include "eos.h"
#include "System/eosApplication.h"
#include "Services/eosAppLoop.h"
#include "Services/Gui/eosGui.h"
#include "Services/Gui/eosGuiTouchPad.h"
#include "Controllers/TouchPad/eosTouchPad.h"
#include "Controllers/TouchPad/Drivers/eosFT5336.h"
#include "HAL/halSYS.h"
#include "HAL/halGPIO.h"

#include <stdlib.h>
#include <stdio.h>


using namespace eos;


class LedLoopService: public AppLoopService {
	public:
    	LedLoopService(Application *application):
        	AppLoopService(application) {}

    protected:
    	void onSetup();
        void onRun();
};


class MyApplication: public Application {
	private:
		GuiService *guiService;
		GuiTouchPadService *guiTouchPadService;
		LedLoopService *ledService;

    public :
        MyApplication();

    protected:
        void onInitialize();
};


static const char *title = "EOS v2.0: Gui+TouchPad Demo";


///-----------------------------------------------------------------------
/// \brief Contructor.
///
MyApplication::MyApplication() {

	guiService = new GuiService(this);
	guiTouchPadService = new GuiTouchPadService(this);
	ledService = new LedLoopService(this);
}


/// ---------------------------------------------------------------------
/// \brief Processa la inicialitzacio de l'aplicacio
///
void MyApplication::onInitialize() {

	guiService->initialize();
	guiTouchPadService->initialize();
	ledService->initialize();
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio de la tasca.
///
void LedLoopService::onSetup() {

	// Inicialitza el LED 1
	//
	halGPIOInitializePinOutput(LEDS_LD1_PORT, LEDS_LD1_PIN);
	halGPIOClearPin(LEDS_LD1_PORT, LEDS_LD1_PIN);

#ifdef LEDS_LD2_PORT

	// Inicialitza el LED 2
	//
	halGPIOInitializePinOutput(LEDS_LD2_PORT, LEDS_LD2_PIN);
	halGPIOSetPin(LEDS_LD2_PORT, LEDS_LD2_PIN);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedLoopService::onRun() {

	while (true) {

		halGPIOTogglePin(LEDS_LD1_PORT, LEDS_LD1_PIN);
#ifdef LEDS_LD2_PORT
		halGPIOTogglePin(LEDS_LD2_PORT, LEDS_LD2_PIN);
#endif

		Task::delay(500);
	}
}


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void AppMain() {

    MyApplication *app = new MyApplication();
    app->execute();
    delete app;
}
