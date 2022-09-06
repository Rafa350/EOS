#include "eos.h"
#include "Controllers/Serial/eosAsyncSerialDriver_UART.h"
#include "appApplication.h"
#include "appLoopService.h"


using namespace eos;
using namespace htl;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
MyAppLoopService::MyAppLoopService(
	Application* application):

	AppLoopService(application),
	_serial(nullptr),
	_txCompletedCallback(*this, &MyAppLoopService::txCompletedEventHandler),
	_rxCompletedCallback(*this, &MyAppLoopService::rxCompletedEventHandler) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void MyAppLoopService::onSetup() {

	// Inicialitza el LED
	//
	Led::initOutput(GPIODriver::pushPull);
	Led::clear();

    // Inicialitza la UART
	//
	Uart::initialize();
	Uart::initTXPin<PinTX>();
	Uart::initRXPin<PinRX>();
	Uart::setProtocol(_wordBits, _parity, _stopBits);
#if defined( EOS_PLATFORM_STM32)
	Uart::setTimming(_baudMode, UARTClockSource::automatic, 0, UARTOverSampling::_16);
#elif defined(EOS_PLATFORM_PIC32)
	Uart::setTimming(_baudMode);
#else
#error "Undefined EOS_PLATFORM_XXX"
#endif
	INT_1::setInterruptVectorPriority(_vector,	_priority, _subPriority);
	INT_1::enableInterruptVector(_vector);
	Uart::enable();

	// Configura el driver de comunicacio serie
	//
	_serial = new AsyncSerialDriver_UART(getUARTWrapper<Uart>());
	_serial->initialize();
	_serial->enableTxCompletedCallback(_txCompletedCallback);
	_serial->enableRxCompletedCallback(_rxCompletedCallback);
}


/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio.
///
void MyAppLoopService::onLoop() {

	uint8_t buffer[10];

	while (true) {

		if (_serial->receive(buffer, sizeof(buffer))) {
			Led::toggle();
			if (_rxCompleted.wait(unsigned(-1))) {
				if (_rxDataCount > 0) {
					if (_serial->transmit(buffer, _rxDataCount))
						_txCompleted.wait(unsigned(-1));
				}
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    : Procesa l'event del UART txCompleted
/// \params   : args : Parametres del event.
///
void MyAppLoopService::txCompletedEventHandler(
	const AsyncSerialDriver::TxCompletedEventArgs &args) {

	_txCompleted.releaseISR();
}


/// ----------------------------------------------------------------------
/// \brief    : Procesa l'event del UART rxCompleted
/// \params   : args : Parametres del event.
///
void MyAppLoopService::rxCompletedEventHandler(
	const AsyncSerialDriver::RxCompletedEventArgs &args) {

	_rxDataCount = args.count;
	_rxCompleted.releaseISR();
}

