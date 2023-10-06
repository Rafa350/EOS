#include "HTL/htl.h"
#include "HTL/STM32/htlSPI.h"
#include "HAL/STM32/halSYS.h"


using namespace htl::spi;


#define SPI_CR1_BR_DIV2         (0 << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV4         (1 << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV8         (2 << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV16        (3 << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV32        (4 << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV64        (5 << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV128       (6 << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV256       (7 << SPI_CR1_BR_Pos)

#define SPI_CR2_DS_LEN8         (7 << SPI_CR2_DS_Pos)
#define SPI_CR2_DS_LEN16        (15 << SPI_CR2_DS_Pos)


static void setClockDivider(SPI_TypeDef * const spi, ClockDivider clkDivider);
static void setMode(SPI_TypeDef * const spi, SPIMode mode);
static void setClkPolarity(SPI_TypeDef * const spi, ClkPolarity polarity);
static void setClkPhase(SPI_TypeDef * const spi, ClkPhase phase);
static void setSize(SPI_TypeDef * const spi, WordSize size);
static void setFirstBit(SPI_TypeDef * const spi, FirstBit firstBit);

static void write8(SPI_TypeDef * const spi, uint8_t data);
static void write16(SPI_TypeDef * const spi, uint16_t data);
static uint8_t read8(SPI_TypeDef * const spi);
static uint16_t read16(SPI_TypeDef * const spi);

static bool isTxEmpty(SPI_TypeDef * const spi);
static bool isRxNotEmpty(SPI_TypeDef * const spi);
static bool isBusy(SPI_TypeDef * const spi);


/// ----------------------------------------------------------------------
/// \brief    Espera que el dispositiu estigui lliure
/// \param    regs: El bloc de registres.
/// \param    startTime: Temps del inici de les operacions
/// \param    timeout: Temps maxim de bloqueig.
///
static void waitBusy(
	SPI_TypeDef *regs,
	unsigned startTime,
	unsigned timeout) {

	while ((regs->SR & SPI_SR_BSY) != 0) {
		if (halSYSCheckTimeout(startTime, timeout)) {
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el fifo de transmissio estigui buit.
/// \param    regs: El bloc de registres.
/// \param    startTime: Temps del inici de les operacions
/// \param    timeout: Temps maxim de bloqueig.
///
#ifdef EOS_PLATFORM_STM32F7
static void waitRxFifoEmpty(
	SPI_TypeDef *regs,
	unsigned startTime,
	unsigned timeout) {

	while ((regs->SR & SPI_SR_FRLVL) != 0) {
		if (halSYSCheckTimeout(startTime, timeout)) {

		}

		uint8_t dummy = *((__IO uint8_t *)&regs->DR);
	}
}
static void waitTxFifoEmpty(
	SPI_TypeDef *regs,
	unsigned startTime,
	unsigned timeout) {

	while ((regs->SR & SPI_SR_FTLVL) != 0) {
		if (halSYSCheckTimeout(startTime, timeout)) {

		}
	}
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Espera que el fifo de recepcio estigui buit.
/// \param    regs: El bloc de registres.
/// \param    startTime: Temps del inici de les operacions
/// \param    timeout: Temps maxim de bloqueig.
///
#ifdef EOS_PLATFORM_STM32F7
#endif


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    spi: Registres hardware del modul SPI.
///
SPIDevice::SPIDevice(
	SPI_TypeDef *spi):

	_spi {spi},
	_state {State::reset} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul SPI.
/// \param    mode: El modus de comunicacio.
/// \param    clkPolarity: Polaritat del senyal CLK
/// \param    clkPhase: Fase del senyal CLK
/// \param    size: El tamany de trama
/// \param    firstBite: El primer bit de la trama.
/// \param    clkDivider: Divisor de frequencia.
/// \return   El resultst de l'operacio.
///
SPIDevice::Result SPIDevice::initialize(
	SPIMode mode,
	ClkPolarity clkPolarity,
	ClkPhase clkPhase,
	WordSize size,
	FirstBit firstBit,
	ClockDivider clkDivider) {

	if (_state == State::reset) {

		activate();
		disable();

		setClockDivider(_spi, clkDivider);
		setMode(_spi, mode);
		setClkPolarity(_spi, clkPolarity);
		setClkPhase(_spi, clkPhase);
		setSize(_spi, size);
		setFirstBit(_spi, firstBit);

		_state = State::ready;

		return Result::ok;
	}
	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul SPI.
/// \return   El resultat de l'operacio.
///
SPIDevice::Result SPIDevice::deinitialize() {

	if (_state == State::ready) {

		disable();
		deactivate();

		_state = State::reset;

		return Result::ok;
	}
	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades.
/// \param    txBuffer: El buffer de transmissio.
/// \param    size: Tamany del buffer.
/// \return   El resultat de l'operacio
///
SPIDevice::Result SPIDevice::transmit(
	const uint8_t *txBuffer,
	uint16_t size) {

	if (_state == State::ready) {

		uint16_t count = 0;

		while (count < size) {
			write8(_spi, txBuffer[count++]);
			while (!isTxEmpty(_spi))
				continue;
		}
		while (isBusy(_spi))
			continue;

		return Result::ok;
	}

	else
		return Result::busy;
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades.
/// \param    txBuffer: El buffer de transmissio.
/// \param    rxBuffer: El buffer de recepcio.
/// \param    size: Tamany del buffer.
/// \return   El resultat de l'operacio.
///
SPIDevice::Result SPIDevice::transmit(
	const uint8_t *txBuffer,
	uint8_t *rxBuffer,
	uint16_t size) {

	if (_state == State::ready) {

		uint16_t count = 0;

		while (count < size) {
			write8(_spi, txBuffer[count]);
			while (!isTxEmpty(_spi))
				continue;
			rxBuffer[count] = read8(_spi);
			count++;
		}
		while (isBusy(_spi))
			continue;

		return Result::ok;
	}

	else
		return Result::busy;
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades.
/// \param    rxBuffer: El buffer de recepcio.
/// \param    size: Tamany del buffer.
/// \return   El resultat de l'operacio
///
SPIDevice::Result SPIDevice::receive(
	uint8_t *rxBuffer,
	uint16_t size) {

	if (_state == State::ready) {

		uint16_t count = 0;

		while (count < size) {
			write8(_spi, 0x00);
			while (!isTxEmpty(_spi))
				continue;
			rxBuffer[count++] = read8(_spi);
		}
		while (isBusy(_spi))
			continue;

		return Result::ok;
	}

	else
		return Result::busy;
}


/*
/// ----------------------------------------------------------------------
/// \brief    Transfereix un bloc de dades.
/// \param    regs: El bloc de registres.
/// \param    data: El bloc de dades.
/// \param    dataLength: Longitut del blñoc de dades.
/// \param    timeout: El temps maxim de bloqueig.
///
void SPIBase_x::send(
	SPI_TypeDef *regs,
	const uint8_t *data,
	unsigned dataLength,
	unsigned timeout) {

	unsigned count = dataLength;
	const uint8_t *p = data;
	unsigned startTime = halSYSGetTick();

	while (count > 0) {

		#if defined(EOS_PLATFORM_STM32G0) || defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F0)
		*((volatile uint8_t*)&regs->DR) = *((uint8_t*)p);
		p += sizeof(uint8_t);
		count -= sizeof(uint8_t);

		#elif defined(EOS_PLATFORM_STM32F7)
		if (count > 1) {
			// Acces com a 16 bits (Packing mode)
			regs->DR = *((uint16_t*)p);
			p += sizeof(uint16_t);
			count -= sizeof(uint16_t);
		}
		else {
			// Access com a 8 bits
			*((volatile uint8_t*)&regs->DR) = *((uint8_t*)p);
			p += sizeof(uint8_t);
			count -= sizeof(uint8_t);
		}
		#else
		#error "Undefined EOS_PLATFORM_XXXX"
		#endif

		while ((regs->SR & SPI_SR_TXE) == 0) {
			if (halSYSCheckTimeout(startTime, timeout)) {

			}
		}
	}

#ifdef EOS_PLATFORM_STM32F7
	waitTxFifoEmpty(regs, startTime, timeout);
#endif
	waitBusy(regs, startTime, timeout);
#ifdef EOS_PLATFORM_STM32F7
	waitRxFifoEmpty(regs, startTime, timeout);
#endif
}

*/


/// -------------------------------------------------------------------------
/// \brief    Asigna el divisor del rellotge.
/// \param    spi: Els registres de hardware del dispositiu SPI.
/// \param    clkDivider: El valor del divisor.
/// \remarks  La frequencia resultant es PCLK/clkDivider
///
static void setClockDivider(
	SPI_TypeDef *spi,
	ClockDivider clkDivider) {

	uint32_t tmp = spi->CR1;
	tmp &= ~SPI_CR1_BR_Msk;
	switch (clkDivider) {
		case ClockDivider::_2:
			tmp |= SPI_CR1_BR_DIV2;
			break;

		case ClockDivider::_4:
			tmp |= SPI_CR1_BR_DIV4;
			break;

		case ClockDivider::_8:
			tmp |= SPI_CR1_BR_DIV8;
			break;

		case ClockDivider::_16:
			tmp |= SPI_CR1_BR_DIV16;
			break;

		case ClockDivider::_32:
			tmp |= SPI_CR1_BR_DIV32;
			break;

		case ClockDivider::_64:
			tmp |= SPI_CR1_BR_DIV64;
			break;

		case ClockDivider::_128:
			tmp |= SPI_CR1_BR_DIV128;
			break;

		case ClockDivider::_256:
			tmp |= SPI_CR1_BR_DIV256;
			break;
	}
	spi->CR1 = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el modus de comunicacio (Polaritat i fase).
/// \param    spi: Els registres de hardware del dispositiu SPI
/// \param    mode: El modus de treball.
///
static void setMode(
	SPI_TypeDef *spi,
	SPIMode mode) {

	if (mode == SPIMode::master)
		spi->CR1 |= SPI_CR1_MSTR | SPI_CR1_SSI | SPI_CR1_SSM;

	// Per defecte Full-duplex
	//
	spi->CR1 &= ~(SPI_CR1_BIDIMODE | SPI_CR1_RXONLY);
};


/// ----------------------------------------------------------------------
/// \brief    Asigna la polaritat del senyal CLK
/// \param    spi: Els registres de hardware del dispositiu SPI.
/// \param    polarity: La polaritat.
///
static void setClkPolarity(
	SPI_TypeDef *spi,
	ClkPolarity polarity) {

	if (polarity == ClkPolarity::high)
		spi->CR1 |= SPI_CR1_CPOL;
	else
		spi->CR1 &= ~SPI_CR1_CPOL;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la fase del senyal CLK
/// \param    regs: Els regiostres de hardware del dispositiu SPI.
/// \param    polarity: La fase.
///
static void setClkPhase(
	SPI_TypeDef *spi,
	ClkPhase phase) {

	if (phase == ClkPhase::edge2)
		spi->CR1 |= SPI_CR1_CPHA;
	else
		spi->CR1 &= ~SPI_CR1_CPHA;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el tamany de la trama.
/// \param    spi: Els registres de hardware del dispositiu SPI..
/// \param    size: El tamany.
///
static void setSize(
	SPI_TypeDef *spi,
	WordSize size) {

	#if defined(EOS_PLATFORM_STM32F4)
	if (size == WordSize::_16)
		spi->CR1 |= SPI_CR1_DFF;
	else
		spi->CR1 &= ~SPI_CR1_DFF;

	#elif defined(EOS_PLATFORM_STM32F7)
	uint32_t tmp = regs->CR2;
	tmp &= ~(SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0);
	switch (size) {
		case WordSize::_8:
			tmp |= SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;
			break;

		case WordSize::_16:
			tmp |= SPI_CR2_DS_3 | SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;
			break;
	}
	regs->CR2 = tmp;

	#elif defined(EOS_PLATFORM_STM32G0)
	uint32_t tmp = spi->CR2;
	tmp &= ~SPI_CR2_DS_Msk;
	switch (size) {
		case WordSize::_8:
			tmp |= SPI_CR2_DS_LEN8;
			break;

		case WordSize::_16:
			tmp |= SPI_CR2_DS_LEN16;
			break;
	}
	spi->CR2 = tmp;
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Indica quin es el primer bit a transmetre en cada trama.
/// \param    spi: Els registres de hardware del dispositiu SPI.
/// \param    firstBit: Quin bit es el primer.
///
static void setFirstBit(
	SPI_TypeDef * const spi,
	FirstBit firstBit) {

	if (firstBit == FirstBit::lsb)
		spi->CR1 |= SPI_CR1_LSBFIRST;
	else
		spi->CR1 &= ~SPI_CR1_LSBFIRST;
}


/// ----------------------------------------------------------------------
/// \brief    Excriu una paraula de 8 bits en el registre de sortida
///           de dades.
/// \param    spi: Els registres de hardware del dispositiu SPI
/// \param    data: Les dades a transmetre.
///
static void write8(
	SPI_TypeDef * const spi,
	uint8_t data) {

	*((volatile uint8_t*)&spi->DR) = data;
}


/// ----------------------------------------------------------------------
/// \brief    Excriu una paraula de 16 bits en el registre de sortida
///           de dades.
/// \param    spi: Els registre de hardware del dispositiu SPI
/// \param    data: Les dades a transmetre.
///
static void write16(
	SPI_TypeDef * const spi,
	uint16_t data) {

	*((volatile uint16_t*)&spi->DR) = data;
}


static uint8_t read8(
	SPI_TypeDef * const spi) {

	return *((volatile uint8_t*)&spi->DR);
}


static uint16_t read16(
	SPI_TypeDef * const spi) {

	return *((volatile uint16_t*)&spi->DR);
}


static bool isTxEmpty(
	SPI_TypeDef * const spi) {

	return (spi->SR & SPI_SR_TXE) != 0;
}


static bool isRxNotEmpty(
	SPI_TypeDef * const spi) {

	return (spi->SR & SPI_SR_RXNE) != 0;
};


static bool isBusy(
	SPI_TypeDef * const spi) {

	return (spi->SR & SPI_SR_BSY) != 0;
}

