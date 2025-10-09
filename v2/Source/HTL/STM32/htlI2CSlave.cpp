#include "eosAssert.h"
#include "HTL/htl.h"
#include "HTL/htlBits.h"
#include "HTL/STM32/htlI2C.h"


using namespace eos;
using namespace htl::bits;
using namespace htl::i2c;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    i2c: Registres hardware del modul I2C.
///
I2CSlaveDevice::I2CSlaveDevice(
	I2C_TypeDef *i2c) :

	I2CDevice {i2c},
	_state {State::reset},
	_restart {false} {

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
		disable();
#if HTL_I2C_OPTION_IRQ == 1
		disableInterrupts();
#endif
		setTimming(prescaler, scldel, sdadel, sclh, scll);

		// Configura l'adressa I2C
		//
		modify(_i2c->OAR1,
			I2C_OAR1_OA1_Msk | I2C_OAR1_OA1EN,
			((addr << I2C_OAR1_OA1_Pos) & I2C_OAR1_OA1_Msk) | I2C_OAR1_OA1EN);

		clear(_i2c->OAR2, I2C_OAR2_OA2EN);

		// Configura els parametres de comunicacio i protocol
		//
		clear(_i2c->CR1, I2C_CR1_NOSTRETCH | I2C_CR1_SBC);

		_state = State::ready;

		return Results::success;
	}

	else
		return Results::error;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul.
///
#if HTL_I2C_OPTION_DEACTIVATE == 1
Result I2CSlaveDevice::deinitialize() {

	if (_state == State::ready) {

		disable();
#if HTL_I2C_OPTION_IRQ == 1
		disableInterrupts();
#endif
		deactivate();
		_state = State::reset;

		return Results::success;
	}

	else
		return Results::errorState;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Asigna el event de notificacio.
/// \param    event: El event.
/// \param    enabled: Indica si l'habilita.
/// \return   El resultat de l'operacio.
///
Result I2CSlaveDevice::setNotifyEvent(
    ISlaveNotifyEvent &event,
    bool enabled) {

    if ((_state == State::reset) || (_state == State::ready)) {
    	_erNotify.set(event, enabled);
    	return Results::success;
    }
    else
    	return Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Configura el modul en modus d'escolta amb interrupcions.
/// \param    restart: Reinicia l'escolta al finalitzar la transmissio.
///
#if HTL_I2C_OPTION_IRQ == 1
Result I2CSlaveDevice::listen_IRQ(
	bool restart) {

    // Comprova si l'estat es 'ready'
    //
	if (_state == State::ready) {

        // Canvia l'estat a 'listen'
		//
		enable();
		enableListenInterrupts();
		_restart = restart;
		_state = State::listen;

		return Results::success;
	}

	else if ((_state == State::listen) || (_state == State::receiving) || (_state == State::transmiting))
	    return Results::busy;

	else
		return Results::errorState;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Aborta les operacions de comunicacio.
/// \return   El resultat de l'operacio.
///
Result I2CSlaveDevice::abort() {

	if ((_state == State::listen) ||
		(_state == State::receiving) ||
		(_state == State::transmiting)) {

		// Torna a l'estat 'ready'
		//
		disable();
#if HTL_I2C_OPTION_IRQ == 1
		disableInterrupts();
#endif
		_state = State::ready;

		return Results::success;
	}

	else
        return Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
#if HTL_I2C_OPTION_IRQ == 1
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
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per l'estat 'listen'
///
#if HTL_I2C_OPTION_IRQ == 1
void I2CSlaveDevice::interruptServiceListen() {

	auto CR1 = _i2c->CR1;
	auto ISR = _i2c->ISR;

	// S'ha detectat coincidencia amb l'adressa.
	//
	if (isSet(CR1, I2C_CR1_ADDRIE) && isSet(ISR, I2C_ISR_ADDR)) {

		// Desabilita les interrupcions
		//
		disableInterrupts();

        // Notifica la coincidencia en l'adressa.
        //
        uint16_t addr =
            (((ISR & I2C_ISR_ADDCODE_Msk) >> I2C_ISR_ADDCODE_Pos) << 1) |
			(((ISR & I2C_ISR_DIR_Msk) >> I2C_ISR_DIR_Pos) << 0);
        notifyAddressMatch(addr, true);

        // Si es modus lectura, prepara la transmissio
		//
		if (isSet(ISR, I2C_ISR_DIR)) {

    		// Notifica l'inici de la transmissio de primer bloc. Obte
			// el punter al buffer de dades i el nombre de bytes
			// a transmetre.
    		//
			_dataCount = 0;
			_buffer = nullptr;
			notifyTxStart(_buffer, _dataCount, true);

			// Si NOSTRTECH == 0, fa un flush, en cas contrari
			// transmet el primer byte
			//
			set(_i2c->ISR, I2C_ISR_TXE);

			enableTransmitInterrupts();
			_state = State::transmiting;
    	}

		// En cas contrari, es modus escriptura, prepara la recepcio
		//
    	else {

    		// Notifica l'inici de la recepcio del primer bloc i obte
    		// el buffer de dades, i el nombre de bytes per rebre.
    		//
			_dataCount = 0;
			_buffer = nullptr;
	        notifyRxStart(_buffer, _dataCount, true);

        	enableReceiveInterrupts();
        	_state = State::receiving;
    	}

		_xferCount = 0;

        // Borra el flag aqui per stretch-clock
        //
        _i2c->ICR = I2C_ICR_ADDRCF;
	}
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per l'estat 'receiving'
///
#if HTL_I2C_OPTION_IRQ == 1
void I2CSlaveDevice::interruptServiceReceive() {

	auto CR1 = _i2c->CR1;
	auto ISR = _i2c->ISR;

	// El registre de recepcio de dades no es buit
	//
	if (isSet(CR1, I2C_CR1_RXIE) && isSet(ISR, I2C_ISR_RXNE)) {

		// Llegeix aqui per borrar el flag RXNE
		//
		auto d = (uint8_t) _i2c->RXDR;

	    if (_dataCount > 0) {
	        *_buffer++ = d;
	        _dataCount--;
	        _xferCount++;
	    }
	}

	// Deteccio de la condicio STOP
	//
	if (isSet(CR1, I2C_CR1_STOPIE) && isSet(ISR, I2C_ISR_STOPF)) {

		// Borra el flag STOP
		//
		_i2c->ICR = I2C_ICR_STOPCF;

        // Notifica el final de la recepcio de dades, indicant
	    // el nombre de bytes rebuts.
	    //
        notifyRxCompleted(_xferCount, true);

        // Torna a activar el modus listen si s'escau.
        //
        disableInterrupts();
        if (_restart) {
        	enableListenInterrupts();
        	_state = State::listen;
        }
        else {
    		disable();
        	_state = State::ready;
        }
	}
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per l'estat 'transmiting'
///
#if HTL_I2C_OPTION_IRQ == 1
void I2CSlaveDevice::interruptServiceTransmit() {

	auto CR1 = _i2c->CR1;
	auto ISR = _i2c->ISR;

	// S'ha detectat un NACK. Despres el MASTER generara una
	// condicio STOP.
	//
	if (isSet(CR1, I2C_CR1_NACKIE) && isSet(ISR, I2C_ISR_NACKF)) {

		// Borra el flag NACK
		//
		_i2c->ICR = I2C_ICR_NACKCF;
	}

	// S'ha detectat la condicio STOP
	//
	if (isSet(CR1, I2C_CR1_STOPIE) && isSet(ISR, I2C_ISR_STOPF)) {

		// Borra el flag STOP
		//
		_i2c->ICR = I2C_ICR_STOPCF;

        // Notifica el final de la transmissio
		//
    	notifyTxCompleted(_xferCount, true);

    	// Torna a activar el modus listen si s'escau.
    	//
    	disableInterrupts();
    	if (_restart) {
    		enableListenInterrupts();
    		_state = State::listen;
    	}
    	else {
    		disable();
    		_state = State::ready;
    	}
    }

	// El registre de transmissio de dades es buit
	//
	if (isSet(CR1, I2C_CR1_TXIE) && isSet(ISR, I2C_ISR_TXIS)) {

		if (_dataCount > 0) {
			_i2c->TXDR = *_buffer++;
			_dataCount--;
			_xferCount++;
		}

		// No hi ha res per enviar, retorna 0xFF
		//
		else
			_i2c->TXDR = 0xFF;
	}
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Notifica la coincidencia amb l'adressa del esclau.
/// \param    addr: L'adressa.
/// \param    irq: Indica si es notifica desde una interrupcio.
///
void I2CSlaveDevice::notifyAddressMatch(
    uint16_t addr,
    bool irq) {

	NotifyEventArgs args = {
		.id = NotifyID::addressMatch,
		.irq = irq,
		.addressMatch {
			.addr = addr
		}
	};
	_erNotify.raise(this, &args);
}


/// ----------------------------------------------------------------------
/// \brief    Notifica l'inici de la recepcio de dades.
/// \param    buffer: El buffer de dades
/// \param    bufferSize: El tamany del buffer de dades en bytes.
/// \param    irq: Indica si esnotifica desde una interrupcio.
///
void I2CSlaveDevice::notifyRxStart(
    uint8_t * &buffer,
    unsigned &bufferSize,
    bool irq) {

	NotifyEventArgs args = {
		.id = NotifyID::rxStart,
		.irq = irq,
		.rxStart {
			.buffer = nullptr,
			.bufferSize = 0
		}
	};
	_erNotify.raise(this, &args);
	buffer = args.rxStart.buffer;
	bufferSize = args.rxStart.bufferSize;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica que ha finalitzat la recepcio de dades.
/// \param    length: Nombre de bytes rebuts.
/// \param    irq: Indica si es notifica desde una interrupcio.
///
void I2CSlaveDevice::notifyRxCompleted(
    unsigned length,
    bool irq) {

	NotifyEventArgs args = {
		.id = NotifyID::rxCompleted,
		.irq = irq,
		.rxCompleted {
			.length = length
		}
	};
	_erNotify.raise(this, &args);
}


/// ----------------------------------------------------------------------
/// \brief    Noitifica l'inici de la transmissio d'un bloc de dades.
/// \param    buffer: Buffer de dades.
/// \param    length: Nombre de bytes a transmetre.
/// \param    irq: Indica si es notifica desde una interrupcio.
///
void I2CSlaveDevice::notifyTxStart(
    uint8_t * &buffer,
    unsigned &length,
    bool irq) {

	NotifyEventArgs args = {
		.id = NotifyID::txStart,
		.irq = irq,
		.txStart {
			.buffer = nullptr,
			.length = 0
		}
	};
	_erNotify.raise(this, &args);
	buffer = args.txStart.buffer;
	length = args.txStart.length;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de la transmissio.
/// \param    length: Nombre de bytes transmessos.
/// \param    irq: Indica si es notifica desde una interrupcio.
///
void I2CSlaveDevice::notifyTxCompleted(
    unsigned length,
    bool irq) {

	NotifyEventArgs args = {
		.id = NotifyID::txCompleted,
		.irq = irq,
		.txCompleted {
			.length = length
		}
	};
	_erNotify.raise(this, &args);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita les interrupcions per espera
///
#if HTL_I2C_OPTION_IRQ == 1
void I2CSlaveDevice::enableListenInterrupts() {

	set(_i2c->CR1,
        I2C_CR1_ADDRIE |     // Habilita ADDR
        I2C_CR1_ERRIE);      // Habilita ERR
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Habilita les interrupcions per transmissio
///
#if HTL_I2C_OPTION_IRQ == 1
void I2CSlaveDevice::enableTransmitInterrupts() {

	set(_i2c->CR1,
		I2C_CR1_TXIE |       // Habilita TX
		I2C_CR1_STOPIE |     // Habilita STOP
		I2C_CR1_NACKIE |     // Habilita NACK
		I2C_CR1_ERRIE);      // Habilita ERR
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Habilita les interrupcions per recepcio
///
#if HTL_I2C_OPTION_IRQ == 1
void I2CSlaveDevice::enableReceiveInterrupts() {

	set(_i2c->CR1,
		I2C_CR1_RXIE |       // Habilita RX
		I2C_CR1_STOPIE |     // Habilita STOP
		I2C_CR1_ERRIE);      // Habilita ERR
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Desabilita les interrupcions.
///
#if HTL_I2C_OPTION_IRQ == 1
void I2CSlaveDevice::disableInterrupts() {

	clear(_i2c->CR1,
		I2C_CR1_RXIE |       // Desabilita RX
		I2C_CR1_TXIE |       // Desabilita TX
		I2C_CR1_ADDRIE |     // Deshabilita ADDR
		I2C_CR1_STOPIE |     // Desabilita STOP
		I2C_CR1_TCIE |       // Deshabilita TC
		I2C_CR1_NACKIE |     // Deshabilita NACK
		I2C_CR1_ERRIE);      // Deshabilita ERR
}
#endif
