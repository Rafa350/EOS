#include "HTL/htl.h"
#include "HTL/STM32/htlClock.h"
#include "HTL/STM32/htlUART.h"


using namespace htl;
using namespace htl::uart;


/// ----------------------------------------------------------------------
/// \brief    Obte el rellotge asignat al generador de bauds.
/// \param    regs: El bloc de registres
/// \return   La opcio corresponent al rellotge.
///
static ClockSource getClockSource(
	USART_TypeDef *regs) {

	uint8_t sclk = 0;
    switch ((uint32_t)regs) {
		#ifdef HTL_UART1_EXIST
			case USART1_BASE:
				#if defined(EOS_PLATFORM_STM32G0) && defined(RCC_CCIPR_USART1SEL)
				sclk = (RCC->CCIPR & RCC_CCIPR_USART1SEL) >> RCC_CCIPR_USART1SEL_Pos;
				#elif defined(EOS_PLATFORM_STM32F0)
				sclk = (RCC->CFGR3 & RCC_CFGR3_USART1SW) >> RCC_CFGR3_USART1SW_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART1SEL) >> RCC_DCKCFGR2_USART1SEL_Pos;
				#endif
				break;
		#endif

		#ifdef HTL_UART2_EXIST
			case USART2_BASE:
				#if defined(EOS_PLATFORM_STM32G0) && defined(RCC_CCIPR_USART2SEL)
				sclk = (RCC->CCIPR & RCC_CCIPR_USART2SEL) >> RCC_CCIPR_USART2SEL_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART2SEL) >> RCC_DCKCFGR2_USART2SEL_Pos;
				#endif
				break;
		#endif

		#ifdef HTL_UART3_EXIST
			case USART3_BASE:
				#if defined(EOS_PLATFORM_STM32G0) && defined(RCC_CCIPR_USART3SEL)
				sclk = (RCC->CCIPR & RCC_CCIPR_USART3SEL) >> RCC_CCIPR_USART3SEL_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART3SEL) >> RCC_DCKCFGR2_USART3SEL_Pos;
				#endif
				break;
		#endif

		#ifdef HTL_UART4_EXIST
			case USART4_BASE:
				#if defined(EOS_PLATFORM_STM32G0)  && defined(RCC_CCIPR_USART4SEL)
				sclk = (RCC->CCIPR & RCC_CCIPR_USART4SEL) >> RCC_CCIPR_USART4SEL_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART4SEL) >> RCC_DCKCFGR2_UART4SEL_Pos;
				#endif
				break;
		#endif

		#ifdef HTL_UART5_EXIST
			case UART5_BASE:
				#if defined(EOS_PLATFORM_STM32F7)
				sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART5SEL) >> RCC_DCKCFGR2_UART5SEL_Pos;
				#endif
				break;
		#endif

		#ifdef HTL_UART6_EXIST
			case USART6_BASE:
				#if defined(EOS_PLATFORM_STM32F7)
				sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART6SEL) >> RCC_DCKCFGR2_USART6SEL_Pos;
				#endif
				break;
		#endif

		#ifdef HTL_UART7_EXIST
			case UART7_BASE:
				#if defined(EOS_PLATFORM_STM32F7)
				sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART7SEL) >> RCC_DCKCFGR2_UART7SEL_Pos;
				#endif
				break;
		#endif

		#ifdef HTL_UART8_EXIST
			case UART8_BASE:
				#if defined(EOS_PLATFORM_STM32F7)
				sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART8SEL) >> RCC_DCKCFGR2_UART8SEL_Pos;
				#endif
				break;
		#endif
    }

    switch (sclk & 0x03) {
    	default:
    	case 0: return ClockSource::pclk;
    	case 1: return ClockSource::sysclk;
    	case 2: return ClockSource::hsi;
    	case 3: return ClockSource::lse;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    usart: Registres hardware del modul USART.
///
UARTDevice::UARTDevice(
	USART_TypeDef *usart):

	_usart {usart},
	_state {State::reset},
	_notifyEvent {nullptr},
	_notifyEventEnabled {false} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul UART.
/// \return   El resultat de l'operacio.
///
UARTDevice::Result UARTDevice::initialize() {

	if (_state == State::reset) {

		activate();
		disable();

		_usart->CR1 &= ~USART_CR1_FIFOEN;
	    _usart->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
		_usart->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);

		_state = State::ready;
		return Result::ok;
	}

	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul.
/// \return   El resultat de l'operacio.
///
UARTDevice::Result UARTDevice::deinitialize() {

	if (_state == State::ready) {

		disable();
		deactivate();

		_state = State::reset;

		return Result::ok;
	}

	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el protocol de comunicacio.
/// \param    wordBits: Lers opcions de paraula.
/// \param    parity: Les opcions de paritat.
/// \param    stopBits: Les opcions de parada.
/// \param    handsake: Protocol.
///
void UARTDevice::setProtocol(
	WordBits wordBits,
	Parity parity,
	StopBits stopBits,
	Handsake handsake) {

	uint32_t tmp;

	// Configura el registre CR1 (Control Register 1)
	// -Tamany de paraula
	// -Paritat
	//
	tmp = _usart->CR1;

	switch (7 + uint32_t(wordBits) + (parity == Parity::none ? 0 : 1)) {
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		case 7:
			tmp |= USART_CR1_M1;
			tmp &= ~USART_CR1_M0;
			break;
		#endif

		case 8:
			#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			tmp &= ~USART_CR1_M1;
			tmp &= ~USART_CR1_M0;
			#else
			tmp &= ~USART_CR1_M;
			#endif
			break;

		case 9:
			#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			tmp &= ~USART_CR1_M1;
			tmp |= USART_CR1_M0;
			#else
			tmp |= USART_CR1_M;
			#endif
			break;
	}

    switch (parity) {
    	case Parity::none:
    		tmp &= ~USART_CR1_PCE;
    		break;

    	case Parity::even:
    		tmp |= USART_CR1_PCE;
    		tmp &= ~USART_CR1_PS;
    		break;

    	case Parity::odd:
    		tmp |= USART_CR1_PCE;
    		tmp |= USART_CR1_PS;
    		break;
    }
	_usart->CR1 = tmp;

	// Configura el registre CR2 (Control Register 2)
	// -Bits de parada
	// -Habilita del timeout en recepcio
	//
	tmp = _usart->CR2;
    switch (stopBits) {
    	case StopBits::_0p5:
    		tmp &= ~USART_CR2_STOP_1;
    		tmp |= USART_CR2_STOP_0;
    		break;

    	case StopBits::_1:
    		tmp &= ~USART_CR2_STOP_1;
    		tmp &= ~USART_CR2_STOP_0;
    		break;

    	case StopBits::_1p5:
    		tmp |= USART_CR2_STOP_1;
    		tmp |= USART_CR2_STOP_0;
    		break;

    	case StopBits::_2:
    		tmp |= USART_CR2_STOP_1;
    		tmp &= ~USART_CR2_STOP_0;
    		break;
    }
	tmp |= USART_CR2_RTOEN;
    _usart->CR2 = tmp;

    // Configura el registre CR3
    // -Opcions CTS
    // -Opcions RST
    //
    tmp = _usart->CR3;
    switch (handsake) {
		case Handsake::none:
			tmp &= ~(USART_CR3_RTSE | USART_CR3_CTSE);
			break;

		case Handsake::ctsrts:
			tmp |= (USART_CR3_RTSE | USART_CR3_CTSE);
			break;
	}
    _usart->CR3 = tmp;

    // El timeout en recepcio
    //
    _usart->RTOR = 11 * 100;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna els valor de temporitzacio.
/// \param    baudMode: Les opcions del baud rate
/// \param    clockSource: Les opcions de clocking.
/// \param    rate: El valor de velocitat.
/// \param    overSampling: Tipus de mostreig
///
void UARTDevice::setTimming(
	BaudMode baudMode,
	ClockSource clockSource,
	uint32_t rate,
	OverSampling overSampling) {

	switch (baudMode) {
    	case BaudMode::_1200:
    		rate = 1200;
    		break;

    	case BaudMode::_2400:
    		rate = 2400;
    		break;

    	case BaudMode::_4800:
    		rate = 4800;
    		break;

    	case BaudMode::_9600:
    		rate = 9600;
    		break;

    	case BaudMode::_19200:
    		rate = 19200;
    		break;

    	case BaudMode::_38400:
    		rate = 38400;
    		break;

    	case BaudMode::_57600:
    		rate = 57600;
    		break;

    	case BaudMode::_115200:
    		rate = 115200;
    		break;

    	default:
    		break;
    }

    uint32_t fclk;
    if (clockSource == ClockSource::automatic)
    	clockSource = getClockSource(_usart);
    switch (clockSource) {
    	default:
    	case ClockSource::pclk:
			#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
    		if ((uint32_t(_usart) == USART1_BASE) ||
    			(uint32_t(_usart) == USART6_BASE))
    			fclk =  clock::getClockFrequency(clock::ClockID::pclk2);
    		else
			#endif
    			fclk = clock::getClockFrequency(clock::ClockID::pclk);
    		break;

    	case ClockSource::sysclk:
    		fclk = clock::getClockFrequency(clock::ClockID::sysclk);
    		break;

		case ClockSource::hsi:
			#if defined(EOS_PLATFORM_STM32G0)
			fclk = clock::getClockFrequency(clock::ClockID::hsi16);
			#else
			fclk = clock::getClockFrequency(clock::ClockID::hsi);
			#endif
			break;

		case ClockSource::lse:
    		fclk = clock::getClockFrequency(clock::ClockID::lse);
    		break;
    }

    uint32_t div;
    if (baudMode == BaudMode::div)
    	div = rate;
    else {
        if (overSampling == OverSampling::_8)
        	div = (fclk + fclk + (rate / 2)) / rate;
        else
           	div = (fclk + (rate / 2)) / rate;
    }

    if (overSampling == OverSampling::_8) {
        uint32_t temp = (uint16_t)(div & 0xFFF0U);
        temp |= (uint16_t)((div & (uint16_t)0x000FU) >> 1U);
        _usart->BRR = temp;
    }
    else
    	_usart->BRR = div;
}


void UARTDevice::setNotifyEvent(
	INotifyEvent &event,
	bool enabled) {

	_notifyEvent = &event;
	_notifyEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades.
/// \param    data: Buffer de dades.
/// \param    dataLength: El nombre de bytes en el buffer.
/// \return   El resultat de l'operacio
///
UARTDevice::Result UARTDevice::transmit(
	const uint8_t *data,
	uint16_t dataLength) {

	if (_state == State::ready) {

		_state = State::transmiting;

		_txBuffer = data;
		_txSize = dataLength;
		_txCount = 0;

		_usart->CR1 |= USART_CR1_TXEIE_TXFNFIE;
		enableTX();

		return Result::ok;
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return Result::busy;

	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades.
/// \param    data: Buffer de dades.
/// \param    dataSize: Tamany del buffer en bytes.
/// \return   El resultat de l'operacio.
///
UARTDevice::Result UARTDevice::receive(
	uint8_t *data,
	uint16_t dataSize) {

	if (_state == State::ready) {

		_state = State::receiving;

		_rxBuffer = data;
		_rxSize = dataSize;
		_rxCount = 0;

		_usart->CR1 |= USART_CR1_RXNEIE_RXFNEIE;
		enableRX();

		return Result::ok;
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return Result::busy;

	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
void UARTDevice::interruptService() {

	if (_usart->CR1 & USART_CR1_FIFOEN) {

	}

	else {

		// Interrupcio TXEFE (FIFO/TX empty)
		//
		if ((_usart->CR1 & USART_CR1_TXEIE_TXFNFIE) && (_usart->ISR & USART_ISR_TXE_TXFNF)) {

			if (_txCount < _txSize) {
				_usart->TDR = _txBuffer[_txCount++];
				if (_txCount == _txSize)
					ATOMIC_MODIFY_REG(_usart->CR1, USART_CR1_TXEIE_TXFNFIE, USART_CR1_TCIE);
			}
		}

		// Interrupcio TC (Transmission complete). Nomes en l'ultim caracter transmes
		//
		if ((_usart->CR1 & USART_CR1_TCIE) && (_usart->ISR & USART_ISR_TC)) {

			_usart->ICR |= USART_ICR_TCCF;
			ATOMIC_CLEAR_BIT(_usart->CR1, USART_CR1_TXEIE_TXFNFIE | USART_CR1_TCIE | USART_CR1_TE);
			notifyTxCompleted(_txBuffer, _txCount);
			_state = State::ready;
		}

		/// Interupcio FIFO/RD not empty
		//
		if ((_usart->CR1 & USART_CR1_RXNEIE_RXFNEIE) && (_usart->ISR & USART_ISR_RXNE_RXFNE)) {

			if (_rxCount < _rxSize) {
				_rxBuffer[_rxCount++] = _usart->RDR;
				if (_rxCount == _rxSize) {
					ATOMIC_CLEAR_BIT(_usart->CR1, USART_CR1_RXNEIE_RXFNEIE | USART_CR1_RTOIE | USART_CR1_RE);
					notifyRxCompleted(_rxBuffer, _rxCount);
					_state = State::ready;
				}
			}
		}

		// Interrupcio RX timeout
		//
		if ((_usart->CR1 & USART_CR1_RTOIE) && (_usart->ISR & USART_ISR_RTOF)) {

			_usart->ICR |= USART_ICR_RTOCF;
			ATOMIC_CLEAR_BIT(_usart->CR1, USART_CR1_RXNEIE_RXFNEIE | USART_CR1_RTOIE | USART_CR1_RE);
			notifyRxCompleted(_rxBuffer, _rxCount);
			_state = State::ready;
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Invoca el event de notificacio TxComplete
/// \param    buffer: El buffer de dades.
/// \param    count: El nombre de bytes de dades.
///
void UARTDevice::notifyTxCompleted(
	const uint8_t *buffer,
	uint16_t count) {

	if (_notifyEventEnabled) {
		NotifyEventArgs args = {
			.id = NotifyID::txCompleted,
			.isr = true,
			.RxCompleted {
				.buffer = buffer,
				.length = count
			}
		};
		_notifyEvent->execute(this, args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Invoca el event de notificacio RxComplete
/// \param    buffer: El buffer de dades.
/// \param    count: El nombre de bytes de dades.
///
void UARTDevice::notifyRxCompleted(
	const uint8_t *buffer,
	uint16_t count) {

	if (_notifyEventEnabled) {
		NotifyEventArgs args = {
			.id = NotifyID::rxCompleted,
			.isr = true,
			.RxCompleted {
				.buffer = buffer,
				.length = count
			}
		};
		_notifyEvent->execute(this, args);
	}
}

