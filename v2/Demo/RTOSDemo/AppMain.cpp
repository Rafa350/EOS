#include "System/eosApplication.h"
#include "Services/eosAppLoop.h"
#include "hal/halSYS.h"
#include "hal/halGPIO.h"


using namespace eos;


class Led1LoopService: public AppLoopService {
	public:
		Led1LoopService(Application *application):
			AppLoopService(application) {}

	protected:
		void onSetup();
		void onRun();
};


class Led2LoopService: public AppLoopService {
	public:
		Led2LoopService(Application *application):
			AppLoopService(application) {}

	protected:
		void onSetup();
		void onRun();
};


class MyApplication: public Application {
	private:
		Led1LoopService *led1Service;
		Led2LoopService *led2Service;

	protected:
		void onInitialize();

	public:
		MyApplication();
};


/// ----------------------------------------------------------------------
/// \brief Contructor
///
MyApplication::MyApplication() {

	led1Service = new Led1LoopService(this);
	led2Service = new Led2LoopService(this);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio de l'aplicacio.
///
void MyApplication::onInitialize() {

	led1Service->initialize();
	led2Service->initialize();
}


/// ---------------------------------------------------------------------
///\bried Inicialitzacio del proces Led1
///
void Led1LoopService::onSetup() {

	halGPIOInitializePinOutput(LEDS_LD1_PORT, LEDS_LD1_PIN);
	halGPIOSetPin(LEDS_LD1_PORT, LEDS_LD1_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Bucle del proces Led1
///
void Led1LoopService::onRun() {

	while (true) {
		halGPIOTogglePin(LEDS_LD1_PORT, LEDS_LD1_PIN);
		Task::delay(500);
	}
}


/// ---------------------------------------------------------------------
/// \brief Inicialitzacio del proces Led2
///
void Led2LoopService::onSetup() {

	halGPIOInitializePinOutput(LEDS_LD2_PORT, LEDS_LD2_PIN);
	halGPIOSetPin(LEDS_LD2_PORT, LEDS_LD2_PIN);
}

/// ----------------------------------------------------------------------
/// \brief Bucle del proces Led2
///
void Led2LoopService::onRun() {

	while (true) {
		halGPIOTogglePin(LEDS_LD2_PORT, LEDS_LD2_PIN);
		Task::delay(480);
	}
}


/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void AppMain() {

	Application *app = new MyApplication();
	app->execute();
	delete app;
}
