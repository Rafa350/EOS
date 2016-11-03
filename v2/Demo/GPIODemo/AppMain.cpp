#include "System/eosApplication.hpp"
#include "Services/eosAppLoop.hpp"
#include "hal/halGPIO.h"


using namespace eos;


class MyAppLoopService: public AppLoopService {
	public:
		MyAppLoopService(Application *application):
			AppLoopService(application) {}

	protected:
		void loop();
		void setup();
};


class MyApplication: public Application {
	private:
		AppLoopService *loopService;

	public:
		MyApplication();
};


/// ----------------------------------------------------------------------
/// \brief Contructor
///
MyApplication::MyApplication() {

	loopService = new MyAppLoopService((Application*)this);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio.
///
void MyAppLoopService::setup() {

	halGPIOInitializePin(LED1_PORT, LED1_PIN, GPIO_DIRECTION_OUTPUT);
	halGPIOInitializePin(LED2_PORT, LED2_PIN, GPIO_DIRECTION_OUTPUT);

	halGPIOClearPin(LED1_PORT, LED1_PIN);
	halGPIOSetPin(LED2_PORT, LED2_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Bucle principal
///
void MyAppLoopService::loop() {

	while (true) {

		halGPIOTogglePin(LED1_PORT, LED1_PIN);
		halGPIOTogglePin(LED2_PORT, LED2_PIN);

		Task::delay(100);
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
