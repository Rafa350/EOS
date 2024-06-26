#include "eos.h"
#include "Controllers/Sensors/Drivers/VCNL4020/eosSensorDriver_VCNL4020.h"
#include "HAL/halSYS.h"
#include "HAL/halGPIO_ex.h"
#ifdef EOS_STM32
#include "HAL/STM32/halINT_ex.h"
#include "HAL/STM32/halEXTI_ex.h"
#endif
#include "System/eosApplication.h"
#include "System/Core/eosSemaphore.h"
#include "Services/eosAppLoopService.h"


using namespace eos;


class Led1LoopService: public AppLoopService {
	private:
		GPIOPinAdapter<GPIOPort(LEDS_LED1_PORT), GPIOPin(LEDS_LED1_PIN)> _led;

	public:
		Led1LoopService(Application *application):
			AppLoopService(application) {}

	protected:
		void onSetup();
		void onLoop();
};


class VCNL4020LoopService: public AppLoopService {
	private:
		uint16_t _threshold;
		GPIOPinAdapter<GPIOPort(ARDUINO_D6_PORT), GPIOPin(ARDUINO_D6_PIN)> _led1;
		GPIOPinAdapter<GPIOPort(ARDUINO_D7_PORT), GPIOPin(ARDUINO_D7_PIN)> _led2;
		SensorDriver_VCNL4020 *_driver;
		Semaphore _lock;

	public:
		VCNL4020LoopService(Application *application):
			AppLoopService(application) {}

	private:
		void interruptHandler();
		static void interruptHandler(halEXTILine line, void *param);

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

	_led.initOutput(GPIOSpeed::low, GPIODriver::pushPull);
	_led.set();
}


/// ----------------------------------------------------------------------
/// \brief Bucle del proces Led1
///
void Led1LoopService::onLoop() {

    _led.toggle();
	Task::delay(500);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el proces VCNL4020
///
void VCNL4020LoopService::onSetup() {

	_led1.initOutput(GPIOSpeed::low, GPIODriver::pushPull);
	_led2.initOutput(GPIOSpeed::low, GPIODriver::pushPull);

	_driver = new SensorDriver_VCNL4020();
	_driver->initialize(SensorDriver_VCNL4020::Mode::continous, 15);

	uint16_t min = 65535;
	uint16_t max = 0;
	for (int i = 0; i < 10; i++) {

		uint16_t value = _driver->getProximityValue();

		if (value < min)
			min = value;
		if (value > max)
			max = value;
	}
	uint16_t avg = (min + max) / 2;

	_threshold = max;

	_driver->setLowerThreshold(0000);
	_driver->setUpperThreshold(_threshold);

	_driver->configureInterrupts(VCNL4020_INT_COUNT_4 | VCNL4020_INT_THRES_ENABLE);
	_driver->clearInterruptFlags(0x0F);

	typedef EXTIAdapter<EXTILine(VCNL4020_INT_EXTI_LINE)> ExtiINT;
	ExtiINT::init(EXTIPort(VCNL4020_INT_EXTI_PORT), EXTIMode::interrupt, EXTITrigger::falling);
    ExtiINT::setInterruptFunction(interruptHandler, this);

    INT::setInterruptVectorPriority(INTVector(VCNL4020_INT_IRQ), INTPriority(VCNL4020_INT_PRIORITY), INTSubPriority(VCNL4020_INT_SUBPRIORITY));
	INT::enableInterruptVector(INTVector(VCNL4020_INT_IRQ));
 }


/// ----------------------------------------------------------------------
/// \brief Bucle del proces VCNL4020
///
void VCNL4020LoopService::onLoop() {

	if (_lock.wait(-1)) {

		uint8_t status = _driver->getInterruptStatus();

		if ((status & (VCNL4020_INT_STATUS_THHI | VCNL4020_INT_STATUS_THLO)) != 0) {

			_driver->configureInterrupts(VCNL4020_INT_COUNT_4);

			if ((status & VCNL4020_INT_STATUS_THHI) != 0) {

				_driver->setUpperThreshold(0xFFFF);
				_driver->setLowerThreshold(_threshold);

				_led1.set();
			}

			else if ((status & VCNL4020_INT_STATUS_THLO) != 0) {

				_driver->setLowerThreshold(0);
				_driver->setUpperThreshold(_threshold);

				_led1.clear();
			}

			_driver->clearInterruptFlags(VCNL4020_INT_STATUS_THHI | VCNL4020_INT_STATUS_THLO);
			_driver->configureInterrupts(VCNL4020_INT_COUNT_4 | VCNL4020_INT_THRES_ENABLE);
		}
	}
}


void VCNL4020LoopService::interruptHandler() {

	_lock.releaseISR();
}


void VCNL4020LoopService::interruptHandler(
	halEXTILine line,
	void *param) {

	VCNL4020LoopService *service = static_cast<VCNL4020LoopService*>(param);
	service->interruptHandler();
}


/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void appMain() {

	Application *app = new MyApplication();
	app->run();
	delete app;
}
