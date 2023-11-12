#include "HTL/htl.h"
#include "HTL/STM32/htlSPI.h"


using namespace htl;
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


static void spiSetClockDivider(SPI_TypeDef * const spi, ClockDivider clkDivider);
static void spiSetMode(SPI_TypeDef * const spi, SPIMode mode);
static void spiSetClkPolarity(SPI_TypeDef * const spi, ClkPolarity polarity);
static void spiSetClkPhase(SPI_TypeDef * const spi, ClkPhase phase);
static void spiSetWordSize(SPI_TypeDef * const spi, WordSize size);
static void spiSetFirstBit(SPI_TypeDef * const spi, FirstBit firstBit);

static void spiWrite8(SPI_TypeDef * const spi, uint8_t data);
static void spiWrite16(SPI_TypeDef * const spi, uint16_t data);
static uint8_t spiRead8(SPI_TypeDef * const spi);
static uint16_t spiRead16(SPI_TypeDef * const spi);

static bool spiTxEmpty(SPI_TypeDef * const spi);
static bool spiRxNotEmpty(SPI_TypeDef * const spi);
static bool spiBusy(SPI_TypeDef * const spi);


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
Result SPIDevice::initialize(
	SPIMode mode,
	ClkPolarity clkPolarity,
	ClkPhase clkPhase,
	WordSize size,
	FirstBit firstBit,
	ClockDivider clkDivider) {

	if (_state == State::reset) {

		activate();
		disable();

		spiSetClockDivider(_spi, clkDivider);
		spiSetMode(_spi, mode);
		spiSetClkPolarity(_spi, clkPolarity);
		spiSetClkPhase(_spi, clkPhase);
		spiSetWordSize(_spi, size);
		spiSetFirstBit(_spi, firstBit);

		_state = State::ready;

		return Result::success();
	}
	else
		return Result::error();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul SPI.
/// \return   El resultat de l'operacio.
///
Result SPIDevice::deinitialize() {

	if (_state == State::ready) {

		disable();
		deactivate();

		_state = State::reset;

		return Result::success();
	}
	else
		return Result::error();
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades.
/// \param    txBuffer: El buffer de transmissio.
/// \param    rxBuffer: El buffer de recepcio.
/// \param    size: El nombre de bytes a transmetre.
/// \param    timeout: Temps maxim d'espera en ms.
/// \return   El resultat de l'operacio.
///
Result SPIDevice::transmit(
	const uint8_t *txBuffer,
	uint8_t *rxBuffer,
	uint16_t size,
	uint16_t timeout) {

	if (_state == State::ready) {

		_state = State::transmiting;

		bool error = false;
		uint16_t startTime = 0;
		uint16_t count = 0;
		#if defined(EOS_PLATFORM_STM32G0)
		bool len8 = (_spi->CR2 & SPI_CR2_DS_Msk) == SPI_CR2_DS_LEN8;
		#elif defined(EOS_PLATFORM_STM32F4)
		bool len8 = (_spi->CR1 & SPI_CR1_DFF_Msk) == 0;
		#elif defined(EOS_PLATFORM_STM32F7)
		bool len8 = (_spi->CR2 & SPI_CR2_DS_Msk) == SPI_CR2_DS_LEN8;
		#endif

		// Bucle per transmetre i/o rebre
		//
		while ((count < size) && !error) {

			// Espera que el buffer de transmissio estigui buit
			//
			while (!spiTxEmpty(_spi) && !error) {
			}
			if (error)
				continue;

			// Transmiteix les dades
			//
			if (len8)
				spiWrite8(_spi, txBuffer == nullptr ? 0x00 : txBuffer[count]);
			else
				spiWrite16(_spi, txBuffer == nullptr ? 0x0000 : ((const uint16_t*)txBuffer)[count]);

			if (rxBuffer != nullptr) {

				// Espera que el buffer de recepcio no estigui buit
				//
				while (!spiRxNotEmpty(_spi) && !error) {
				}
				if (error)
					continue;

				// Reb les dades
				//
				if (len8)
					rxBuffer[count] = spiRead8(_spi);
				else
					((uint16_t*)rxBuffer)[count] = spiRead16(_spi);
			}

			count += len8 ? 1 : 2;
		}

		// Espera wue finalitzin totes les operacions pendents
		//
		while (spiBusy(_spi) && !error) {
		}

		_state = State::ready;

		return Result::success();
	}

	else
		return Result::busy();
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
static void spiSetClockDivider(
	SPI_TypeDef *spi,
	ClockDivider clkDivider) {

	static const uint32_t clkDividerTbl[] = { SPI_CR1_BR_DIV2, SPI_CR1_BR_DIV4,
		SPI_CR1_BR_DIV8, SPI_CR1_BR_DIV16, SPI_CR1_BR_DIV32, SPI_CR1_BR_DIV64,
		SPI_CR1_BR_DIV128, SPI_CR1_BR_DIV256 };

	uint32_t tmp = spi->CR1;
	tmp &= ~SPI_CR1_BR_Msk;
	tmp |= clkDividerTbl[uint8_t(clkDivider)];
	spi->CR1 = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el modus de comunicacio (Polaritat i fase).
/// \param    spi: Els registres de hardware del dispositiu SPI
/// \param    mode: El modus de treball.
///
static void spiSetMode(
	SPI_TypeDef *spi,
	SPIMode mode) {

	uint32_t tmp = spi->CR1;

	tmp &= ~SPI_CR1_CRCEN;

	if (mode == SPIMode::master)
		tmp |= (SPI_CR1_MSTR | SPI_CR1_SSI | SPI_CR1_SSM);

	// Per defecte Full-duplex
	//
	tmp &= ~(SPI_CR1_BIDIMODE | SPI_CR1_RXONLY);

	spi->CR1 = tmp;
};


/// ----------------------------------------------------------------------
/// \brief    Asigna la polaritat del senyal CLK
/// \param    spi: Els registres de hardware del dispositiu SPI.
/// \param    polarity: La polaritat.
///
static void spiSetClkPolarity(
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
static void spiSetClkPhase(
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
static void spiSetWordSize(
	SPI_TypeDef *spi,
	WordSize size) {

	#if defined(EOS_PLATFORM_STM32F4)
	if (size == WordSize::_16)
		spi->CR1 |= SPI_CR1_DFF;
	else
		spi->CR1 &= ~SPI_CR1_DFF;

	#elif defined(EOS_PLATFORM_STM32F7)
	uint32_t tmp = spi->CR2;
	tmp &= ~(SPI_CR2_DS_3 | SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0);
	switch (size) {
		case WordSize::_8:
			tmp |= SPI_CR2_DS_LEN8;
			break;

		case WordSize::_16:
			tmp |= SPI_CR2_DS_LEN16;
			break;
	}
	spi->CR2 = tmp;

	#elif defined(EOS_PLATFORM_STM32G0)
	uint32_t tmp = spi->CR2;
	tmp &= (SPI_CR2_DS_Msk | SPI_CR2_FRXTH_Msk);
	tmp |= size == WordSize::_8 ?
		SPI_CR2_DS_LEN8 | SPI_CR2_FRXTH :
		SPI_CR2_DS_LEN16;
	spi->CR2 = tmp;
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Indica quin es el primer bit a transmetre en cada trama.
/// \param    spi: Els registres de hardware del dispositiu SPI.
/// \param    firstBit: Quin bit es el primer.
///
static void spiSetFirstBit(
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
static void spiWrite8(
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
static void spiWrite16(
	SPI_TypeDef * const spi,
	uint16_t data) {

	*((volatile uint16_t*)&spi->DR) = data;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix una paraula de 8 bits.
/// \param    spi: Els registres de hardware del dispositiu SPI.
/// \return   El valor de la lectura.
///
static uint8_t spiRead8(
	SPI_TypeDef * const spi) {

	return *((volatile uint8_t*)&spi->DR);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix una paraula de 16 bits.
/// \param    spi: Els registres de hardware del dispositiu SPI.
/// \return   El valor de la lectura.
///
static uint16_t spiRead16(
	SPI_TypeDef * const spi) {

	return *((volatile uint16_t*)&spi->DR);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el registre de sortida es buit.
/// \param    spi: Els registres de hardware del dispoositiu SPI.
/// \return   True si el registre de sortida es buit.
///
static inline bool spiTxEmpty(
	SPI_TypeDef * const spi) {

	return (spi->SR & SPI_SR_TXE) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el registre d'entrada no es buit.
/// \param    spi: Els registres de hardware del dispoositiu SPI.
/// \return   True si el registre d'entrada no es buit.
///
static inline bool spiRxNotEmpty(
	SPI_TypeDef * const spi) {

	return (spi->SR & SPI_SR_RXNE) != 0;
};


/// ----------------------------------------------------------------------
/// \brief    Comprova si encara hi ha una transmissio pendent.
/// \param    spi: Els registres de hardware del dispoositiu SPI.
/// \return   True si hi ha una transmissio pendent.
///
static inline bool spiBusy(
	SPI_TypeDef * const spi) {

	return (spi->SR & SPI_SR_BSY) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el fifo de transmissio estigui buit.
/// \param    regs: El bloc de registres.
/// \param    startTime: Temps del inici de les operacions
/// \param    timeout: Temps maxim de bloqueig.
///
#ifdef EOS_PLATFORM_STM32F7
static void waitRxFifoEmpty(
	SPI_TypeDef *spi,
	unsigned startTime,
	unsigned timeout) {

	while ((spi->SR & SPI_SR_FRLVL) != 0) {

		uint8_t dummy = *((volatile uint8_t *)&spi->DR);
	}
}


static void waitTxFifoEmpty(
	SPI_TypeDef *spi,
	unsigned startTime,
	unsigned timeout) {

	while ((spi->SR & SPI_SR_FTLVL) != 0) {
	}
}
#endif
