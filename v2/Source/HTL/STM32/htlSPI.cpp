#include "HTL/htl.h"
#include "HAL/STM32/halSYS.h"
#include "HTL/STM32/htlSPI.h"


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


/// -------------------------------------------------------------------------
/// \brief    Asigna el divisor del rellotge.
/// \param    regs: El bloc de registres.
/// \param    clkDivider: El valor del divisor.
/// \remarks  La frequencia resultant es PCLK/clkDivider
///
static void setClockDivider(
	SPI_TypeDef *regs,
	ClockDivider clkDivider) {

	uint32_t tmp = regs->CR1;
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

	// Per defecte Full-duplex
	//
	regs->CR1 &= ~(SPI_CR1_BIDIMODE | SPI_CR1_RXONLY);
};


/// ----------------------------------------------------------------------
/// \brief    Asigna la polaritat del senyal CLK
/// \param    regs: El bloc de registres.
/// \param    polarity: La polaritat.
///
static void setClkPolarity(
	SPI_TypeDef *regs,
	ClkPolarity polarity) {

	if (polarity == ClkPolarity::high)
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
	ClkPhase phase) {

	if (phase == ClkPhase::edge2)
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
	WordSize size) {

	#if defined(EOS_PLATFORM_STM32F4)
	if (size == WordSize::_16)
		regs->CR1 |= SPI_CR1_DFF;
	else
		regs->CR1 &= ~SPI_CR1_DFF;

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
	uint32_t tmp = regs->CR2;
	tmp &= ~SPI_CR2_DS_Msk;
	switch (size) {
		case WordSize::_8:
			tmp |= SPI_CR2_DS_LEN8;
			break;

		case WordSize::_16:
			tmp |= SPI_CR2_DS_LEN16;
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
	FirstBit firstBit) {

	if (firstBit == FirstBit::lsb)
		regs->CR1 |= SPI_CR1_LSBFIRST;
	else
		regs->CR1 &= ~SPI_CR1_LSBFIRST;
}


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
SPIDevice::SPIDevice(SPI_TypeDef *spi):
	_spi(spi) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul SPI.
/// \param    mode: El modus de comunicacio.
/// \param    clkPolarity: Polaritat del senyal CLK
/// \param    clkPhase: Fase del senyal CLK
/// \param    size: El tamany de trama
/// \param    firstBite: El primer bit de la trama.
/// \param    clkDivider: Divisor de frequencia.
///
void SPIDevice::initialize(
	SPIMode mode,
	ClkPolarity clkPolarity,
	ClkPhase clkPhase,
	WordSize size,
	FirstBit firstBit,
	ClockDivider clkDivider) {

	activate();
	disable();

	setClockDivider(_spi, clkDivider);
	setMode(_spi, mode);
	setClkPolarity(_spi, clkPolarity);
	setClkPhase(_spi, clkPhase);
	setSize(_spi, size);
	setFirstBit(_spi, firstBit);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul SPI.
///
void SPIDevice::deinitialize() {

	disable();
	deactivate();
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades.
/// \param    buffer: El bloc de dades.
/// \param    size: Tamany del bloc en bytes.
/// \return   El nombre de bytes transmissos.
///
uint16_t SPIDevice::transmit(
	const uint8_t *buffer,
	uint16_t size) {

	uint16_t count = 0;

	while (count < size) {
		write8(buffer[count++]);
		while (!isTxEmpty())
			continue;
	}
	while (isBusy())
		continue;

	return count;
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
