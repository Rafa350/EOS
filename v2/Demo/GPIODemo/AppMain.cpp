#include "System/eosApplication.h"
#include "Services/eosAppLoop.h"
#include "hal/halSYS.h"
#include "hal/halGPIO.h"
#include "hal/halTMR.h"


using namespace eos;


class Led1LoopService: public AppLoopService {
	public:
		Led1LoopService(Application *application):
			AppLoopService(application) {}

	protected:
		static void timerInterrupt(TMRTimer timer, void *pParam);
		void onSetup();
		void onLoop();
};


class Led2LoopService: public AppLoopService {
	public:
		Led2LoopService(Application *application):
			AppLoopService(application) {}

	protected:
		void onSetup();
		void onLoop();
};


class MyApplication: public Application {
	private:
		Led1LoopService *led1Service;
		Led2LoopService *led2Service;

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


/// ---------------------------------------------------------------------
///\bried Inicialitzacio del proces Led1
///
void Led1LoopService::onSetup() {

	TMRInitializeInfo tmrInfo;
	tmrInfo.timer = HAL_TMR_TIMER_3;
	tmrInfo.prescaler = 10000;
	tmrInfo.period = 1000;
	tmrInfo.options = HAL_TMR_MODE_32 | HAL_TMR_CLKDIV_4 | HAL_TMR_INTERRUPT_ENABLE;
	tmrInfo.irqPriority = 0;
	tmrInfo.irqSubPriority = 0;
	tmrInfo.pIrqCall = timerInterrupt;
	tmrInfo.pIrqParams = this;
	halTMRInitialize(&tmrInfo);
	halTMRStartTimer(HAL_TMR_TIMER_3);

	halGPIOInitializePinOutput(LED_LED1_PORT, LED_LED1_PIN);
	halGPIOSetPin(LED_LED1_PORT, LED_LED1_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Bucle del proces Led1
///
void Led1LoopService::onLoop() {

//    halGPIOTogglePin(LED_LED1_PORT, LED_LED1_PIN);
	Task::delay(500);
}


void Led1LoopService::timerInterrupt(
	TMRTimer timer,
	void *pParam) {

	//Led1LoopService *service = reinterpret_cast<Led1LoopService*>(pParam);
	halGPIOTogglePin(LED_LED1_PORT, LED_LED1_PIN);
}

/// ---------------------------------------------------------------------
/// \brief Inicialitzacio del proces Led2
///
void Led2LoopService::onSetup() {

	halGPIOInitializePinOutput(LED_LED2_PORT, LED_LED2_PIN);
	halGPIOSetPin(LED_LED2_PORT, LED_LED2_PIN);
}

/// ----------------------------------------------------------------------
/// \brief Bucle del proces Led2
///
void Led2LoopService::onLoop() {

	halGPIOTogglePin(LED_LED2_PORT, LED_LED2_PIN);
	Task::delay(480);
}


/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void AppMain() {

	Application *app = new MyApplication();
	app->execute();
	delete app;
}
