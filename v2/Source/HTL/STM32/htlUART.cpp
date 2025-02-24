#include "HTL/htl.h"
#include "HTL/STM32/htlClock.h"
#include "HTL/STM32/htlUART.h"


using namespace eos;
using namespace htl;
using namespace htl::uart;
using namespace htl::clock;


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
static void enableTransmissionIRQ(USART_TypeDef *usart);
static void enableTransmissionDMA(USART_TypeDef *usart);
static void disableTransmission(USART_TypeDef *usart);

static void enableReception(USART_TypeDef *usart);
static void enableReceptionIRQ(USART_TypeDef *usart);
static void enableReceptionDMA(USART_TypeDef *usart);
static void disableReception(USART_TypeDef *usart);

static bool waitTransmissionCompleteFlag(USART_TypeDef *usart, unsigned expireTime);
static bool waitTransmissionBufferEmptyFlag(USART_TypeDef *usart, unsigned expireTime);
static bool waitReceptionBufferNotEmptyFlag(USART_TypeDef *usart, unsigned expireTime);

static void clearTransmissionCompleteFlag(USART_TypeDef *usart);
static void clearReceiverTimeOutFlag(USART_TypeDef *usart);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    usart: Registres hardware del modul USART.
///
UARTDevice::UARTDevice(
	USART_TypeDef *usart):

	_usart {usart},
	_state {State::invalid},
	_dmaNotifyEvent {*this, &UARTDevice::dmaNotifyEventHandler} {

	_state = State::reset;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul UART.
/// \return   El resultat de l'operacio.
///
eos::Result UARTDevice::initialize() {

	if (_state == State::reset) {

		activate();
		disable(_usart);

		_usart->CR2 &= ~(
			#if defined(EOS_PLATFORM_STM32G0)
	    	USART_CR2_LINEN |  // Modus sincron, deshabilita LIN
			#endif
			USART_CR2_CLKEN);  // Modus sincron, desabilita CLK

		_usart->CR3 &= ~(
			#if defined(EOS_PLATFORM_STM32G0)
			USART_CR3_SCEN |   // Desabilita smartcad
			USART_CR3_IREN |   // Desabilita IRDA
			#endif
			USART_CR3_HDSEL);  // Desabilita half-duplex

		enable(_usart);

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
		deactivate();

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
		setReceiveTimeout(_usart, 11 * 100);
		return Results::success;
	}
	else
		return Results::errorState;
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
		return Results::success;
	}
	else
		return Results::errorState;
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

		return Results::success;
	}
	else
		return Results::errorState;
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

		auto expireTime = getTick() + timeout;
		bool error = false;

		_state = State::transmiting;

		enableTransmission(_usart);

		while (length-- > 0) {
			if (!waitTransmissionBufferEmptyFlag(_usart, expireTime)) {
				error = true;
				break;
			}
			_usart->TDR = *buffer++;
		}

	    if (!waitTransmissionCompleteFlag(_usart, expireTime))
	    	error = true;

		disableTransmission(_usart);

		_state = State::ready;

		return error ? Results::timeout : Results::success;
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return Results::busy;

	else
		return Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la transmissio d'un bloc de dades per interrupcions.
/// \param    buffer: Buffer de dades.
/// \param    length: El nombre de bytes a transmetre.
/// \return   El resultat de l'operacio
///
eos::Result UARTDevice::transmit_IRQ(
	const uint8_t *buffer,
	unsigned length) {

	if (_state == State::ready) {

		_state = State::transmiting;

		_txBuffer = buffer;
		_txCount = 0;
        _txMaxCount = length;

        enableTransmissionIRQ(_usart);

		return Results::success;
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return Results::busy;

	else
		return Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades utilitzant DMA.
/// \param    devDMA: Dispositiu DMA.
/// \param    buffer: Buffer de dades.
/// \param    length: El nombre de bytes a transmetre.
/// \return   El resultat de l'operacio
///
eos::Result UARTDevice::transmit_DMA(
    dma::DMADevice *devDMA,
    const uint8_t *buffer,
    unsigned length) {

    if (_state == State::ready) {

        _state = State::transmiting;

        _txBuffer = buffer;
        _txCount = 0;
        _txMaxCount = length;

        enableTransmissionDMA(_usart);

        // Inicia la transferencia per DMA
        //
        devDMA->setNotifyEvent(_dmaNotifyEvent, true);
        devDMA->start(buffer, (uint8_t*)&(_usart->TDR), _txMaxCount);

        return Results::success;
    }

    else if ((_state == State::transmiting) || (_state == State::receiving))
        return Results::busy;

    else
        return Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Aborta la transmissio.
///
eos::Result UARTDevice::abortTransmission() {

	if (_state == State::transmiting) {
		disableTransmission(_usart);
		_state = State::ready;
		return eos::Results::success;
	}
	else
		return Results::errorState;
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

		enableReception(_usart);

		while (bufferSize-- > 0) {

			if (!waitReceptionBufferNotEmptyFlag(_usart, expireTime)) {
				error = true;
				break;
			}

			*buffer++ = _usart->RDR;
		}

		disableTransmission(_usart);

		_state = State::ready;

		return error ? Results::timeout : Results::success;
	}
	else if ((_state == State::transmiting) || (_state == State::receiving))
		return Results::busy;

	else
		return Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la recepcio d'un bloc de dades per interrupcions.
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer en bytes.
/// \return   El resultat de l'operacio.
///
eos::Result UARTDevice::receive_IRQ(
	uint8_t *buffer,
	unsigned bufferSize) {

	if (_state == State::ready) {

		_state = State::receiving;

		_rxBuffer = buffer;
		_rxCount = 0;
		_rxMaxCount = bufferSize;

		enableReceptionIRQ(_usart);

		return Results::success;
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return Results::busy;

	else
		return Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades utilitzan DMA.
/// \param    devDMA: El dispositiu DMA.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany del buffer en bytes.
/// \return   El resultat de l'operacio.
///
eos::Result UARTDevice::receive_DMA(
    dma::DMADevice *devDMA,
    uint8_t *buffer,
    unsigned bufferSize) {

	return Results::error;
}


/// ----------------------------------------------------------------------
/// \brief    Aborta la recepcio.
///
eos::Result UARTDevice::abortReception() {

	if (_state == State::receiving) {
		disableReception(_usart);
		_state = State::ready;
		return eos::Results::success;
	}
	else
		return Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
#if defined(EOS_PLATFORM_STM32F0)
void UARTDevice::interruptService() {

	auto CR1 = _usart->CR1;
	auto CR3 = _usart->CR3;
	auto ISR = _usart->ISR;

	// Comprova de forma rapida si hi ha errors
	//
	if (ISR & (USART_ISR_PE | USART_ISR_FE | USART_ISR_ORE | USART_ISR_NE)) {

		// Comprova si es un error PARITY
		//
		if ((ISR & USART_ISR_PE) && (CR1 & USART_CR1_PEIE)) {

			// Borra el flag
			//
			_usart->ICR = USART_ICR_PECF;
		}

		// Comprova si hi ha error FRAME
		//
	    if ((ISR & USART_ISR_FE) && (CR3 & USART_CR3_EIE)) {

			// Borra el flag
			//
	    	_usart->ICR = USART_ICR_FECF;
	    }

	    // Comprova si es un error NOISE
	    //
	    if ((ISR & USART_ISR_NE) && (CR3 & USART_CR3_EIE)) {

			// Borra el flag
			//
	    	_usart->ICR = USART_ICR_NCF;
	    }

		// Comprova si es un error OVERRUN
		//
		if ((ISR & USART_ISR_ORE) &&
			(CR1 & USART_CR1_RXNEIE) &&
			(CR3 & USART_CR3_EIE)) {

			// Borra el flag
			//
			_usart->ICR = USART_ICR_ORECF;
		}
	}

	// No hi han errrors
	//
	else {
		// Interrupcio 'TXE'
		//
		if ((CR1 & USART_CR1_TXEIE) && (ISR & USART_ISR_TXE)) {

			if (_txCount < _txMaxCount) {
				_usart->TDR = _txBuffer[_txCount++];
				if (_txCount == _txMaxCount) {

					ATOMIC_CLEAR_BIT(_usart->CR1,
						USART_CR1_TXEIE); // Deshabilita interrupcio TXE
					ATOMIC_SET_BIT(_usart->CR1,
						USART_CR1_TCIE);          // Habilita interrupcio TC
				}
			}
		}

		// Interrupcio 'TC'. Nomes en l'ultim caracter transmes.
		//
		if ((CR1 & USART_CR1_TCIE) && (CR1 & USART_CR1_TCIE)) {

			clearTransmissionCompleteFlag(_usart);
			disableTransmission(_usart);
			notifyTxCompleted(_txBuffer, _txCount, true);

			_state = State::ready;
		}

		/// Interrupcio 'RXNE'
		//
		if ((CR1 & USART_CR1_RXNEIE) && (ISR & USART_ISR_RXNE)) {
			if (_rxCount < _rxMaxCount) {
				_rxBuffer[_rxCount++] = _usart->RDR;
				if (_rxCount == _rxMaxCount) {

					disableReception(_usart);
					notifyRxCompleted(_rxBuffer, _rxCount, true);

					// Canvia l'estat
					//
					_state = State::ready;
				}
			}
		}

		// Interrupcio 'RTO'
		//
		if ((CR1 & USART_CR1_RTOIE) && (ISR & USART_ISR_RTOF)) {

			clearReceiverTimeOutFlag(_usart);
			disableReception(_usart);
			notifyRxCompleted(_rxBuffer, _rxCount, true);

			// Canvia d'estat
			//
			_state = State::ready;
		}
	}
}

#elif defined(EOS_PLATFORM_STM32F7)
void UARTDevice::interruptService() {

    // Interrupcio TXEFE (FIFO/TX empty)
    //
    if ((_usart->CR1 & USART_CR1_TXEIE) && (_usart->ISR & USART_ISR_TXE)) {

        if (_txCount < _txMaxCount) {
            _usart->TDR = _txBuffer[_txCount++];
            if (_txCount == _txMaxCount)
                ATOMIC_MODIFY_REG(_usart->CR1, USART_CR1_TXEIE, USART_CR1_TCIE);
        }
    }

    // Interrupcio TC (Transmission complete). Nomes en l'ultim caracter transmes
    //
    if ((_usart->CR1 & USART_CR1_TCIE) && (_usart->ISR & USART_ISR_TC)) {

        _usart->ICR |= USART_ICR_TCCF;
        ATOMIC_CLEAR_BIT(_usart->CR1, USART_CR1_TXEIE | USART_CR1_TCIE | USART_CR1_TE);
        notifyTxCompleted(_txBuffer, _txCount, true);
        _state = State::ready;
    }

    /// Interupcio FIFO/RD not empty
    //
    if ((_usart->CR1 & USART_CR1_RXNEIE) && (_usart->ISR & USART_ISR_RXNE)) {

        if (_rxCount < _rxNaxCount) {
            _rxBuffer[_rxCount++] = _usart->RDR;
            if (_rxCount == _rxMaxCount) {
                ATOMIC_CLEAR_BIT(_usart->CR1, USART_CR1_RXNEIE | USART_CR1_RTOIE | USART_CR1_RE);
                notifyRxComplete(_rxBuffer, _rxCount, true);
                _state = State::ready;
            }
        }
    }

    // Interrupcio RX timeout
    //
    if ((_usart->CR1 & USART_CR1_RTOIE) && (_usart->ISR & USART_ISR_RTOF)) {

        _usart->ICR |= USART_ICR_RTOCF;
        ATOMIC_CLEAR_BIT(_usart->CR1, USART_CR1_RXNEIE | USART_CR1_RTOIE | USART_CR1_RE);
        notifyRxCompleted(_rxBuffer, _rxCount, true);
        _state = State::ready;
    }
}

#elif defined(EOS_PLATFORM_STM32G0)
void UARTDevice::interruptService() {

	auto CR1 = _usart->CR1;
	auto CR3 = _usart->CR3;
	auto ISR = _usart->ISR;

	// Comprova de forma rapida si hi ha errors
	//
	if (ISR & (USART_ISR_PE | USART_ISR_FE | USART_ISR_ORE | USART_ISR_NE)) {

		// Comprova si es un error PARITY
		//
		if ((ISR & USART_ISR_PE) && (CR1 & USART_CR1_PEIE)) {

			// Borra el flag
			//
			_usart->ICR = USART_ICR_PECF;
		}

		// Comprova si hi ha error FRAME
		//
	    if ((ISR & USART_ISR_FE) && (CR3 & USART_CR3_EIE)) {

			// Borra el flag
			//
	    	_usart->ICR = USART_ICR_FECF;
	    }

	    // Comprova si es un error NOISE
	    //
	    if ((ISR & USART_ISR_NE) && (CR3 & USART_CR3_EIE)) {

			// Borra el flag
			//
	    	_usart->ICR = USART_ICR_NECF;
	    }

		// Comprova si es un error OVERRUN
		//
		if ((ISR & USART_ISR_ORE) &&
			(CR1 & USART_CR1_RXNEIE_RXFNEIE) &&
			(CR3 & (USART_CR3_RXFTIE | USART_CR3_EIE))) {

			// Borra el flag
			//
			_usart->ICR = USART_ICR_ORECF;
		}
	}

	// No hi han errrors
	//
	else {

		// Transmissio amb el FIFO activat
		//
		if (CR1 & USART_CR1_FIFOEN) {

		}

		// Transmissio amb el FIFO desactivat.
		///
		else {

			// Interrupcio 'TXE'
			//
			if ((CR1 & USART_CR1_TXEIE_TXFNFIE) && (ISR & USART_ISR_TXE_TXFNF)) {

				if (_txCount < _txMaxCount) {
					_usart->TDR = _txBuffer[_txCount++];
					if (_txCount == _txMaxCount) {

						ATOMIC_CLEAR_BIT(_usart->CR1,
							USART_CR1_TXEIE_TXFNFIE); // Deshabilita interrupcio TXE
						ATOMIC_SET_BIT(_usart->CR1,
							USART_CR1_TCIE);          // Habilita interrupcio TC
					}
				}
			}

			// Interrupcio 'TC'. Nomes en l'ultim caracter transmes.
			//
			if ((CR1 & USART_CR1_TCIE) && (CR1 & USART_CR1_TCIE)) {

				clearTransmissionCompleteFlag(_usart);
				disableTransmission(_usart);
				notifyTxCompleted(_txBuffer, _txCount, true);

				_state = State::ready;
			}

			/// Interrupcio 'RXNE'
			//
			if ((CR1 & USART_CR1_RXNEIE_RXFNEIE) && (ISR & USART_ISR_RXNE_RXFNE)) {
				if (_rxCount < _rxMaxCount) {
					_rxBuffer[_rxCount++] = _usart->RDR;
					if (_rxCount == _rxMaxCount) {

						disableReception(_usart);
						notifyRxCompleted(_rxBuffer, _rxCount, true);

						// Canvia l'estat
						//
						_state = State::ready;
					}
				}
			}

			// Interrupcio 'RTO'
			//
			if ((CR1 & USART_CR1_RTOIE) && (ISR & USART_ISR_RTOF)) {

				clearReceiverTimeOutFlag(_usart);
				disableReception(_usart);
				notifyRxCompleted(_rxBuffer, _rxCount, true);

				// Canvia d'estat
				//
				_state = State::ready;
			}
		}
	}
}
#endif


void UARTDevice::txInterruptService() {

}


void UARTDevice::rxInterruptService() {

}


/// ----------------------------------------------------------------------
/// \brief    Reb les notificacions del DMA
/// \param    devDMA: El dispositiu DMA que genera l'event.
/// \param    args: Parametres del event.
///
void UARTDevice::dmaNotifyEventHandler(
    DevDMA *devDMA,
    DMANotifyEventArgs &args) {

    switch (args.id) {

        // Transmissio complerta de tots els bytes.
        //
        case htl::dma::NotifyID::completed:
            _txCount = _txMaxCount;
            _usart->ICR = USART_ICR_TCCF;
            ATOMIC_SET_BIT(_usart->CR1, USART_CR1_TCIE);
            devDMA->disableNotifyEvent();
            break;

        // Error en la transmissio DMA.
        //
        case htl::dma::NotifyID::error:
            break;

        default:
        	break;
    }
}


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
/// \brief    Obte el rellotge asignat al generador de bauds.
/// \param    usart: El bloc de registres
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
            case USART5_BASE:
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

#if defined(EOS_PLATFORM_STM32F0)
    static const ClockSource csTbl[4] = {
        ClockSource::pclk,
        ClockSource::sysclk,
        ClockSource::hsi,
        ClockSource::lse
    };
#elif defined(EOS_PLATFORM_STM32F4)
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
                return Clock::getClockFrequency(clock::ClockID::pclk);

        case ClockSource::sysclk:
            return Clock::getClockFrequency(clock::ClockID::sysclk);

        #if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
        case ClockSource::hsi:
            return Clock::getClockFrequency(clock::ClockID::hsi);
        #endif

        #if defined(EOS_PLATFORM_STM32G0)
        case ClockSource::hsi16:
            return Clock::getClockFrequency(clock::ClockID::hsi16);
        #endif

        case ClockSource::lse:
            return Clock::getClockFrequency(clock::ClockID::lse);

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
/// \params   useParity: True si utilitza bit de paritat
///
static void setWordBits(
    USART_TypeDef *usart,
    WordBits wordBits,
    bool useParity) {

    auto numBits = 7 + uint32_t(wordBits) + (useParity ? 0 : 1);

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
    usart->CR1 = tmp;
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
static void setReceiveTimeout(
    USART_TypeDef *usart,
    unsigned timeout) {

    if (timeout == 0)
        usart->CR2 &= ~USART_CR2_RTOEN;
    else {
        usart->CR2 |= USART_CR2_RTOEN;
        usart->RTOR = timeout;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Borra el flag 'TC'
/// \param    usart: Registres de de hardware del dispositiu
///
static inline void clearTransmissionCompleteFlag(
	USART_TypeDef *usart) {

	usart->ICR = USART_ICR_TCCF;
}


/// ----------------------------------------------------------------------
/// \brief    Borra el flag 'RTO'
/// \param    usart: Registres de de hardware del dispositiu
///
static inline void clearReceiverTimeOutFlag(
	USART_TypeDef *usart) {

	usart->ICR = USART_ICR_RTOCF;
}


/// ----------------------------------------------------------------------
/// \brief    Espera l'activacio del flag TC
/// \param    usart: Registres de hardware del dispositiu.
/// \param    timeout: El temps maxim d'espera en ticks.
/// \return   True si tot es correcte, false en cas de timeout.
///
static bool waitTransmissionCompleteFlag(
	USART_TypeDef *usart,
	unsigned expireTime) {

	while ((usart->ISR & USART_ISR_TC) == 0) {
		if (hasTickExpired(expireTime))
			return false;
	}

	usart->ICR = USART_ICR_TCCF;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Espera l'activacio del flag TC
/// \param    usart: Registres de hardware del dispositiu.
/// \param    expireTime: El limit de temps.
/// \return   True si tot es correcte, false en cas de timeout.
///
static bool waitTransmissionBufferEmptyFlag(
	USART_TypeDef *usart,
	unsigned expireTime) {

#if defined(EOS_PLATFORM_STM32G0)
	while ((usart->ISR & USART_ISR_TXE_TXFNF) == 0) {
#else
	while ((usart->ISR & USART_ISR_TXE) == 0) {
#endif
		if (hasTickExpired(expireTime))
			return false;
	}

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Espera l'activacio de flag RXNE
/// \param    usart: Els registres de hardware del dispositiu.
/// \param    expireTime: El limit de temps.
/// \return   True si tot es correcte, false en cas de timeout.
///
static bool waitReceptionBufferNotEmptyFlag(
	USART_TypeDef *usart,
	unsigned expireTime) {

#if defined(EOS_PLATFORM_STM32G0)
	while ((usart->ISR & USART_ISR_RXNE_RXFNE) == 0) {
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

	usart->CR1 |= USART_CR1_UE;
}


/// ----------------------------------------------------------------------
/// \brief    Desabilita el dispositiu.
/// \param    usart: Registres de hardware del dispositiu.
///
static void disable(
	USART_TypeDef *usart) {

	usart->CR1 &= ~(
		#if defined(EOS_PLATFORM_STM32G0)
		USART_CR1_FIFOEN | // Deshabilita el FIFO
		#endif
		USART_CR1_UE |     // Desabilita el dispositiu
		USART_CR1_TE |     // Desabilita la transmissio
		USART_CR1_RE);     // Deshabilita la recepcio
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la transmissio de dades.
/// \param    usart: Registres de hardware del dispositiu.
///
static void enableTransmission(
	USART_TypeDef *usart) {

	usart->ICR = USART_ICR_TCCF;   // Borra el flag TC

	auto a = startATOMIC();
	usart->CR1 |= USART_CR1_TE;    // Habilita la tramsmissio
	endATOMIC(a);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la transmissio de dades en modus IRQ
/// \param    usart: Registres de hardware del dispositiu.
///
static void enableTransmissionIRQ(
	USART_TypeDef *usart) {

	usart->ICR = USART_ICR_TCCF;   // Borra el flag TC

	auto a = startATOMIC();
	usart->CR1 |=
		#if defined(EOS_PLATFORM_STM32G0)
		USART_CR1_TXEIE_TXFNFIE | // Habilita interrupcio TXE
		#else
		USART_CR1_TXEIE |         // Habilita interrupcio TXE
		#endif
		USART_CR1_TE;             // Habilita la transmissio
	endATOMIC(a);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la transmissio de dades en modus DMA
/// \param    usart: Registres de hardware del dispositiu.
///
static void enableTransmissionDMA(
	USART_TypeDef *usart) {

	usart->ICR = USART_ICR_TCCF;   // Borra el flag TC

	auto a = startATOMIC();
    usart->CR1 |= USART_CR1_TE;    // Habilita transmissio
    usart->CR3 |= USART_CR3_DMAT;  // Habilita DMA
    endATOMIC(a);
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita la transmissio
/// \param    usart: Registres de hardware del dispositiu.
///
static void disableTransmission(
	USART_TypeDef *usart) {

	auto a = startATOMIC();

	// Desabilita interrupcions i transmissio
	//
	usart->CR1 &= ~(
#if defined(EOS_PLATFORM_STM32F0)
		USART_CR1_TXEIE |         // Deshabilita interrupcio TXE
#else
		USART_CR1_TXEIE_TXFNFIE | // Deshabilita interrupcio TXE
#endif
		USART_CR1_TCIE |          // Deshabilita interrupcio TC
		USART_CR1_TE);            // Desabilita transmissio

	// Deshabilita el DMA
	//
	usart->CR3 &= ~USART_CR3_DMAT;

	endATOMIC(a);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la recepcio.
/// \param    usart: Registres de hardware del dispoositiu.
///
static void enableReception(
	USART_TypeDef *usart) {

	usart->ICR = USART_ICR_RTOCF; // Borra el flag RTO

	auto a = startATOMIC();
	usart->CR1 |= USART_CR1_RE;
	endATOMIC(a);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la recepcio en modus IRQ.
/// \param    usart: Registres de hardware del dispoositiu.
///
static void enableReceptionIRQ(
	USART_TypeDef *usart) {

	auto a = startATOMIC();
	usart->CR1 |=
		USART_CR1_RE |              // Habilita la recepcio
		USART_CR1_PEIE |            // Habilita interrupcio PE
		#if defined(EOS_PLATFORM_STM32G0)
		USART_CR1_RXNEIE_RXFNEIE |  // Habilita interrupcio RXNE
		#else
		USART_CR1_RXNEIE |          // Habilita interrupcio RXNE
		#endif
		USART_CR1_RTOIE;            // Habilita interrupcio RTO
	endATOMIC(a);
}


/// ----------------------------------------------------------------------
/// \brief    Desabilita la recepcio.
/// \param    usart: Registres de hardware del dispositiu.
///
static void disableReception(
	USART_TypeDef *usart) {

	auto a = startATOMIC();

	// Desabilita interrupcions i recepcio
	//
	usart->CR1 &= ~(
#if defined(EOS_PLATFORM_STM32F0)
		USART_CR1_RXNEIE |         // Deshabilita interrupcio RXNE
#else
		USART_CR1_RXNEIE_RXFNEIE | // Deshabilita interrupcio RXNE
#endif
		USART_CR1_RTOIE |          // Deshabilita interrupcio RTO
		USART_CR1_PEIE |           // Deshabilita interrupcio PE
		USART_CR1_RE);             // Deshabilita recepcio

	// Deshabilita el DMA
	//
	usart->CR3 &= ~USART_CR3_DMAT;

	endATOMIC(a);
}
