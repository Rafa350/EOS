#include "HTL/htl.h"
#include "HTL/STM32/htlI2C.h"


using namespace htl;
using namespace htl::i2c;


static void setTimming(I2C_TypeDef *i2c, uint8_t prescaler, uint8_t scldel,
        uint8_t sdadel, uint8_t sclh, uint8_t scll);
static void setClockSource(I2C_TypeDef *i2c, ClockSource clockSource);
static ClockSource getClockSource(I2C_TypeDef *i2c);
static void enable(I2C_TypeDef *i2c);
static void disable(I2C_TypeDef *i2c);
static void enableListenInterrupts(I2C_TypeDef *i2c);
static void enableTransmitInterrupts(I2C_TypeDef *i2c);
static void enableReceiveInterrupts(I2C_TypeDef *i2c);
static void disableInterrupts(I2C_TypeDef *i2c);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    i2c: Registres hardware del modul I2C.
///
I2CSlaveDevice::I2CSlaveDevice(
	I2C_TypeDef *i2c) :

	I2CDevice {i2c},
	_state {State::reset},
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

		activate();
		disable(_i2c);
		disableInterrupts(_i2c);
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

		disable(_i2c);
		disableInterrupts(_i2c);
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

    if ((_state == State::reset) || (_state == State::ready)) {
        _notifyEvent = &event;
        _notifyEventEnabled = enabled;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Configura el modul en modus d'escolta.
///
Result I2CSlaveDevice::listen_IRQ() {

    // Comprova si l'estat es 'ready'
    //
	if (_state == State::ready) {

        // Canvia l'estat a 'listen'
		//
		enable(_i2c);
		enableListenInterrupts(_i2c);
		_state = State::listen;

		return Result::success();
	}

	else if ((_state == State::listen) || (_state == State::receiving) || (_state == State::transmiting))
	    return Result::busy();

	else
		return Result::error();
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el modus d'escolta.
///
Result I2CSlaveDevice::abortListen() {

	if (_state == State::listen) {

		// Torna a l'estat 'ready'
		//
		disable(_i2c);
		disableInterrupts(_i2c);
		_state = State::ready;

		return Result::success();
	}

	else if ((_state == State::receiving) || (_state == State::transmiting))
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

		case State::receiving:
			interruptServiceReceive();
			break;

		case State::transmiting:
			interruptServiceTransmit();
			break;

		default:
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per l'estat 'listen'
///
void I2CSlaveDevice::interruptServiceListen() {

	auto CR1 = _i2c->CR1;
	auto ISR = _i2c->ISR;

	// S'ha detectat coincidencia amb l'adressa.
	//
	if ((CR1 & I2C_CR1_ADDRIE) && (ISR & I2C_ISR_ADDR)) {

		// Canvia l'estat 'transmiting' o 'receiving'
		//
		disableInterrupts(_i2c);
    	if (ISR & I2C_ISR_DIR) {
    		enableTransmitInterrupts(_i2c);
    		_state = State::transmiting;
    	}
    	else {
    		enableReceiveInterrupts(_i2c);
    		_state = State::receiving;
    	}

        _buffer = nullptr;
        _maxCount = 0;
        _count = 0;

        // Notifica la coincidencia en l'adressa.
        //
        uint16_t addr =
            (((ISR & I2C_ISR_ADDCODE_Msk) >> I2C_ISR_ADDCODE_Pos) << 1) |
			(((ISR & I2C_ISR_DIR_Msk) >> I2C_ISR_DIR_Pos) << 0);
        notifyAddressMatch(addr, true);

        // Borra el flag aqui per stretch-clock
        //
        _i2c->ICR |= I2C_ICR_ADDRCF;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per l'estat 'receiving'
///
void I2CSlaveDevice::interruptServiceReceive() {

	auto CR1 = _i2c->CR1;
	auto ISR = _i2c->ISR;

	// El registre de recepcio de dades no es buit
	//
	if ((CR1 & I2C_CR1_RXIE) && (ISR & I2C_ISR_RXNE)) {

	    // Notifica l'inici de la recepcio i sol·licita les dades
	    // i el seu tamany maxim.
	    //
	    if ((_buffer == nullptr) || (_count == _maxCount)) {
	        notifyRxStart(_buffer, _maxCount, true);
	        _count = 0;
	    }

        // Llegeix el byte i el acumula en el buffer
        //
	    if ((_buffer != nullptr) && (_count < _maxCount))
	        _buffer[_count++] = (uint8_t) _i2c->RXDR;
	}

	// Deteccio de la condicio STOP
	//
	if ((CR1 & I2C_CR1_STOPIE) && (ISR & I2C_ISR_STOPF)) {

		// Borra el flag STOP
		//
		_i2c->ICR |= I2C_ICR_STOPCF;

	    // Notifica el final de la recepcio de dades, indicant
	    // el nombre de bytes rebuts.
	    //
        notifyRxCompleted(_count, true);

        // Torna a activar el modus listen
        //
        disableInterrupts(_i2c);
        enableListenInterrupts(_i2c);
        _state = State::listen;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per l'estat 'transmiting'
///
void I2CSlaveDevice::interruptServiceTransmit() {

	auto CR1 = _i2c->CR1;
	auto ISR = _i2c->ISR;

	// S'ha detectat un NACK
	//
	if ((CR1 & I2C_CR1_NACKIE) && (CR1 & I2C_CR1_NACKIE)) {

		// Borra el flag NACK
		//
		_i2c->ICR |= I2C_ICR_NACKCF;
	}

	// S'ha detectat la condicio STOP
	//
	if ((CR1 & I2C_CR1_STOPIE) && (ISR & I2C_ISR_STOPF)) {

		// Borra el flag STOP
		//
		_i2c->ICR |= I2C_ICR_STOPCF;

		// Notifica el final de la transmissio
		//
    	notifyTxCompleted(_count, true);

    	// Torna a activar el modus listen
    	//
    	disableInterrupts(_i2c);
    	enableListenInterrupts(_i2c);
        _state = State::listen;
    }

	// El registre de transmissio de dades es buit
	//
	if ((CR1 & I2C_CR1_TXIE) && (ISR & I2C_ISR_TXE)) {

	    if ((_buffer == nullptr) || (_count == _maxCount)) {
            notifyTxStart(_buffer, _maxCount, true);
            _count = 0;
		}

		// Si hi han dades en el buffer els transmiteix, si no
		// transmiteix zeros
		//
		if (_count < _maxCount)
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
/// \brief    Notifica l'inici de la recepcio de dades.
/// \param    buffer: El buffer de dades
/// \param    bufferSize: El tamany del buffer en bytes.
/// \param    irq: Indica si es genera desde una interrupcio.
///
void I2CSlaveDevice::notifyRxStart(
    uint8_t * &buffer,
    unsigned &bufferSize,
    bool irq) {

    if (_notifyEventEnabled) {
        NotifyEventArgs args = {
            .instance = this,
            .id = NotifyID::rxStart,
            .irq = irq,
            .RxStart {
                .buffer = nullptr,
                .bufferSize = 0
            }
        };
        _notifyEvent->execute(args);
        buffer = args.RxStart.buffer;
        bufferSize = args.RxStart.bufferSize;
    }
    else {
        buffer = nullptr;
        bufferSize = 0;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Notifica que ha finalitzat la recepcio de dades.
/// \param    length: Nombre de bytes rebuts.
/// \param    irq: Indica si es genera desde una interrupcio.
///
void I2CSlaveDevice::notifyRxCompleted(
    unsigned length,
    bool irq) {

    if (_notifyEventEnabled) {
        NotifyEventArgs args = {
            .instance = this,
            .id = NotifyID::rxCompleted,
            .irq = irq,
            .RxCompleted {
                .length = length
            }
        };
        _notifyEvent->execute(args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Noitifica l'inici de la transmissio de dades.
/// \param    buffer: Buffer de dades.
/// \param    length: Nombre de bytes a transmetre.
/// \param    irq: Indica si es notifica desde una interrupcio.
///
void I2CSlaveDevice::notifyTxStart(
    uint8_t * &buffer,
    unsigned &length,
    bool irq) {

    if (_notifyEventEnabled) {
        NotifyEventArgs args = {
            .instance = this,
            .id = NotifyID::txStart,
            .irq = irq,
            .TxStart {
                .buffer = nullptr,
                .length = 0
            }
        };
        _notifyEvent->execute(args);
        buffer = args.TxStart.buffer;
        length = args.TxStart.length;
    }
    else {
        buffer = nullptr;
        length = 0;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de la transmissio.
/// \param    length: Nombre de bytes transmessos.
/// \param    irq: Indica si es notifica desde una interrupcio.
///
void I2CSlaveDevice::notifyTxCompleted(
    unsigned length,
    bool irq) {

    if (_notifyEventEnabled) {
        NotifyEventArgs args = {
            .instance = this,
            .id = NotifyID::txCompleted,
            .irq = irq,
            .TxCompleted {
                .length = length
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


/// ----------------------------------------------------------------------
/// \brief    Habilita les comunicacions.
/// \param    i2c: Els registres de hardware del dispositiu.
///
static void enable(
	I2C_TypeDef *i2c) {

	i2c->CR1 |= I2C_CR1_PE;
}


/// ----------------------------------------------------------------------
/// \brief    Desabilita les comunicacions.
/// \param    i2c: Els registres de hardware del dispositiu.
///
static void disable(
	I2C_TypeDef *i2c) {

	i2c->CR1 &= ~I2C_CR1_PE;
}



/// ----------------------------------------------------------------------
/// \brief    Habilita les interrupcions per espera
/// \param    i2c: Registres del dispositiu.
///
static void enableListenInterrupts(
	I2C_TypeDef *i2c) {

	i2c->CR1 |=
        I2C_CR1_ADDRIE | // Habilita ADDR
        I2C_CR1_ERRIE;   // Habilita ERR
}


/// ----------------------------------------------------------------------
/// \brief    Habilita les interrupcions per transmissio
/// \param    i2c: Registres del dispositiu.
///
static void enableTransmitInterrupts(
	I2C_TypeDef *i2c) {

	i2c->CR1 |=
		I2C_CR1_STOPIE | // Habilita STOP
		I2C_CR1_TXIE |   // Habilita TX
		I2C_CR1_NACKIE | // Habilita NACK
		I2C_CR1_ERRIE;   // Habilita ERR
}


/// ----------------------------------------------------------------------
/// \brief    Habilita les interrupcions per recepcio
/// \param    i2c: Registres del dispositiu.
///
static void enableReceiveInterrupts(
	I2C_TypeDef *i2c) {

	i2c->CR1 |=
		I2C_CR1_RXIE |   // Habilita RX
		I2C_CR1_STOPIE | // Hanilita STOP
		I2C_CR1_ERRIE;   // Habilita ERR
}


/// ----------------------------------------------------------------------
/// \brief    Desabilita les interrupcions.
/// \param    i2c: Registres del dispositiu.
///
static void disableInterrupts(
	I2C_TypeDef *i2c) {

	i2c->CR1 &= ~(
		I2C_CR1_RXIE |   // Desabilita RX
		I2C_CR1_TXIE |   // Desabilita TX
		I2C_CR1_STOPIE | // Desabilita STOP
		I2C_CR1_TCIE |   // Deshabilita TC
		I2C_CR1_ADDRIE | // Deshabilita ADDR
		I2C_CR1_NACKIE | // Deshabilita NACK
		I2C_CR1_ERRIE);  // Deshabilita ERR
}
