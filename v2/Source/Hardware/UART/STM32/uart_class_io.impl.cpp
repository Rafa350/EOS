module;


#include "hardware.h"


module Eos.Hardware.UART.__CLASSES;


import Eos.Bits;
import Eos.Hardware.Atomic;


using namespace eos;
using namespace eos::hardware::uart;


/// ----------------------------------------------------------------------
/// @brief    Aborta la transmissio.
///
UARTDevice::Result UARTDevice::abortTransmission() {

	if (_state == State::transmiting) {
		disableTransmission();
		disable();
		_state = State::ready;
		return ErrorCode::ok;
	}
	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Aborta la recepcio.
///
UARTDevice::Result UARTDevice::abortReception() {

	if (_state == State::receiving) {
		disableReception();
		disable();
		_state = State::ready;
		return ErrorCode::ok;
	}
	else
		return ErrorCode::errorState;
}

/// ----------------------------------------------------------------------
/// @brief    Deshabilita la transmissio
///
void UARTDevice::disableTransmission() const {

	auto a = Atomic::start();

	Bits::clear(_usart->CR1,
#if defined(EOS_PLATFORM_STM32G0)
		USART_CR1_TXEIE_TXFNFIE | // Deshabilita interrupcio TXE
#else
		USART_CR1_TXEIE |         // Deshabilita interrupcio TXE
#endif
		USART_CR1_TCIE);          // Deshabilita interrupcio TC

	Bits::clear(_usart->CR3,
		USART_CR3_DMAT);      // Desabilita el DMA

	// TODO: Asegurar-se que l'ultim byte s'ha transmes abans de deshabilitar
	// la transmissio

	Bits::clear(_usart->CR1,
		USART_CR1_TE);            // Desabilita transmissio

	Atomic::end(a);
}


/// ----------------------------------------------------------------------
/// @brief    Deshabilita la recepcio.
///
void UARTDevice::disableReception() const {

	auto a = Atomic::start();

	Bits::clear(_usart->CR1,
#if defined(EOS_PLATFORM_STM32G0)
		USART_CR1_RXNEIE_RXFNEIE | // Deshabilita interrupcio RXNE
#else
		USART_CR1_RXNEIE |         // Deshabilita interrupcio RXNE
#endif
#if !defined(EOS_PLATFORM_STM32F4)
		USART_CR1_RTOIE |          // Deshabilita interrupcio RTO
#endif
		USART_CR1_IDLEIE |         // Deshabilita interrupcio IDLE
		USART_CR1_PEIE);           // Deshabilita interrupcio PE

	Bits::clear(_usart->CR3,
		USART_CR3_DMAT);           // Desabilita el DMA

	Bits::clear(_usart->CR1,
		USART_CR1_RE);             // Deshabilita recepcio

	Atomic::end(a);
}


/// ----------------------------------------------------------------------
/// @brief    Genera un event de notificacio 'TxComplete'
/// @param    buffer: El buffer de dades.
/// @param    length: El nombre de bytes de dades.
/// @param    irq: true si ve d'una interrupcio.
///
void UARTDevice::raiseTxCompletedNotification(
	const UInt8 *buffer,
	UInt32 length,
	bool irq) {

	if (_notificationEventRaiser) {

		NotificationEventArgs args = {
			.id = NotificationID::txCompleted,
			.irq = irq,
			.txCompleted {
				.buffer = buffer,
				.length = length
			}
		};

		_notificationEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Genera un event de notificacio 'RxComplete'
/// @param    buffer: El buffer de dades.
/// @param    length: El nombre de bytes de dades.
/// @param    irq: true si ve d'una interrupcio.
///
void UARTDevice::raiseRxCompletedNotification(
	const UInt8 *buffer,
	UInt32 length,
	bool irq) {

	if (_notificationEventRaiser) {

		NotificationEventArgs args = {
			.id = NotificationID::rxCompleted,
			.irq = irq,
			.rxCompleted {
				.buffer = buffer,
				.length = length
			}
		};

		_notificationEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Espera que s'hagi completat la transmissio
/// @param    timeout: El temps maxim d'espera en ticks.
/// \return   True si tot es correcte, false en cas de timeout.
///
bool UARTDevice::waitTransmissionComplete(
	Ticks expireTime) {

#if defined(EOS_PLATFORM_STM32F4)
	while (!isSet(_usart->SR, USART_SR_TC)) {
#else
	while (!Bits::isSet(_usart->ISR, USART_ISR_TC)) {
#endif
		if (expireTime.hasExpiredNow())
			return false;
	}

	//usart->ICR = USART_ICR_TCCF;

	return true;
}


/// ----------------------------------------------------------------------
/// @brief    Espera que el buffer de transmissio estigui buit.
/// @param    expireTime: El limit de temps.
/// \return   True si tot es correcte, false en cas de timeout.
///
bool UARTDevice::waitTransmissionBufferEmpty(
	Ticks expireTime) {

#if defined(EOS_PLATFORM_STM32G0)
	while (!Bits::isSet(_usart->ISR, USART_ISR_TXE_TXFNF)) {
#elif defined(EOS_PLATFORM_STM32F4)
	while (!isSet(_usart->SR, USART_SR_TXE)) {
#else
	while (!isSet(_usart->ISR, USART_ISR_TXE)) {
#endif
		if (expireTime.hasExpiredNow())
			return false;
	}

	return true;
}


/// ----------------------------------------------------------------------
/// @brief    Espera que el buffer de recepcio estigui ple
/// @param    expireTime: El limit de temps.
/// \return   True si tot es correcte, false en cas de timeout.
///
bool UARTDevice::waitReceptionBufferFull(
	Ticks expireTime) {

#if defined(EOS_PLATFORM_STM32G0)
	while ((_usart->ISR & USART_ISR_RXNE_RXFNE) == 0) {
#elif defined(EOS_PLATFORM_STM32F4)
	while ((_usart->SR & USART_SR_RXNE) == 0) {
#else
	while ((_usart->ISR & USART_ISR_RXNE) == 0) {
#endif
		if (expireTime.hasExpiredNow())
			return false;
	}

	return true;
}


/// ----------------------------------------------------------------------
/// @brief    Escriu el registre de transmissio des dades.
/// @param    usart: Registres de hardware del dispositiu.
/// @param    data: Les dades a transmetre.
//
void UARTDevice::writeData(
	UInt8 data) const {

#if defined(EOS_PLATFORM_STM32F4)
	_usart->DR = data;
#else
	_usart->TDR = data;
#endif
}


/// ----------------------------------------------------------------------
/// @brief    Llegeix el registre de recepcio dades.
/// @param    usart: Registres de hardware del dispositiu.
/// \return   Les dades rebudes.
//
UInt8 UARTDevice::readData() const {

#if defined(EOS_PLATFORM_STM32F4)
	return _usart->DR;
#else
	return _usart->RDR;
#endif
}


#if (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)
/// ----------------------------------------------------------------------
/// @brief    Comprova si el fifo esta disposnible en la uart
/// \return   El resultat de l'operacio.
///
bool htl::uart::UARTDevice::isFifoAvailable() const {

	return false;
}
#endif // (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)


#if (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)
/// ----------------------------------------------------------------------
/// @brief    Comprova si el fifo esta activat
/// \return   El resultatd e l'operacio.
///
bool htl::uart::UARTDevice::isFifoEnabled() const {

	return isSet(_uart->CR1, USART_CR1_FIFOEN);
}
#endif // (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)
