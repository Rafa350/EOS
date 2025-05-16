#include "eos.h"
#include "HTL/htlINT.h"
#include "HTL/htlDMA.h"
#include "Controllers/Serial/eosSerialDriver_UART.h"

#include "appConfig.h"
#include "appMainService.h"

using namespace app;
using namespace htl::irq;


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
	devUART->initPinTX<hw::PinTX>();
	devUART->initPinRX<hw::PinRX>();
	devUART->initialize();

	devUART->setProtocol(htl::uart::WordBits::word8, htl::uart::Parity::none,
	        htl::uart::StopBits::_1, htl::uart::Handsake::none);
	devUART->setTimming(htl::uart::BaudMode::b19200,
	        htl::uart::ClockSource::automatic, 0, htl::uart::OverSampling::_16);

	setInterruptVectorPriority(hw::devUART_VectorID, Priority::p5);
	enableInterruptVector(hw::devUART_VectorID);

	devUART->setNotifyEvent(_uartNotifyEvent, true);

	const char *txBuffer = "Hello world!\r\n";

	while (!stopSignal()) {

		devUART->transmit_IRQ((const uint8_t*)txBuffer, strlen(txBuffer));

		_completed.wait((unsigned) -1);
		eos::Task::delay(1000);
	}
}


/// ----------------------------------------------------------------------
/// \brief    : Procesa l'event del UART rxCompleted
/// \param    : notifyID: Identificador de la notificacio.
/// \params   : args : Parametres del event.
///
void MainService::uartNotifyEventHandler(
    htl::uart::NotifyID notifyID,
	htl::uart::NotifyEventArgs * const args) {

    switch (notifyID) {
        case htl::uart::NotifyID::txCompleted:
        	_completed.releaseISR();
            break;

        case htl::uart::NotifyID::rxCompleted:
        	//_completed.releaseISR();
            break;

        default:
            break;

    }
}

