#include "HTL/htl.h"
#include "HTL/STM32/htlI2C.h"


using namespace htl::i2c;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    i2c: Bloc de registres de hardware del modul I2C.
///
I2CMasterDevice::I2CMasterDevice(
	I2C_TypeDef *i2c):

	_i2c {i2c},
	_state {State::reset} {

}


I2CMasterDevice::Result I2CMasterDevice::initialize(
	uint8_t prescaler,
	uint8_t scldel,
	uint8_t sdadel,
	uint8_t sclh,
	uint8_t scll) {

	if (_state == State::reset) {

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

		_state = State::ready;

		return Result::ok;
	}
	else
		return Result::error;
}


I2CMasterDevice::Result I2CMasterDevice::deinitialize() {

	if (_state == State::ready) {

		_i2c->CR1 &= ~I2C_CR1_PE;
		deactivate();

		_state = State::reset;

		return Result::ok;
	}
	else
		return Result::error;
}


I2CMasterDevice::Result I2CMasterDevice::send(
	uint16_t addr,
	const uint8_t *buffer,
	uint16_t size,
	uint16_t timeout) {

	uint32_t tmp;

	tmp = _i2c->CR2;

	// Configura adressa de 8 bits, escriptura
	//
	tmp &= ~(I2C_CR2_SADD_Msk | I2C_CR2_ADD10_Msk | I2C_CR2_RD_WRN_Msk);

	// Asigna l'adressa del esclau
	//
	tmp |= (addr << I2C_CR2_SADD_Pos) & I2C_CR2_SADD_Msk;

	// Modus AUTOEND
	//
	tmp |= I2C_CR2_AUTOEND;

	// Configura el nombre de bytes a transmetre
	//
	tmp &= ~(I2C_CR2_NBYTES_Msk | I2C_CR2_RELOAD);
	if (size < 255)
		tmp |= (size << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk;
	else {
		tmp |= (255 << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk;
		tmp |= I2C_CR2_RELOAD;
	}

	_i2c->CR2 = tmp;


	// Inicia la comunicacio.
	//
	_i2c->CR1 |= I2C_CR1_PE;    // Habilita el dispositiu.
	_i2c->CR2 |= I2C_CR2_START; // Inicia la sequencia START, ADDR

	uint16_t blockSize = size < 255 ? size : 255;
	while (size > 0) {

		while ((_i2c->ISR & I2C_ISR_TXIS) == 0)
			continue;

		_i2c->TXDR = *buffer++;

		size--;
		blockSize--;

		// Si es necesari prepara un altre bloc
		//
		if ((size > 0) && (blockSize == 0)) {

			while ((_i2c->ISR & I2C_ISR_TCR) == 0)
				continue;

			// TODO: Preparar el seguent bloc

			blockSize = size < 255 ? size : 255;
		}
	}

	while ((_i2c->ISR & I2C_ISR_STOPF) == 0)
		continue;

	// Finalitza la comunicacio
	//
	_i2c->CR1 &= ~I2C_CR1_PE;    // Deshabilita el dispositiu.

	return Result::ok;
}


I2CMasterDevice::Result I2CMasterDevice::receive(
	uint16_t addr,
	uint8_t *buffer,
	uint16_t size,
	uint16_t timeout) {

	return Result::error;
}


void I2CMasterDevice::interruptService() {

}