#include "HTL/htl.h"
#include "HTL/STM32/htlSPI.h"
#include "HTL/STM32/htlDMA.h"


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


static void setClockDivider(SPI_TypeDef *spi, ClockDivider clkDivider);
static void setMode(SPI_TypeDef *spi, Mode mode);
static void setClkPolarity(SPI_TypeDef *spi, ClkPolarity polarity);
static void setClkPhase(SPI_TypeDef *spi, ClkPhase phase);
static void setWordSize(SPI_TypeDef *spi, WordSize size);
static void setFirstBit(SPI_TypeDef *spi, FirstBit firstBit);

static void enable(SPI_TypeDef *spi);
static void disable(SPI_TypeDef *spi);

static void write8(SPI_TypeDef *spi, uint8_t data);
static void write16(SPI_TypeDef *spi, uint16_t data);
static uint8_t read8(SPI_TypeDef *spi);
static uint16_t read16(SPI_TypeDef *spi);

static bool isTxEmpty(SPI_TypeDef *spi);
static bool isRxNotEmpty(SPI_TypeDef *spi);
static bool isBusy(SPI_TypeDef *spi);

#if defined(EOS_PLATFORM_STM32G0) || defined(EOS_PLATFORM_STM32F7)
static bool waitRxFifoEmpty(SPI_TypeDef *spi, Tick expireTime);
static bool waitTxFifoEmpty(SPI_TypeDef *spi, Tick expireTime);
#endif
static bool waitNotBusy(SPI_TypeDef *spi, Tick expireTime);
static bool waitRxNotEmpty(SPI_TypeDef *spi, Tick expireTime);
static bool waitTxEmpty(SPI_TypeDef *spi, Tick expireTime);

static void clearOverrunFlag(SPI_TypeDef *spi);


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
	Mode mode,
	ClkPolarity clkPolarity,
	ClkPhase clkPhase,
	WordSize size,
	FirstBit firstBit,
	ClockDivider clkDivider) {

	if (_state == State::reset) {

		activate();
		disable(_spi);

		setClockDivider(_spi, clkDivider);
		setMode(_spi, mode);
		setClkPolarity(_spi, clkPolarity);
		setClkPhase(_spi, clkPhase);
		setWordSize(_spi, size);
		setFirstBit(_spi, firstBit);

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

		disable(_spi);
		deactivate();

		_state = State::reset;

		return Result::success();
	}
	else
		return Result::error();
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'event de notificacio.
/// \param    event: L'event.
/// \param    enabled: True per habilitar l'event.
///
void SPIDevice::setNotifyEvent(
    INotifyEvent &event,
    bool enabled) {

    _notifyEvent = &event;
    _notifyEventEnabled = enabled;
}


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
	Tick timeout) {

	if (_state == State::ready) {

		_state = State::transmiting;

		auto expireTime = htl::getTick() + timeout;

		#if defined(EOS_PLATFORM_STM32G0)
		bool len8 = (_spi->CR2 & SPI_CR2_DS_Msk) == SPI_CR2_DS_LEN8;
		#elif defined(EOS_PLATFORM_STM32F4)
		bool len8 = (_spi->CR1 & SPI_CR1_DFF_Msk) == 0;
		#elif defined(EOS_PLATFORM_STM32F7)
		bool len8 = (_spi->CR2 & SPI_CR2_DS_Msk) == SPI_CR2_DS_LEN8;
		#endif

		// Habilita la comunicacio
		//
		enable(_spi);

		// Bucle per transmetre i/o rebre
		//
        bool error = false;
        unsigned count = 0;
		while ((count < bufferSize) && !error) {

			// Espera que el buffer de transmissio estigui buit
			//
            if (!waitTxEmpty(_spi, expireTime)) {
                error = true;
                continue;
            }

            // Transmiteix les dades
            //
            if (len8) {
                if (txBuffer == nullptr)
                    write8(_spi, 0);
                else {
                    uint8_t data = txBuffer[count];
                    write8(_spi, data);
                }
            }
            else {
                if (txBuffer == nullptr)
                    write16(_spi, 0);
                else {
                    uint16_t data = *(const uint16_t*)&txBuffer[count];
                    write16(_spi, data);
                }
            }

            // Espera que el buffer de recepcio no estigui buit
            //
            if (!waitRxNotEmpty(_spi, expireTime)) {
                error = true;
                continue;
            }

            // Reb les dades
            //
            if (len8) {
                uint8_t data = read8(_spi);
                if (rxBuffer != nullptr)
                    rxBuffer[count] = data;
            }
            else {
                uint16_t data = read16(_spi);
                if (rxBuffer != nullptr)
                    *(uint16_t*)(&rxBuffer[count]) = data;
            }

            count += len8 ? 1 : 2;
		}

		if (!error) {
            #if defined(EOS_PLATFORM_STM32G0) || defined(EOS_PLATFORM_STM32F7)
		    if (!waitTxFifoEmpty(_spi, expireTime))
		        error = true;
		    else if (!waitNotBusy(_spi, expireTime))
		        error = true;
		    else if (!waitRxFifoEmpty(_spi, expireTime))
		        error = true;
            #else
            if (!waitNotBusy(_spi, expireTime))
                error = true;
            #endif
		}

		// Deshabilita la comunicacio
		//
		disable(_spi);

		_state = State::ready;

		return error ? Result::error() : Result::success();
	}

	else
		return Result::busy();
}


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

    // Habilita les transferencies per DMA
    //
    _spi->CR2 |= SPI_CR2_TXDMAEN;

    // Habilita la comunicacio
    //
    enable(_spi);

    // Inicia la transferencia i espera que finalitzi
    //
    devTxDMA->start(txBuffer, (uint8_t*)&(_spi->DR), bufferSize);
    devTxDMA->waitForFinish(Tick(1000));

    // Espera que el SPI acabi de transferir
    //
    while (isBusy(_spi))
        continue;

    // Desabilita la comunicacio
    //
    disable(_spi);

    // Deshabilita la transfertencia per DMA
    //
    _spi->CR2 &= ~SPI_CR2_TXDMAEN;

    return Result::success();
}


/// -------------------------------------------------------------------------
/// \brief    Asigna el divisor del rellotge.
/// \param    spi: Els registres de hardware del dispositiu SPI.
/// \param    clkDivider: El valor del divisor.
/// \remarks  La frequencia resultant es PCLK/clkDivider
///
static void setClockDivider(
	SPI_TypeDef *spi,
	ClockDivider clkDivider) {

	static const uint32_t clkDividerTbl[] = { SPI_CR1_BR_DIV2, SPI_CR1_BR_DIV4,
		SPI_CR1_BR_DIV8, SPI_CR1_BR_DIV16, SPI_CR1_BR_DIV32, SPI_CR1_BR_DIV64,
		SPI_CR1_BR_DIV128, SPI_CR1_BR_DIV256 };

	uint32_t CR1 = spi->CR1;
	CR1 &= ~SPI_CR1_BR_Msk;
	CR1 |= clkDividerTbl[uint8_t(clkDivider)];
	spi->CR1 = CR1;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el modus de comunicacio (Polaritat i fase).
/// \param    spi: Els registres de hardware del dispositiu SPI
/// \param    mode: El modus de treball.
///
static void setMode(
	SPI_TypeDef *spi,
	Mode mode) {

    // Configura el registre CR1
    //
	uint32_t CR1 = spi->CR1;
	CR1 &= ~SPI_CR1_CRCEN;
	if (mode == Mode::master)
		CR1 |= (SPI_CR1_MSTR | SPI_CR1_SSI | SPI_CR1_SSM);
	CR1 &= ~(SPI_CR1_BIDIMODE | SPI_CR1_RXONLY);
	spi->CR1 = CR1;

	// Configura el registre CR2
	//
	uint32_t CR2 = spi->CR2;
	CR2 &= ~(SPI_CR2_SSOE | SPI_CR2_FRF);
    #if defined(EOS_PLATFORM_STM32G0)
	CR2 &= ~SPI_CR2_NSSP;
    #endif
	spi->CR2 = CR2;
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
static void setWordSize(
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

    #else
    #error "Unknown platform"
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Indica quin es el primer bit a transmetre en cada trama.
/// \param    spi: Els registres de hardware del dispositiu SPI.
/// \param    firstBit: Quin bit es el primer.
///
static void setFirstBit(
	SPI_TypeDef *spi,
	FirstBit firstBit) {

	if (firstBit == FirstBit::lsb)
		spi->CR1 |= SPI_CR1_LSBFIRST;
	else
		spi->CR1 &= ~SPI_CR1_LSBFIRST;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita les comunicacions.
/// \param    spi: Registres de hardware del dispositiu SPI
///
static void enable(
    SPI_TypeDef *spi) {

    spi->CR1 |= SPI_CR1_SPE;
}


/// ----------------------------------------------------------------------
/// \brief    Desabilita les comunicacions.
/// \param    spi: Registres de hardware del dispositiu SPI
///
static void disable(
    SPI_TypeDef *spi) {

    #if defined(EOS_PLATFORM_STM32G0)
    while ((spi->SR & SPI_SR_FTLVL) != 0)
        continue;

    while ((spi->SR & SPI_SR_BSY) != 0)
        continue;

    spi->CR1 &= ~SPI_CR1_SPE;

    while ((spi->SR & SPI_SR_FRLVL) != 0)
        read8(spi);
    #endif

}


/// ----------------------------------------------------------------------
/// \brief    Excriu una paraula de 8 bits en el registre de sortida
///           de dades.
/// \param    spi: Els registres de hardware del dispositiu SPI
/// \param    data: Les dades a transmetre.
///
static void write8(
	SPI_TypeDef *spi,
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
	SPI_TypeDef *spi,
	uint16_t data) {

	*((volatile uint16_t*)&spi->DR) = data;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix una paraula de 8 bits.
/// \param    spi: Els registres de hardware del dispositiu SPI.
/// \return   El valor de la lectura.
///
static uint8_t read8(
	SPI_TypeDef *spi) {

	return *((volatile uint8_t*)&spi->DR);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix una paraula de 16 bits.
/// \param    spi: Els registres de hardware del dispositiu SPI.
/// \return   El valor de la lectura.
///
static uint16_t read16(
	SPI_TypeDef *spi) {

	return *((volatile uint16_t*)&spi->DR);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el registre de sortida es buit.
/// \param    spi: Els registres de hardware del dispoositiu SPI.
/// \return   True si el registre de sortida es buit.
///
static inline bool isTxEmpty(
	SPI_TypeDef *spi) {

	return (spi->SR & SPI_SR_TXE) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el registre d'entrada no es buit.
/// \param    spi: Els registres de hardware del dispoositiu SPI.
/// \return   True si el registre d'entrada no es buit.
///
static inline bool isRxNotEmpty(
	SPI_TypeDef *spi) {

	return (spi->SR & SPI_SR_RXNE) != 0;
};


/// ----------------------------------------------------------------------
/// \brief    Comprova si encara hi ha una transmissio pendent.
/// \param    spi: Els registres de hardware del dispoositiu SPI.
/// \return   True si hi ha una transmissio pendent.
///
static inline bool isBusy(
	SPI_TypeDef *spi) {

	return (spi->SR & SPI_SR_BSY) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el fifo de recepcio estigui buit.
/// \param    regs: El bloc de registres.
/// \param    expireTime: Temps limit.
/// \return   True si tot es correcte. False en cas de timeout.
///
#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
static bool waitRxFifoEmpty(
	SPI_TypeDef *spi,
	Tick expireTime) {

	while ((spi->SR & SPI_SR_FRLVL) != 0) {

		uint8_t dummy = *((volatile uint8_t *)&spi->DR);
	}

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el fifo de transmissio estigui buit.
/// \param    regs: El bloc de registres.
/// \param    expireTime: Temps limit
/// \return   True si tot es correcte. False en cas de timeout.
///
static bool waitTxFifoEmpty(
	SPI_TypeDef *spi,
	Tick expireTime) {

	while ((spi->SR & SPI_SR_FTLVL) != 0) {
	}

	return true;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Espera el final de les operacions.
/// \param    spi: El bloc de registres del dispositiu.
/// \param    expireTime: Temps limit.
/// \return   True si tot es correcte. False en cas de timeout.
///
static bool waitNotBusy(
    SPI_TypeDef *spi,
    Tick expireTime) {

    while (isBusy(spi)) {
        if (hasTickExpired(expireTime)) {
            return false;
        }
    }

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Espera fins que el registre de transmissio estigui buit.
/// \param    spi: El bloc de registres del dispositiu.
/// \param    expiteRime: Temps limit.
/// \return   TRue si tot es correcte, false en cas d'error (TimeOut)
///
static bool waitTxEmpty(
    SPI_TypeDef *spi,
    Tick expireTime) {

    while (!isTxEmpty(spi)) {
        if (hasTickExpired(expireTime))
            return false;
    }

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Espera fins que el registre de recepcio no estigui buit.
/// \param    spi: El bloc de registres del dispositiu.
/// \param    expiteRime: Temps limit.
/// \return   TRue si tot es correcte, false en cas d'error (TimeOut)
///
static bool waitRxNotEmpty(
    SPI_TypeDef *spi,
    Tick expireTime) {

    while (!isRxNotEmpty(spi)) {
        if (hasTickExpired(expireTime))
            return false;
    }

    return true;
}


static void clearOverrunFlag(
    SPI_TypeDef *spi) {

    uint32_t volatile tmp;
    tmp = spi->DR;
    tmp = spi->SR;
}
