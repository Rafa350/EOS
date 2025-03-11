#include "HTL/htl.h"
#include "HTL/STM32/htlI2C.h"

#include <cmath>


using namespace eos;
using namespace htl::i2c;


static void setWriteAddress(I2C_TypeDef *i2c, I2CAddr addr);
static void setReadAddress(I2C_TypeDef *i2c, I2CAddr addr);
static void setTimming(I2C_TypeDef *i2c, uint8_t prescaler, uint8_t scldel, uint8_t sdadel, uint8_t sclh, uint8_t scll);
static void start(I2C_TypeDef *i2c);
static void start(I2C_TypeDef *i2c, unsigned count, unsigned maxCount);
static void enable(I2C_TypeDef *i2c);
static void disable(I2C_TypeDef *i2c);
static void enableTransmitInterrupts(I2C_TypeDef *i2c);
static void enableReceiveInterrupts(I2C_TypeDef *i2c);
static void disableInterrupts(I2C_TypeDef *i2c);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    i2c: Bloc de registres de hardware del modul I2C.
///
I2CMasterDevice::I2CMasterDevice(
	I2C_TypeDef *i2c):

	I2CDevice {i2c},
	_state {State::reset} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
/// \param    prescaler: Divisor del rellotge.
/// \param    scldel:
/// \param    sdadel:
/// \param    sclh
/// \param    scll:
///
Result I2CMasterDevice::initialize(
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
		enable(_i2c);

		_state = State::ready;

		return Results::success;
	}
	else
		return Results::error;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el dispositiu.
///
Result I2CMasterDevice::deinitialize() {

	if (_state == State::ready) {

		disable(_i2c);
		disableInterrupts(_i2c);
		deactivate();

		_state = State::reset;

		return Results::success;
	}
	else
		return Results::error;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el event de notificacio.
/// \param    event: L'event.
/// \param    enabled: True per habilitar l'event.
/// \return   El resultat de l'operacio.
///
eos::Result I2CMasterDevice::setNotifyEvent(
	IMasterNotifyEvent &event,
	bool enabled) {

    if ((_state == State::reset) || (_state == State::ready)) {
    	_erNotify.set(event, enabled);
    	return Results::success;
    }
    else
    	return Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica que ha finalitzat la transmissio de dades.
/// \param    length: Nombre de bytes transmissos.
/// \param    irq: True si es notifica desde una interrupcio.
///
void I2CMasterDevice::notifyTxCompleted(
	unsigned length,
	bool irq) {

	if (_erNotify.isEnabled()) {
		NotifyEventArgs args = {
			.irq = irq,
			.rxCompleted {
				.length = length
			}
		};
		_erNotify.raise(NotifyID::txCompleted, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Notifica que ha finalitzat la recepcio de dades.
/// \param    length: Nombre de bytes rebuts.
/// \param    irq: True si es notifica desde una interrupcio.
///
void I2CMasterDevice::notifyRxCompleted(
	unsigned length,
	bool irq) {

	if (_erNotify.isEnabled()) {
		NotifyEventArgs args = {
			.irq = irq,
			.rxCompleted {
				.length = length
			}
		};
		_erNotify.raise(NotifyID::rxCompleted, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteis un bloc de dades en modus polling
/// \param    addr: L'adressa del esclau.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El nombre de bytes en el buffer.
/// \param    timeout: El temps maxim en ms.
///
Result I2CMasterDevice::transmit(
	uint16_t addr,
	const uint8_t *buffer,
	unsigned bufferSize,
	unsigned timeout) {

	uint32_t tmp;

	setWriteAddress(_i2c, addr);

	tmp = _i2c->CR2;

	// Modus AUTOEND
	//
	tmp |= I2C_CR2_AUTOEND;

	// Configura el nombre de bytes a transmetre
	//
	tmp &= ~(I2C_CR2_NBYTES_Msk | I2C_CR2_RELOAD);
	if (bufferSize < 255)
		tmp |= (bufferSize << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk;
	else {
		tmp |= (255 << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk;
		tmp |= I2C_CR2_RELOAD;
	}

	// Inicia la comunicacio
	//
	start(_i2c);

	_i2c->CR2 = tmp;

	unsigned blockSize = std::min(bufferSize, 255u);
	while (bufferSize > 0) {

		while ((_i2c->ISR & I2C_ISR_TXIS) == 0)
			continue;

		_i2c->TXDR = *buffer++;

		bufferSize--;
		blockSize--;

		// Si es necesari prepara un altre bloc
		//
		if ((bufferSize > 0) && (blockSize == 0)) {

			while ((_i2c->ISR & I2C_ISR_TCR) == 0)
				continue;

			// TODO: Preparar el seguent bloc

			blockSize = std::min(bufferSize, 255u);
		}
	}

	while ((_i2c->ISR & I2C_ISR_STOPF) == 0)
		continue;

	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades.
/// \param    addr: Adresa del escalu.
/// \param    buffer: Buffer de dades.
/// \param    size: Tamany en bytes del buffer de dades.
/// \param    timeout: Temps maxim.
///
Result I2CMasterDevice::receive(
	uint16_t addr,
	uint8_t *buffer,
	unsigned bufferSize,
	unsigned timeout) {

    uint32_t tmp;

    tmp = _i2c->CR2;

    setReadAddress(_i2c, addr);

    // Modus AUTOEND
    //
    tmp |= I2C_CR2_AUTOEND;

    // Configura el nombre de bytes a rebre
    //
    tmp &= ~(I2C_CR2_NBYTES_Msk | I2C_CR2_RELOAD);
    if (bufferSize < 255)
        tmp |= (bufferSize << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk;
    else {
        tmp |= (255 << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk;
        tmp |= I2C_CR2_RELOAD;
    }

    _i2c->CR2 = tmp;

    // Inicia la comunicacio.
    //
    start(_i2c);

    unsigned blockSize = std::min(bufferSize, 255u);
    while (bufferSize > 0) {

        while ((_i2c->ISR & I2C_ISR_RXNE) == 0)
            continue;

        *buffer++ = _i2c->RXDR;

        bufferSize--;
        blockSize--;

        // si es necesari, prepara un altre bloc
        //
    }

    // Espera l'indicador STOP
    //
    while ((_i2c->ISR & I2C_ISR_STOPF) == 0)
        continue;

    // Borra l'indicador STOP
    //
    _i2c->ICR |= I2C_ISR_STOPF;

    return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la transmissio de dades en modus interrupcio.
/// \param    addr: Adressa del esclau.
/// \param    buffer: Adressa del buffer de dades.
/// \param    length: Nombre de bytes en el buffer de dades.
/// \return   El resultat de l'operacio.
///
Result I2CMasterDevice::transmit_IRQ(
	uint16_t addr,
	const uint8_t *buffer,
	unsigned length) {

	if (_state == State::ready) {

		_buffer = (uint8_t*) buffer;
		_maxCount = length;
		_count = 0;

		setWriteAddress(_i2c, addr);

		// Configura el modus de transmisio de dades en funcio del nombre
		// de bytes a transmetre.
		//
		uint32_t tmp = _i2c->CR2;
		tmp &= ~(I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND);
		if (length < 255) {

			// Transmet totes les dades d'una tirada en un sol bloc
			// i genera el STOP automaticament al final
			//
			tmp |= (length << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk;
			tmp |= I2C_CR2_AUTOEND; // Genera stop automaticament
		}

		else {

			// Transmet les dades en blocs de 255 bytes.
			//
			tmp |= (255 << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk;
			tmp |= I2C_CR2_RELOAD; // Solicita carregar el seguent bloc
		}
		_i2c->CR2 = tmp;

		// Canvia a l'estat 'transmiting'
		//
		_state = State::transmiting;

		// Inicia la transmissio
		//
		enableTransmitInterrupts(_i2c);
	    start(_i2c);

		return Results::success;
	}

	else
		return Results::busy;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la transmissio de dades en modus interrupcio.
/// \param    addr: Adressa del esclau.
/// \param    buffer: Adressa del buffer de dades.
/// \param    bufferSize: Tamany del buffer en bytes.
/// \return   El resultat de l'operacio.
///
Result I2CMasterDevice::receive_IRQ(
	uint16_t addr,
	uint8_t *buffer,
	unsigned bufferSize) {

	if (_state == State::ready) {

		_buffer = buffer;
		_maxCount = bufferSize;
		_count = 0;

		setReadAddress(_i2c, addr);

		uint32_t tmp;

		// Configura el nombre de bytes a rebre
		//
		tmp = _i2c->CR2;
		tmp &= ~(I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND);
		if (bufferSize < 255) {
			tmp |= (bufferSize << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk;
			tmp |= I2C_CR2_AUTOEND; // Genera STOP automaticament
		}
		else {
			tmp |= (255 << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk;
			tmp |= I2C_CR2_RELOAD;
		}
		_i2c->CR2 = tmp;

		// Canvia a l'estat 'receiving'
		//
		_state = State::receiving;

		// Inicia la recepcio
		//
		enableReceiveInterrupts(_i2c);
	    start(_i2c);

		return Results::success;
	}
	else
		return Results::busy;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
void I2CMasterDevice::interruptService() {

	switch (_state) {
		case State::transmiting:
			interruptServiceTransmit();
			break;

		case State::receiving:
			interruptServiceReceive();
			break;

		default:
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per transmissio.
///
void I2CMasterDevice::interruptServiceTransmit() {

	auto CR1 = _i2c->CR1;
	auto ISR = _i2c->ISR;

	// Event NACK
	//
	if ((CR1 & I2C_CR1_NACKIE) && (ISR & I2C_ISR_NACKF)) {

		// Borra el flag
		//
		_i2c->ICR = I2C_ICR_NACKCF;

		// Flush TX
		//
		if (ISR & I2C_ISR_TXIS)
			_i2c->TXDR = 0;
		if (ISR & I2C_ISR_TXE)
        	_i2c->ISR |= I2C_ISR_TXE;
	}

	// Event TXIS
	//
	else if ((CR1 & I2C_CR1_TXIE) && (ISR & I2C_ISR_TXIS) && !(ISR & I2C_ISR_TC)) {

		if (_count < _maxCount)
			_i2c->TXDR = _buffer[_count++];
	}

	// Event TC
	//
	else if ((CR1 & I2C_CR1_TCIE) && (ISR & I2C_ISR_TC)) {
	}

	// Event TCR
	//
	else if ((CR1 & I2C_CR1_TCIE) && (ISR & I2C_ISR_TCR)) {
	}

	// Event STOP
	//
	else if ((CR1 & I2C_CR1_STOPIE) && (ISR & I2C_ISR_STOPF)) {

		_i2c->ICR = I2C_ICR_STOPCF; // Borra el flag
        //****** si esta actiu el flag NACK, el borra i notifica el error

        // ***** flush tx

		// Canvia a l'estat 'ready'
		//
		disableInterrupts(_i2c);
		_state = State::ready;

		// Notifica el final de la transmissio
		//
		notifyTxCompleted(_maxCount, true);
	}

	// Event ERR: Bus error
	//
	else if ((CR1 & I2C_CR1_ERRIE) && (ISR & I2C_ISR_BERR)) {
		_i2c->ICR = I2C_ICR_BERRCF;
	}

	// Event ERR: Arbitration lost
	//
	else if ((CR1 & I2C_CR1_ERRIE) && (ISR & I2C_ISR_ARLO)) {
		_i2c->ICR = I2C_ICR_ARLOCF;
	}

	// Event ERR: Overrun/underrun
	//
	else if ((CR1 & I2C_CR1_ERRIE) && (ISR & I2C_ISR_OVR)) {
		_i2c->ICR = I2C_ICR_OVRCF;
	}

	// Event ERR: PEC eror
	//
	else if ((CR1 & I2C_CR1_ERRIE) && (ISR & I2C_ISR_PECERR)) {
		_i2c->ICR = I2C_ICR_PECCF;
	}

	// Event ERR: Timeout
	//
	else if ((CR1 & I2C_CR1_ERRIE) && (ISR & I2C_ISR_TIMEOUT)) {
		_i2c->ICR = I2C_ICR_TIMOUTCF;
	}

	/// Event ERR: SMBus alert
	///
	else if ((CR1 & I2C_CR1_ERRIE) && (ISR & I2C_ISR_ALERT)) {
		_i2c->ICR = I2C_ICR_ALERTCF;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per recepcio.
///
void I2CMasterDevice::interruptServiceReceive() {

	auto CR1 = _i2c->CR1;
	auto ISR = _i2c->ISR;

	// El buffer de recepcio no es buit
	//
	if ((CR1 & I2C_CR1_RXIE) & (ISR & I2C_ISR_RXNE)) {

		if (_count < _maxCount)
			_buffer[_count++] = _i2c->RXDR;
	}

	// Recepcio complerta
	//
	else if ((CR1 & I2C_CR1_TCIE) & (ISR & I2C_ISR_TC)) {

	}

	// S'ha detectat STOP
	//
	else if ((CR1 & I2C_CR1_STOPIE) && (I2C_ISR_STOPF)) {

		_i2c->ICR = I2C_ICR_STOPCF; // Borra el flag

		// Canvia a l'estat 'ready'
		//
		disableInterrupts(_i2c);
		_state = State::ready;

		// Notifica el final de la recepcio
		//
		notifyRxCompleted(_count, true);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'adressa per escriptura.
/// \param    i2c: El bloc de registres del dispositiu.
/// \param    addr: L'adressa.
///
static void setWriteAddress(
	I2C_TypeDef *i2c,
	I2CAddr addr) {

	auto tmp = i2c->CR2;

	tmp &= ~(I2C_CR2_SADD | I2C_CR2_ADD10 | I2C_CR2_RD_WRN);
	tmp |= (addr << I2C_CR2_SADD_Pos) & I2C_CR2_SADD_Msk;

	i2c->CR2 = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'adressa per lectura.
/// \param    i2c: El bloc de registres del dispositiu.
/// \param    addr: L'adressa.
///
static void setReadAddress(
	I2C_TypeDef *i2c,
	I2CAddr addr) {

	auto tmp = i2c->CR2;

	tmp &= ~(I2C_CR2_SADD | I2C_CR2_ADD10);
	tmp |= (addr << I2C_CR2_SADD_Pos) & I2C_CR2_SADD_Msk;
	tmp |= I2C_CR2_RD_WRN;

	i2c->CR2 = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna els valors de temporitzacio.
/// \param    i2c: Registres del dispositiu.
/// \param    prescaler: Divisor del rellotge.
/// \param    scldel:
/// \param    sdadel:
/// \param    sclh
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
/// \brief    Inicia la comunicacio generant una condicio START.
/// \param    i2c: Els registres de hardware del dispositiu.
///
static void start(
	I2C_TypeDef *i2c) {

	i2c->CR2 |= I2C_CR2_START;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la comunicacio generant una condicio START.
/// \param    i2c: Els registres de hardware del dispositiu.
/// \param    count: Bytes transmesos fins al moment.
/// \param    macCount: Bytes totals a transmetre.
///
static void start(
	I2C_TypeDef *i2c,
	unsigned count,
	unsigned maxCount) {

	auto CR2 = i2c->CR2;
	auto length = maxCount - count;

	// Configura el modus de transmisio de dades en funcio del nombre
	// de bytes a transmetre.
	//
	CR2 &= ~(I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND);
	if (length < 255) {

		// Transmet totes les dades d'una tirada en un sol bloc
		// i genera el STOP automaticament al final
		//
		CR2 |= (length << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk;
		CR2 |= I2C_CR2_AUTOEND; // Genera stop automaticament
	}

	else {

		// Transmet les dades en blocs de 255 bytes.
		//
		CR2 |= (255 << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk;
		CR2 |= I2C_CR2_RELOAD; // Solicita carregar el seguent bloc
	}
	CR2 |= I2C_CR2_START;

	i2c->CR2 = CR2;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita el dispositiu.
/// \param    i2c: Els registres de hardware del dispositiu.
///
static void enable(
	I2C_TypeDef *i2c) {

	i2c->CR1 |= I2C_CR1_PE;
}


/// ----------------------------------------------------------------------
/// \brief    Desabilita el dispositiu.
/// \param    i2c: Els registres de hardware del dispositiu.
///
static void disable(
	I2C_TypeDef *i2c) {

	i2c->CR1 &= ~I2C_CR1_PE;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita les interrupcions per transmissio.
/// \param    i2c: Registres del dispositiu.
///
static void enableTransmitInterrupts(
	I2C_TypeDef *i2c) {

	i2c->ICR |=
		I2C_ICR_NACKCF | // Borra NACK
		I2C_ICR_STOPCF;  // Borra STOP

	i2c->CR1 |=
		I2C_CR1_ERRIE |  // Habilita ERR
		I2C_CR1_TXIE |   // Habilita TX
		I2C_CR1_NACKIE | // Habilita NACK
		I2C_CR1_TCIE |   // Habilita TC
		I2C_CR1_STOPIE;  // Habilita STOP
}

/// ----------------------------------------------------------------------
/// \brief    Habilita les interrupcions per recepcio
/// \param    i2c: Registres del dispositiu.
///
static void enableReceiveInterrupts(
	I2C_TypeDef *i2c) {

	i2c->ICR |=
		I2C_ICR_STOPCF;  // Borra STOP

	i2c->CR1 |=
		I2C_CR1_ERRIE |  // Habilita ERR
		I2C_CR1_RXIE |   // Habilita RX
		I2C_CR1_TCIE |   // Habilita TC
		I2C_CR1_STOPIE;  // Habilita STOP
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita les interrupcions.
/// \param    i2c: Registres del dispositiu.
///
static void disableInterrupts(
	I2C_TypeDef *i2c) {

    i2c->CR1 &= ~(
		I2C_CR1_ERRIE |  // Deshabilita ERR
		I2C_CR1_NACKIE | // Deshabilita NACK
		I2C_CR1_TCIE |   // Deshabilita TC
		I2C_CR1_TXIE |   // Deshabilita TX
		I2C_CR1_RXIE |   // Deshabilita RX
		I2C_CR1_STOPIE); // Deshabilita STOP
}
