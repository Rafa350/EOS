#include "System/eosApplication.hpp"
#include "Services/eosAppLoop.hpp"
#include "hal/halGPIO.h"


using namespace eos;


class Led1LoopService: public AppLoopService {
	public:
		Led1LoopService(Application *application):
			AppLoopService(application) {}

	protected:
		void onRun();
};


class Led2LoopService: public AppLoopService {
	public:
		Led2LoopService(Application *application):
			AppLoopService(application) {}

	protected:
		void onRun();
};


class MyApplication: public Application {
	protected:
		void onInitialize();

	public:
		MyApplication();
};


/// ----------------------------------------------------------------------
/// \brief Contructor
///
MyApplication::MyApplication() {

	new Led1LoopService((Application*)this);
	new Led2LoopService((Application*)this);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio de l'aplicacio.
///
void MyApplication::onInitialize() {

	halGPIOInitializePin(LEDS_LD1_PORT, LEDS_LD1_PIN, HAL_GPIO_DIRECTION_OUTPUT);
	halGPIOInitializePin(LEDS_LD2_PORT, LEDS_LD2_PIN, HAL_GPIO_DIRECTION_OUTPUT);

	halGPIOClearPin(LEDS_LD1_PORT, LEDS_LD1_PIN);
	halGPIOClearPin(LEDS_LD2_PORT, LEDS_LD2_PIN);

	Application::onInitialize();
}


/// ----------------------------------------------------------------------
/// \brief Bucle principal del proces
///
void Led1LoopService::onRun() {

	while (true) {

		halGPIOTogglePin(LEDS_LD1_PORT, LEDS_LD1_PIN);

		Task::delay(100);
	}
}


/// ----------------------------------------------------------------------
/// \brief Bucle principal del proces
///
void Led2LoopService::onRun() {

	while (true) {

		halGPIOTogglePin(LEDS_LD2_PORT, LEDS_LD2_PIN);

		Task::delay(80);
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
