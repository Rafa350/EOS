#include "HTL/htl.h"
#include "HAL/STM32/halSYS.h"
#include "HTL/STM32/htlSPI.h"


using namespace htl;


/// -------------------------------------------------------------------------
/// \brief    Asigna el divisor del rellotge.
/// \param    regs: El bloc de registres.
/// \param    clkDivider: El valor del divisor.
///
static void setClockDivider(
	SPI_TypeDef *regs,
	SPIClockDivider clkDivider) {

	uint32_t tmp = regs->CR1;
	tmp &= ~(SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0);
	switch (clkDivider) {
		case SPIClockDivider::_2:
			break;

		case SPIClockDivider::_4:
			tmp |= SPI_CR1_BR_0;
			break;

		case SPIClockDivider::_8:
			tmp |= SPI_CR1_BR_1;
			break;

		case SPIClockDivider::_16:
			tmp |= SPI_CR1_BR_1 | SPI_CR1_BR_0;
			break;

		case SPIClockDivider::_32:
			tmp |= SPI_CR1_BR_2;
			break;

		case SPIClockDivider::_64:
			tmp |= SPI_CR1_BR_2 | SPI_CR1_BR_0;
			break;

		case SPIClockDivider::_128:
			tmp |= SPI_CR1_BR_2 | SPI_CR1_BR_1;
			break;

		case SPIClockDivider::_256:
			tmp |= SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0;
			break;
	}
	regs->CR1 = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el modus de comunicacio (Polaritat i fase).
/// \param    regs: El bloc de registres.
/// \param    mode: El modus de treball.
///
static void setMode(
	SPI_TypeDef *regs,
	SPIMode mode) {

	if (mode == SPIMode::master)
		regs->CR1 |= SPI_CR1_MSTR | SPI_CR1_SSI | SPI_CR1_SSM;
};


/// ----------------------------------------------------------------------
/// \brief    Asigna la polaritat del senyal CLK
/// \param    regs: El bloc de registres.
/// \param    polarity: La polaritat.
///
static void setClkPolarity(
	SPI_TypeDef *regs,
	SPIClkPolarity polarity) {

	if (polarity == SPIClkPolarity::high)
		regs->CR1 |= SPI_CR1_CPOL;
	else
		regs->CR1 &= ~SPI_CR1_CPOL;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la fase del senyal CLK
/// \param    regs: El bloc de registres.
/// \param    polarity: La fase.
///
static void setClkPhase(
	SPI_TypeDef *regs,
	SPIClkPhase phase) {

	if (phase == SPIClkPhase::edge2)
		regs->CR1 |= SPI_CR1_CPHA;
	else
		regs->CR1 &= ~SPI_CR1_CPHA;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el tamany de la trama.
/// \param    regs: El bloc de registres.
/// \param    size: El tamany.
///
static void setSize(
	SPI_TypeDef *regs,
	SPISize size) {

	#if defined(EOS_STM32F4)
		if (size == SPISize::_16)
			regs->CR1 |= SPI_CR1_DFF;
		else
			regs->CR1 &= ~SPI_CR1_DFF;

	#elif defined(EOS_STM32F7)
		uint32_t tmp = regs->CR2;
		tmp &= ~(SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0);
		switch (size) {
			case SPISize::_8:
				tmp |= SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;
				break;

			case SPISize::_16:
				tmp |= SPI_CR2_DS_3 | SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;
				break;
		}
		regs->CR2 = tmp;
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Indica quin es el primer bit a transmetre en cada trama.
/// \param    regs: El bloc de registres.
/// \param    firstBit: Quin bit es el primer.
///
static void setFirstBit(
	SPI_TypeDef *regs,
	SPIFirstBit firstBit) {

	if (firstBit == SPIFirstBit::lsb)
		regs->CR1 |= SPI_CR1_LSBFIRST;
	else
		regs->CR1 &= ~SPI_CR1_LSBFIRST;
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el dispositiu estigui lliure
/// \param    regs: El bloc de registres.
/// \param    startTime: Temps del inici de les operacions
/// \param    blockTime: Temps maxim de bloqueig.
///
static void waitBusy(
	SPI_TypeDef *regs,
	unsigned startTime,
	unsigned blockTime) {

	while ((regs->SR & SPI_SR_BSY) != 0) {
		if (halSYSCheckTimeout(startTime, blockTime)) {
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el fifo de transmissio estigui buit.
/// \param    regs: El bloc de registres.
/// \param    startTime: Temps del inici de les operacions
/// \param    blockTime: Temps maxim de bloqueig.
///
#ifdef EOS_STM32F7
static void waitTxFifoEmpty(
	SPI_TypeDef *regs,
	unsigned startTime,
	unsigned blockTime) {

	while ((regs->SR & SPI_SR_FTLVL) != SPI_FTLVL_EMPTY) {
		if (halSYSCheckTimeout(startTime, blockTime)) {

		}
	}
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Espera que el fifo de recepcio estigui buit.
/// \param    regs: El bloc de registres.
/// \param    startTime: Temps del inici de les operacions
/// \param    blockTime: Temps maxim de bloqueig.
///
#ifdef EOS_STM32F7
static void waitRxFifoEmpty(
	SPI_TypeDef *regs,
	unsigned startTime,
	unsigned blockTime) {

	while ((regs->SR & SPI_SR_FRLVL) != SPI_FRLVL_EMPTY) {
		if (halSYSCheckTimeout(startTime, blockTime)) {

		}

		uint8_t dummy = *((__IO uint8_t *)&regs->DR);
	}
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul SPI.
/// \param    regs: El bloc de registres
/// \param    mode: El modus de comunicacio.
/// \param    size: El tamany de trama
/// \param    firstBite: El primer bit de la trama.
/// \param    clkDivider: Divisor de frequencia.
///
void htl::SPI_init(
	SPI_TypeDef *regs,
	SPIMode mode,
	SPIClkPolarity clkPolarity,
	SPIClkPhase clkPhase,
	SPISize size,
	SPIFirstBit firstBit,
	SPIClockDivider clkDivider) {

	setClockDivider(regs, clkDivider);
	setMode(regs, mode);
	setClkPolarity(regs, clkPolarity);
	setClkPhase(regs, clkPhase);
	setSize(regs, size);
	setFirstBit(regs, firstBit);
}


/// ----------------------------------------------------------------------
/// \brief    Transfereix un bloc de dades.
/// \param    regs: El bloc de registres.
/// \param    data: El bloc de dades.
/// \param    size: El tamany del bloc de dades en bytes.
/// \param    blockTime: El temps maxim de bloqueig.
///
void htl::SPI_send(
	SPI_TypeDef *regs,
	const void *data,
	int size,
	unsigned blockTime) {

	int count = size;
	const uint8_t *p = (const uint8_t*) data;
	unsigned startTime = halSYSGetTick();

	while (count > 0) {

#if defined(EOS_STM32F4)
		*((volatile uint8_t*)&regs->DR) = *((uint8_t*)p);
		p += sizeof(uint8_t);
		count -= sizeof(uint8_t);

#elif defined(EOS_STM32F7)
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
#error "CPU no soportada."
#endif

		while ((regs->SR & SPI_SR_TXE) == 0) {
			if (halSYSCheckTimeout(startTime, blockTime)) {

			}
		}
	}

#ifdef EOS_STM32F7
	waitTxFifoEmpty(regs, startTime, blockTime);
#endif
	waitBusy(regs, startTime, blockTime);
#ifdef EOS_STM32F7
	waitRxFifoEmpty(regs, startTime, blockTime);
#endif
}
