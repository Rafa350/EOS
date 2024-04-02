#include "HTL/htl.h"
#include "HTL/STM32/htlI2C.h"


using namespace htl;
using namespace htl::i2c;


static void setTimming(I2C_TypeDef *i2c, uint8_t prescaler, uint8_t scldel,
        uint8_t sdadel, uint8_t sclh, uint8_t scll);
static void setClockSource(I2C_TypeDef *i2c, ClockSource clockSource);
static ClockSource getClockSource(I2C_TypeDef *i2c);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    i2c: Registres hardware del modul I2C.
///
I2CSlaveDevice::I2CSlaveDevice(
	I2C_TypeDef *i2c) :

	I2CDevice {i2c},
	_state {State::reset},
	_buffer {nullptr},
	_bufferSize {0},
	_count {0},
    _notifyEvent {nullptr},
    _notifyEventEnabled {false} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul com esclau.
/// \param    addr: Adressa I2C.
///
Result I2CSlaveDevice::initialize(
	uint16_t addr,
	uint8_t prescaler,
	uint8_t scldel,
	uint8_t sdadel,
	uint8_t sclh,
	uint8_t scll) {

	if (_state == State::reset) {

		// Activa el dispositiu
		//
		activate();
		reset();

		// Configura els parametres de timing
		//
		setTimming(_i2c, prescaler, scldel, sdadel, sclh, scll);

		// Configura l'adressa I2C
		//
		_i2c->OAR1 &= ~I2C_OAR1_OA1EN;
		_i2c->OAR1 |= (addr << I2C_OAR1_OA1_Pos) & I2C_OAR1_OA1_Msk;
		_i2c->OAR1 |= I2C_OAR1_OA1EN;

		_i2c->OAR2 &= ~I2C_OAR2_OA2EN;

		// Configura els parametres de comunicacio i protocol
		//
		_i2c->CR1 &= ~(I2C_CR1_NOSTRETCH | I2C_CR1_SBC);

		_state = State::ready;

		return Result::success();
	}

	else
		return Result::error();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul.
///
Result I2CSlaveDevice::deinitialize() {

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
/// \brief    Asigna el event de notificacio.
/// \param    event: El event.
/// \param    enabled: Indica si l'habilita.
///
void I2CSlaveDevice::setNotifyEvent(
    ISlaveNotifyEvent &event,
    bool enabled) {

    _notifyEvent = &event;
    _notifyEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Configura el modul en modus d'escolta.
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer de dades en bytes.
///
Result I2CSlaveDevice::listen_IRQ(
	uint8_t *buffer,
	unsigned bufferSize) {

    // Comprova si l'estat es 'ready'
    //
	if (_state == State::ready) {

	    // Prepara les variables per process de comunicacio.
	    //
        _buffer = buffer;
		_bufferSize = bufferSize;

		// Canvia l'estat a 'listen'
		//
		_state = State::listen;

		// Habilita les comunicacions i les interrupcions
		//
		_i2c->CR1 |=
            I2C_CR1_PE |     // Habilita les comunicacions
            I2C_CR1_ADDRIE | // Habilita la interrupcio ADDR
            I2C_CR1_ERRIE |  // Habilita la interrupcio ERR
            I2C_CR1_NACKIE | // Habilita la interrupcio NACK
            I2C_CR1_STOPIE;  // Habilita la interrupcio STOP

		return Result::success();
	}

	else if ((_state == State::listen) || (_state == State::listenRx) || (_state == State::listenTx))
	    return Result::busy();

	else
		return Result::error();
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el modus d'escolta.
///
Result I2CSlaveDevice::abortListen() {

	if (_state == State::listen) {

		// Deshabilita els comunicacions i les interrupcions
		//
		_i2c->CR1 &= ~(I2C_CR1_PE | I2C_CR1_ADDRIE | I2C_CR1_ERRIE | I2C_CR1_NACKIE | I2C_CR1_STOPIE);

		_buffer = nullptr;
		_bufferSize = 0;

		_state = State::ready;

		return Result::success();
	}

	else if ((_state == State::listenRx) || (_state == State::listenTx))
	    return Result::busy();

	else
        return Result::error();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
void I2CSlaveDevice::interruptService() {

	switch (_state) {
		case State::listen:
			interruptServiceListen();
			break;

		case State::listenRx:
			interruptServiceListenRx();
			break;

		case State::listenTx:
			interruptServiceListenTx();
			break;

		default:
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per l'estat 'listen'
///
void I2CSlaveDevice::interruptServiceListen() {

	// S'ha detectat coincidencia amb l'adressa.
	//
	if (isAddressMatchInterruptEnabled() &&
	    isAddressMatchFlagSet()) {

	    clearAddressMatchFlag();
	    disableAddressMatchInterrupt();

    	// Comprova si es una transmissio (S->M)
    	//
    	if (_i2c->ISR & I2C_ISR_DIR) {
    		enableTxBufferEmptyInterrupt();
            enableStopDetectionInterrupt();
    		_state = State::listenTx;
    	}

    	// En cas contrari, es una recepcio (M->S)
    	//
    	else {
    		enableRxBufferNotEmptyInterrupt();
            enableStopDetectionInterrupt();
    		_state = State::listenRx;
    	}

        uint16_t addr = 
            (((_i2c->ISR & I2C_ISR_ADDCODE_Msk) >> I2C_ISR_ADDCODE_Pos) << 1) |
			(((_i2c->ISR & I2C_ISR_DIR_Msk) >> I2C_ISR_DIR_Pos) << 0);
        notifyAddressMatch(addr, true);

        _count = 0;
        _length = 0;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per l'estat 'listenRx'
///
void I2CSlaveDevice::interruptServiceListenRx() {

	// El registre de recepcio de dades no es buit
	//
	if (isRxBufferNotEmptyInterruptEnabled() &&
	    isRxBufferNotEmptyFlagSet()) {

        // Llegeix el byte i el acumula en el buffer
        //
        _buffer[_count++] = (uint8_t) _i2c->RXDR;

        // Comprova si el buffer es ple
        //
        if (_count == _bufferSize) {

            // Notifica que hi han dades disponibles.
            //
            notifyRxDataAvailable(_buffer, _count, true);

            // Inicialitza el contador per començar de nou
            // a omplir el buffer.
            //
            _count = 0;
        }
	}

	// Deteccio de la condicio STOP
	//
	if (isStopDetectionInterruptEnabled() &&
	    isStopDetectionFlagSet()) {

	    clearStopDetectionFlag();
	    disableStopDetectionInterrupt();
	    disableRxBufferNotEmptyInterrupt();

	    // Notifica el final de la recepcio de dades, indicant
	    // les dades disponibles que resten.
	    //
        notifyRxCompleted(_buffer, _count, true);

        enableAddressMatchInterrupt();

		_state = State::listen;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per l'estat 'listenTx'
///
void I2CSlaveDevice::interruptServiceListenTx() {

	// S'ha detectat un NACK
	//
	if (isNackDetectionInterruptEnabled() &&
	    isNackDetectionFlagSet()) {

		_i2c->ICR |= I2C_ICR_NACKCF;
	}

	// S'ha detectat la condicio STOP
	//
	if (isStopDetectionInterruptEnabled() &&
	    isStopDetectionFlagSet()) {

    	clearStopDetectionFlag();
    	disableStopDetectionInterrupt();
    	disableTxBufferEmptyInterrupt();

    	notifyTxCompleted(true);

        enableAddressMatchInterrupt();

        _state = State::listen;
	}

	// El registre de transmissio de dades es buit
	//
	if (isTxBufferEmptyInterruptEnabled() &&
	    isTxBufferEmptyFlagSet()) {

		// Si el buffer es buit, o si ja s'ha transmes tot el contingut del
		// buffer, ho notifica a l'aplicacio perque suministri mes dades.
		//
		if (_count == _length) {
            _count = 0;
            _length = 0;
            notifyTxDataRequest(_buffer, _bufferSize, _length, true);
            if (_length > _bufferSize)
                _length = _bufferSize;
		}

		// Si hi han dades en el buffer els transmiteix, si no
		// transmiteix zeros
		//
		if (_count < _length)
		    _i2c->TXDR = _buffer[_count++];
		else
		    _i2c->TXDR = 0;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Notifica la coincidencia amb l'adressa del esclau.
/// \param    addr: L'adressa.
/// \param    irq: Indica si es genera desde una interrupcio.
///
void I2CSlaveDevice::notifyAddressMatch(
    uint16_t addr,
    bool irq) {
    
    if (_notifyEventEnabled) {
        NotifyEventArgs args = {
            .instance = this,
            .id = NotifyID::addressMatch,
            .irq = irq,
            .AddressMatch {
                .addr = addr
            }
        };
        _notifyEvent->execute(args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Notifica que hi han dades rebudes disposibles.
/// \param    buffer: Buffer de dades.
/// \param    length: Tamany de les dades en bytes.
/// \param    irq: Indica si es genera desde una interrupcio.
///
void I2CSlaveDevice::notifyRxDataAvailable(
    const uint8_t *buffer, 
    unsigned length,
    bool irq) {
    
    if (_notifyEventEnabled) {
        NotifyEventArgs args = {
            .instance = this,
            .id = NotifyID::rxDataAvailable,
            .irq = irq,
            .RxDataAvailable {
                .buffer = buffer,
                .length = length
            }
        };
        _notifyEvent->execute(args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Notifica que ha finalitzat la recepcio de dades.
/// \param    buffer: Buffer de dades.
/// \param    length: Tamany de dades en bytes.
/// \param    irq: Indica si es genera desde una interrupcio.
///
void I2CSlaveDevice::notifyRxCompleted(
    const uint8_t *buffer, 
    unsigned length,
    bool irq) {
    
    if (_notifyEventEnabled) {
        NotifyEventArgs args = {
            .instance = this,
            .id = NotifyID::rxCompleted,
            .irq = irq,
            .RxCompleted {
                .buffer = buffer,
                .length = length
            }
        };
        _notifyEvent->execute(args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Noitifica que falten dades per transmetre.
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer.
/// \param    length: Nombre de bytes en el buffer.
/// \param    irq: Indica si es notifica desde una interrupcio.
///
void I2CSlaveDevice::notifyTxDataRequest(
    uint8_t *buffer, 
    unsigned bufferSize,
    unsigned &length,
    bool irq) {
    
    if (_notifyEventEnabled) {
        NotifyEventArgs args = {
            .instance = this,
            .id = NotifyID::txDataRequest,
            .irq = irq,
            .TxDataRequest {
                .buffer = buffer,
                .bufferSize = bufferSize,
                .length = 0
            }
        };
        _notifyEvent->execute(args);
        length = args.TxDataRequest.length;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de la transmissio.
/// \param    irq: Indica si es notifica desde una interrupcio.
///
void I2CSlaveDevice::notifyTxCompleted(
    bool irq) {
    
    if (_notifyEventEnabled) {
        NotifyEventArgs args = {
            .instance = this,
            .id = NotifyID::txCompleted,
            .irq = irq,
            .TxCompleted {
                .length = 0
            }
        };
        _notifyEvent->execute(args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el rellotge.
/// \param    i2c: Els registres de hardware del dispositiu.
/// \param    clockSource: El rellotge.
///
static void setClockSource(
    I2C_TypeDef *i2c,
    ClockSource clockSource) {

#if defined(EOS_PLATFORM_STM32G0)

    uint32_t pos;
    uint32_t msk;

    switch (reinterpret_cast<uint32_t>(i2c)) {
        #if defined(HTL_I2C1_EXIST)
        case I2C1_BASE:
            pos = RCC_CCIPR_I2C1SEL_Pos;
            msk = RCC_CCIPR_I2C1SEL_Msk;
            break;
        #endif

        #if defined(HTL_I2C2_EXIST) && defined(RCC_CCIPR_ISC2SEL_Pos)
        case I2C2_BASE:
            pos = RCC_CCIPR_I2C2SEL_Pos;
            msk = RCC_CCIPR_I2C2SEL_Msk;
            break;
        #endif

        default:
            return;
    }

    uint32_t tmp = RCC->CCIPR;
    tmp &= ~msk;
    switch (clockSource) {
        case ClockSource::sysclk:
            tmp |= (1 << pos) & msk;
            break;

        case ClockSource::hsi16:
            tmp |= (2 << pos) & msk;
            break;

        default:
            return;
    }
    RCC->CCIPR = tmp;
#else
#error "Unknown platform"
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Configura els parametres de temporitzacio.
/// \param    i2c: Els registres de hardware del dispositiu.
/// \param    prescaler: Divisor del rellotge.
/// \param    scldel:
/// \param    sdadel:
/// \param    sclh:
/// \param    scll:
///
static void setTimming(
    I2C_TypeDef *i2c,
    uint8_t prescaler,
    uint8_t scldel,
    uint8_t sdadel,
    uint8_t sclh,
    uint8_t scll) {

    i2c->TIMINGR =
        ((prescaler << I2C_TIMINGR_PRESC_Pos) & I2C_TIMINGR_PRESC_Msk) |
        ((scldel << I2C_TIMINGR_SCLDEL_Pos) & I2C_TIMINGR_SCLDEL_Msk) |
        ((sdadel << I2C_TIMINGR_SDADEL_Pos) & I2C_TIMINGR_SDADEL_Msk) |
        ((sclh << I2C_TIMINGR_SCLH_Pos) & I2C_TIMINGR_SCLH_Msk) |
        ((scll << I2C_TIMINGR_SCLL_Pos) & I2C_TIMINGR_SCLL_Msk);
}
