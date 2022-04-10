#include "eos.h"
#include "Controllers/Sensors/VCNL4020/eosVCNL4020Driver.h"
#include "HAL/halSYS.h"
#include "HAL/halGPIO.h"
#include "System/eosApplication.h"
#include "Services/eosAppLoopService.h"


using namespace eos;


class Led1LoopService: public AppLoopService {
	public:
		Led1LoopService(Application *application):
			AppLoopService(application) {}

	protected:
		void onSetup();
		void onLoop();
};


class VCNL4020LoopService: public AppLoopService {
	public:
		VCNL4020LoopService(Application *application):
			AppLoopService(application) {}

	protected:
		void onSetup();
		void onLoop();
};


class MyApplication: public Application {
	private:
		Led1LoopService *_led1Service;
		VCNL4020LoopService *_vcnl4020Service;

	public:
		MyApplication();
};


/// ----------------------------------------------------------------------
/// \brief Contructor
///
MyApplication::MyApplication() {

	_led1Service = new Led1LoopService(this);
	_vcnl4020Service = new VCNL4020LoopService(this);
}


/// ---------------------------------------------------------------------
///\bried Inicialitzacio del proces Led1
///
void Led1LoopService::onSetup() {

	halGPIOInitializePinOutput(LEDS_LED1_PORT, LEDS_LED1_PIN);
	halGPIOSetPin(LEDS_LED1_PORT, LEDS_LED1_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Bucle del proces Led1
///
void Led1LoopService::onLoop() {

    halGPIOTogglePin(LEDS_LED1_PORT, LEDS_LED1_PIN);
	Task::delay(500);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el proces VCNL4020
///
void VCNL4020LoopService::onSetup() {

	VCNL4020Driver driver;

	driver.initialize();
}


/// ----------------------------------------------------------------------
/// \brief Bucle del proces VCNL4020
///
void VCNL4020LoopService::onLoop() {

}


/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void appMain() {

	Application *app = new MyApplication();
	app->run();
	delete app;
}
