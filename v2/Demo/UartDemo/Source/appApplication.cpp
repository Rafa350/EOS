#include "eos.h"
#include "HAL/halSYS.h"
#include "HTL/htlINT.h"
#include "HTL/htlTMR.h"
#include "HTL/htlUART.h"
#include "Services/eosDigOutputService.h"
#include "Services/eosDigInputService.h"
#include "System/eosApplication.h"

#include "appApplication.h"
#include "appLoopService.h"


using namespace eos;
using namespace htl;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
MyApplication::MyApplication():
    _swEventCallback(this, &MyApplication::swEventHandler) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {

	initializeHardware();
	initializeServices();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el hardware associat a l'aplicacio.
///
void MyApplication::initializeHardware() {

	// Inicialitza els pin del pulsador
	//
	PinSW::initInput(GPIOPull::up);

    // Inicialitza els pin del led
    //
	PinLED::initOutput(GPIODriver::pushPull);
	PinLED::clear();

    // Inicialitza la UART
	//
	Uart::init();
	Uart::initTXPin<PinTX>();
	Uart::initRXPin<PinRX>();
	Uart::setProtocol(UARTWord::_8, UARTParity::none, UARTStop::_1);
	Uart::setTimming(UARTBaudMode::_9600, UARTClockSource::automatic, 0, UARTOverSampling::_16);
	Uart::enable();
	INT_1::setInterruptVectorPriority(config::uartService::uartVector,	config::uartService::uartVectorPriority, config::uartService::uartVectorSubPriority);
	INT_1::enableInterruptVector(INTVector::vUART6);

	// Inicialitza el temporitzador per les entrades digitals
	//
	Tmr1::init();
	Tmr1::setClockDivider(TMRClockDivider::_1);
	Tmr1::setPrescaler((halSYSGetTimerClock1Frequency() / 1000000L) - 1);
	Tmr1::setPeriod((1000 * config::digInputService::tmrPeriod) - 1);
	Tmr1::setInterruptFunction(isrTmr1, this);
    INT_1::setInterruptVectorPriority(config::digInputService::tmrVector, config::digInputService::tmrVectorPriority, config::digInputService::tmrVectorSubPriority);
    INT_1::enableInterruptVector(config::digInputService::tmrVector);

	// Inicialitza el temporitzador per les sortides digitals
	//
	Tmr2::init();
	Tmr2::setClockDivider(TMRClockDivider::_1);
	Tmr2::setPrescaler((halSYSGetTimerClock1Frequency() / 1000000L) - 1);
	Tmr2::setPeriod((1000 * config::digOutputService::tmrPeriod) - 1);
	Tmr2::enableInterrupt(TMREvent::update);
	Tmr2::setInterruptFunction(isrTmr2, this);
    INT_1::setInterruptVectorPriority(config::digOutputService::tmrVector, config::digOutputService::tmrVectorPriority, config::digOutputService::tmrVectorSubPriority);
    INT_1::enableInterruptVector(config::digOutputService::tmrVector);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els serveis associats a l'aplicacio.
///
void MyApplication::initializeServices() {

    // Inicialitza el servei d'entrades digitals
	//
    _digInputService = new DigInputService(this);
    _digInputService->setPriority(Task::Priority::high);

    _sw = new DigInput(_digInputService, getAdapter<PinSW>());
    _sw->setCallback(_swEventCallback, nullptr);

    // Inicialitza el servei de sortides digitals
    //
    _digOutputService = new DigOutputService(this);
    _led = new DigOutput(_digOutputService, getAdapter<PinLED>());

	// Inicialitza el servei UART
	//
	_uartService = new UARTService(this);

	// Inicialitza el servei AppLoop
	//
	_loopService = new MyAppLoopService(this, _uartService);

	// Arranca el temporitzador de gestio de les entrades digitals
	//
	Tmr1::enableInterrupt(TMREvent::update);
	Tmr1::start();

	// Arranca el temporitzador de les sortides digitals
	//
	Tmr2::enableInterrupt(TMREvent::update);
	Tmr2::start();
}


/// ----------------------------------------------------------------------
/// \brief    Funcio d'interrupcio del temporitzador Tmr1
/// \param    event: El event.
/// \param    param: El parametre.
///
void MyApplication::isrTmr1(
	TMREvent event,
	TMRInterruptParam param) {

	MyApplication *app = reinterpret_cast<MyApplication*>(param);
	app->_digInputService->tmrInterruptFunction();
}


/// ----------------------------------------------------------------------
/// \brief    Funcio d'interrupcio del temporitzador Tmr2
/// \param    event: El event.
/// \param    param: El parametre.
///
void MyApplication::isrTmr2(
	TMREvent event,
	TMRInterruptParam param) {

	MyApplication *app = reinterpret_cast<MyApplication*>(param);
	app->_digOutputService->tmrInterruptFunction();
}


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch.
/// \param    args: Parametres del event.
///
void MyApplication::swEventHandler(
    const DigInput::EventArgs &args) {

    if (_sw->read()) {
        _led->pulse(1000);
        _uartService->send((uint8_t*) "hola\r\n", 6, unsigned(-1));
    }
}
