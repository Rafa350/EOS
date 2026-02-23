#include "HTL/htl.h"
#include "HTL/htlBits.h"
#include "HTL/STM32/htlSPI.h"
#include "HTL/STM32/htlDMA.h"


using namespace eos;
using namespace htl;
using namespace htl::bits;
using namespace htl::spi;


#define SPI_CR1_BR_DIV2      (0UL << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV4      (1UL << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV8      (2UL << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV16     (3UL << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV32     (4UL << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV64     (5UL << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV128    (6UL << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV256    (7UL << SPI_CR1_BR_Pos)

#if defined(EOS_PLATFORM_STM32G0)
#define SPI_CR2_DS_LEN8      (7UL << SPI_CR2_DS_Pos)
#define SPI_CR2_DS_LEN16     (15UL << SPI_CR2_DS_Pos)
#elif defined(EOS_PLATFORM_STM32F4)
#elif defined(EOS_PLATFORM_STM32F7)
#define SPI_CR2_DS_LEN8      (7UL << SPI_CR2_DS_Pos)
#define SPI_CR2_DS_LEN16     (15UL << SPI_CR2_DS_Pos)
#else
#error "Undefined platform"
#endif


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    spi: Registres hardware del modul SPI.
///
SPIDevice::SPIDevice(
	SPI_TypeDef *spi):

	_spi {spi},
	_state {State::reset} {

	_state = State::reset;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul SPI.
/// \param    mode: El modus de comunicacio.
/// \param    clkPolarity: Polaritat del senyal CLK
/// \param    clkPhase: Fase del senyal CLK
/// \param    size: El tamany de trama
/// \param    firstBite: El primer bit de la trama.
/// \param    clkDivider: Divisor de frequencia.
/// \return   El resultat de l'operacio.
///
Result SPIDevice::initialize(
	Mode mode,
	ClkPolarity clkPolarity,
	ClkPhase clkPhase,
	WordSize size,
	FirstBit firstBit,
	ClockDivider clkDivider) {

	if (_state == State::reset) {

		activate();
		disable();

		setClockDivider(clkDivider);
		setMode(mode);
		setClkPolarity(clkPolarity);
		setClkPhase(clkPhase);
		setWordSize(size);
		setFirstBit(firstBit);

		_state = State::ready;

		return Result::ErrorCodes::ok;
	}
	else
		return Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul SPI.
/// \return   El resultat de l'operacio.
///
#if HTL_SPI_OPTION_DEACTIVATE == 1
Result SPIDevice::deinitialize() {

	if (_state == State::ready) {

		disable();
		deactivate();

		_state = State::reset;

		return Results::success;
	}
	else
		return Results::errorState;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades.
/// \param    txBuffer: El buffer de transmissio.
/// \param    rxBuffer: El buffer de recepcio.
/// \param    bufferSize: El nombre de bytes a transmetre.
/// \param    timeout: Temps maxim d'espera en ms.
/// \return   El resultat de l'operacio.
///
Result SPIDevice::transmit(
	const uint8_t *txBuffer,
	uint8_t *rxBuffer,
	unsigned bufferSize,
	unsigned timeout) {

	if (_state == State::ready) {

		_state = State::transmiting;

		auto expireTime = htl::getTick() + timeout;

#if defined(EOS_PLATFORM_STM32G0)
		bool len8 = (_spi->CR2 & SPI_CR2_DS) == SPI_CR2_DS_LEN8;
#elif defined(EOS_PLATFORM_STM32F4)
		bool len8 = (_spi->CR1 & SPI_CR1_DFF) == 0;
#elif defined(EOS_PLATFORM_STM32F7)
		bool len8 = (_spi->CR2 & SPI_CR2_DS) == SPI_CR2_DS_LEN8;
#else
#error "Unknown platform"
#endif

		// Habilita la comunicacio
		//
		enable();

		// Bucle per transmetre i/o rebre
		//
        bool error = false;
        unsigned count = 0;
		while ((count < bufferSize) && !error) {

			// Espera que el buffer de transmissio estigui buit
			//
            if (!waitTxEmpty(expireTime)) {
                error = true;
                continue;
            }

            // Transmiteix les dades
            //
            if (len8) {
                if (txBuffer == nullptr)
                    write8(0);
                else {
                    uint8_t data = txBuffer[count];
                    write8(data);
                }
            }
            else {
                if (txBuffer == nullptr)
                    write16(0);
                else {
                    uint16_t data = *(const uint16_t*)&txBuffer[count];
                    write16(data);
                }
            }

            // Espera que el buffer de recepcio no estigui buit
            //
            if (!waitRxNotEmpty(expireTime)) {
                error = true;
                continue;
            }

            // Reb les dades
            //
            if (len8) {
                uint8_t data = read8();
                if (rxBuffer != nullptr)
                    rxBuffer[count] = data;
            }
            else {
                uint16_t data = read16();
                if (rxBuffer != nullptr)
                    *(uint16_t*)(&rxBuffer[count]) = data;
            }

            count += len8 ? 1 : 2;
		}

		if (!error) {
#if defined(EOS_PLATFORM_STM32G0) || defined(EOS_PLATFORM_STM32F7)
			// Espera que es buidin els fifos
			//
		    if (!waitTxFifoEmpty(expireTime))
		        error = true;
		    else if (!waitNotBusy(expireTime))
		        error = true;
		    else if (!waitRxFifoEmpty(expireTime))
		        error = true;
#elif defined(EOS_PLATFORM_STM32F4)
		    // Espera que s'hagin transmes totes les trames
		    //
		    if (!waitNotBusy(expireTime))
		        error = true;
#else
#error "Unknown platform"
#endif
		}

		// Deshabilita la comunicacio
		//
		disable();

		_state = State::ready;

		return error ? Result::ErrorCodes::error : Result::ErrorCodes::ok;
	}

	else if (_state == State::transmiting)
		return Result::ErrorCodes::busy;

	else
		return Result::ErrorCodes::errorState;
}


#if HTL_SPI_OPTION_DMA == 1
/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades en modus DMA
/// \param    devTxDMA: DMA per la transmissio
/// \param    txBuffer: El buffer de transmissio.
/// \param    bufferSize: El nombre de bytes a transmetre.
/// \return   El resultat de l'operacio.
///
Result SPIDevice::transmit_DMA(
    htl::dma::DMADevice *devTxDMA,
    const uint8_t *txBuffer,
    unsigned bufferSize) {

	if (_state == State::ready) {

		// Habilita les transferencies per DMA
		//
		set(_spi->CR2, SPI_CR2_TXDMAEN);

		// Habilita la comunicacio
		//
		enable();

		// Inicia la transferencia i espera que finalitzi
		//
		devTxDMA->start(txBuffer, (uint8_t*)&(_spi->DR), bufferSize);
		devTxDMA->waitForFinish(1000);

		// Espera que el SPI acabi de transferir
		//
		while (isSPIBusy())
			continue;

		// Desabilita la comunicacio
		//
		disable();

		// Deshabilita la transfertencia per DMA
		//
		clear(_spi->CR2, SPI_CR2_TXDMAEN);

		return Result::ErrorCodes::ok;
	}
	else
		return Result::ErrorCodes::errorState;
}
#endif // HTL_SPI_OPTION_DMA == 1


/// ----------------------------------------------------------------------
/// \brief    Habilita les comunicacions.
///
void SPIDevice::enable() const {

    set(_spi->CR1, SPI_CR1_SPE);
}


/// ----------------------------------------------------------------------
/// \brief    Desabilita les comunicacions.
/// \remarks  Asegurar-se que les comunicacions han finalitzat.
///
void SPIDevice::disable() const {

#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	clear(_spi->CR1, SPI_CR1_SPE);

#elif defined(EOS_PLATFORM_STM32G0)
    while ((_spi->SR & SPI_SR_FTLVL) != 0)
        continue;

    while ((_spi->SR & SPI_SR_BSY) != 0)
        continue;

    clear(_spi->CR1, SPI_CR1_SPE);

    while ((_spi->SR & SPI_SR_FRLVL) != 0)
        read8();
#else
#error "Unknown platform"
#endif
}


/// -------------------------------------------------------------------------
/// \brief    Asigna el divisor del rellotge.
/// \param    clkDivider: El valor del divisor.
/// \remarks  La frequencia resultant es PCLK/clkDivider
///
void SPIDevice::setClockDivider(
	ClockDivider clkDivider) const {

	auto CR1 = _spi->CR1;
	clear(CR1, SPI_CR1_BR);
	set(CR1, ((uint32_t) clkDivider << SPI_CR1_BR_Pos) & SPI_CR1_BR_Msk);
	_spi->CR1 = CR1;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el modus de comunicacio (Master/Slave).
/// \param    mode: El modus de treball.
///
void SPIDevice::setMode(
	Mode mode) const {

    // Configura el registre CR1
    //
	auto CR1 = _spi->CR1;
	clear(CR1,
		SPI_CR1_CRCEN |      // Deshabilita CRC
		SPI_CR1_BIDIMODE |   // Deshabilita modus bitireccional
		SPI_CR1_RXONLY);     // Desabilita modus lectura
	if (mode == Mode::master)
		set(CR1,
			SPI_CR1_MSTR |   // Habilita modus master
			SPI_CR1_SSI |    // Habilita seleccio d'esclau per software
			SPI_CR1_SSM);    // Habilita control del esclau per software
	_spi->CR1 = CR1;

	// Configura el registre CR2
	//
	auto CR2 = _spi->CR2;
	clear(CR2,
#if defined(EOS_PLATFORM_STM32G0) || defined(EOS_PLATFORM_STM32F7)
	    SPI_CR2_NSSP |       // Deshabilita puls entre tramas
#endif
		SPI_CR2_SSOE);       // Desabilita la sortida SS
	_spi->CR2 = CR2;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la polaritat del senyal CLK
/// \param    polarity: La polaritat.
///
void SPIDevice::setClkPolarity(
	ClkPolarity polarity) const {

	if (polarity == ClkPolarity::high)
		set(_spi->CR1, SPI_CR1_CPOL);
	else
		clear(_spi->CR1, SPI_CR1_CPOL);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la fase del senyal CLK
/// \param    polarity: La fase.
///
void SPIDevice::setClkPhase(
	ClkPhase phase) const {

	if (phase == ClkPhase::edge2)
		set(_spi->CR1, SPI_CR1_CPHA);
	else
		clear(_spi->CR1, SPI_CR1_CPHA);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el tamany de la trama.
/// \param    size: El tamany.
///
void SPIDevice::setWordSize(
	WordSize size) const {

#if defined(EOS_PLATFORM_STM32F4)
	if (size == WordSize::ws16)
		set(_spi->CR1, SPI_CR1_DFF);
	else
		clear(_spi->CR1, SPI_CR1_DFF);

#elif defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
	auto CR2 = _spi->CR2;
	clear(CR2, SPI_CR2_DS | SPI_CR2_FRXTH);
	set(CR2, size == WordSize::ws8 ?
		SPI_CR2_DS_LEN8 | SPI_CR2_FRXTH :
		SPI_CR2_DS_LEN16);
	_spi->CR2 = CR2;

#else
    #error "Unknown platform"
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Indica quin es el primer bit a transmetre en cada trama.
/// \param    firstBit: Quin bit es el primer.
///
void SPIDevice::setFirstBit(
	FirstBit firstBit) const {

	if (firstBit == FirstBit::lsb)
		set(_spi->CR1, SPI_CR1_LSBFIRST);
	else
		clear(_spi->CR1, SPI_CR1_LSBFIRST);
}


/// ----------------------------------------------------------------------
/// \brief    Excriu una paraula de 8 bits en el registre de sortida
///           de dades.
/// \param    data: Les dades a transmetre.
///
void SPIDevice::write8(
	uint8_t data) const {

	*((volatile uint8_t*)&_spi->DR) = data;
}


/// ----------------------------------------------------------------------
/// \brief    Excriu una paraula de 16 bits en el registre de sortida
///           de dades.
/// \param    data: Les dades a transmetre.
///
void SPIDevice::write16(
	uint16_t data) const {

	*((volatile uint16_t*)&_spi->DR) = data;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix una paraula de 8 bits.
/// \return   El valor de la lectura.
///
uint8_t SPIDevice::read8() const {

	return *((volatile uint8_t*)&_spi->DR);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix una paraula de 16 bits.
/// \return   El valor de la lectura.
///
uint16_t SPIDevice::read16() const {

	return *((volatile uint16_t*)&_spi->DR);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el registre de sortida es buit.
/// \return   True si el registre de sortida es buit.
///
bool SPIDevice::isTxEmpty() const {

	return isSet(_spi->SR, SPI_SR_TXE);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el registre d'entrada no es buit.
/// \return   True si el registre d'entrada no es buit.
///
bool SPIDevice::isRxNotEmpty() const {

	return isSet(_spi->SR, SPI_SR_RXNE);
};


/// ----------------------------------------------------------------------
/// \brief    Comprova si encara hi ha una transmissio pendent.
/// \return   True si hi ha una transmissio pendent.
///
bool SPIDevice::isSPIBusy() const {

	return isSet(_spi->SR, SPI_SR_BSY);
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el fifo de recepcio estigui buit.
/// \param    expireTime: Temps limit.
/// \return   True si tot es correcte. False en cas de timeout.
///
#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
bool SPIDevice::waitRxFifoEmpty(
	unsigned expireTime) const {

	while ((_spi->SR & SPI_SR_FRLVL) != 0) {
        if (hasTickExpired(expireTime))
            return false;

        read8();
	}

	return true;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Espera que el fifo de transmissio estigui buit.
/// \param    expireTime: Temps limit
/// \return   True si tot es correcte. False en cas de timeout.
///
#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
bool SPIDevice::waitTxFifoEmpty(
	unsigned expireTime) const {

	while ((_spi->SR & SPI_SR_FTLVL) != 0) {
        if (hasTickExpired(expireTime))
            return false;
	}

	return true;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Espera el final de les operacions.
/// \return   True si tot es correcte. False en cas de timeout.
///
bool SPIDevice::waitNotBusy(
    unsigned expireTime) const {

    while (isSPIBusy()) {
        if (hasTickExpired(expireTime))
            return false;
    }

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Espera fins que el registre de transmissio estigui buit.
/// \param    expiteRime: Temps limit.
/// \return   TRue si tot es correcte, false en cas d'error (TimeOut)
///
bool SPIDevice::waitTxEmpty(
    unsigned expireTime) const {

    while (!isTxEmpty()) {
        if (hasTickExpired(expireTime))
            return false;
    }

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Espera fins que el registre de recepcio no estigui buit.
/// \param    expiteRime: Temps limit.
/// \return   TRue si tot es correcte, false en cas d'error (TimeOut)
///
bool SPIDevice::waitRxNotEmpty(
    unsigned expireTime) const {

    while (!isRxNotEmpty()) {
        if (hasTickExpired(expireTime))
            return false;
    }

    return true;
}
