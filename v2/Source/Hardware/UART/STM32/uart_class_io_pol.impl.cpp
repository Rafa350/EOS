module;


#include "HTL/htl.h"


module Eos.Hardware.UART.__CLASSES;


import Eos.Bits;
import Eos.Hardware.Atomic;
import Eos.Types;
import Eos.System.Core.Ticks;


using namespace eos;
using namespace eos::hardware::uart;


/// ----------------------------------------------------------------------
/// @brief    Transmiteix un bloc de dades.
/// @param    buffer: El bloc de dades.
/// @param    length: La longitut del bloc en bytes.
/// @param    blockTime: Temps maxim de bloqueig.
///
UARTDevice::Result UARTDevice::transmit(
	const UInt8 *buffer,
	UInt32 length,
	Ticks blockTime) {

	if (_state == State::ready) {

		auto expireTime = Ticks::now() + blockTime;
		bool error = false;

		_state = State::transmiting;

		enable();
		enableTransmission();

		while (length-- > 0) {
			if (!waitTransmissionBufferEmpty(expireTime)) {
				error = true;
				break;
			}
			writeData(*buffer++);
		}

	    error = !waitTransmissionComplete(expireTime);

		disableTransmission();
		disable();

		_state = State::ready;

		return error ? ErrorCode::timeout : ErrorCode::ok;
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return ErrorCode::busy;

	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Reb en bloc de dades.
/// @param    buffer: Buffer de recepcio de dades.
/// @param    bufferSize: Tamany del buffer en bytes.
/// @param    blockTime: Temps maxim de bloqueig.
/// \return   El resultat.
///
UARTDevice::Result UARTDevice::receive(
	UInt8 *buffer,
	UInt32 bufferSize,
	Ticks blockTime) {

	if (_state == State::ready) {

		_state = State::receiving;

		auto expireTime = eos::Ticks::now() + blockTime;
		bool error = false;

		enable();
		enableReception();

		while (bufferSize-- > 0) {

			if (!waitReceptionBufferFull(expireTime)) {
				error = true;
				break;
			}
			*buffer++ = readData();
		}

		disableTransmission();

		_state = State::ready;

		return error ? ErrorCode::timeout : ErrorCode::ok;
	}
	else if ((_state == State::transmiting) || (_state == State::receiving))
		return ErrorCode::busy;

	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Habilita la transmissio de dades.
///
void UARTDevice::enableTransmission() const {

	auto a = Atomic::start();
	Bits::set(_usart->CR1,
		USART_CR1_TE);       // Habilita la tramsmissio
	Atomic::end(a);
}


/// ----------------------------------------------------------------------
/// @brief    Habilita la recepcio.
///
void UARTDevice::enableReception() const {

#if !defined(EOS_PLATFORM_STM32F4)
	_usart->ICR = USART_ICR_RTOCF; // Borra el flag RTO
#endif

	auto a = Atomic::start();
	Bits::set(_usart->CR1,
		USART_CR1_RE);            // Habilita la recepcio
	Atomic::end(a);
}
