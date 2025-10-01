#include "HTL/htl.h"
#include "HTL/htlBits.h"
#include "HTL/STM32/htlI2C.h"

#include <cmath>


using namespace eos;
using namespace htl::bits;
using namespace htl::i2c;


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
		disable();
		disableInterrupts();
		setTimming(prescaler, scldel, sdadel, sclh, scll);
		enable();

		_state = State::ready;

		return Results::success;
	}

	else
		return Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el dispositiu.
///
Result I2CMasterDevice::deinitialize() {

	if (_state == State::ready) {

		disable();
		disableInterrupts();
		deactivate();

		_state = State::reset;

		return Results::success;
	}

	else
		return Results::errorState;
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
/// \param    timeout: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
///
Result I2CMasterDevice::transmit(
	uint16_t addr,
	const uint8_t *buffer,
	unsigned bufferSize,
	unsigned timeout) {

	if (_state == State::ready) {

		_state = State::transmiting;

		auto expireTime = htl::getTick() + timeout;
		bool error = false;

		unsigned bufferCount = 0;

		unsigned blockSize = std::min(bufferSize, (unsigned)255);
		unsigned blockCount = 0;

		startTransmit(addr, bufferCount, bufferSize);

		while ((bufferCount < bufferSize) && !error) {

			// Espera que el registre TXD estigui buit
			//
			if (!waitTxEmpty(expireTime)) {
				error = true;
				continue;
			}

			_i2c->TXDR = *buffer++;

			bufferCount++;
			blockCount++;

			// Si es necesari prepara un altre bloc
			//
			if ((bufferCount < bufferSize) && (blockCount == blockSize)) {

				// Espera que s'hagi completat la transmissio de l'ultim byte
				//
				while (!isTxCompleteReload())
					continue;

				blockSize = std::min(bufferSize - bufferCount, (unsigned)255);
				blockCount = 0;

				startTransmit(addr, bufferCount, bufferSize);
			}
		}

		if (!waitSTOPCondition(expireTime))
			error = true;

		_state = State::ready;

		return error ? Results::error : Results::success;
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return Results::busy;

	else
		return Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades.
/// \param    addr: Adresa del escalu.
/// \param    buffer: Buffer de dades.
/// \param    size: Tamany en bytes del buffer de dades.
/// \param    timeout: Temps maxim d'espera.
///
Result I2CMasterDevice::receive(
	uint16_t addr,
	uint8_t *buffer,
	unsigned bufferSize,
	unsigned timeout) {

	if (_state == State::ready) {

		auto expireTime = htl::getTick() + timeout;
		bool error = false;

		unsigned bufferCount = 0;

		unsigned blockSize = std::min(bufferSize, (unsigned)255);
		unsigned blockCount = 0;

		startReceive(addr, bufferCount, bufferSize);

		while ((bufferCount < bufferSize) && !error) {

			 if (waitRxNotEmpty(expireTime)) {
				 error = true;
				 continue;
			 }

			*buffer++ = _i2c->RXDR;

			bufferCount++;
			blockSize--;

			// si es necesari, prepara un altre bloc
			//
			if ((bufferCount < bufferSize) && (blockCount == blockSize)) {

				blockSize = std::min(bufferSize - bufferCount, (unsigned)255);
				blockCount = 0;
			}
		}

		// Espera l'indicador STOP
		//
		if (!waitSTOPCondition(expireTime))
			error = true;

		return error ? Results::error : Results::success;
	}

	else if (_state == State::receiving || _state == State::transmiting)
		return Results::busy;

	else
		return Results::errorState;
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
		_state = State::transmiting;

		enableTransmitInterrupts();
		startTransmit(addr, _count, _maxCount);

		return Results::success;
	}

	else if (_state == State::receiving || _state == State::transmiting)
		return Results::busy;

	else
		return Results::errorState;
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
		_state = State::receiving;

		enableReceiveInterrupts();
		startReceive(addr, _count, _maxCount);

		return Results::success;
	}

	else if (_state == State::receiving || _state == State::transmiting)
		return Results::busy;

	else
		return Results::errorState;
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

	// Event NACK.
	// Error al transmetre dades al esclau.
	//
	if (isSet(CR1, I2C_CR1_NACKIE) && isSet(ISR, I2C_ISR_NACKF)) {

		// Borra el flag
		//
		_i2c->ICR = I2C_ICR_NACKCF;

		// Flush TX
		//
		if (isSet(ISR, I2C_ISR_TXIS))
			_i2c->TXDR = 0;
		if (isSet(ISR, I2C_ISR_TXE))
        	set(_i2c->ISR, I2C_ISR_TXE);
	}

	// Event TXI.
	// El registre dades es buit, cal transmitre el seguent byte
	//
	else if (isSet(CR1, I2C_CR1_TXIE) && isSet(ISR, I2C_ISR_TXIS) && !isSet(ISR, I2C_ISR_TC)) {

		_i2c->TXDR = _buffer[_count++];
	}

	// Event TC.
	// Transferencia completada. No mes es genera interrupcio si AUTOEND=0
	//
	else if (isSet(CR1, I2C_CR1_TCIE) && isSet(ISR, I2C_ISR_TC)) {

	}

	// Event TCR.
	// Transmissio del bloc de 255 bytes finalitzat, pero
	// en queden mes de pendents de transmetre
	//
	else if (isSet(CR1, I2C_CR1_TCIE) && isSet(ISR, I2C_ISR_TCR)) {

		startTransmit(0, _count, _maxCount);
	}

	// Event STOP.
	// S'ha detectat una condicio stop.
	//
	else if (isSet(CR1, I2C_CR1_STOPIE) && isSet(ISR, I2C_ISR_STOPF)) {

		disableInterrupts();
		_i2c->ICR = I2C_ICR_STOPCF;
		_state = State::ready;

		notifyTxCompleted(_count, true);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions per recepcio.
///
void I2CMasterDevice::interruptServiceReceive() {

	auto CR1 = _i2c->CR1;
	auto ISR = _i2c->ISR;

	// Event RXIE.
	// El buffer de recepcio no es buit
	//
	if (isSet(CR1, I2C_CR1_RXIE) && isSet(ISR, I2C_ISR_RXNE)) {

		_buffer[_count++] = _i2c->RXDR;
	}

	// Event TC.
	// Recepcio complerta
	//
	else if (isSet(CR1, I2C_CR1_TCIE) && isSet(ISR, I2C_ISR_TC)) {

	}

	// Event TCR.
	// Recepcio complerta del bloc, pero queden bytes pendents. Cal
	// tornar a reiniciar
	//
	else if (isSet(CR1, I2C_CR1_TCIE) && isSet(ISR, I2C_ISR_TCR)) {

		startReceive(0, _count, _maxCount);
	}

	// Event STOP
	//
	else if (isSet(CR1, I2C_CR1_STOPIE) && isSet(ISR, I2C_ISR_STOPF)) {

		disableInterrupts();
		_i2c->ICR = I2C_ICR_STOPCF;
		_state = State::ready;

		notifyRxCompleted(_count, true);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la tranmissio generant una condicio START.
/// \param    addr: L'adressa
/// \param    count: Bytes transmesos fins al moment.
/// \param    macCount: Bytes totals a transmetre.
///
void I2CMasterDevice::startTransmit(
	I2CAddr addr,
	unsigned count,
	unsigned maxCount) {

	auto length = maxCount - count;

	auto CR2 = _i2c->CR2;
	clear(CR2, I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND);

	// Si el bloc es menor o igual a 255 bytes, aleshores transmet
	// totes les dades d'una tirada en un sol bloc
	// i genera el STOP automaticament al final
	//
	if (length <= 255) {
		set(CR2, (length << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk);
		set(CR2, I2C_CR2_AUTOEND); // Genera stop automaticament, no genera TC
	}

	// En cas contrari, transmet de 255 bytes,
	// genere TCR al final, per continuar amb el seguent bloc
	//
	else {
		set(CR2, (255 << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk);
		set(CR2, I2C_CR2_RELOAD); // Genera TCR per carregar el seguent bloc
	}

	// Si es tracta del inici de la transmissio, genera una
	// condicio START i transmet l'adressa I2C del esclau.
	//
	if (count == 0) {
		clear(CR2, I2C_CR2_SADD | I2C_CR2_ADD10 | I2C_CR2_RD_WRN);
		set(CR2, (addr << I2C_CR2_SADD_Pos) & I2C_CR2_SADD_Msk);
     	set(CR2, I2C_CR2_START);
	}

	_i2c->CR2 = CR2;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la recepcio generant una condicio START.
/// \param    addr: L'adressa
/// \param    count: Bytes transmesos fins al moment.
/// \param    maxCount: Bytes totals a transmetre.
///
void I2CMasterDevice::startReceive(
	I2CAddr addr,
	unsigned count,
	unsigned maxCount) {

	auto length = maxCount - count;

	auto CR2 = _i2c->CR2;
    clear(CR2, I2C_CR2_NBYTES_Msk | I2C_CR2_RELOAD | I2C_CR2_AUTOEND);
    if (length <= 255) {
        set(CR2, (length << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk);
    	set(CR2, I2C_CR2_AUTOEND);
    }
    else {
        set(CR2, (255 << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk);
        set(CR2, I2C_CR2_RELOAD);
    }

    // Si es tracta del inici de la recepcio, genera una
	// condicio START i transmet l'adressa I2C del esclau.
	//
	if (count == 0) {
		clear(CR2, I2C_CR2_SADD | I2C_CR2_ADD10);
		set(CR2, (addr << I2C_CR2_SADD_Pos) & I2C_CR2_SADD_Msk);
		set(CR2, I2C_CR2_RD_WRN);
     	set(CR2, I2C_CR2_START);
	}
	_i2c->CR2 = CR2;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita les interrupcions per transmissio.
///
void I2CMasterDevice::enableTransmitInterrupts() {

	_i2c->ICR =
		I2C_ICR_NACKCF | // Borra flag NACK
		I2C_ICR_STOPCF;  // Borra flag STOP

	set(_i2c->CR1,
		I2C_CR1_ERRIE |  // Habilita ERR
		I2C_CR1_TXIE |   // Habilita TX
		I2C_CR1_NACKIE | // Habilita NACK
		I2C_CR1_TCIE |   // Habilita TC/TCR
		I2C_CR1_STOPIE); // Habilita STOP
}


/// ----------------------------------------------------------------------
/// \brief    Habilita les interrupcions per recepcio
///
void I2CMasterDevice::enableReceiveInterrupts() {

	_i2c->ICR =
		I2C_ICR_NACKCF | // Borra flag NACK
		I2C_ICR_STOPCF;  // Borra flag STOP

	set(_i2c->CR1,
		I2C_CR1_ERRIE |  // Habilita ERR
		I2C_CR1_RXIE |   // Habilita RX
		I2C_CR1_NACKIE | // Habilita NACK
		I2C_CR1_TCIE |   // Habilita TC/TCR
		I2C_CR1_STOPIE); // Habilita STOP
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita les interrupcions.
///
void I2CMasterDevice::disableInterrupts() {

    clear(_i2c->CR1,
		I2C_CR1_ERRIE |  // Deshabilita ERR
		I2C_CR1_NACKIE | // Deshabilita NACK
		I2C_CR1_TCIE |   // Deshabilita TC/TCR
		I2C_CR1_TXIE |   // Deshabilita TX
		I2C_CR1_RXIE |   // Deshabilita RX
		I2C_CR1_STOPIE); // Deshabilita STOP
}


/// ----------------------------------------------------------------------
/// \brief    Espera fins que el registre de transmissio no estigui
///           buit.
/// \param    expiteTime: Temps limit.
/// \return   True si no es buit, false en cas d'error (TimeOut)
///
bool I2CMasterDevice::waitRxNotEmpty(
    unsigned expireTime) const {

    while (!isRxNotEmpty()) {
        if (hasTickExpired(expireTime))
            return false;
    }

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Espera fins que el registre de transmissio estigui buit.
/// \param    expiteTime: Temps limit.
/// \return   True si tot es correcte, false en cas d'error (TimeOut)
///
bool I2CMasterDevice::waitTxEmpty(
    unsigned expireTime) const {

    while (!isTxEmpty()) {
        if (hasTickExpired(expireTime))
            return false;
    }

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Espera fins que es detecti una condicio STOP.
/// \param    expiteTime: Temps limit.
/// \return   True si tot es correcte, false en cas d'error (TimeOut)
///
bool I2CMasterDevice::waitSTOPCondition(
    unsigned expireTime) const {

    while (!isSTOPCondition()) {
        if (hasTickExpired(expireTime))
            return false;
    }

    return true;
}

/// ----------------------------------------------------------------------
/// \brief    Comprova que el registre de recepcio no estigui buit
/// \return   True si no es buit, false en cas contrari.
///
bool I2CMasterDevice::isRxNotEmpty() const {

	return isSet(_i2c->ISR, I2C_ISR_RXNE);
}

/// ----------------------------------------------------------------------
/// \brief    Comprova que el registre de transmissio estigui buit
/// \return   True si es buit, false en cas contrari.
///
bool I2CMasterDevice::isTxEmpty() const {

	return isSet(_i2c->ISR, I2C_ISR_TXIS);
}

/// ----------------------------------------------------------------------
/// \brief    Comprova si ha finalitzat la transmissio
/// \return   True si ha finalitzat, false en cas contrari.
///
bool I2CMasterDevice::isTxCompleteReload() const {

	return isSet(_i2c->ISR, I2C_ISR_TCR);
}

/// ----------------------------------------------------------------------
/// \brief    Comprova si s'ha detectat una condicio STOP
/// \return   True si s'ha detectet, false en cas contrari.
///
bool I2CMasterDevice::isSTOPCondition() const {

	return isSet(_i2c->ISR, I2C_ISR_STOPF);
}

