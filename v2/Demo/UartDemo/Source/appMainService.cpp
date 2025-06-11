#include "eos.h"
#include "HTL/htlINT.h"
#include "HTL/htlDMA.h"
#include "HTL/htlUART.h"

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
	_devUART {hw::devUART},
	_uartNotifyEvent {*this, &MainService::uartNotifyEventHandler} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void MainService::onExecute() {

    // Inicialitza la UART
	//
	_devUART->initPinTX<hw::PinTX>();
	_devUART->initPinRX<hw::PinRX>();
	_devUART->initialize();

	_devUART->setProtocol(WordBits::wb8, Parity::none, StopBits::sb1, Handsake::none);
	_devUART->setTimming(BaudMode::b19200, 0, OverSampling::os16);
#if defined(EOS_PLATFORM_STM32F7)
	_devUART->setClockSource(ClockSource::pclk);
#elif defined(EOS_PLATFORM_STM32G0)
	_devUART->setClockSource(ClockSource::pclk);
#endif

	while (!stopSignal()) {

		testInterruptMode();
	}
}


void MainService::testPollingMode() {

	const char *txBuffer = "Interrupt: Hello world!\r\n";
	for (auto i = 0; (i < 100) && !stopSignal(); i++)
		_devUART->transmit((const uint8_t*)txBuffer, strlen(txBuffer), 1000);
}


void MainService::testInterruptMode() {

	setInterruptVectorPriority(hw::devUART_VectorID, Priority::p5);
	enableInterruptVector(hw::devUART_VectorID);

	_devUART->setNotifyEvent(_uartNotifyEvent, true);

	const char *txBuffer = "Interrupt: Hello world!\r\n";
	for (auto i = 0; (i < 100) && !stopSignal(); i++) {
		_devUART->transmit_IRQ((const uint8_t*)txBuffer, strlen(txBuffer));
		_completed.wait((unsigned) -1);
	}

	_devUART->disableNotifyEvent();

	disableInterruptVector(hw::devUART_VectorID);
}


void MainService::testDmaMode() {

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

