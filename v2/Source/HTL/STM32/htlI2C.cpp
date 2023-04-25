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
	_buffer(nullptr),
	_size(0),
	_count(0),
	_addressMatchCallback(nullptr),
	_rxPartialCallback(nullptr),
	_rxCompletedCallback(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul com esclau.
/// \param    addr: Adressa I2C.
///
void I2CSlaveDevice::initialize(
	uint16_t addr) {

	activate();
	disable();

	_i2c->OAR1 = I2C_OAR1_OA1EN | ((addr << I2C_OAR1_OA1_Pos) & I2C_OAR1_OA1_Msk);
	_i2c->OAR2 = 0;
	_i2c->CR1 &= ~(I2C_CR1_NOSTRETCH | I2C_CR1_SBC);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul.
///
void I2CSlaveDevice::deinitialize() {

	disable();
	deactivate();
}


/// ----------------------------------------------------------------------
/// \brief Configuracio del timing
/// \param prescaler:
/// \param scldel:
/// \param sdadel:
/// \param sclh:
/// \param scll:
///
void I2CSlaveDevice::setTimming(
	uint8_t prescaler,
	uint8_t scldel,
	uint8_t sdadel,
	uint8_t sclh,
	uint8_t scll) {

	_i2c->TIMINGR =
		((prescaler << I2C_TIMINGR_PRESC_Pos) & I2C_TIMINGR_PRESC_Msk) |
		((scldel << I2C_TIMINGR_SCLDEL_Pos) & I2C_TIMINGR_SCLDEL_Msk) |
		((sdadel << I2C_TIMINGR_SDADEL_Pos) & I2C_TIMINGR_SDADEL_Msk) |
		((sclh << I2C_TIMINGR_SCLH_Pos) & I2C_TIMINGR_SCLH_Msk) |
		((scll << I2C_TIMINGR_SCLL_Pos) & I2C_TIMINGR_SCLL_Msk);
}


/// ----------------------------------------------------------------------
/// \brief    Configura el modul en modus espera.
/// \param    buffer: Buffer de dades.
/// \param    size: Tamany del buffer de dades.
///
void I2CSlaveDevice::listen(
	uint8_t *buffer,
	uint16_t size) {

	_buffer = buffer;
	_size = size;

	// Autoritza la interrupcio ADDR
	//
	_i2c->ICR |= I2C_ICR_ADDRCF;  // Borra el flag
	_i2c->CR1 |= I2C_CR1_ADDRIE;  // Habilita la interrupcio

	// Habilita el modul.
	//
	enable();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
void I2CSlaveDevice::interruptService() {

	uint32_t cr1 = _i2c->CR1;
	uint32_t isr = _i2c->ISR;
	uint32_t icr = _i2c->ICR;

	// Address match
	//
	if ((cr1 & I2C_CR1_ADDRIE) && (isr & I2C_ISR_ADDR)) {

    	cr1 &= ~I2C_CR1_ADDRIE;
    	if (isr & I2C_ISR_DIR)
    		cr1 |= I2C_CR1_TXIE | I2C_CR1_STOPIE;
    	else
    		cr1 |= I2C_CR1_RXIE | I2C_CR1_STOPIE | I2C_CR1_NACKIE;

    	icr |= I2C_ICR_ADDRCF;

    	_count = 0;

    	// Notifica l'adressa i la direccio de la transferencia
    	//
    	if (_addressMatchCallback != nullptr)
    		_addressMatchCallback->execute((isr & I2C_ISR_ADDCODE_Msk) >> I2C_ISR_ADDCODE_Pos);
	}

	// RXD not empty
	//
	if ((cr1 & I2C_CR1_RXIE) &&	(isr & I2C_ISR_RXNE)) {

		// Lectura necesaria per borrar el flag
		//
		uint8_t data = _i2c->RXDR;

		if (_count < _size) {
			_buffer[_count++] = data;

			// Si el buffer es ple, notifica i inicialitza el buffer
			//
			if (_count == _size) {
	    		if (_rxPartialCallback != nullptr)
		    		_rxPartialCallback->execute(_buffer, _count);

	    		// Contador a zero per tornar a carregar el buffer
	    		//
				_count = 0;
			}
		}
	}

	// TXD empty
	//
	if ((cr1 & I2C_CR1_TXIE) && (isr & I2C_ISR_TXE)) {

		if (_count < _size)
			_i2c->TXDR = _buffer[_count++];

		//if (_function != nullptr)
    	//	_function(I2CInterruptNotify::txEmpty, _isrParam);
	}

	// NACK received
	//
	if ((cr1 & I2C_CR1_NACKIE) && (isr & I2C_ISR_NACKF)) {

    	//if (_function != nullptr)
    	//	_function(I2CInterruptNotify::nack, _isrParam);
	}

	// STOP condition
	//
	if ((cr1 & I2C_CR1_STOPIE) && (isr & I2C_ISR_STOPF)) {

    	cr1 &= ~(I2C_CR1_RXIE | I2C_CR1_TXIE | I2C_CR1_STOPIE | I2C_CR1_NACKIE);
    	cr1 |= I2C_CR1_ADDRIE;

    	icr |= I2C_ICR_STOPCF;

		if (_rxCompletedCallback != nullptr)
   			_rxCompletedCallback->execute(_buffer, _count);

	}

	_i2c->CR1 = cr1;
	_i2c->ICR = icr;
}
