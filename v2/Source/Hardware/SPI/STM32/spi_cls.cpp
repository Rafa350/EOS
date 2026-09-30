module;


#include "HTL/htl.h"
#include "eosEvents.h"


export module Eos.Hardware.SPI.Classes;


import Eos.Bits;
import Eos.Hardware.DMA;
import Eos.Result;
import Eos.System.Core.Ticks;
import Eos.Types;


export namespace eos::hardware::spi {

    class SPIDevice: private NonCopyableClass {
        public:
            enum class Mode {
                master,
                slave
            };

            enum class ClkPolarity {
                low,
                high
            };

            enum class ClkPhase {
                edge1,
                edge2
            };

            enum class WordSize {
                ws8,
                ws16
            };

            enum class FirstBit {
                lsb,
                msb
            };

            enum class ClockDivider {
                div2,
                div4,
                div8,
                div16,
                div32,
                div64,
                div128,
                div256
            };

            enum class NotificationID {
                null,
                completed,
                error
            };
            struct NotificationEventArgs {
                NotificationID const id;
                bool const irq;
            };
            using NotificationEventRaiser = EventRaiser<SPIDevice, NotificationEventArgs>;
            using INotificationEvent = NotificationEventRaiser::IEvent;
            template <typename Instance_> using NotificationEvent = NotificationEventRaiser::Event<Instance_>;

            enum class State {
                reset,
                ready,
                transmiting
            };

            enum class ErrorCode {
                ok,
                busy,
                timeout,
                error,
                errorState,
                errorParam
            };
            using Result = SimpleResultX<ErrorCode, ErrorCode::ok>;

        private:
            SPI_TypeDef * const _spi;
            State _state;
            NotificationEventRaiser _notificationEventRaiser;

        private:
            void activate() const {
                activateImpl();
            }
#if HTL_SPI_OPTION_DEACTIVATE == 1
            void deactivate() const {
                deactivateImpl();
            }
#endif

        protected:
            SPIDevice(SPI_TypeDef *spi);

            Result initialize(Mode mode, ClkPolarity clkPolarity,
                    ClkPhase clkPhase, WordSize size, FirstBit firstBit,
                    ClockDivider clkDivider);

            void interruptService();

            virtual void activateImpl() const = 0;
#if HTL_SPI_OPTION_DEACTIVATE == 1
            virtual void deactivateImpl() const = 0;
#endif

            void enable() const;
            void disable() const;

            void setClockDivider(ClockDivider clkDivider) const;
            void setMode(Mode mode) const;
            void setClkPolarity(ClkPolarity polarity) const;
            void setClkPhase(ClkPhase phase) const;
            void setWordSize(WordSize size) const;
            void setFirstBit(FirstBit firstBit) const;

            void write8(uint8_t data) const;
            void write16(uint16_t data) const;
            uint8_t read8() const;
            uint16_t read16() const;

            bool isTxEmpty() const;
            bool isRxNotEmpty() const;
            bool isSPIBusy() const;
            bool waitNotBusy(Ticks expirationTime) const;
            bool waitRxNotEmpty(Ticks expirationTime) const;
            bool waitTxEmpty(Ticks expirationTime) const;
#if defined(EOS_PLATFORM_STM32G0) || defined(EOS_PLATFORM_STM32F7)
            bool waitRxFifoEmpty(Ticks expirationTime) const;
            bool waitTxFifoEmpty(Ticks expirationTime) const;
#endif

        public:
            virtual ~SPIDevice() = default;
            Result initMaster(ClkPolarity clkPolarity,
                    ClkPhase clkPhase, WordSize size, FirstBit firstBit,
                    ClockDivider clkDivider) {
                return initialize(Mode::master, clkPolarity, clkPhase,
                        size, firstBit, clkDivider);
            }
#if HTL_SPI_OPTION_DEACTIVATE == 1
            Result deinitialize();
#endif

            inline void enableNotificationEvent(INotificationEvent &event) {
                _notificationEventRaiser.enable(event);
            }
            inline void disableNotificationEvent() {
                _notificationEventRaiser.disable();
            }

            Result transmit(const uint8_t *txBuffer, uint8_t *rxBuffer,
                    uint32_t bufferSize, Ticks blockTime);
            Result receive(uint8_t *rxBuffer, uint32_t bufferSize,
                    Ticks blockTime)  {
                return transmit(nullptr, rxBuffer, bufferSize, blockTime);
            }
            Result transmit(const uint8_t *txBuffer, uint32_t bufferSize,
                    Ticks blockTime) {
                return transmit(txBuffer, nullptr, bufferSize, blockTime);
            }

#if HTL_SPI_OPTION_DMA == 1
            Result transmit_DMA(dma::DMADevice *devTxDMA,
                    const uint8_t *txBuffer, unsigned bufferSize);
#endif
            State getState() const { return _state; }
            bool isReady() const { return _state == State::ready; }
            bool isBusy() const { return _state != State::ready; }
    };

}


using namespace eos;
using namespace eos::hardware::spi;


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
SPIDevice::Result SPIDevice::initialize(
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

		return ErrorCode::ok;
	}
	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul SPI.
/// \return   El resultat de l'operacio.
///
#if HTL_SPI_OPTION_DEACTIVATE == 1
eos::Result SPIDevice::deinitialize() {

	if (_state == State::ready) {

		disable();
		deactivate();

		_state = State::reset;

		return eos::Results::success;
	}
	else
		return eos::Results::errorState;
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
SPIDevice::Result SPIDevice::transmit(
	const uint8_t *txBuffer,
	uint8_t *rxBuffer,
	uint32_t bufferSize,
	Ticks blockTime) {

	if (_state == State::ready) {

		_state = State::transmiting;

		auto expirationTime = Ticks::now() + blockTime;

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
            if (!waitTxEmpty(expirationTime)) {
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
            if (!waitRxNotEmpty(expirationTime)) {
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

		// TODO: Comprovar si en full duples es transmit l'ultim byte, ja
		// que la recepcio va desplaçada un byte respecte la transmissio. Mirsr
		// si cal transmetre un byte 0x00 per rebre l'ultim byte

		if (!error) {
#if defined(EOS_PLATFORM_STM32G0) || defined(EOS_PLATFORM_STM32F7)
			// Espera que es buidin els fifos
			//
		    if (!waitTxFifoEmpty(expirationTime))
		        error = true;
		    else if (!waitNotBusy(expirationTime))
		        error = true;
		    else if (!waitRxFifoEmpty(expirationTime))
		        error = true;
#elif defined(EOS_PLATFORM_STM32F4)
		    // Espera que s'hagin transmes totes les trames
		    //
		    if (!waitNotBusy(expirationTime))
		        error = true;
#else
#error "Unknown platform"
#endif
		}

		// Deshabilita la comunicacio
		//
		disable();

		_state = State::ready;

		return error ? ErrorCode::error : ErrorCode::ok;
	}

	else if (_state == State::transmiting)
		return ErrorCode::busy;

	else
		return ErrorCode::errorState;
}


#if HTL_SPI_OPTION_DMA == 1
/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades en modus DMA
/// \param    devTxDMA: DMA per la transmissio
/// \param    txBuffer: El buffer de transmissio.
/// \param    bufferSize: El nombre de bytes a transmetre.
/// \return   El resultat de l'operacio.
///
SPIDevice::Result SPIDevice::transmit_DMA(
    dma::DMADevice *devTxDMA,
    const uint8_t *txBuffer,
    unsigned bufferSize) {

	if (_state == State::ready) {

		// Habilita les transferencies per DMA
		//
		Bits::set(_spi->CR2, SPI_CR2_TXDMAEN);

		// Habilita la comunicacio
		//
		enable();

		// Inicia la transferencia i espera que finalitzi
		//
		devTxDMA->start(txBuffer, (uint8_t*)&(_spi->DR), bufferSize);
		devTxDMA->waitForFinish(Ticks::fromMiliseconds(1000));

		// Espera que el SPI acabi de transferir
		//
		while (isSPIBusy())
			continue;

		// Desabilita la comunicacio
		//
		disable();

		// Deshabilita la transfertencia per DMA
		//
		Bits::clear(_spi->CR2, SPI_CR2_TXDMAEN);

		return ErrorCode::ok;
	}
	else
		return ErrorCode::errorState;
}
#endif // HTL_SPI_OPTION_DMA == 1


/// ----------------------------------------------------------------------
/// \brief    Habilita les comunicacions.
///
void SPIDevice::enable() const {

    Bits::set(_spi->CR1, SPI_CR1_SPE);
}


/// ----------------------------------------------------------------------
/// \brief    Desabilita les comunicacions.
/// \remarks  Asegurar-se que les comunicacions han finalitzat.
///
void SPIDevice::disable() const {

#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	eos::Bits::clear(_spi->CR1, SPI_CR1_SPE);

#elif defined(EOS_PLATFORM_STM32G0)
    while ((_spi->SR & SPI_SR_FTLVL) != 0)
        continue;

    while ((_spi->SR & SPI_SR_BSY) != 0)
        continue;

    Bits::clear(_spi->CR1, SPI_CR1_SPE);

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
	Bits::clear(CR1, SPI_CR1_BR);
	Bits::set(CR1, ((uint32_t) clkDivider << SPI_CR1_BR_Pos) & SPI_CR1_BR_Msk);
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
	Bits::clear(CR1,
		SPI_CR1_CRCEN |      // Deshabilita CRC
		SPI_CR1_BIDIMODE |   // Deshabilita modus bitireccional
		SPI_CR1_RXONLY);     // Desabilita modus lectura
	if (mode == Mode::master)
		Bits::set(CR1,
			SPI_CR1_MSTR |   // Habilita modus master
			SPI_CR1_SSI |    // Habilita seleccio d'esclau per software
			SPI_CR1_SSM);    // Habilita control del esclau per software
	_spi->CR1 = CR1;

	// Configura el registre CR2
	//
	auto CR2 = _spi->CR2;
	Bits::clear(CR2,
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
		Bits::set(_spi->CR1, SPI_CR1_CPOL);
	else
		Bits::clear(_spi->CR1, SPI_CR1_CPOL);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la fase del senyal CLK
/// \param    polarity: La fase.
///
void SPIDevice::setClkPhase(
	ClkPhase phase) const {

	if (phase == ClkPhase::edge2)
		Bits::set(_spi->CR1, SPI_CR1_CPHA);
	else
		Bits::clear(_spi->CR1, SPI_CR1_CPHA);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el tamany de la trama.
/// \param    size: El tamany.
///
void SPIDevice::setWordSize(
	WordSize size) const {

#if defined(EOS_PLATFORM_STM32F4)
	if (size == WordSize::ws16)
		Bits::set(_spi->CR1, SPI_CR1_DFF);
	else
		Bits::clear(_spi->CR1, SPI_CR1_DFF);

#elif defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
	auto CR2 = _spi->CR2;
	Bits::clear(CR2, SPI_CR2_DS | SPI_CR2_FRXTH);
	Bits::set(CR2, size == WordSize::ws8 ?
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
		Bits::set(_spi->CR1, SPI_CR1_LSBFIRST);
	else
		Bits::clear(_spi->CR1, SPI_CR1_LSBFIRST);
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

	return Bits::isSet(_spi->SR, SPI_SR_TXE);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el registre d'entrada no es buit.
/// \return   True si el registre d'entrada no es buit.
///
bool SPIDevice::isRxNotEmpty() const {

	return Bits::isSet(_spi->SR, SPI_SR_RXNE);
};


/// ----------------------------------------------------------------------
/// \brief    Comprova si encara hi ha una transmissio pendent.
/// \return   True si hi ha una transmissio pendent.
///
bool SPIDevice::isSPIBusy() const {

	return Bits::isSet(_spi->SR, SPI_SR_BSY);
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el fifo de recepcio estigui buit.
/// \param    expirationTime: Temps limit.
/// \return   True si tot es correcte. False en cas de timeout.
///
#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
bool SPIDevice::waitRxFifoEmpty(
	Ticks expirationTime) const {

	while ((_spi->SR & SPI_SR_FRLVL) != 0) {
        if (expirationTime.hasExpiredNow())
            return false;

        read8();
	}

	return true;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Espera que el fifo de transmissio estigui buit.
/// \param    expirationTime: Temps limit
/// \return   True si tot es correcte. False en cas de timeout.
///
#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
bool SPIDevice::waitTxFifoEmpty(
	Ticks expirationTime) const {

	while ((_spi->SR & SPI_SR_FTLVL) != 0) {
        if (expirationTime.hasExpiredNow())
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
    Ticks expirationTime) const {

    while (isSPIBusy()) {
        if (expirationTime.hasExpiredNow())
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
    Ticks expirationTime) const {

    while (!isTxEmpty()) {
        if (expirationTime.hasExpiredNow())
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
    Ticks expirationTime) const {

    while (!isRxNotEmpty()) {
        if (expirationTime.hasExpiredNow())
            return false;
    }

    return true;
}
