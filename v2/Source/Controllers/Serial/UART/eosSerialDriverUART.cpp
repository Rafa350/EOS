module;


#include "eos.h"


#ifndef EOS_NEW_UART
#include "HTL/htlUART.h"
#endif


export module Eos.Controllers.Serial.UART;


export import Eos.Controllers.Serial;


#ifdef EOS_NEW_UART
import Eos.Hardware.UART;
#endif


export namespace eos {

	class SerialDriver_UART: public SerialDriver {
		public:
#ifdef EOS_NEW_UART
			using UARTDevice = eos::hardware::uart::UARTDevice;
#else
			using UARTDevice = htl::uart::UARTDevice;
#endif

		protected:
			UARTDevice * const _devUART;

		private:
			UARTDevice::NotificationEvent<SerialDriver_UART> _devUART_notificationEvent;

		private:
			void devUART_notificationEventHandler(UARTDevice *sender, UARTDevice::NotificationEventArgs *args);

		protected:
            bool onInitialize() override;
            bool onDeinitialize() override;
            bool onTransmit(const uint8_t *buffer, size_t length) override;
            bool onReceive(uint8_t *buffer, size_t bufferSize) override;
            bool onAbort() override;

		public:
			SerialDriver_UART(UARTDevice *devUART);
	};
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devUART: El dispositiu uart a utilitzar.
///
eos::SerialDriver_UART::SerialDriver_UART(
	UARTDevice *devUART):

	_devUART {devUART},
	_devUART_notificationEvent {*this, &SerialDriver_UART::devUART_notificationEventHandler} {
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la inicialitzacio del driver.
/// \return   True si tot es correcte.
///
bool eos::SerialDriver_UART::onInitialize() {

	_devUART->enableNotificationEvent(_devUART_notificationEvent);

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la desinicialitzacio del driver.
/// \return   True si tot es correcte.
///
bool eos::SerialDriver_UART::onDeinitialize() {

	_devUART->disableNotificationEvent();

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la transmissio de dades.
/// \param    buffer: El buffer de dades.
/// \param    length: Nombre de bytes a transmetre.
/// \return   True si tot es correcte.
///
bool eos::SerialDriver_UART::onTransmit(
	const uint8_t *buffer,
	size_t length) {

    return _devUART->transmit_IRQ(buffer, length).isSuccess();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la recepcio de dades.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany en bytes del buffer de dades.
/// \return   True si tot es correcte.
///
bool eos::SerialDriver_UART::onReceive(
	uint8_t *buffer,
	size_t bufferSize) {

	return _devUART->receive_IRQ(buffer, bufferSize).isSuccess();
}


/// ----------------------------------------------------------------------
/// \brief    Aborta l'operacio en curs.
/// \return   True si tot es correcte.
///
bool eos::SerialDriver_UART::onAbort() {

	switch (getState()) {
		case State::receiving:
			return _devUART->abortReception().isSuccess();

		case State::transmiting:
			return _devUART->abortTransmission().isSuccess();

		default:
			return false;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Reb les notificacions del UART
/// \param    sender: El remitent.
/// \param    args: Parametres del event.
///
void eos::SerialDriver_UART::devUART_notificationEventHandler(
	UARTDevice *sender,
	UARTDevice::NotificationEventArgs *args) {

	switch (args->id) {

		// Notificacio del final de la transmissio
		//
		case UARTDevice::NotificationID::txCompleted:
		    notifyTxCompleted(args->txCompleted.length, args->irq);
			break;

    	// Notificacio del final de la recepcio
		//
		case UARTDevice::NotificationID::rxCompleted:
		    notifyRxCompleted(args->rxCompleted.length, args->irq);
			break;

    	// Notificacio un error en la comunicacio
		//
		case UARTDevice::NotificationID::error:
			break;

    	// Notificacio nula
		//
		case UARTDevice::NotificationID::null:
			break;
	}
}
