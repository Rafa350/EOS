#include "eos.h"
#include "Controllers/Serial/eosAsyncSerialDriver_UART.h"

#include "appApplication.h"
#include "appMainService.h"


using namespace eos;
using namespace htl;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
MainService::MainService():
	_serial(nullptr),
	_txCompletedEvent(*this, &MainService::txCompletedEventHandler),
	_rxCompletedEvent(*this, &MainService::rxCompletedEventHandler) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
bool MainService::onTaskStart() {

	// Inicialitza el LED
	//
	LED1_Initialize();
	LED1_Off();

    // Inicialitza la UART
	//
	COM_UART::initialize();
	COM_UART::initTXPin<COM_TX_GPIO>();
	COM_UART::initRXPin<COM_RX_GPIO>();
	COM_UART::setProtocol(_wordBits, _parity, _stopBits);
#if defined( EOS_PLATFORM_STM32)
	COM_UART::setTimming(_baudMode, UARTClockSource::automatic, 0, UARTOverSampling::_16);
#elif defined(EOS_PLATFORM_PIC32)
	COM_UART::setTimming(_baudMode);
#else
#error "Undefined EOS_PLATFORM_XXX"
#endif
	INT_1::setInterruptVectorPriority(_vector,	_priority, _subPriority);
	INT_1::enableInterruptVector(_vector);
	COM_UART::enable();

	// Configura el driver de comunicacio serie
	//
	_serial = new AsyncSerialDriver_UART(htl::getUART<COM_UART>());
	_serial->initialize();
	_serial->setTxCompletedEvent(_txCompletedEvent);
	_serial->setRxCompletedEvent(_rxCompletedEvent);

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio.
///
bool MainService::onTask() {

	uint8_t buffer[10];

	while (true) {
		if (_serial->receive(buffer, sizeof(buffer))) {
			LED1_Toggle();
			if (_rxCompleted.wait(unsigned(-1))) {
				if (_rxDataCount > 0) {
					if (_serial->transmit(buffer, _rxDataCount))
						_txCompleted.wait(unsigned(-1));
				}
			}
		}
	}

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    : Procesa l'event del UART txCompleted
/// \params   : args : Parametres del event.
///
void MainService::txCompletedEventHandler(
	const AsyncSerialDriver::TxCompletedEventArgs &args) {

	_txCompleted.releaseISR();
}


/// ----------------------------------------------------------------------
/// \brief    : Procesa l'event del UART rxCompleted
/// \params   : args : Parametres del event.
///
void MainService::rxCompletedEventHandler(
	const AsyncSerialDriver::RxCompletedEventArgs &args) {

	_rxDataCount = args.count;
	_rxCompleted.releaseISR();
}

