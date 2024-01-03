#include "HTL/htl.h"
#include "HTL/STM32/htlClock.h"
#include "HTL/STM32/htlUART.h"


using namespace htl;
using namespace htl::uart;


static void setParity(USART_TypeDef *usart, Parity parity);
static void setWordBits(USART_TypeDef *usart, WordBits wordBits, bool parity);
static void setStopBits(USART_TypeDef *usart, StopBits stopBits);
static void setHandsake(USART_TypeDef *usart, Handsake handsake);
static void setRxTimeout(USART_TypeDef *usart, uint32_t timeout);

static ClockSource getClockSource(USART_TypeDef *usart);
static unsigned getClockFrequency(USART_TypeDef *usart, ClockSource clockSource);


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
Result UARTDevice::initialize() {

	if (_state == State::reset) {

		activate();
		disable();

        #if defined(EOS_PLATFORM_STM32G0)
		_usart->CR1 &= ~USART_CR1_FIFOEN;
        #endif
	    _usart->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
		_usart->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);

		_state = State::ready;
		return Result::success();
	}

	else
		return Result::error();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul.
/// \return   El resultat de l'operacio.
///
Result UARTDevice::deinitialize() {

	if (_state == State::ready) {

		disable();
		deactivate();

		_state = State::reset;

		return Result::success();
	}

	else
		return Result::error();
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

    if (clockSource == ClockSource::automatic)
    	clockSource = getClockSource(_usart);

    uint32_t fclk = getClockFrequency(_usart, clockSource);

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
/// \param    buffer: Buffer de dades.
/// \param    size: El nombre de bytes en el buffer.
/// \return   El resultat de l'operacio
///
Result UARTDevice::transmit_IRQ(
	const uint8_t *buffer,
	uint16_t size) {

	if (_state == State::ready) {

		_state = State::transmiting;

		_txBuffer = buffer;
		_txSize = size;
		_txCount = 0;

        #if defined(EOS_PLATFORM_STM32F7)
        _usart->CR1 |= USART_CR1_TXEIE;
        #elif defined(EOS_PLATFORM_STM32G0)
		_usart->CR1 |= USART_CR1_TXEIE_TXFNFIE;
        #endif

		enableTX();

		return Result::success();
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return Result::busy();

	else
		return Result::error();
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades per
/// \param    buffer: Buffer de dades.
/// \param    size: Tamany del buffer en bytes.
/// \return   El resultat de l'operacio.
///
Result UARTDevice::receive_IRQ(
	uint8_t *buffer,
	uint16_t size) {

	if (_state == State::ready) {

		_state = State::receiving;

		_rxBuffer = buffer;
		_rxSize = size;
		_rxCount = 0;

        #if defined(EOS_PLATFORM_STM32F7)
        _usart->CR1 |= USART_CR1_RXNEIE;
        #elif defined(EOS_PLATFORM_STM32G0)
		_usart->CR1 |= USART_CR1_RXNEIE_RXFNEIE;
        #endif

		enableRX();

		return Result::success();
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return Result::busy();

	else
		return Result::error();
}


Result UARTDevice::transmit_DMA(
	const uint8_t *buffer,
	uint16_t size) {

	return Result::error();
}


Result UARTDevice::receive_DMA(
	uint8_t *buffer,
	uint16_t size) {

	return Result::error();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions de la UART.
///
#if defined(EOS_PLATFORM_STM32F7)
void UARTDevice::interruptService() {

    // Interrupcio TXEFE (FIFO/TX empty)
    //
    if ((_usart->CR1 & USART_CR1_TXEIE) && (_usart->ISR & USART_ISR_TXE)) {

        if (_txCount < _txSize) {
            _usart->TDR = _txBuffer[_txCount++];
            if (_txCount == _txSize)
                ATOMIC_MODIFY_REG(_usart->CR1, USART_CR1_TXEIE, USART_CR1_TCIE);
        }
    }

    // Interrupcio TC (Transmission complete). Nomes en l'ultim caracter transmes
    //
    if ((_usart->CR1 & USART_CR1_TCIE) && (_usart->ISR & USART_ISR_TC)) {

        _usart->ICR |= USART_ICR_TCCF;
        ATOMIC_CLEAR_BIT(_usart->CR1, USART_CR1_TXEIE | USART_CR1_TCIE | USART_CR1_TE);
        notifyTxCompleted(_txBuffer, _txCount);
        _state = State::ready;
    }

    /// Interupcio FIFO/RD not empty
    //
    if ((_usart->CR1 & USART_CR1_RXNEIE) && (_usart->ISR & USART_ISR_RXNE)) {

        if (_rxCount < _rxSize) {
            _rxBuffer[_rxCount++] = _usart->RDR;
            if (_rxCount == _rxSize) {
                ATOMIC_CLEAR_BIT(_usart->CR1, USART_CR1_RXNEIE | USART_CR1_RTOIE | USART_CR1_RE);
                notifyRxCompleted(_rxBuffer, _rxCount);
                _state = State::ready;
            }
        }
    }

    // Interrupcio RX timeout
    //
    if ((_usart->CR1 & USART_CR1_RTOIE) && (_usart->ISR & USART_ISR_RTOF)) {

        _usart->ICR |= USART_ICR_RTOCF;
        ATOMIC_CLEAR_BIT(_usart->CR1, USART_CR1_RXNEIE | USART_CR1_RTOIE | USART_CR1_RE);
        notifyRxCompleted(_rxBuffer, _rxCount);
        _state = State::ready;
    }
}

#elif defined(EOS_PLATFORM_STM32G0)
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
#endif


/// ----------------------------------------------------------------------
/// \brief    Llança un event de notificacio TxComplete
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
/// \brief    llança un event de notificacio RxComplete
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


/// ----------------------------------------------------------------------
/// \brief    Obte el rellotge asignat al generador de bauds.
/// \param    regs: El bloc de registres
/// \return   La opcio corresponent al rellotge.
///
static ClockSource getClockSource(
    USART_TypeDef *usart) {

    uint8_t sclk = 0;
    switch (reinterpret_cast<uint32_t>(usart)) {
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

#if defined(EOS_PLATFORM_STM32F4)
    static const ClockSource csTbl[4] = {
        ClockSource::pclk1,
        ClockSource::sysclk,
        ClockSource::hsi,
        ClockSource::lse
    };
#elif defined(EOS_PLATFORM_STM32F7)
    static const ClockSource csTbl[4] = {
        ClockSource::pclk,
        ClockSource::sysclk,
        ClockSource::hsi,
        ClockSource::lse
    };
#elif defined(EOS_PLATFORM_STM32G0)
    static const ClockSource csTbl[4] = {
        ClockSource::pclk,
        ClockSource::sysclk,
        ClockSource::hsi16,
        ClockSource::lse
    };
#else
    #error "Unknown platform"
#endif

    return csTbl[sclk];
}


/// ----------------------------------------------------------------------
/// \brief    Obte la frequencia del rellotge de la uart.
/// \param    usart: El bloc de registres del dispositiu.
/// \param    clockSource: El rellotge asignat.
/// \return   La frequencia del rellotge.Zero en cas d'error.
///
static unsigned getClockFrequency(
    USART_TypeDef *usart,
    ClockSource clockSource) {

    switch (clockSource) {
        case ClockSource::pclk:
            #if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
            if ((uint32_t(usart) == USART1_BASE) ||
                (uint32_t(usart) == USART6_BASE))
                return clock::getClockFrequency(clock::ClockID::pclk2);
            else
            #endif
                return clock::getClockFrequency(clock::ClockID::pclk);

        case ClockSource::sysclk:
            return clock::getClockFrequency(clock::ClockID::sysclk);

        #if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
        case ClockSource::hsi:
            return clock::getClockFrequency(clock::ClockID::hsi);
        #endif

        #if defined(EOS_PLATFORM_STM32G0)
        case ClockSource::hsi16:
            return clock::getClockFrequency(clock::ClockID::hsi16);
        #endif

        case ClockSource::lse:
            return clock::getClockFrequency(clock::ClockID::lse);

        default:
            return 0;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Configura la paritat.
/// \param    usart: Registres de hardware del dispositiu.
/// \param    parity: Opcions de paritat.
///
static void setParity(
    USART_TypeDef *usart,
    Parity parity) {

    auto tmp = usart->CR1;
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
    usart->CR1 = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Configura el nombre de bits de parada
/// \param    usart: Registres de harware del dispositiu.
/// \param    stopBits: Opcions dels bits de parada.
///
static void setStopBits(
    USART_TypeDef *usart,
    StopBits stopBits) {

    auto tmp = usart->CR2;
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
    usart->CR2 = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Configura nombre de bits de paraula.
/// \param    usart: Registres de herdware del dispositiu.
/// \param    wordBits: Opcions dels bits de paraula.
/// \params   parity: True si utilitza bit de paritat
///
static void setWordBits(
    USART_TypeDef *usart,
    WordBits wordBits,
    bool parity) {

    auto numBits = 7 + uint32_t(wordBits) + (parity ? 0 : 1);

    auto tmp = usart->CR1;
    switch (numBits) {
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
    usart->CR2 = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Configura el protocol.
/// \param    usart: Registres de hardware del dispositiu.
/// \param    handsake: Opcions de protocol.
///
static void setHandsake(
    USART_TypeDef *usart,
    Handsake handsake) {

    auto tmp = usart->CR3;
    switch (handsake) {
        case Handsake::none:
            tmp &= ~(USART_CR3_RTSE | USART_CR3_CTSE);
            break;

        case Handsake::ctsrts:
            tmp |= (USART_CR3_RTSE | USART_CR3_CTSE);
            break;
    }
    usart->CR3 = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Configura el timeout per recepcio.
/// \param    usart: Registres de hardware del dispositiu.
/// \param    timeout: Timeout en temps de bit individual.
///
static void setRxTimeout(
    USART_TypeDef *usart,
    uint32_t timeout) {

    if (timeout == 0)
        usart->CR2 &= ~USART_CR2_RTOEN;
    else {
        usart->CR2 |= USART_CR2_RTOEN;
        usart->RTOR = timeout;
    }
}
