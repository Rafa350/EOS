#include "eos.h"
#include "HTL/htlINT.h"
#include "HTL/htlDMA.h"
#include "Controllers/Serial/eosSerialDriver_UART.h"

#include "appConfig.h"
#include "appMainService.h"

using namespace app;
using namespace eos;
using namespace htl::irq;
using namespace htl::uart;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
MainService::MainService():
	_uartNotifyEvent {*this, &MainService::uartNotifyEventHandler} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void MainService::onExecute() {

	auto devUART = hw::devUART;

    // Inicialitza la UART
	//
	devUART->initPinTX<hw::PinTX::portID, hw::PinTX::pinID>();
	devUART->initPinRX<hw::PinRX::portID, hw::PinRX::pinID>();
	devUART->initialize();

	devUART->setProtocol(WordBits::word8, Parity::none, StopBits::_1, Handsake::none);
	devUART->setTimming(BaudMode::b19200, ClockSource::automatic, 0, OverSampling::_16);

	setInterruptVectorPriority(hw::devUART_VectorID, Priority::p5);
	enableInterruptVector(hw::devUART_VectorID);

	devUART->setNotifyEvent(_uartNotifyEvent, true);

	const char *txBuffer = "Hello world!\r\n";

	while (!stopSignal()) {

		devUART->transmit_IRQ((const uint8_t*)txBuffer, strlen(txBuffer));

		_completed.wait((unsigned) -1);
		Task::delay(1000);
	}
}


/// ----------------------------------------------------------------------
/// \brief    : Procesa l'event del UART rxCompleted
/// \param    : notifyID: Identificador de la notificacio.
/// \params   : args : Parametres del event.
///
void MainService::uartNotifyEventHandler(
    UARTNotifyID notifyID,
	UARTNotifyEventArgs * const args) {

    switch (notifyID) {
        case UARTNotifyID::txCompleted:
        	_completed.releaseISR();
            break;

        case UARTNotifyID::rxCompleted:
        	//_completed.releaseISR();
            break;

        default:
            break;

    }
}

