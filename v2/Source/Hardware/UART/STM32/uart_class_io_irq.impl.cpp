module;


#include "hardware.h"


module Eos.Hardware.UART.__CLASSES;


import Eos.Bits;
import Eos.Hardware.Atomic;


using namespace eos;
using namespace eos::hardware::uart;


/// ----------------------------------------------------------------------
/// @brief    Inicia la transmissio d'un bloc de dades per interrupcions.
/// @param    buffer: Buffer de dades.
/// @param    length: El nombre de bytes a transmetre.
/// @return   El resultat de l'operacio
///
UARTDevice::Result UARTDevice::transmit_IRQ(
	const UInt8 *buffer,
	UInt32 length) {

	if (_state == State::ready) {

		_state = State::transmiting;

		_txBuffer = buffer;
		_txCount = 0;
        _txMaxCount = length;

        enable();
        enableTransmissionIRQ();

		return ErrorCode::ok;
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return ErrorCode::busy;

	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Inicia la recepcio d'un bloc de dades per interrupcions.
/// @param    buffer: Buffer de dades.
/// @param    bufferSize: Tamany del buffer en bytes.
/// @return   El resultat de l'operacio.
///
UARTDevice::Result UARTDevice::receive_IRQ(
	UInt8 *buffer,
	UInt32 bufferSize) {

	if (_state == State::ready) {

		_state = State::receiving;

		_rxBuffer = buffer;
		_rxCount = 0;
		_rxMaxCount = bufferSize;

		enable();
		enableReceptionIRQ();

		return ErrorCode::ok;
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return ErrorCode::busy;

	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Habilita la transmissio de dades en modus IRQ
///
#if defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
void htl::uart::UARTDevice::enableTransmissionIRQ() const {

	auto a = startAtomic();

	set(_usart->CR1,
		USART_CR1_TXEIE |          // Habilita interrupcio TXE
		USART_CR1_TE);             // Habilita la transmissio
	endAtomic(a);
}
#elif defined(EOS_PLATFORM_STM32G0)
void UARTDevice::enableTransmissionIRQ() const {

	auto a = Atomic::start();

	Bits::set(_usart->CR1,
		USART_CR1_TXEIE_TXFNFIE |  // Habilita interrupcio TXE
		USART_CR1_TE);             // Habilita la transmissio

	Atomic::end(a);
}
#else
#error "Unknown platform"
#endif // defined(EOS_PLATFORM_XXX)


/// ----------------------------------------------------------------------
/// @brief    Habilita la recepcio en modus IRQ.
/// @param    usart: Registres de hardware del dispoositiu.
///
void UARTDevice::enableReceptionIRQ() const {

#if !defined(EOS_PLATFORM_STM32F4)
	Bits::set(_usart->ICR,
		USART_ICR_RTOCF |           // Borra el flag RTO
		USART_ICR_IDLECF);          // Borra el flag IDLE
#endif

	auto a = Atomic::start();

	Bits::set(_usart->CR1,
		USART_CR1_PEIE |            // Habilita interrupcio PE
#if defined(EOS_PLATFORM_STM32G0)
		USART_CR1_RXNEIE_RXFNEIE |  // Habilita interrupcio RXNE
#else
		USART_CR1_RXNEIE |          // Habilita interrupcio RXNE
#endif
		USART_CR1_RE);              // Habilita la recepcio

	// Activa RTO si es posible, si no, activa IDLE
	// Notes:  Si RTO no esta suportat RTOEN sempre estara a zero per hardware
	//
#if defined(EOS_PLATFORM_STM32F4)
	set(_usart->CR1, USART_CR1_IDLEIE);       // Habilita interrupcio IDLE
#else
	if (_usart->CR2 & USART_CR2_RTOEN)
		Bits::set(_usart->CR1, USART_CR1_RTOIE);    // Habilita interrupcio RTO
	else
		Bits::set(_usart->CR1, USART_CR1_IDLEIE);   // Habilita interrupcio IDLE
#endif

	Atomic::end(a);
}


/// ----------------------------------------------------------------------
/// @brief    Procesa les interrupcions.
///
void UARTDevice::interruptService() {

	if (_state == State::transmiting)
		txInterruptService();

	else if (_state == State::receiving)
		rxInterruptService();

	// Espera que no hagin escriptures pendents
	//
	DSB();
}


/// ----------------------------------------------------------------------
/// @brief    Procesa les interrupcions per la transmissio
///
#if defined(EOS_PLATFORM_STM32F4)
void UARTDevice::txInterruptService() {

	auto CR1 = _usart->CR1;
	auto SR = _usart->SR;

	// Interrupcio 'TXE'
	//
	if (isSet(CR1, USART_CR1_TXEIE) && isSet(SR, USART_SR_TXE)) {
		if (_txCount < _txMaxCount) {
			_usart->DR = _txBuffer[_txCount++];
			if (_txCount == _txMaxCount) {
				auto a = startAtomic();
				clear(_usart->CR1, USART_CR1_TXEIE); // Deshabilita interrupcio TXE
				set(_usart->CR1, USART_CR1_TCIE);    // Habilita interrupcio TC
				endAtomic(a);
			}
		}
	}

	// Interrupcio 'TC'. Nomes en l'ultim caracter transmes.
	//
	if (isSet(CR1, USART_CR1_TCIE) && isSet(SR, USART_SR_TC)) {
		disableTransmission();
		notifyTxCompleted(_txBuffer, _txCount, true);
		_state = State::ready;
	}
}

#elif defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F7)
void htl::uart::UARTDevice::txInterruptService() {

	auto CR1 = _usart->CR1;
	auto ISR = _usart->ISR;

	// Interrupcio 'TXE'
	//
	if (isSet(CR1, USART_CR1_TXEIE) && isSet(ISR, USART_ISR_TXE)) {
		if (_txCount < _txMaxCount) {
			_usart->TDR = _txBuffer[_txCount++];
			if (_txCount == _txMaxCount) {
				auto a = startAtomic();
				clear(_usart->CR1, USART_CR1_TXEIE); // Deshabilita interrupcio TXE
				set(_usart->CR1, USART_CR1_TCIE);    // Habilita interrupcio TC
				endAtomic(a);
			}
		}
	}

	// Interrupcio 'TC'. Nomes en l'ultim caracter transmes.
	//
	if (isSet(CR1, USART_CR1_TCIE) && isSet(ISR, USART_ISR_TC)) {
		disableTransmission();
		raiseTxCompletedNotification(_txBuffer, _txCount, true);
		_state = State::ready;
	}
}

#elif defined(EOS_PLATFORM_STM32G0)
void UARTDevice::txInterruptService() {

	auto CR1 = _usart->CR1;
	auto ISR = _usart->ISR;

	// Interrupcio 'TXE' (Transmission buffer empty)
	//
	if (Bits::isSet(CR1, USART_CR1_TXEIE_TXFNFIE) &&
		Bits::isSet(ISR, USART_ISR_TXE_TXFNF)) {
		if (_txCount < _txMaxCount) {
			_usart->TDR = _txBuffer[_txCount++];
			if (_txCount == _txMaxCount) {
				auto a = Atomic::start();
				eos::Bits::clear(_usart->CR1, USART_CR1_TXEIE_TXFNFIE);  // Deshabilita interrupcio TXE
				eos::Bits::set(_usart->CR1, USART_CR1_TCIE);             // Habilita interrupcio TC
				Atomic::end(a);
			}
		}
	}

	// Interrupcio 'TC'. (Transmission complete)
	//
	if (Bits::isSet(CR1, USART_CR1_TCIE) &&
		Bits::isSet(ISR, USART_ISR_TC)) {
		disableTransmission();
		raiseTxCompletedNotification(_txBuffer, _txCount, true);
		_state = State::ready;
	}
}
#else
#error "Unknown platform"
#endif // defined(SOS_PLATFORM_XXX)


/// ----------------------------------------------------------------------
/// @brief    Procesa les interrupcions per la recepcio.
///
#if defined(EOS_PLATFORM_STM32F4)
void UARTDevice::rxInterruptService() {

	auto CR1 = _usart->CR1;
	auto SR = _usart->SR;

	/// Interrupcio 'RXNE'
	//
	if (isSet(CR1, USART_CR1_RXNEIE) && isSet(SR, USART_SR_RXNE)) {
		if (_rxCount < _rxMaxCount) {
			_rxBuffer[_rxCount++] = _usart->DR;
			if (_rxCount == _rxMaxCount) {
				disableReception();
				notifyRxCompleted(_rxBuffer, _rxCount, true);
				_state = State::ready;
			}
		}
	}

	// Interrupcio 'IDLE'
	//
	if (isSet(CR1, USART_CR1_IDLEIE) && isSet(SR, USART_SR_IDLE)) {
		if (_rxCount > 0) {
			disableReception();
			notifyRxCompleted(_rxBuffer, _rxCount, true);
			_state = State::ready;
		}
	}
}

#elif defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F7)
void UARTDevice::rxInterruptService() {

	auto CR1 = _usart->CR1;
	auto ISR = _usart->ISR;

	/// Interrupcio 'RXNE'
	//
	if (isSet(CR1, USART_CR1_RXNEIE) && isSet(ISR, USART_ISR_RXNE)) {
		if (_rxCount < _rxMaxCount) {
			_rxBuffer[_rxCount++] = _usart->RDR;
			if (_rxCount == _rxMaxCount) {
				disableReception();
				raiseRxCompletedNotification(_rxBuffer, _rxCount, true);
				_state = State::ready;
			}
		}
	}

	// Interrupcio 'IDLE'
	//
	if (isSet(CR1, USART_CR1_IDLEIE) && isSet(ISR, USART_ISR_IDLE)) {
		_usart->ICR = USART_ICR_IDLECF;
		if (_rxCount > 0) {
			disableReception();
			raiseRxCompletedNotification(_rxBuffer, _rxCount, true);
			_state = State::ready;
		}
	}

	// Interrupcio 'RTO'
	//
	if (isSet(CR1, USART_CR1_RTOIE) && isSet(ISR, USART_ISR_RTOF)) {
		_usart->ICR = USART_ICR_RTOCF;
		disableReception();
		raiseRxCompletedNotification(_rxBuffer, _rxCount, true);
		_state = State::ready;
	}
}

#elif defined(EOS_PLATFORM_STM32G0)
void UARTDevice::rxInterruptService() {

	auto CR1 = _usart->CR1;
	auto ISR = _usart->ISR;

	/// Interrupcio 'RXNE'
	//
	if (eos::Bits::isSet(CR1, USART_CR1_RXNEIE_RXFNEIE) &&
		eos::Bits::isSet(ISR, USART_ISR_RXNE_RXFNE)) {
		if (_rxCount < _rxMaxCount) {
			_rxBuffer[_rxCount++] = _usart->RDR;
			if (_rxCount == _rxMaxCount) {
				disableReception();
				raiseRxCompletedNotification(_rxBuffer, _rxCount, true);
				_state = State::ready;
			}
		}
	}

	// Interrupcio 'IDLE'
	//
	if (eos::Bits::isSet(CR1, USART_CR1_IDLEIE) &&
		eos::Bits::isSet(ISR, USART_ISR_IDLE)) {
		_usart->ICR = USART_ICR_IDLECF;
		if (_rxCount > 0) {
			disableReception();
			raiseRxCompletedNotification(_rxBuffer, _rxCount, true);
			_state = State::ready;
		}
	}

	// Interrupcio 'RTO'
	//
	if (eos::Bits::isSet(CR1, USART_CR1_RTOIE) &&
		eos::Bits::isSet(ISR, USART_ISR_RTOF)) {
		_usart->ICR = USART_ICR_RTOCF;
		disableReception();
		raiseRxCompletedNotification(_rxBuffer, _rxCount, true);
		_state = State::ready;
	}
}
#else
#error "Unknown platform"
#endif // defined(EOS_PLATFORM_XXX
