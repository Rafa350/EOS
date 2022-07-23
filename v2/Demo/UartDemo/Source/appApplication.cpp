#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HAL/halINT.h"
#include "HAL/halSYS.h"
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

	// Inicialitza els pins SW del pulsador
	//
	GPIO_SW::initInput(GPIOPull::up);

    // Inicialitza els pins LED del leds
    //
	GPIO_LED::initOutput(GPIODriver::pushPull);
	GPIO_LED::clear();

    // Inicialitza la UART i els pins TX/RX de la UART
	//
	UART::init();
	UART::initTXPin<GPIO_TX>();
	UART::initRXPin<GPIO_RX>();
	UART::setProtocol(UARTWord::word8, UARTParity::none, UARTStop::stop1);
	UART::setTimming(UARTBaudMode::b9600, UARTClockMode::pclk, 0, UARTOverSampling::os16);

	halINTEnableInterruptVector(HAL_INT_VECTOR_UART6);
	halINTSetInterruptVectorPriority(HAL_INT_VECTOR_UART6, HAL_INT_PRIORITY_10, HAL_INT_SUBPRIORITY_0);

	// Inicialitza el temporitzador per les entrades digitals
	//
	TMR_INPSRV::init();
	TMR_INPSRV::setClockDivider(TMRClockDivider::div1);
	TMR_INPSRV::setPrescaler((halSYSGetTimerClock1Frequency() / 1000000L) - 1);
	TMR_INPSRV::setPeriod((1000 * config::digInputService::period) - 1);

    halINTSetInterruptVectorPriority(DigInputService_TimerInterruptVector, DigInputService_TimerInterruptPriority, DigInputService_TimerInterruptSubPriority);
    halINTEnableInterruptVector(DigInputService_TimerInterruptVector);

	// Inicialitza el temporitzador per les sortides digitals
	//
	TMR_OUTSRV::init();
	TMR_OUTSRV::setClockDivider(TMRClockDivider::div1);
	TMR_OUTSRV::setPrescaler((halSYSGetTimerClock1Frequency() / 1000000L) - 1);
	TMR_OUTSRV::setPeriod((1000 * config::digOutputService::period) - 1);

	// Inicialitza les interrupcions
	//

    halINTSetInterruptVectorPriority(DigOutputService_TimerInterruptVector, DigOutputService_TimerInterruptPriority, DigOutputService_TimerInterruptSubPriority);
    halINTEnableInterruptVector(DigOutputService_TimerInterruptVector);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els serveis associats a l'aplicacio.
///
void MyApplication::initializeServices() {

    // Inicialitza el servei d'entrades digitals
	//
    _digInputService = new DigInputService(this);
    _digInputService->setPriority(Task::Priority::high);

    _sw = new DigInput(_digInputService, getAdapter<GPIO_SW>());
    _sw->setCallback(_swEventCallback, nullptr);

    // Inicialitza el servei de sortides digitals
    //
    _digOutputService = new DigOutputService(this);
    _led = new DigOutput(_digOutputService, getAdapter<GPIO_LED>());

	// Inicialitza el servei UART
	//
	_uartService = new UARTService(this);

	// Inicialitza el servei AppLoop
	//
	_loopService = new MyAppLoopService(this, _uartService);
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
