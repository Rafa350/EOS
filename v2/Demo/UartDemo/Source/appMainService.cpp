#include "eos.h"
#include "Controllers/Serial/eosAsyncSerialDriver_UART.h"

#include "appConfig.h"
#include "appApplication.h"
#include "appMainService.h"


using namespace eos;
using namespace htl;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
MainService::MainService():
	_uartNotifyEvent {*this, &MainService::uartNotifyEventHandler} {

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
	hw::devUART->initPinTX<hw::PinTX>();
	hw::devUART->initPinRX<hw::PinRX>();
	hw::devUART->initialize();

	hw::devUART->setProtocol(htl::uart::WordBits::_8, htl::uart::Parity::none,
	        htl::uart::StopBits::_1, htl::uart::Handsake::none);
#if defined( EOS_PLATFORM_STM32)
	hw::devUART->setTimming(htl::uart::BaudMode::_19200,
	        htl::uart::ClockSource::automatic, 0, htl::uart::OverSampling::_16);
#elif defined(EOS_PLATFORM_PIC32)
	hw::devUART->setTimming(_baudMode);
#else
#error "Undefined EOS_PLATFORM_XXX"
#endif
	irq::setInterruptVectorPriority(irq::VectorID::uart1, irq::Priority::_5);
	irq::enableInterruptVector(irq::VectorID::uart1);
	hw::devUART->setNotifyEvent(_uartNotifyEvent, true);
	hw::devUART->enable();

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio.
///
bool MainService::onTask() {

	const char *txBuffer = "Hello world!\r\n";

	hw::devUART->transmit_IRQ((const uint8_t*)txBuffer, strlen(txBuffer));

	Task::delay(100);

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    : Procesa l'event del UART rxCompleted
/// \params   : args : Parametres del event.
///
void MainService::uartNotifyEventHandler(
    const htl::uart::UARTDevice *uart,
	const htl::uart::NotifyEventArgs &args) {

    switch (args.id) {
        case uart::NotifyID::txCompleted:
            break;

        case uart::NotifyID::rxCompleted:
            break;

        default:
            break;

    }
}

