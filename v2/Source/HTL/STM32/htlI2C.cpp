#include "htl/htl.h"
#include "htl/htlI2C.h"


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
	_addressMatchCallback(nullptr),
	_rxDataCallback(nullptr),
	_rxCompletedCallback(nullptr),
	_txDataCallback(nullptr),
	_txCompletedCallback(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul com esclau.
/// \param    addr: Adressa I2C.
///
void I2CSlaveDevice::initialize(
	uint16_t addr,
	uint8_t prescaler,
	uint8_t scldel,
	uint8_t sdadel,
	uint8_t sclh,
	uint8_t scll) {

	if (_state == State::reset) {

		activate();
		disable();

		_i2c->TIMINGR =
			((prescaler << I2C_TIMINGR_PRESC_Pos) & I2C_TIMINGR_PRESC_Msk) |
			((scldel << I2C_TIMINGR_SCLDEL_Pos) & I2C_TIMINGR_SCLDEL_Msk) |
			((sdadel << I2C_TIMINGR_SDADEL_Pos) & I2C_TIMINGR_SDADEL_Msk) |
			((sclh << I2C_TIMINGR_SCLH_Pos) & I2C_TIMINGR_SCLH_Msk) |
			((scll << I2C_TIMINGR_SCLL_Pos) & I2C_TIMINGR_SCLL_Msk);

		_i2c->OAR1 &= ~I2C_OAR1_OA1EN;
		_i2c->OAR1 |= (addr << I2C_OAR1_OA1_Pos) & I2C_OAR1_OA1_Msk;
		_i2c->OAR1 |= I2C_OAR1_OA1EN;

		_i2c->OAR2 &= ~I2C_OAR2_OA2EN;

		_i2c->CR1 &= ~(I2C_CR1_NOSTRETCH | I2C_CR1_SBC);

		_state = State::ready;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul.
///
void I2CSlaveDevice::deinitialize() {

	if (_state == State::ready) {

		disable();
		deactivate();

		_state = State::reset;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Configura el modul en modus d'escolta.
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer de dades.
///
void I2CSlaveDevice::listen(
	uint8_t *buffer,
	uint16_t bufferSize) {

	if (_state == State::ready) {

		_buffer = buffer;
		_bufferSize = bufferSize;
		_state = State::listen;

		enable();

		_i2c->CR1 |= I2C_CR1_ADDRIE | I2C_CR1_ERRIE | I2C_CR1_NACKIE | I2C_CR1_STOPIE;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el modus d'escolta.
///
void I2CSlaveDevice::endListen() {

	if (_state == State::listen) {

		_i2c->CR1 &= ~(I2C_CR1_ADDRIE | I2C_CR1_ERRIE | I2C_CR1_NACKIE | I2C_CR1_STOPIE);

		disable();

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

	// Obte el valor dels registres
	//
	uint32_t cr1 = _i2c->CR1;
	uint32_t isr = _i2c->ISR;
	uint32_t icr = _i2c->ICR;

	// S'ha detectat coincidencia amb l'adressa.
	//
	if ((cr1 & I2C_CR1_ADDRIE) && (isr & I2C_ISR_ADDR)) {

		// Borra el flag i allivera el bus
		//
    	icr |= I2C_ICR_ADDRCF;

    	// Si es una transmissio
    	//
    	if (isr & I2C_ISR_DIR) {

    		// Inicialitza els contadors
    		//
    		_count = 0;
    		_maxCount = 0;

    		// Habilita la interrupcio TX
    		//
    		cr1 |= I2C_CR1_TXIE;

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
    		cr1 |= I2C_CR1_RXIE;

    		_state = State::listenRx;
    	}

    	// Notifica l'adressa
    	//
    	if (_addressMatchCallback != nullptr)
    		_addressMatchCallback->execute(
    			(((isr & I2C_ISR_ADDCODE_Msk) >> I2C_ISR_ADDCODE_Pos) << 1) |
				(((isr & I2C_ISR_DIR_Msk) >> I2C_ISR_DIR_Pos) << 0));

	}

	// Actualitza el valor dels registres.
	//
	_i2c->CR1 = cr1;
	_i2c->ICR = icr;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per l'estat 'listenRx'
///
void I2CSlaveDevice::interruptServiceListenRx() {

	// Obte el valor dels registres
	//
	uint32_t cr1 = _i2c->CR1;
	uint32_t isr = _i2c->ISR;
	uint32_t icr = _i2c->ICR;

	// El registre de recepcio de dades no es buit
	//
	if ((cr1 & I2C_CR1_RXIE) &&	(isr & I2C_ISR_RXNE)) {

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
	    		if (_rxDataCallback != nullptr)
		    		_rxDataCallback->execute(_buffer, _count);

	    		// Contador a zero per tornar a carregar el buffer
	    		//
				_count = 0;
			}
		}
	}

	// Deteccio de la condicio STOP
	//
	if ((cr1 & I2C_CR1_STOPIE) && (isr & I2C_ISR_STOPF)) {

		// Borra el flag
		//
    	icr |= I2C_ICR_STOPCF;

    	// Desabilita les interrupcions
    	//
    	cr1 &= ~I2C_CR1_RXIE;

		// Notifica el final
		//
		if (_rxCompletedCallback != nullptr)
			_rxCompletedCallback->execute(_buffer, _count);

		// Canvia al nou estat
		//
		_state = State::listen;
	}

	// Actualitza el valor dels registres
	//
	_i2c->CR1 = cr1;
	_i2c->ICR = icr;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per l'estat 'listenTx'
///
void I2CSlaveDevice::interruptServiceListenTx() {

	// Obte el valor dels registres
	//
	uint32_t cr1 = _i2c->CR1;
	uint32_t isr = _i2c->ISR;
	uint32_t icr = _i2c->ICR;

	// S'ha detectat un NACK
	//
	if ((cr1 & I2C_CR1_NACKIE) && (isr & I2C_ISR_NACKF)) {

		// Borra el flag
		//
		icr |= I2C_ICR_NACKCF;
	}

	// S'ha detectat la condicio STOP
	//
	if ((cr1 & I2C_CR1_STOPIE) && (isr & I2C_ISR_STOPF)) {

		// Borra el flag
		//
    	icr |= I2C_ICR_STOPCF;

    	// Desabilita les interrupcions
    	//
    	cr1 &= ~(I2C_CR1_TXIE | I2C_CR1_RXIE);

		// Deshabilita les interrupcions.
		//
		cr1 &= ~I2C_CR1_TXIE;

		// Notifica el final
		//
		if (_txCompletedCallback != nullptr)
			_txCompletedCallback->execute();

		// Canvia al nou estat
		//
		_state = State::listen;
	}

	// El registre de transmissio de dades es buit
	//
	if ((cr1 & I2C_CR1_TXIE) && (isr & I2C_ISR_TXE)) {

		// Si el buffer es buit, o si ja s'han transmet tot el contingut del
		// buffer, ho notifica
		//
		if ((_count == 0) || (_count == _maxCount)) {
			_count = 0;
			_maxCount = 0;
			if (_txDataCallback != nullptr)
				_txDataCallback->execute(_buffer, _bufferSize, _maxCount);
		}

		// Si hi han dades en el buffer els transmiteix
		//
		if (_count < _maxCount)
			_i2c->TXDR = _buffer[_count++];
		else {
			_i2c->TXDR = 0;
			//cr1 &= ~I2C_CR1_TXIE;
		}
	}

	// Actualitza el valor dels registres.
	//
	_i2c->CR1 = cr1;
	_i2c->ICR = icr;
}
