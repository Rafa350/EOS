#include "HTL/htl.h"
#include "HTL/STM32/htlUART.h"


#include "HTL/htlBits.h"
#include "HTL/htlAtomic.h"
#include "HTL/STM32/htlClock.h"


using namespace htl::clock;
using namespace htl::bits;
using namespace htl::uart;


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

		activate();
		disable();

#if defined(EOS_PLATFORM_STM32G0)
#if HTL_UART_OPTION_FIFO == 1
		if (isFifoAvailable())
			set(_usart->CR1,
				USART_CR1_FIFOEN);    // Habilita el FIFO
		else
#endif
			clear(_usart->CR1,
				USART_CR1_FIFOEN);    // Deshabilita el FIFO
#endif

		clear(_usart->CR2,
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			USART_CR2_LINEN |     // Deshabilita modus LIN
#endif
#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			USART_CR2_RTOEN |     // Deshabilita receiver timeout
#endif
     		USART_CR2_CLKEN);     // Deshabilita clock extern

		clear(_usart->CR3,
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			USART_CR3_SCEN |      // Deshabilita modus SmartCard
			USART_CR3_IREN |      // Deshabilita modus IrDA
#endif
			USART_CR3_DMAT |      // Desbilita DMA
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

		disable();
#if HTL_UART_OPTION_DEACTIVATE == 1
		deactivate();
#endif

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
	Handsake handsake) const {

	if (_state == State::ready) {
		setParity(parity);
		setWordBits(wordBits, parity != Parity::none);
		setStopBits(stopBits);
		setHandsake(handsake);
		return eos::Results::success;
	}
	else
		return eos::Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Configura la paritat.
/// \param    usart: Registres de hardware del dispositiu.
/// \param    parity: Opcions de paritat.
///
 void UARTDevice::setParity(
    Parity parity) const {

    auto CR1 = _usart->CR1;
    if (parity == Parity::none)
    	clear(CR1, USART_CR1_PCE);
    else {
    	set(CR1, USART_CR1_PCE);
    	if (parity == Parity::even)
    		clear(CR1, USART_CR1_PS);
    	else
    		set(CR1, USART_CR1_PS);
    }
    _usart->CR1 = CR1;
}


/// ----------------------------------------------------------------------
/// \brief    Configura el nombre de bits de parada
/// \param    usart: Registres de harware del dispositiu.
/// \param    stopBits: Opcions dels bits de parada.
///
void UARTDevice::setStopBits(
    StopBits stopBits) const {

    auto CR2 = _usart->CR2;
    switch (stopBits) {
        case StopBits::sb0p5:
            clear(CR2, USART_CR2_STOP_1);
            set(CR2, USART_CR2_STOP_0);
            break;

        case StopBits::sb1:
        	clear(CR2, USART_CR2_STOP_1);
        	clear(CR2, USART_CR2_STOP_0);
            break;

        case StopBits::sb1p5:
        	set(CR2, USART_CR2_STOP_1);
        	set(CR2, USART_CR2_STOP_0);
            break;

        case StopBits::sb2:
        	set(CR2, USART_CR2_STOP_1);
        	clear(CR2, USART_CR2_STOP_0);
            break;
    }
    _usart->CR2 = CR2;
}


/// ----------------------------------------------------------------------
/// \brief    Configura nombre de bits de paraula.
/// \param    usart: Registres de herdware del dispositiu.
/// \param    wordBits: Opcions dels bits de paraula.
/// \params   useParity: True si utilitza bit de paritat
///
#if defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
void UARTDevice::setWordBits(
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

	auto a = startAtomic();
	auto CR1 = _usart->CR1;
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
	_usart->CR1 = CR1;
	endAtomic(a);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Configura el protocol.
/// \param    usart: Registres de hardware del dispositiu.
/// \param    handsake: Opcions de protocol.
///
void UARTDevice::setHandsake(
    Handsake handsake) const {

    auto CR3 = _usart->CR3;
    switch (handsake) {
        case Handsake::none:
        	clear(CR3, USART_CR3_RTSE | USART_CR3_CTSE);
            break;

        case Handsake::ctsrts:
        	set(CR3, USART_CR3_RTSE | USART_CR3_CTSE);
            break;
    }
    _usart->CR3 = CR3;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el valor del timeout per recepcio.
/// \param    timeout: El temps.
/// \param    El resultat de l'operacio.
///
#if defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
eos::Result UARTDevice::setRxTimeout(
    unsigned timeout) const {

	if (_state == State::ready) {

		if (isRTOAvailable()) {
			if (timeout == 0)
				clear(_usart->CR2, USART_CR2_RTOEN);
			else {
				set(_usart->CR2, USART_CR2_RTOEN);
				_usart->RTOR = timeout;
			}
		}

		return eos::Results::success;
	}
	else
		return eos::Results::errorState;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Asigna els valor de temporitzacio.
/// \param    baudMode: Les opcions del baud rate
/// \param    rate: El valor de velocitat.
/// \param    overSampling: Tipus de mostreig
/// \return   El resultat de l'operacio.
///
eos::Result UARTDevice::setTimming(
	BaudMode baudMode,
	uint32_t rate,
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

		unsigned fclk = ClockDevice::pInst->getClockFrequency(getUARTClock());

		unsigned div;
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

		return eos::Results::success;
	}
	else
		return eos::Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la font del relloge del generador de bauds
/// \param    clockSource: La font.
/// \return   El resultat de l'operacio.
///
eos::Result UARTDevice::setClockSource(
	ClockSource clockSource) const {

	if(_state == State::ready){

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

        enable();
        enableTransmissionIRQ();

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

        enable();
        enableTransmissionDMA();

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
		disableTransmission();
		disable();
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

		enable();
		enableReceptionIRQ();

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
		disableReception();
		disable();
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
		notifyTxCompleted(_txBuffer, _txCount, true);
		_state = State::ready;
	}
}

#elif defined(EOS_PLATFORM_STM32G0)
void UARTDevice::txInterruptService() {

	auto CR1 = _usart->CR1;
	auto ISR = _usart->ISR;

	// Interrupcio 'TXE' (Transmission buffer empty)
	//
	if (isSet(CR1, USART_CR1_TXEIE_TXFNFIE) && isSet(ISR, USART_ISR_TXE_TXFNF)) {
		if (_txCount < _txMaxCount) {
			_usart->TDR = _txBuffer[_txCount++];
			if (_txCount == _txMaxCount) {
				auto a = startAtomic();
				clear(_usart->CR1, USART_CR1_TXEIE_TXFNFIE);  // Deshabilita interrupcio TXE
				set(_usart->CR1, USART_CR1_TCIE);             // Habilita interrupcio TC
				endAtomic(a);
			}
		}
	}

	// Interrupcio 'TC'. (Transmission complete)
	//
	if (isSet(CR1, USART_CR1_TCIE) && isSet(ISR, USART_ISR_TC)) {
		disableTransmission();
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
			disableReception();
			notifyRxCompleted(_rxBuffer, _rxCount, true);
			_state = State::ready;
		}
	}

	// Interrupcio 'RTO'
	//
	if (isSet(CR1, USART_CR1_RTOIE) && isSet(ISR, USART_ISR_RTOF)) {
		_usart->ICR = USART_ICR_RTOCF;
		disableReception();
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
				disableReception();
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
			disableReception();
			notifyRxCompleted(_rxBuffer, _rxCount, true);
			_state = State::ready;
		}
	}

	// Interrupcio 'RTO'
	//
	if (isSet(CR1, USART_CR1_RTOIE) && isSet(ISR, USART_ISR_RTOF)) {
		_usart->ICR = USART_ICR_RTOCF;
		disableReception();
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
/// \brief    Espera que s'hagi completat la transmissio
/// \param    timeout: El temps maxim d'espera en ticks.
/// \return   True si tot es correcte, false en cas de timeout.
///
bool UARTDevice::waitTransmissionComplete(
	unsigned expireTime) {

#if defined(EOS_PLATFORM_STM32F4)
	while (!isSet(_usart->SR, USART_SR_TC)) {
#else
	while (!isSet(_usart->ISR, USART_ISR_TC)) {
#endif
		if (hasTickExpired(expireTime))
			return false;
	}

	//usart->ICR = USART_ICR_TCCF;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el buffer de transmissio estigui buit.
/// \param    expireTime: El limit de temps.
/// \return   True si tot es correcte, false en cas de timeout.
///
bool UARTDevice::waitTransmissionBufferEmpty(
	unsigned expireTime) {

#if defined(EOS_PLATFORM_STM32G0)
	while (!isSet(_usart->ISR, USART_ISR_TXE_TXFNF)) {
#elif defined(EOS_PLATFORM_STM32F4)
	while (!isSet(_usart->SR, USART_SR_TXE)) {
#else
	while (!isSet(_usart->ISR, USART_ISR_TXE)) {
#endif
		if (hasTickExpired(expireTime))
			return false;
	}

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el buffer de recepcio estigui ple
/// \param    expireTime: El limit de temps.
/// \return   True si tot es correcte, false en cas de timeout.
///
bool UARTDevice::waitReceptionBufferFull(
	unsigned expireTime) {

#if defined(EOS_PLATFORM_STM32G0)
	while ((_usart->ISR & USART_ISR_RXNE_RXFNE) == 0) {
#elif defined(EOS_PLATFORM_STM32F4)
	while ((_usart->SR & USART_SR_RXNE) == 0) {
#else
	while ((_usart->ISR & USART_ISR_RXNE) == 0) {
#endif
		if (hasTickExpired(expireTime))
			return false;
	}

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita el dispositiu.
///
void UARTDevice::enable() const {

	set(_usart->CR1,
		USART_CR1_UE);  // Habilita el dispositiu
}


/// ----------------------------------------------------------------------
/// \brief    Desabilita el dispositiu.
///
void UARTDevice::disable() const {

	clear(_usart->CR1,
		USART_CR1_UE |  // Desabilita el dispositiu
		USART_CR1_TE |  // Desabilita la transmissio
		USART_CR1_RE);  // Deshabilita la recepcio
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la transmissio de dades.
///
void UARTDevice::enableTransmission() const {

	auto a = startAtomic();
	set(_usart->CR1,
		USART_CR1_TE);       // Habilita la tramsmissio
	endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la transmissio de dades en modus IRQ
///
#if HTL_UART_OPTION_IRQ == 1
#if defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
void UARTDevice::enableTransmissionIRQ() const {

	auto a = startAtomic();

	set(_usart->CR1,
		USART_CR1_TXEIE |          // Habilita interrupcio TXE
		USART_CR1_TE);             // Habilita la transmissio
	endAtomic(a);
}
#elif defined(EOS_PLATFORM_STM32G0)
void UARTDevice::enableTransmissionIRQ() const {

	auto a = startAtomic();

	set(_usart->CR1,
		USART_CR1_TXEIE_TXFNFIE |  // Habilita interrupcio TXE
		USART_CR1_TE);             // Habilita la transmissio
	endAtomic(a);
}
#endif // defined(EOS_PLATFORM_XXX)
#endif // HTL_UART_OPTION_IRQ == 1


/// ----------------------------------------------------------------------
/// \brief    Habilita la transmissio de dades en modus DMA
///
#if HTL_UART_OPTION_DMA == 1
void UARTDevice::enableTransmissionDMA() const {

	//TODO: Comprovar si es necesari
	_usart->ICR = USART_ICR_TCCF;  // Borra el flag TC

	auto a = startAtomic();

    set(_usart->CR1,
    	USART_CR1_TE);            // Habilita transmissio
    set(_usart->CR3,
    	USART_CR3_DMAT);          // Habilita DMA

    endAtomic(a);
}
#endif // HTL_UART_OPTION_DMA == 1


/// ----------------------------------------------------------------------
/// \brief    Deshabilita la transmissio
///
void UARTDevice::disableTransmission() const {

	auto a = startAtomic();

	clear(_usart->CR1,
#if defined(EOS_PLATFORM_STM32G0)
		USART_CR1_TXEIE_TXFNFIE | // Deshabilita interrupcio TXE
#else
		USART_CR1_TXEIE |         // Deshabilita interrupcio TXE
#endif
		USART_CR1_TCIE);          // Deshabilita interrupcio TC

#if HTL_UART_OPTION_DMA == 1
	clear(_usart->CR3,
		USART_CR3_DMAT);          // Desabilita el DMA
#endif

	// TODO: Asegurar-se que l'ultim byte s'ha transmes abans de deshabilitar
	// la transmissio

	clear(_usart->CR1,
		USART_CR1_TE);            // Desabilita transmissio

	endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la recepcio.
///
void UARTDevice::enableReception() const {

#if !defined(EOS_PLATFORM_STM32F4)
	_usart->ICR = USART_ICR_RTOCF; // Borra el flag RTO
#endif

	auto a = startAtomic();
	set(_usart->CR1,
		USART_CR1_RE);            // Habilita la recepcio
	endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la recepcio en modus IRQ.
/// \param    usart: Registres de hardware del dispoositiu.
///
#if HTL_UART_OPTION_IRQ == 1
void UARTDevice::enableReceptionIRQ() const {

#if !defined(EOS_PLATFORM_STM32F4)
	set(_usart->ICR,
		USART_ICR_RTOCF |           // Borra el flag RTO
		USART_ICR_IDLECF);          // Borra el flag IDLE
#endif

	auto a = startAtomic();

	set(_usart->CR1,
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
		set(_usart->CR1, USART_CR1_RTOIE);    // Habilita interrupcio RTO
	else
		set(_usart->CR1, USART_CR1_IDLEIE);   // Habilita interrupcio IDLE
#endif

	endAtomic(a);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Deshabilita la recepcio.
///
void UARTDevice::disableReception() const {

	auto a = startAtomic();

	clear(_usart->CR1,
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
	clear(_usart->CR3,
		USART_CR3_DMAT);           // Desabilita el DMA
#endif

	clear(_usart->CR1,
		USART_CR1_RE);             // Deshabilita recepcio

	endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu el registre de transmissio des dades.
/// \param    usart: Registres de hardware del dispositiu.
/// \param    data: Les dades a transmetre.
//
void UARTDevice::writeData(
	uint8_t data) const {

#if defined(EOS_PLATFORM_STM32F4)
	_usart->DR = data;
#else
	_usart->TDR = data;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix el registre de recepcio dades.
/// \param    usart: Registres de hardware del dispositiu.
/// \return   Les dades rebudes.
//
uint8_t UARTDevice::readData() const {

#if defined(EOS_PLATFORM_STM32F4)
	return _usart->DR;
#else
	return _usart->RDR;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el fifo esta disposnible en la uart
/// \return   El resultat de l'operacio.
///
#if (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)
bool UARTDevice::isFifoAvailable() const {

	return false;
}
#endif // (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)


/// ----------------------------------------------------------------------
/// \brief    Comprova si el fifo esta activat
/// \return   El resultatd e l'operacio.
///
#if (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)
bool UARTDevice::isFifoEnabled() const {

	return isSet(_uart->CR1, USART_CR1_FIFOEN);
}
#endif // (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)
