#include "HTL/htl.h"
#include "HTL/STM32/htlUART.h"


#include "HTL/htlBits.h"
#include "HTL/htlAtomic.h"
#include "HTL/STM32/htlClock.h"


#define HTL_UART_OPTION_FIFO  0


using namespace htl;
using namespace htl::bits;
using namespace htl::uart;


static void setParity(USART_TypeDef *usart, Parity parity);
static void setWordBits(USART_TypeDef *usart, WordBits wordBits, bool useParity);
static void setStopBits(USART_TypeDef *usart, StopBits stopBits);
static void setHandsake(USART_TypeDef *usart, Handsake handsake);
static void setReceiveTimeout(USART_TypeDef *usart, unsigned timeout);

static ClockSource getClockSource(USART_TypeDef *usart);
static unsigned getClockFrequency(USART_TypeDef *usart, ClockSource clockSource);

static void enable(USART_TypeDef *usart);
static void disable(USART_TypeDef *usart);

static void enableTransmission(USART_TypeDef *usart);
#if HTL_UART_OPTION_IRQ == 1
static void enableTransmissionIRQ(USART_TypeDef *usart);
#endif
#if HTL_UART_OPTION_DMA == 1
static void enableTransmissionDMA(USART_TypeDef *usart);
#endif
static void disableTransmission(USART_TypeDef *usart);

static void enableReception(USART_TypeDef *usart);
#if HTL_UART_OPTION_IRQ == 1
static void enableReceptionIRQ(USART_TypeDef *usart);
#endif
#if HTL_UART_OPTION_DMA == 1
static void enableReceptionDMA(USART_TypeDef *usart);
#endif
static void disableReception(USART_TypeDef *usart);

static void writeData(USART_TypeDef *usart, uint16_t data);
static uint16_t readData(USART_TypeDef *usart);
static bool waitTransmissionComplete(USART_TypeDef *usart, unsigned expireTime);
static bool waitTransmissionBufferEmpty(USART_TypeDef *usart, unsigned expireTime);
static bool waitReceptionBufferFull(USART_TypeDef *usart, unsigned expireTime);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    usart: Registres hardware del modul USART.
///
UARTDevice::UARTDevice(
	USART_TypeDef *usart):

	_usart {usart},
	_state {State::invalid}
#if HTL_UART_OPTION_DMA == 1
	, _dmaNotifyEvent {*this, &UARTDevice::dmaNotifyEventHandler}
#endif
	{

	_state = State::reset;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul UART.
/// \return   El resultat de l'operacio.
///
eos::Result UARTDevice::initialize() {

	if (_state == State::reset) {

		disable(_usart);

		clear(_usart->CR2,
#if defined(EOS_PLATFORM_STM32G0)
			USART_CR2_LINEN |     // Deshabilita modus LIN
#endif
#if defined(EOS_PLATFORM_STM32G0) || \
	defined(EOS_PLATFORM_STM32F7)
			USART_CR2_RTOEN |     // Deshabilita receiver timeout
#endif
     		USART_CR2_CLKEN);     // Deshabilita clock extern

		clear(_usart->CR3,
#if defined(EOS_PLATFORM_STM32G0)
			USART_CR3_SCEN |      // Deshabilita
			USART_CR3_IREN |      // Deshabilita modus IrDA
#endif
			USART_CR3_HDSEL);     // Deshabilita half duplex

		_state = State::ready;

		return eos::Results::success;
	}

	else
		return eos::Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul.
/// \return   El resultat de l'operacio.
///
eos::Result UARTDevice::deinitialize() {

	if (_state == State::ready) {

		disable(_usart);

		_state = State::reset;

		return eos::Results::success;
	}

	else
		return eos::Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el protocol de comunicacio.
/// \param    wordBits: Les opcions de paraula.
/// \param    parity: Les opcions de paritat.
/// \param    stopBits: Les opcions de parada.
/// \param    handsake: Protocol.
/// \return   El resultat de l'operacio.
///
eos::Result UARTDevice::setProtocol(
	WordBits wordBits,
	Parity parity,
	StopBits stopBits,
	Handsake handsake) {

	if (_state == State::ready) {
		setParity(_usart, parity);
		setWordBits(_usart, wordBits, parity != Parity::none);
		setStopBits(_usart, stopBits);
		setHandsake(_usart, handsake);
		return eos::Results::success;
	}
	else
		return eos::Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el valor del timeout per recepcio.
/// \param    timeout: El temps.
/// \param    El resultat de l'operacio.
///
eos::Result UARTDevice::setRxTimeout(
    unsigned timeout) {

	if (_state == State::ready) {
		setReceiveTimeout(_usart, timeout);
		return eos::Results::success;
	}
	else
		return eos::Results::errorState;
}



/// ----------------------------------------------------------------------
/// \brief    Asigna els valor de temporitzacio.
/// \param    baudMode: Les opcions del baud rate
/// \param    clockSource: Les opcions de clocking.
/// \param    rate: El valor de velocitat.
/// \param    overSampling: Tipus de mostreig
/// \return   El resultat de l'operacio.
///
eos::Result UARTDevice::setTimming(
	BaudMode baudMode,
	ClockSource clockSource,
	uint32_t rate,
	OverSampling overSampling) {

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

		if (clockSource == ClockSource::automatic)
			clockSource = getClockSource(_usart);

		unsigned fclk = getClockFrequency(_usart, clockSource);

		unsigned div;
		if (baudMode == BaudMode::div)
			div = rate;
		else {
			if (overSampling == OverSampling::_8)
				div = (fclk + fclk + (rate / 2)) / rate;
			else
				div = (fclk + (rate / 2)) / rate;
		}

		if (overSampling == OverSampling::_8) {
			unsigned temp = (uint16_t)(div & 0xFFF0U);
			temp |= (uint16_t)((div & (uint16_t)0x000FU) >> 1U);
			_usart->BRR = temp;
		}
		else
			_usart->BRR = div;

		return eos::Results::success;
	}
	else
		return eos::Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades.
/// \param    buffer: El bloc de dades.
/// \param    length: La longitut del bloc en bytes.
///
eos::Result UARTDevice::transmit(
	const uint8_t *buffer,
	unsigned length,
	unsigned timeout) {

	if (_state == State::ready) {

		unsigned expireTime = getTick() + timeout;
		bool error = false;

		_state = State::transmiting;

		enable(_usart);
		enableTransmission(_usart);

		while (length-- > 0) {
			if (!waitTransmissionBufferEmpty(_usart, expireTime)) {
				error = true;
				break;
			}
			writeData(_usart, *buffer++);
		}

	    error = !waitTransmissionComplete(_usart, expireTime);

		disableTransmission(_usart);
		disable(_usart);

		_state = State::ready;

		return error ? eos::Results::timeout : eos::Results::success;
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return eos::Results::busy;

	else
		return eos::Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la transmissio d'un bloc de dades per interrupcions.
/// \param    buffer: Buffer de dades.
/// \param    length: El nombre de bytes a transmetre.
/// \return   El resultat de l'operacio
///
#if HTL_UART_OPTION_IRQ == 1
eos::Result UARTDevice::transmit_IRQ(
	const uint8_t *buffer,
	unsigned length) {

	if (_state == State::ready) {

		_state = State::transmiting;

		_txBuffer = buffer;
		_txCount = 0;
        _txMaxCount = length;

        enable(_usart);
        enableTransmissionIRQ(_usart);

		return eos::Results::success;
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return eos::Results::busy;

	else
		return eos::Results::errorState;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades utilitzant DMA.
/// \param    devDMA: Dispositiu DMA.
/// \param    buffer: Buffer de dades.
/// \param    length: El nombre de bytes a transmetre.
/// \return   El resultat de l'operacio
///
#if HTL_UART_OPTION_DMA == 1
eos::Result UARTDevice::transmit_DMA(
    dma::DMADevice *devDMA,
    const uint8_t *buffer,
    unsigned length) {

    if (_state == State::ready) {

        _state = State::transmiting;

        _txBuffer = buffer;
        _txCount = 0;
        _txMaxCount = length;

        enable(_usart);
        enableTransmissionDMA(_usart);

        // Inicia la transferencia per DMA
        //
        devDMA->setNotifyEvent(_dmaNotifyEvent, true);
        devDMA->start(buffer, (uint8_t*)&(_usart->TDR), _txMaxCount);

        return eos::Results::success;
    }

    else if ((_state == State::transmiting) || (_state == State::receiving))
        return eos::Results::busy;

    else
        return eos::Results::errorState;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Aborta la transmissio.
///
eos::Result UARTDevice::abortTransmission() {

	if (_state == State::transmiting) {
		disableTransmission(_usart);
		disable(_usart);
		_state = State::ready;
		return eos::Results::success;
	}
	else
		return eos::Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Reb en bloc de dades.
/// \param    buffer: Buffer de recepcio de dades.
/// \param    bufferSize: Tamany del buffer en bytes.
/// \param    timeout: Temps maxim de bloqueig.
/// \return   El resultat.
///
eos::Result UARTDevice::receive(
	uint8_t *buffer,
	unsigned bufferSize,
	unsigned timeout) {

	if (_state == State::ready) {

		_state = State::receiving;

		auto expireTime = getTick() + timeout;
		bool error = false;

		enable(_usart);
		enableReception(_usart);

		while (bufferSize-- > 0) {

			if (!waitReceptionBufferFull(_usart, expireTime)) {
				error = true;
				break;
			}
			*buffer++ = readData(_usart);
		}

		disableTransmission(_usart);

		_state = State::ready;

		return error ? eos::Results::timeout : eos::Results::success;
	}
	else if ((_state == State::transmiting) || (_state == State::receiving))
		return eos::Results::busy;

	else
		return eos::Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la recepcio d'un bloc de dades per interrupcions.
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer en bytes.
/// \return   El resultat de l'operacio.
///
#if HTL_UART_OPTION_IRQ == 1
eos::Result UARTDevice::receive_IRQ(
	uint8_t *buffer,
	unsigned bufferSize) {

	if (_state == State::ready) {

		_state = State::receiving;

		_rxBuffer = buffer;
		_rxCount = 0;
		_rxMaxCount = bufferSize;

		enable(_usart);
		enableReceptionIRQ(_usart);

		return eos::Results::success;
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return eos::Results::busy;

	else
		return eos::Results::errorState;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades utilitzan DMA.
/// \param    devDMA: El dispositiu DMA.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany del buffer en bytes.
/// \return   El resultat de l'operacio.
///
#if HTL_UART_OPTION_DMA == 1
eos::Result UARTDevice::receive_DMA(
    dma::DMADevice *devDMA,
    uint8_t *buffer,
    unsigned bufferSize) {

	return eos::Results::error;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Aborta la recepcio.
///
eos::Result UARTDevice::abortReception() {

	if (_state == State::receiving) {
		disableReception(_usart);
		disable(_usart);
		_state = State::ready;
		return eos::Results::success;
	}
	else
		return eos::Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
#if HTL_UART_OPTION_IRQ == 1
void UARTDevice::interruptService() {

	if (_state == State::transmiting)
		txInterruptService();
	else if (_state == State::receiving)
		rxInterruptService();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per la transmissio
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
				clearBits(_usart->CR1, USART_CR1_TXEIE);          // Deshabilita interrupcio TXE
				setBits(_usart->CR1, USART_CR1_TCIE);             // Habilita interrupcio TC
				endAtomic(a);
			}
		}
	}

	// Interrupcio 'TC'. Nomes en l'ultim caracter transmes.
	//
	if (isSet(CR1, USART_CR1_TCIE) && isSet(SR, USART_SR_TC)) {
		disableTransmission(_usart);
		notifyTxCompleted(_txBuffer, _txCount, true);
		_state = State::ready;
	}
}

#elif defined(EOS_PLATFORM_STM32F7)
void UARTDevice::txInterruptService() {

	auto CR1 = _usart->CR1;
	auto ISR = _usart->ISR;

	// Interrupcio 'TXE'
	//
	if (isSet(CR1, USART_CR1_TXEIE) && isSet(ISR, USART_ISR_TXE)) {
		if (_txCount < _txMaxCount) {
			_usart->TDR = _txBuffer[_txCount++];
			if (_txCount == _txMaxCount) {
				auto a = startAtomic();
				clearBits(_usart->CR1, USART_CR1_TXEIE);          // Deshabilita interrupcio TXE
				setBits(_usart->CR1, USART_CR1_TCIE);             // Habilita interrupcio TC
				endAtomic(a);
			}
		}
	}

	// Interrupcio 'TC'. Nomes en l'ultim caracter transmes.
	//
	if (isSet(CR1, USART_CR1_TCIE) && isSet(ISR, USART_ISR_TC)) {
		disableTransmission(_usart);
		notifyTxCompleted(_txBuffer, _txCount, true);
		_state = State::ready;
	}
}

#elif defined(EOS_PLATFORM_STM32G0)
void UARTDevice::txInterruptService() {

	auto CR1 = _usart->CR1;
	auto CR3 = _usart->CR3;
	auto ISR = _usart->ISR;

	// Interrupcio 'TXFT' (Transmission fifo threshold)
	//
#if HTL_UART_OPTION_FIFO == 1
	if (isSet(CR3, USART_CR3_TXFTIE) && isSet(ISR, USART_ISR_TXFT)) {
		while ((_txCount < _txMaxCount) && isSet(_usart->ISR, USART_ISR_TXE_TXFNF))
			_usart->TDR = _txBuffer[_txCount++];
		if (_txCount == _txMaxCount) {
			auto a = startAtomic();
			clearBits(_usart->CR3, USART_CR3_TXFTIE);  // Deshabilita interrupcio TXFT
			setBits(_usart->CR1, USART_CR1_TCIE);      // Habilita interrupcio TC
			endAtomic(a);
		}
	}
#endif

	// Interrupcio 'TXE' (Transmission buffer empty)
	//
	if (isSet(CR1, USART_CR1_TXEIE_TXFNFIE) && isSet(ISR, USART_ISR_TXE_TXFNF)) {
		if (_txCount < _txMaxCount) {
			_usart->TDR = _txBuffer[_txCount++];
			if (_txCount == _txMaxCount) {
				auto a = startAtomic();
				clearBits(_usart->CR1, USART_CR1_TXEIE_TXFNFIE);  // Deshabilita interrupcio TXE
				setBits(_usart->CR1, USART_CR1_TCIE);             // Habilita interrupcio TC
				endAtomic(a);
			}
		}
	}

	// Interrupcio 'TC'. (Transmission complete)
	//
	if (isSet(CR1, USART_CR1_TCIE) && isSet(ISR, USART_ISR_TC)) {
		disableTransmission(_usart);
		notifyTxCompleted(_txBuffer, _txCount, true);
		_state = State::ready;
	}
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per la recepcio.
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
				disableReception(_usart);
				notifyRxCompleted(_rxBuffer, _rxCount, true);
				_state = State::ready;
			}
		}
	}

	// Interrupcio 'IDLE'
	//
	if (isSet(CR1, USART_CR1_IDLEIE) && isSet(SR, USART_SR_IDLE)) {
		if (_rxCount > 0) {
			disableReception(_usart);
			notifyRxCompleted(_rxBuffer, _rxCount, true);
			_state = State::ready;
		}
	}
}

#elif defined(EOS_PLATFORM_STM32F7)
void UARTDevice::rxInterruptService() {

	auto CR1 = _usart->CR1;
	auto ISR = _usart->ISR;

	/// Interrupcio 'RXNE'
	//
	if (isSet(CR1, USART_CR1_RXNEIE) && isSet(ISR, USART_ISR_RXNE)) {
		if (_rxCount < _rxMaxCount) {
			_rxBuffer[_rxCount++] = _usart->RDR;
			if (_rxCount == _rxMaxCount) {
				disableReception(_usart);
				notifyRxCompleted(_rxBuffer, _rxCount, true);
				_state = State::ready;
			}
		}
	}

	// Interrupcio 'IDLE'
	//
	if (isSet(CR1, USART_CR1_IDLEIE) && isSet(ISR, USART_ISR_IDLE)) {
		_usart->ICR = USART_ICR_IDLECF;
		if (_rxCount > 0) {
			disableReception(_usart);
			notifyRxCompleted(_rxBuffer, _rxCount, true);
			_state = State::ready;
		}
	}

	// Interrupcio 'RTO'
	//
	if (isSet(CR1, USART_CR1_RTOIE) && isSet(ISR, USART_ISR_RTOF)) {
		_usart->ICR = USART_ICR_RTOCF;
		disableReception(_usart);
		notifyRxCompleted(_rxBuffer, _rxCount, true);
		_state = State::ready;
	}
}

#elif defined(EOS_PLATFORM_STM32G0)
void UARTDevice::rxInterruptService() {

	auto CR1 = _usart->CR1;
	auto ISR = _usart->ISR;

	/// Interrupcio 'RXNE'
	//
	if (isSet(CR1, USART_CR1_RXNEIE_RXFNEIE) && isSet(ISR, USART_ISR_RXNE_RXFNE)) {
		if (_rxCount < _rxMaxCount) {
			_rxBuffer[_rxCount++] = _usart->RDR;
			if (_rxCount == _rxMaxCount) {
				disableReception(_usart);
				notifyRxCompleted(_rxBuffer, _rxCount, true);
				_state = State::ready;
			}
		}
	}

	// Interrupcio 'IDLE'
	//
	if (isSet(CR1, USART_CR1_IDLEIE) && isSet(ISR, USART_ISR_IDLE)) {
		_usart->ICR = USART_ICR_IDLECF;
		if (_rxCount > 0) {
			disableReception(_usart);
			notifyRxCompleted(_rxBuffer, _rxCount, true);
			_state = State::ready;
		}
	}

	// Interrupcio 'RTO'
	//
	if (isSet(CR1, USART_CR1_RTOIE) && isSet(ISR, USART_ISR_RTOF)) {
		_usart->ICR = USART_ICR_RTOCF;
		disableReception(_usart);
		notifyRxCompleted(_rxBuffer, _rxCount, true);
		_state = State::ready;
	}
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Reb les notificacions del DMA
/// \param    devDMA: El dispositiu DMA que genera l'event.
/// \param    args: Parametres del event.
///
#if HTL_UART_OPTION_DMA == 1
void UARTDevice::dmaNotifyEventHandler(
    DevDMA *devDMA,
    DMANotifyEventArgs &args) {

    switch (args.id) {

        // Transmissio complerta de tots els bytes.
        //
        case htl::dma::NotifyID::completed: {
            _txCount = _txMaxCount;
            _usart->ICR = USART_ICR_TCCF;
            auto a = startAtomic();
            set(_usart->CR1, USART_CR1_TCIE);
            endAtomic(a);
            devDMA->disableNotifyEvent();
            break;
        }

        // Error en la transmissio DMA.
        //
        case htl::dma::NotifyID::error:
            break;

        default:
        	break;
    }
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Genera un event de notificacio 'TxComplete'
/// \param    buffer: El buffer de dades.
/// \param    length: El nombre de bytes de dades.
/// \param    irq: true si ve d'una interrupcio.
///
void UARTDevice::notifyTxCompleted(
	const uint8_t *buffer,
	unsigned length,
	bool irq) {

	NotifyEventArgs args = {
		.irq = irq,
		.txCompleted {
			.buffer = buffer,
			.length = length
		}
	};
	_erNotify.raise(NotifyID::txCompleted, &args);
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event de notificacio 'RxComplete'
/// \param    buffer: El buffer de dades.
/// \param    length: El nombre de bytes de dades.
/// \param    irq: true si ve d'una interrupcio.
///
void UARTDevice::notifyRxCompleted(
	const uint8_t *buffer,
	unsigned length,
	bool irq) {

	NotifyEventArgs args = {
		.irq = irq,
		.rxCompleted {
			.buffer = buffer,
			.length = length
		}
	};
	_erNotify.raise(NotifyID::rxCompleted, &args);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el rellotge asignat a la UART
/// \param    usart: El bloc de registres
/// \return   El rellotge.
///
#if defined(EOS_PLATFORM_STM32F0)
static ClockSource getClockSource(
    USART_TypeDef *usart) {

	static const ClockSource clockSourceTbl[] = {
		ClockSource::pclk, ClockSource::sysclk, ClockSource::hsi, ClockSource::lse};

    if ((unsigned) usart == USART1_BASE) {
        unsigned sel = (RCC->CFGR3 & RCC_CFGR3_USART1SW) >> RCC_CFGR3_USART1SW_Pos;
		return clockSourceTbl[sel];
    }
    else
	    return ClockSource::pclk;
}

#elif defined(EOS_PLATFORM_STM32F4)
static ClockSource getClockSource(
    USART_TypeDef *usart) {

	return ClockSource::pclk;
}


#elif defined(EOS_PLATFORM_STM32F7)
static ClockSource getClockSource(
    USART_TypeDef *usart) {

	static const ClockSource clockSourceTbl[] = {
		ClockSource::pclk, ClockSource::sysclk, ClockSource::hsi, ClockSource::lse};

    unsigned sel;
    switch ((unsigned) usart) {
#ifdef HTL_UART1_EXIST
        case USART1_BASE:
            sel = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART1SEL) >> RCC_DCKCFGR2_USART1SEL_Pos;
            break;
#endif

#ifdef HTL_UART2_EXIST
        case USART2_BASE:
            sel = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART2SEL) >> RCC_DCKCFGR2_USART2SEL_Pos;
            break;
#endif

#ifdef HTL_UART3_EXIST
        case USART3_BASE:
            sel = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART3SEL) >> RCC_DCKCFGR2_USART3SEL_Pos;
            break;
#endif

#ifdef HTL_UART4_EXIST
        case UART4_BASE:
            sel = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART4SEL) >> RCC_DCKCFGR2_UART4SEL_Pos;
            break;
#endif

#ifdef HTL_UART5_EXIST
        case UART5_BASE:
            sel = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART5SEL) >> RCC_DCKCFGR2_UART5SEL_Pos;
            break;
#endif

#ifdef HTL_UART6_EXIST
        case USART6_BASE:
            sel = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART6SEL) >> RCC_DCKCFGR2_USART6SEL_Pos;
            break;
#endif

#ifdef HTL_UART7_EXIST
        case UART7_BASE:
            sel = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART7SEL) >> RCC_DCKCFGR2_UART7SEL_Pos;
            break;
#endif

#ifdef HTL_UART8_EXIST
        case UART8_BASE:
            sel = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART8SEL) >> RCC_DCKCFGR2_UART8SEL_Pos;
            break;
#endif
        default:
        	sel = 0;
        	break;
    }

    return clockSourceTbl[sel];
}

#elif defined(EOS_PLATFORM_STM32G0)
static ClockSource getClockSource(
    USART_TypeDef *usart) {

    static const ClockSource clockSourceTbl[4] = {
        ClockSource::pclk, ClockSource::sysclk, ClockSource::hsi16, ClockSource::lse};

    unsigned sel;
    switch ((unsigned) usart) {
#ifdef HTL_UART1_EXIST
        case USART1_BASE:
            sel = (RCC->CCIPR & RCC_CCIPR_USART1SEL) >> RCC_CCIPR_USART1SEL_Pos;
            break;
#endif

#if defined(HTL_UART2_EXIST) && defined(RCC_CCIPR_USART2SEL)
        case USART2_BASE:
            sel = (RCC->CCIPR & RCC_CCIPR_USART2SEL) >> RCC_CCIPR_USART2SEL_Pos;
            break;
#endif

#if defined(HTL_UART3_EXIST) && defined(RCC_CCIPR_USART3SEL)
        case USART3_BASE:
            sel = (RCC->CCIPR & RCC_CCIPR_USART3SEL) >> RCC_CCIPR_USART3SEL_Pos;
            break;
#endif
        default:
        	sel = 0;
           	break;
    }

    return clockSourceTbl[sel];
}
#endif


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
#if defined(EOS_PLATFORM_STM32F7)
            if (((unsigned) usart == USART1_BASE) ||
                ((unsigned) usart == USART6_BASE))
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

    auto CR1 = usart->CR1;
    if (parity == Parity::none)
    	clear(CR1, USART_CR1_PCE);
    else {
    	set(CR1, USART_CR1_PCE);
    	if (parity == Parity::even)
    		clear(CR1, USART_CR1_PS);
    	else
    		set(CR1, USART_CR1_PS);
    }
    usart->CR1 = CR1;
}


/// ----------------------------------------------------------------------
/// \brief    Configura el nombre de bits de parada
/// \param    usart: Registres de harware del dispositiu.
/// \param    stopBits: Opcions dels bits de parada.
///
static void setStopBits(
    USART_TypeDef *usart,
    StopBits stopBits) {

    auto CR2 = usart->CR2;
    switch (stopBits) {
        case StopBits::_0p5:
            clear(CR2, USART_CR2_STOP_1);
            set(CR2, USART_CR2_STOP_0);
            break;

        case StopBits::_1:
        	clear(CR2, USART_CR2_STOP_1);
        	clear(CR2, USART_CR2_STOP_0);
            break;

        case StopBits::_1p5:
        	set(CR2, USART_CR2_STOP_1);
        	set(CR2, USART_CR2_STOP_0);
            break;

        case StopBits::_2:
        	set(CR2, USART_CR2_STOP_1);
        	clear(CR2, USART_CR2_STOP_0);
            break;
    }
    usart->CR2 = CR2;
}


/// ----------------------------------------------------------------------
/// \brief    Configura nombre de bits de paraula.
/// \param    usart: Registres de herdware del dispositiu.
/// \param    wordBits: Opcions dels bits de paraula.
/// \params   useParity: True si utilitza bit de paritat
///
#if defined(EOS_PLATFORM_STM32F0) || \
    defined(EOS_PLATFORM_STM32F4) || \
    defined(EOS_PLATFORM_STM32F7)
static void setWordBits(
    USART_TypeDef *usart,
    WordBits wordBits,
    bool useParity) {

	auto numBits = useParity? 1 : 0;
	switch (wordBits) {
		case WordBits::word8:
			numBits += 8;
			break;

		case WordBits::word9:
			numBits += 9;
			break;
	}

	auto a = startAtomic();
	auto CR1 = usart->CR1;
	if (numBits == 8)
		CR1 &= ~USART_CR1_M;
	else
		CR1 |= USART_CR1_M;
	usart->CR1 = CR1;
	endAtomic(a);
}

#elif defined(EOS_PLATFORM_STM32G0)
static void setWordBits(
    USART_TypeDef *usart,
    WordBits wordBits,
    bool useParity) {

	auto numBits = useParity? 1 : 0;
	switch (wordBits) {
		case WordBits::word7:
			numBits += 7;
			break;

		case WordBits::word8:
			numBits += 8;
			break;

		case WordBits::word9:
			numBits += 9;
			break;
	}

	auto a = startAtomic();
	auto CR1 = usart->CR1;
	switch (numBits) {
		case 7:
			clear(CR1, USART_CR1_M0);
			set(CR1, USART_CR1_M1);
			break;

		default:
		case 8:
			clear(CR1, USART_CR1_M0);
			clear(CR1, USART_CR1_M1);
			break;

		case 9:
			set(CR1, USART_CR1_M0);
			clear(CR1, USART_CR1_M1);
			break;
	}
	usart->CR1 = CR1;
	endAtomic(a);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Configura el protocol.
/// \param    usart: Registres de hardware del dispositiu.
/// \param    handsake: Opcions de protocol.
///
static void setHandsake(
    USART_TypeDef *usart,
    Handsake handsake) {

    auto CR3 = usart->CR3;
    switch (handsake) {
        case Handsake::none:
        	clear(CR3, USART_CR3_RTSE | USART_CR3_CTSE);
            break;

        case Handsake::ctsrts:
        	set(CR3, USART_CR3_RTSE | USART_CR3_CTSE);
            break;
    }
    usart->CR3 = CR3;
}


/// ----------------------------------------------------------------------
/// \brief    Configura el timeout per recepcio.
/// \param    usart: Registres de hardware del dispositiu.
/// \param    timeout: Timeout en temps de bit individual.
///
#if defined(EOS_PLATFORM_STM32G0) || \
	defined(EOS_PLATFORM_STM32F7)
static void setReceiveTimeout(
    USART_TypeDef *usart,
    unsigned timeout) {

    if (timeout == 0)
    	clear(usart->CR2, USART_CR2_RTOEN);
    else {
    	set(usart->CR2, USART_CR2_RTOEN);
        usart->RTOR = timeout;
    }
}
#else
static void setReceiveTimeout(
    USART_TypeDef *usart,
    unsigned timeout) {
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Espera que s'hagi completat la transmissio
/// \param    usart: Registres de hardware del dispositiu.
/// \param    timeout: El temps maxim d'espera en ticks.
/// \return   True si tot es correcte, false en cas de timeout.
///
static bool waitTransmissionComplete(
	USART_TypeDef *usart,
	unsigned expireTime) {

#if defined(EOS_PLATFORM_STM32F4)
	while (!isSet(usart->SR, USART_SR_TC)) {
#else
	while (!isSet(usart->ISR, USART_ISR_TC)) {
#endif
		if (hasTickExpired(expireTime))
			return false;
	}

	//usart->ICR = USART_ICR_TCCF;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el buffer de transmissio estigui buit.
/// \param    usart: Registres de hardware del dispositiu.
/// \param    expireTime: El limit de temps.
/// \return   True si tot es correcte, false en cas de timeout.
///
static bool waitTransmissionBufferEmpty(
	USART_TypeDef *usart,
	unsigned expireTime) {

#if defined(EOS_PLATFORM_STM32G0)
	while (!isSet(usart->ISR, USART_ISR_TXE_TXFNF)) {
#elif defined(EOS_PLATFORM_STM32F4)
	while (!isSet(usart->SR, USART_SR_TXE)) {
#else
	while (!isSet(usart->ISR, USART_ISR_TXE)) {
#endif
		if (hasTickExpired(expireTime))
			return false;
	}

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el buffer de recepcio estigui ple
/// \param    usart: Els registres de hardware del dispositiu.
/// \param    expireTime: El limit de temps.
/// \return   True si tot es correcte, false en cas de timeout.
///
static bool waitReceptionBufferFull(
	USART_TypeDef *usart,
	unsigned expireTime) {

#if defined(EOS_PLATFORM_STM32G0)
	while ((usart->ISR & USART_ISR_RXNE_RXFNE) == 0) {
#elif defined(EOS_PLATFORM_STM32F4)
	while ((usart->SR & USART_SR_RXNE) == 0) {
#else
	while ((usart->ISR & USART_ISR_RXNE) == 0) {
#endif
		if (hasTickExpired(expireTime))
			return false;
	}

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita el dispositiu.
/// \param    usart: Registres de hardware del dispositiu.
///
static inline void enable(
	USART_TypeDef *usart) {

	set(usart->CR1,
#if HLT_UART_OPTION_FIFO == 1
		USART_CR1_FIFOEN |   // Habilita el fifo
#endif
		USART_CR1_UE);       // Habilita el dispositiu
}


/// ----------------------------------------------------------------------
/// \brief    Desabilita el dispositiu.
/// \param    usart: Registres de hardware del dispositiu.
///
static void disable(
	USART_TypeDef *usart) {

	clear(usart->CR1,
		USART_CR1_FIFOEN |        // Desabilita el FIFO
		USART_CR1_UE |            // Desabilita el dispositiu
		USART_CR1_TE |            // Desabilita la transmissio
		USART_CR1_RE);            // Deshabilita la recepcio
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la transmissio de dades.
/// \param    usart: Registres de hardware del dispositiu.
///
static void enableTransmission(
	USART_TypeDef *usart) {

	auto a = startAtomic();
	set(usart->CR1,
		USART_CR1_TE);       // Habilita la tramsmissio
	endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la transmissio de dades en modus IRQ
/// \param    usart: Registres de hardware del dispositiu.
///
#if HTL_UART_OPTION_IRQ == 1
static void enableTransmissionIRQ(
	USART_TypeDef *usart) {

	auto a = startAtomic();

#if HTL_UART_OPTION_FIFO == 1
	// Habilita el nivell d'interrupcio del fifo
	//
	clear(usart->CR3, USART_CR3_TXFTCFG);
	set(usart->CR3, (uint32_t)(2 << USART_CR3_TXFTCFG_Pos));

	set(usart->CR3,
		USART_CR3_TXFTIE);         // Habilita la interrupcio de nivell del FIFO
#endif

	set(usart->CR1,
#if HTL_UART_OPTION_FIFO == 0
#if defined(EOS_PLATFORM_STM32G0)
		USART_CR1_TXEIE_TXFNFIE |  // Habilita interrupcio TXE
#else
		USART_CR1_TXEIE |          // Habilita interrupcio TXE
#endif
#endif
		USART_CR1_TE);             // Habilita la transmissio

	endAtomic(a);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Habilita la transmissio de dades en modus DMA
/// \param    usart: Registres de hardware del dispositiu.
///
#if HTL_UART_OPTION_DMA == 1
static void enableTransmissionDMA(
	USART_TypeDef *usart) {

	usart->ICR = USART_ICR_TCCF;  // Borra el flag TC

	auto a = startAtomic();

    set(usart->CR1,
    	USART_CR1_TE);            // Habilita transmissio
    set(usart->CR3,
    	USART_CR3_DMAT);          // Habilita DMA

    endAtomic(a);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Deshabilita la transmissio
/// \param    usart: Registres de hardware del dispositiu.
///
static void disableTransmission(
	USART_TypeDef *usart) {

	auto a = startAtomic();

	clear(usart->CR1,
#if defined(EOS_PLATFORM_STM32G0)
		USART_CR1_TXEIE_TXFNFIE | // Deshabilita interrupcio TXE
#else
		USART_CR1_TXEIE |         // Deshabilita interrupcio TXE
#endif
		USART_CR1_TCIE);          // Deshabilita interrupcio TC

#if HTL_UART_OPTION_FIFO == 1
	clear(usart->CR3,
		USART_CR3_TXFTIE);        // Desabilita la interrupcio de nivell del fifo
#endif

#if HTL_UART_OPTION_DMA == 1
	clear(usart->CR3,
		USART_CR3_DMAT);          // Desabilita el DMA
#endif

	// TODO: Asegurar-se que l'ultim byte s'ha transmes abans de deshabilitar
	// ta transmissio

	clear(usart->CR1,
		USART_CR1_TE);            // Desabilita transmissio

	endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la recepcio.
/// \param    usart: Registres de hardware del dispoositiu.
///
static void enableReception(
	USART_TypeDef *usart) {

#if !defined(EOS_PLATFORM_STM32F4)
	usart->ICR = USART_ICR_RTOCF; // Borra el flag RTO
#endif

	auto a = startAtomic();
	set(usart->CR1,
		USART_CR1_RE);            // Habilita la recepcio
	endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la recepcio en modus IRQ.
/// \param    usart: Registres de hardware del dispoositiu.
///
#if HTL_UART_OPTION_IRQ == 1
static void enableReceptionIRQ(
	USART_TypeDef *usart) {

#if !defined(EOS_PLATFORM_STM32F4)
	set(usart->ICR,
		USART_ICR_RTOCF |           // Borra el flag RTO
		USART_ICR_IDLECF);          // Borra el flag IDLE
#endif

	auto a = startAtomic();

	set(usart->CR1,
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
	set(usart->CR1, USART_CR1_IDLEIE);       // Habilita interrupcio IDLE
#else
	if (usart->CR2 & USART_CR2_RTOEN)
		set(usart->CR1, USART_CR1_RTOIE);    // Habilita interrupcio RTO
	else
		set(usart->CR1, USART_CR1_IDLEIE);   // Habilita interrupcio IDLE
#endif

	endAtomic(a);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Deshabilita la recepcio.
/// \param    usart: Registres de hardware del dispositiu.
///
static void disableReception(
	USART_TypeDef *usart) {

	auto a = startAtomic();

	clear(usart->CR1,
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

#if HTL_UART_OPTION_DMA == 1
	clear(usart->CR3,
		USART_CR3_DMAT);           // Desabilita el DMA
#endif

	clear(usart->CR1,
		USART_CR1_RE);             // Deshabilita recepcio

	endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu el registre de transmissio des dades.
/// \param    usart: Registres de hardware del dispositiu.
/// \param    data: Les dades a transmetre.
//
static void writeData(
		USART_TypeDef *usart,
		uint16_t data) {

#if defined(EOS_PLATFORM_STM32F4)
	usart->DR = data;
#else
	usart->TDR = data;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix el registre de recepcio dades.
/// \param    usart: Registres de hardware del dispositiu.
/// \return   Les dades rebudes.
//
static uint16_t readData(
	USART_TypeDef *usart) {

#if defined(EOS_PLATFORM_STM32F4)
	return usart->DR;
#else
	return usart->RDR;
#endif
}

