#include "eos.h"
#include "Controllers/Sensors/Drivers/VCNL4020/eosSensorDriver_VCNL4020.h"
#include "HAL/halSYS.h"
#include "HAL/halGPIOTpl.h"
#ifdef EOS_STM32
#include "HAL/STM32/halINTTpl.h"
#include "HAL/STM32/halEXTITpl.h"
#endif
#include "System/eosApplication.h"
#include "Services/eosAppLoopService.h"


using namespace eos;


class Led1LoopService: public AppLoopService {
	private:
		typedef GPIOPinAdapter<GPIOPort(LEDS_LED1_PORT), GPIOPin(LEDS_LED1_PIN)> PinLED;

	public:
		Led1LoopService(Application *application):
			AppLoopService(application) {}

	protected:
		void onSetup();
		void onLoop();
};


class VCNL4020LoopService: public AppLoopService {
	private:
		VCNL4020Driver *_driver;

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

	PinLED::initOutput(GPIOSpeed::low, GPIODriver::pushPull);
	PinLED::set();
}


/// ----------------------------------------------------------------------
/// \brief Bucle del proces Led1
///
void Led1LoopService::onLoop() {

    PinLED::toggle();
	Task::delay(500);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el proces VCNL4020
///
void VCNL4020LoopService::onSetup() {

	_driver = new VCNL4020Driver();
	_driver->initialize(VCNL4020Driver::Mode::continous);
	_driver->setLowerThreshold(0000);
	_driver->setUpperThreshold(3300);
	_driver->configureInterrupts(VCNL4020_INT_COUNT_4 | VCNL4020_INT_THRES_ENABLE);
	_driver->clearInterruptFlags(0x0F);

	INT::setInterruptVectorPriority(INTVector(VCNL4020_INT_IRQ), INTPriority(VCNL4020_INT_PRIORITY), INTSubPriority(VCNL4020_INT_SUBPRIORITY));
	INT::enableInterruptVector(INTVector(VCNL4020_INT_IRQ));
 }


/// ----------------------------------------------------------------------
/// \brief Bucle del proces VCNL4020
///
void VCNL4020LoopService::onLoop() {

	int ir = _driver->getLedCurrent() * 10;
	//int proximity = _driver->getProximityValue();
	//int ambient = _driver->getAmbientValue();

	bool intStatus = PIN_C7::read();

	Task::delay(1000);
}


/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void appMain() {

	Application *app = new MyApplication();
	app->run();
	delete app;
}
