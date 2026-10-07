module;


#include "HTL/htl.h"


module Eos.Hardware.UART.__CLASSES;


import Eos.Bits;
import Eos.Types;
import Eos.Hardware.Atomic;


using namespace eos;
using namespace eos::hardware::uart;


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el modul UART.
/// \return   El resultat de l'operacio.
///
UARTDevice::Result UARTDevice::initialize() {

	if (_state == State::reset) {

		activate();
		disable();

#if defined(EOS_PLATFORM_STM32G0)
#if HTL_UART_OPTION_FIFO == 1
		if (isFifoAvailable())
			bits::set(_usart->CR1,
				USART_CR1_FIFOEN);    // Habilita el FIFO
		else
#endif
			Bits::clear(_usart->CR1,
				USART_CR1_FIFOEN);    // Deshabilita el FIFO
#endif

		Bits::clear(_usart->CR2,
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			USART_CR2_LINEN |     // Deshabilita modus LIN
#endif
#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			USART_CR2_RTOEN |     // Deshabilita receiver timeout
#endif
     		USART_CR2_CLKEN);     // Deshabilita clock extern

		Bits::clear(_usart->CR3,
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			USART_CR3_SCEN |      // Deshabilita modus SmartCard
			USART_CR3_IREN |      // Deshabilita modus IrDA
#endif
			USART_CR3_DMAT |      // Desbilita DMA
			USART_CR3_HDSEL);     // Deshabilita half duplex

		_state = State::ready;

		return ErrorCode::ok;
	}

	else
		return ErrorCode::errorState;
}


/// ---------------------------------------------------------------------------
/// @brief    Desinicialitza el modul.
/// \return   El resultat de l'operacio.
///
#if HTL_UART_OPTION_DEACTIVATE == 1
eos::Result htl::uart::UARTDevice::deinitialize() {

	if (_state == State::ready) {

		disable();
		deactivate();

		_state = State::reset;

		return eos::Result::ErrorCodes::success;
	}

	else
		return eos::Result::ErrorCodes::errorState;
}
#endif


/// ---------------------------------------------------------------------------
/// @brief    Aactiva el dispositiu fisic.
///
void UARTDevice::activate() const {

    activateImpl();
}


/// ---------------------------------------------------------------------------
/// @brief    Desactiva el dispositiu fisic.
///
#if HTL_UART_OPTION_DEACTIVATE == 1
void  u::UARTDevice::deactivate() const {

    deactivateImpl();
}
#endif


/// ----------------------------------------------------------------------
/// @brief    Selecciona el protocol de comunicacio.
/// @param    wordBits: Les opcions de paraula.
/// @param    parity: Les opcions de paritat.
/// @param    stopBits: Les opcions de parada.
/// @param    handsake: Protocol.
/// @return   El resultat de l'operacio.
///
UARTDevice::Result UARTDevice::setProtocol(
	WordBits wordBits,
	Parity parity,
	StopBits stopBits,
	Handsake handsake) const {

	if (_state == State::ready) {
		setParity(parity);
		setWordBits(wordBits, parity != Parity::none);
		setStopBits(stopBits);
		setHandsake(handsake);
		return ErrorCode::ok;
	}
	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Configura la paritat.
/// @param    usart: Registres de hardware del dispositiu.
/// @param    parity: Opcions de paritat.
///
 void UARTDevice::setParity(
    Parity parity) const {

    auto CR1 = _usart->CR1;
    if (parity == Parity::none)
    	Bits::clear(CR1, USART_CR1_PCE);
    else {
    	Bits::set(CR1, USART_CR1_PCE);
    	if (parity == Parity::even)
    		Bits::clear(CR1, USART_CR1_PS);
    	else
    		Bits::set(CR1, USART_CR1_PS);
    }
    _usart->CR1 = CR1;
}


/// ----------------------------------------------------------------------
/// @brief    Configura el nombre de bits de parada
/// @param    usart: Registres de harware del dispositiu.
/// @param    stopBits: Opcions dels bits de parada.
///
void UARTDevice::setStopBits(
    StopBits stopBits) const {

    auto CR2 = _usart->CR2;
    switch (stopBits) {
        case StopBits::sb0p5:
            Bits::clear(CR2, USART_CR2_STOP_1);
            Bits::set(CR2, USART_CR2_STOP_0);
            break;

        case StopBits::sb1:
        	Bits::clear(CR2, USART_CR2_STOP_1);
        	Bits::clear(CR2, USART_CR2_STOP_0);
            break;

        case StopBits::sb1p5:
        	Bits::set(CR2, USART_CR2_STOP_1);
        	Bits::set(CR2, USART_CR2_STOP_0);
            break;

        case StopBits::sb2:
        	Bits::set(CR2, USART_CR2_STOP_1);
        	Bits::clear(CR2, USART_CR2_STOP_0);
            break;
    }
    _usart->CR2 = CR2;
}


/// ----------------------------------------------------------------------
/// @brief    Configura nombre de bits de paraula.
/// @param    usart: Registres de herdware del dispositiu.
/// @param    wordBits: Opcions dels bits de paraula.
/// \params   useParity: True si utilitza bit de paritat
///
#if defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
void htl::uart::UARTDevice::setWordBits(
    WordBits wordBits,
    bool useParity) const {

	auto numBits = useParity? 1 : 0;
	switch (wordBits) {
		case WordBits::wb8:
			numBits += 8;
			break;

		case WordBits::wb9:
			numBits += 9;
			break;
	}

	auto a = startAtomic();
	auto CR1 = _usart->CR1;
	if (numBits == 8)
		clear(CR1, USART_CR1_M);
	else
		set(CR1, USART_CR1_M);
	_usart->CR1 = CR1;
	endAtomic(a);
}

#elif defined(EOS_PLATFORM_STM32G0)
void UARTDevice::setWordBits(
    WordBits wordBits,
    bool useParity) const {

	auto numBits = useParity? 1 : 0;
	switch (wordBits) {
		case WordBits::wb7:
			numBits += 7;
			break;

		case WordBits::wb8:
			numBits += 8;
			break;

		case WordBits::wb9:
			numBits += 9;
			break;
	}

	auto a = Atomic::start();

	auto CR1 = _usart->CR1;
	switch (numBits) {
		case 7:
			Bits::clear(CR1, USART_CR1_M0);
			Bits::set(CR1, USART_CR1_M1);
			break;

		default:
		case 8:
			Bits::clear(CR1, USART_CR1_M0);
			Bits::clear(CR1, USART_CR1_M1);
			break;

		case 9:
			Bits::set(CR1, USART_CR1_M0);
			Bits::clear(CR1, USART_CR1_M1);
			break;
	}
	_usart->CR1 = CR1;

	Atomic::end(a);
}
#else
#error "Unknown platform"
#endif // defined(EOS_PLATFORM_XXX)


/// ----------------------------------------------------------------------
/// @brief    Configura el protocol.
/// @param    usart: Registres de hardware del dispositiu.
/// @param    handsake: Opcions de protocol.
///
void UARTDevice::setHandsake(
    Handsake handsake) const {

    auto CR3 = _usart->CR3;
    switch (handsake) {
        case Handsake::none:
        	Bits::clear(CR3, USART_CR3_RTSE | USART_CR3_CTSE);
            break;

        case Handsake::ctsrts:
        	Bits::set(CR3, USART_CR3_RTSE | USART_CR3_CTSE);
            break;
    }
    _usart->CR3 = CR3;
}


#if defined(EOS_PLATFORM_STM32F0) || \
	defined(EOS_PLATFORM_STM32F7) || \
	defined(EOS_PLATFORM_STM32G0)
/// ----------------------------------------------------------------------
/// @brief    Asigna el valor del timeout per recepcio.
/// @param    timeout: El temps.
/// @param    El resultat de l'operacio.
///
UARTDevice::Result UARTDevice::setRxTimeout(
    unsigned timeout) const {

	if (_state == State::ready) {

		if (isRTOAvailable()) {
			if (timeout == 0)
				Bits::clear(_usart->CR2, USART_CR2_RTOEN);
			else {
				Bits::set(_usart->CR2, USART_CR2_RTOEN);
				_usart->RTOR = timeout;
			}
		}

		return ErrorCode::ok;
	}
	else
		return ErrorCode::errorState;
}
#endif // defined(EOS_PLATFORM_XXX)


/// ----------------------------------------------------------------------
/// @brief    Asigna els valor de temporitzacio.
/// @param    baudMode: Les opcions del baud rate
/// @param    rate: El valor de velocitat.
/// @param    overSampling: Tipus de mostreig
/// @return   El resultat de l'operacio.
///
UARTDevice::Result UARTDevice::setTimming(
	BaudMode baudMode,
	UInt32 rate,
	OverSampling overSampling) const {

	if (_state == State::ready) {

		switch (baudMode) {
			case BaudMode::b1200:
				rate = 1200;
				break;

			case BaudMode::b2400:
				rate = 2400;
				break;

			case BaudMode::b4800:
				rate = 4800;
				break;

			case BaudMode::b9600:
				rate = 9600;
				break;

			case BaudMode::b19200:
				rate = 19200;
				break;

			case BaudMode::b38400:
				rate = 38400;
				break;

			case BaudMode::b57600:
				rate = 57600;
				break;

			case BaudMode::b115200:
				rate = 115200;
				break;

			default:
				break;
		}

		auto fclk = eos::hardware::clock::Clock::pInst->getClockFrequency(getUARTClock());

		UInt32 div;
		if (baudMode == BaudMode::div)
			div = rate;
		else {
			if (overSampling == OverSampling::os8)
				div = (fclk + fclk + (rate / 2)) / rate;
			else
				div = (fclk + (rate / 2)) / rate;
		}

		if (overSampling == OverSampling::os8) {
			unsigned temp = (uint16_t)(div & 0xFFF0U);
			temp |= (uint16_t)((div & (uint16_t)0x000FU) >> 1U);
			_usart->BRR = temp;
		}
		else
			_usart->BRR = div;

		return ErrorCode::ok;
	}
	else
		return ErrorCode::errorState;
}


#if defined(EOS_PLATFORM_STM32F7) || \
	defined(EOS_PLATFORM_STM32G0)
/// ----------------------------------------------------------------------
/// @brief    Selecciona la font del relloge del generador de bauds
/// @param    clockSource: La font.
/// @return   El resultat de l'operacio.
///
UARTDevice::Result UARTDevice::setClockSource(
	ClockSource source) const {

	if(_state == State::ready){

		setClockSourceImpl(source);
		return ErrorCode::ok;
	}
	else
		return ErrorCode::errorState;
}
#endif // defined(EOS_PLATFORM_XXX)
