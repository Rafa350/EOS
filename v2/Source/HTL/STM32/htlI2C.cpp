#include "HTL/htl.h"
#include "HTL/htlI2C.h"


using namespace htl::i2c;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    i2c: Registres hardware del modul I2C.
///
I2CSlaveDevice::I2CSlaveDevice(
	I2C_TypeDef *i2c) :

	_i2c(i2c),
	_state(State::reset),
	_buffer(nullptr),
	_bufferSize(0),
	_count(0),
	_addressMatchEvent(nullptr),
	_rxDataEvent(nullptr),
	_rxCompletedEvent(nullptr),
	_txDataEvent(nullptr),
	_txCompletedEvent(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul com esclau.
/// \param    addr: Adressa I2C.
///
I2CSlaveDevice::Result I2CSlaveDevice::initialize(
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

		// Deshabilita les comunicacions
		//
		_i2c->CR1 &= ~I2C_CR1_PE;

		// Configura els parametres de timing
		//
		_i2c->TIMINGR =
			((prescaler << I2C_TIMINGR_PRESC_Pos) & I2C_TIMINGR_PRESC_Msk) |
			((scldel << I2C_TIMINGR_SCLDEL_Pos) & I2C_TIMINGR_SCLDEL_Msk) |
			((sdadel << I2C_TIMINGR_SDADEL_Pos) & I2C_TIMINGR_SDADEL_Msk) |
			((sclh << I2C_TIMINGR_SCLH_Pos) & I2C_TIMINGR_SCLH_Msk) |
			((scll << I2C_TIMINGR_SCLL_Pos) & I2C_TIMINGR_SCLL_Msk);

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

		return Result::ok;
	}

	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul.
///
I2CSlaveDevice::Result I2CSlaveDevice::deinitialize() {

	if (_state == State::ready) {

		// Deshabilita les comunicacions.
		//
		_i2c->CR1 &= ~I2C_CR1_PE;

		// Desactiva el dispositiu.
		//
		deactivate();

		_state = State::reset;

		return Result::ok;
	}

	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Configura el modul en modus d'escolta.
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer de dades.
///
I2CSlaveDevice::Result I2CSlaveDevice::listen(
	uint8_t *buffer,
	uint16_t bufferSize) {

	if (_state == State::ready) {

		_buffer = buffer;
		_bufferSize = bufferSize;
		_state = State::listen;

		// Habilita les comunicacions i les interrupcions
		//
		_i2c->CR1 |= I2C_CR1_PE | I2C_CR1_ADDRIE | I2C_CR1_ERRIE | I2C_CR1_NACKIE | I2C_CR1_STOPIE;

		return Result::ok;
	}

	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el modus d'escolta.
///
void I2CSlaveDevice::endListen() {

	if (_state == State::listen) {

		// Deshabilita els comunicacions i les interrupcions
		//
		_i2c->CR1 &= ~(I2C_CR1_PE | I2C_CR1_ADDRIE | I2C_CR1_ERRIE | I2C_CR1_NACKIE | I2C_CR1_STOPIE);

		_buffer = nullptr;
		_bufferSize = 0;
		_state = State::ready;
	}
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
	if ((_i2c->CR1 & I2C_CR1_ADDRIE) && (_i2c->ISR & I2C_ISR_ADDR)) {

		// Borra el flag i allivera el bus
		//
		_i2c->ICR |= I2C_ICR_ADDRCF;

    	// Si es una transmissio
    	//
    	if (_i2c->ISR & I2C_ISR_DIR) {

    		// Inicialitza els contadors
    		//
    		_count = 0;
    		_maxCount = 0;

    		// Habilita la interrupcio TX
    		//
    		_i2c->CR1 |= I2C_CR1_TXIE;

    		_state = State::listenTx;
    	}

    	// En cas contrari, es una recepcio
    	//
    	else {

    		// Inicialitza els contadors
    		//
    		_count = 0;
    		_maxCount = _bufferSize;

    		// Habilita la interrupcio RX
    		//
    		_i2c->CR1 |= I2C_CR1_RXIE;

    		_state = State::listenRx;
    	}

    	// Notifica l'adressa
    	//
    	if (_addressMatchEvent != nullptr)
    		_addressMatchEvent->execute(
    			(((_i2c->ISR & I2C_ISR_ADDCODE_Msk) >> I2C_ISR_ADDCODE_Pos) << 1) |
				(((_i2c->ISR & I2C_ISR_DIR_Msk) >> I2C_ISR_DIR_Pos) << 0));

	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per l'estat 'listenRx'
///
void I2CSlaveDevice::interruptServiceListenRx() {

	// El registre de recepcio de dades no es buit
	//
	if ((_i2c->CR1 & I2C_CR1_RXIE) && (_i2c->ISR & I2C_ISR_RXNE)) {

		// Lectura necesaria per borrar el flag i alliverar el bus
		//
		uint8_t data = _i2c->RXDR;

		// Acumula el byte en el buffer
		//
		if (_count < _maxCount) {
			_buffer[_count++] = data;

			// Si el buffer es ple, notifica i inicialitza el buffer
			//
			if (_count == _maxCount) {
	    		if (_rxDataEvent != nullptr)
		    		_rxDataEvent->execute(_buffer, _count);

	    		// Contador a zero per tornar a carregar el buffer
	    		//
				_count = 0;
			}
		}
	}

	// Deteccio de la condicio STOP
	//
	if ((_i2c->CR1 & I2C_CR1_STOPIE) && (_i2c->ISR & I2C_ISR_STOPF)) {

		// Borra el flag
		//
		_i2c->ICR |= I2C_ICR_STOPCF;

    	// Desabilita les interrupcions
    	//
		_i2c->CR1 &= ~I2C_CR1_RXIE;

		// Notifica el final
		//
		if (_rxCompletedEvent != nullptr)
			_rxCompletedEvent->execute(_buffer, _count);

		// Canvia al nou estat
		//
		_state = State::listen;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per l'estat 'listenTx'
///
void I2CSlaveDevice::interruptServiceListenTx() {

	// S'ha detectat un NACK
	//
	if ((_i2c->CR1 & I2C_CR1_NACKIE) && (_i2c->ISR & I2C_ISR_NACKF)) {

		// Borra el flag
		//
		_i2c->ICR |= I2C_ICR_NACKCF;
	}

	// S'ha detectat la condicio STOP
	//
	if ((_i2c->CR1 & I2C_CR1_STOPIE) && (_i2c->ISR & I2C_ISR_STOPF)) {

		// Borra el flag
		//
    	_i2c->ICR |= I2C_ICR_STOPCF;

    	// Desabilita les interrupcions
    	//
    	_i2c->CR1 &= ~(I2C_CR1_TXIE | I2C_CR1_RXIE);

		// Notifica el final
		//
		if (_txCompletedEvent != nullptr)
			_txCompletedEvent->execute();

		// Canvia al nou estat
		//
		_state = State::listen;
	}

	// El registre de transmissio de dades es buit
	//
	if ((_i2c->CR1 & I2C_CR1_TXIE) && (_i2c->ISR & I2C_ISR_TXE)) {

		// Si el buffer es buit, o si ja s'han transmet tot el contingut del
		// buffer, ho notifica
		//
		if ((_count == 0) || (_count == _maxCount)) {
			_count = 0;
			_maxCount = 0;
			if (_txDataEvent != nullptr)
				_txDataEvent->execute(_buffer, _bufferSize, _maxCount);
		}

		// Si hi han dades en el buffer els transmiteix
		//
		if (_count < _maxCount)
			_i2c->TXDR = _buffer[_count++];
		else {
			_i2c->TXDR = 0;
			//_i2c->CR1 &= ~I2C_CR1_TXIE;
		}
	}
}
