module;


#include "HTL/htl.h"
#include "HTL/STM32/htlClock.h"
#include "eosBits.h"
#include "eosResults.h"
#include "HTL/htlDevice.h"
#include "HTL/htlDMA.h"
#include "HTL/htlGPIO.h"
#include "eosEvents.h"


export module Eos.Hardware.UART.Device;


import Eos.Hardware.Atomic;
import Eos.System.Core.Ticks;


export namespace eos::hardware::uart {

    class UARTDevice;

	#if defined(EOS_PLATFORM_STM32G0)
	/// Origen del rellotge del generador de bauds
	///
	enum class ClockSource {
		pclk = 0,
		sysclk = 1,
		hsi16 = 2,
		lse = 3
	};

	#elif defined(EOS_PLATFORM_STM32F7)
	enum class ClockSource {
		pclk = 0,
		sysclk = 1,
		hsi = 2,
		lse = 3
	};
	#endif

		// Mostreig den la recepcio de dades
		//
		enum class OverSampling {
			os8,
			os16
		};

		/// Clase que implementa el dispositiu de comunicacio UART.
		///
		class UARTDevice: htl::Device {
			public:
				/// Primer bit a transmetre.
				///
				enum class FirstBit {
					lsb, ///< Primer transmet el bit menys significatiu.
					msb  ///< Primer transmet el bit mes significatiu.
				};

				/// Paritat.
				///
				enum class Parity {
					none, ///< Sense paritat.
					even, ///< Parell
					odd   ///< Senas
				};

				/// Nombre de bits de paraula (No inclou el bit de paritat).
				///
				enum class WordBits {
#if defined(EOS_PLATFORM_STM32G0)
					wb7,  ///< Paraula de 7 bits
#endif
					wb8,  ///< Paraula de 8 bits
					wb9   ///< Paraula de 9 bits
				};

				/// Nombre de bits de parada.
				///
				enum class StopBits {
					sb0p5, ///< 0.5 bits de parada
					sb1,   ///< 1 bit de parada
					sb1p5, ///< 1.5 bits de parada
					sb2    ///< 2 bits de parada
				};

				/// Opcions de velocitat de transmissio.
				///
				enum class BaudMode {
					b1200,    ///< 1200 baud.
					b2400,    ///< 2400 baud.
					b4800,    ///< 4800 baud.
					b9600,    ///< 9600 baud.
					b19200,   ///< 19200 baud.
					b38400,   ///< 38600 baud.
					b57600,   ///< 57600 baud.
					b115200,  ///< 115200 baud.
					div,      ///< Utilitza el divisor per calcular la velocitat.
					rate,     ///< Utilitza la velocitat especificada.
					automatic ///< Deteccio automatica.
				};

				/// Protocol de comunicacio
				///
				enum class Handsake {
					none,  ///< Cap protocol.
					ctsrts ///< Protocol CTS/RTS
				};

			public:
				/// Identificador de la notificacio
				///
				enum class NotificationID {
					null,
					rxCompleted, ///< Recepcio complerta.
					txCompleted, ///< Transmissio complerta.
					error        ///< Error de comunicacio.
				};

				/// Parametres del event de notificacio.
				///
				struct NotificationEventArgs {
					NotificationID id;             ///< Identificador de la notificacio
					bool irq;                      ///< Indica si es notifica desde una interrupcio.
					union {
						struct {
							const uint8_t *buffer; ///< Dades transmeses.
							uint32_t length;       ///< Nombre de bytes transmessos.
						} txCompleted;             ///< Parametres de 'TxComplete'
						struct {
							const uint8_t *buffer; ///< Dades rebudes.
							uint32_t length;       ///< Nombre de bytes rebuts.
						} rxCompleted;             ///< Parametres de 'RxComplete'
					};
				};

				// Event de notificacio
				//
				using NotificationEventRaiser = eos::EventRaiser<UARTDevice, NotificationEventArgs>;
				using INotificationEvent = NotificationEventRaiser::IEvent;
				template <typename Instance_> using NotificationEvent = NotificationEventRaiser::Event<Instance_>;

			public:
				/// Estats en que es troba el dispositiu.
				///
				enum class State {
					reset,       ///< Creat, pero sense inicialitzar.
					ready,       ///< Inicialitzat i preparat per operar.
					transmiting, ///< Transmeten dades.
					receiving    ///< Rebent dades.
				};

			private:
#if HTL_UART_OPTION_DMA == 1
				using DMANotificationEvent = htl::dma::DMADevice::NotificationEvent<UARTDevice>;
				using DMANotificationEventArgs = htl::dma::DMADevice::NotificationEventArgs;
#endif

			private:
				USART_TypeDef * const _usart;   ///< Instancia del dispositiu.
				State _state;                   ///< Estat actual.
				uint8_t *_rxBuffer;             ///< Buffer de recepcio.
				uint32_t _rxCount;              ///< Contador de bytes rebuts.
				uint32_t _rxMaxCount;           ///< Maxim del contador de bytes rebuts.
				const uint8_t *_txBuffer;       ///< Buffer de transmissio.
				uint32_t _txCount;              ///< Contador de bytes transmesos.
				uint32_t _txMaxCount;           ///< Maxim del contador de bytes rebuts.
				NotificationEventRaiser _notificationEventRaiser;   ///< Event de notificacio
#if HTL_UART_OPTION_DMA == 1
				DMANotificationEvent _dmaNotificationEvent; ///< Event de notificacio del DMA.
#endif

			private:
				void setWordBits(WordBits wordBits, bool useParity) const;
				void setStopBits(StopBits wordBits) const;
				void setParity(Parity parity) const;
				void setHandsake(Handsake handsake) const;

				void activate() const;
#if HTL_UART_OPTION_DEACTIVATE == 1
				void deactivate() const;
#endif

				void enable() const;
				void disable() const;

				void enableTransmission() const;
				void disableTransmission() const;
#if HTL_UART_OPTION_IRQ == 1
				void enableTransmissionIRQ() const;
#endif
#if HTL_UART_OPTION_DMA == 1
				void enableTransmissionDMA() const;
#endif

				void enableReception() const;
				void disableReception() const;
#if HTL_UART_OPTION_IRQ == 1
				void enableReceptionIRQ() const;
#endif
#if HTL_UART_OPTION_DMA == 1
				void enableReceptionDMA() const;
#endif

				void writeData(uint8_t data) const;
				uint8_t readData() const;
				bool waitTransmissionComplete(eos::Ticks expireTime);
				bool waitTransmissionBufferEmpty(eos::Ticks expireTime);
				bool waitReceptionBufferFull(eos::Ticks expireTime);

#if (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)
				constexpr virtual bool isFIFOAvailable() const = 0;
				bool isFIFOEnabled() const;
#endif
				constexpr virtual bool isRTOAvailable() const = 0;

				virtual htl::clock::ClockID getUARTClock() const = 0;

				void raiseTxCompletedNotification(const uint8_t *buffer, uint32_t length, bool irq);
				void raiseRxCompletedNotification(const uint8_t *buffer, uint32_t length, bool irq);
#if HTL_UART_OPTION_DMA == 1
				void dmaNotificationEventHandler(htl::dma::DMADevice *devDMA, htl::dma::DMADevice::NotificationEventArgs *args);
#endif

			protected:
				UARTDevice(USART_TypeDef *usart);

				virtual void activateImpl() const = 0;
#if HTL_UART_OPTION_DEACTIVATE == 1
				virtual void deactivateImpl() const = 0;
#endif
#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
				virtual void setClockSourceImpl(ClockSource source) const = 0;
#endif

#if HTL_UART_OPTION_IRQ == 1
				void interruptService();
				void txInterruptService();
				void rxInterruptService();
#endif
			public:
				eos::Result initialize();
#if HTL_UART_OPTION_DEACTIVATE == 1
				eos::Result deinitialize();
#endif
				eos::Result setProtocol(WordBits wordBits, Parity parity,
						StopBits stopBits, Handsake handlsake) const;
				eos::Result setTimming(BaudMode baudMode, uint32_t rate, OverSampling oversampling) const;
#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
				eos::Result setClockSource(ClockSource clockSource) const;
#endif
#if defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
				eos::Result setRxTimeout(unsigned timeout) const;
#endif

				void enableNotificationEvent(INotificationEvent &event) {
					_notificationEventRaiser.enable(event);
				}
				void disableNotificationEvent() {
					_notificationEventRaiser.disable();
				}

				eos::Result transmit(const uint8_t *buffer, uint32_t length, eos::Ticks blockTime);
				eos::Result receive(uint8_t *buffer, uint32_t bufferSize, eos::Ticks blockTime);

#if HTL_UART_OPTION_IRQ == 1
				eos::Result transmit_IRQ(const uint8_t *buffer, uint32_t length);
				eos::Result receive_IRQ(uint8_t *buffer, uint32_t bufferSize);
#endif
#if HTL_UART_OPTION_DMA == 1
				eos::Result transmit_DMA(htl::dma::DMADevice *devDMA, const uint8_t *buffer, uint32_t length);
				eos::Result receive_DMA(htl::dma::DMADevice *devDMA, uint8_t *buffer, uint32_t bufferSize);
#endif
				eos::Result abortTransmission();
				eos::Result abortReception();

				State getState() const { return _state; }
				inline bool isReady() const { return _state == State::ready; }
				inline bool isBusy() const { return _state != State::ready; }
		};
}


namespace g = htl::gpio;
using namespace eos;
using namespace eos::hardware;
using namespace eos::hardware::uart;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @param    usart: Registres hardware del modul USART.
///
UARTDevice::UARTDevice(
	USART_TypeDef *usart):

	_usart {usart},
	_state {State::reset}
#if HTL_UART_OPTION_DMA == 1
	, _dmaNotificationEvent {*this, &UARTDevice::dmaNotificationEventHandler}
#endif
{
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el modul UART.
/// \return   El resultat de l'operacio.
///
eos::Result UARTDevice::initialize() {

	if (_state == State::reset) {

		activate();
		disable();

#if defined(EOS_PLATFORM_STM32G0)
#if HTL_UART_OPTION_FIFO == 1
		if (isFifoAvailable())
			bits::set(_usart->CR1,
				USART_CR1_FIFOEN);    // Habilita el FIFO
		else
#endif
			Bits::clear(_usart->CR1,
				USART_CR1_FIFOEN);    // Deshabilita el FIFO
#endif

		Bits::clear(_usart->CR2,
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			USART_CR2_LINEN |     // Deshabilita modus LIN
#endif
#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			USART_CR2_RTOEN |     // Deshabilita receiver timeout
#endif
     		USART_CR2_CLKEN);     // Deshabilita clock extern

		Bits::clear(_usart->CR3,
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			USART_CR3_SCEN |      // Deshabilita modus SmartCard
			USART_CR3_IREN |      // Deshabilita modus IrDA
#endif
			USART_CR3_DMAT |      // Desbilita DMA
			USART_CR3_HDSEL);     // Deshabilita half duplex

		_state = State::ready;

		return Result::ErrorCodes::ok;
	}

	else
		return Result::ErrorCodes::errorState;
}


/// ---------------------------------------------------------------------------
/// @brief    Desinicialitza el modul.
/// \return   El resultat de l'operacio.
///
#if HTL_UART_OPTION_DEACTIVATE == 1
eos::Result htl::uart::UARTDevice::deinitialize() {

	if (_state == State::ready) {

		disable();
		deactivate();

		_state = State::reset;

		return eos::Result::ErrorCodes::success;
	}

	else
		return eos::Result::ErrorCodes::errorState;
}
#endif


/// ---------------------------------------------------------------------------
/// @brief    Aactiva el dispositiu fisic.
///
void UARTDevice::activate() const {

    activateImpl();
}


/// ---------------------------------------------------------------------------
/// @brief    Desactiva el dispositiu fisic.
///
#if HTL_UART_OPTION_DEACTIVATE == 1
void  u::UARTDevice::deactivate() const {

    deactivateImpl();
}
#endif


/// ----------------------------------------------------------------------
/// @brief    Selecciona el protocol de comunicacio.
/// @param    wordBits: Les opcions de paraula.
/// @param    parity: Les opcions de paritat.
/// @param    stopBits: Les opcions de parada.
/// @param    handsake: Protocol.
/// \return   El resultat de l'operacio.
///
Result UARTDevice::setProtocol(
	WordBits wordBits,
	Parity parity,
	StopBits stopBits,
	Handsake handsake) const {

	if (_state == State::ready) {
		setParity(parity);
		setWordBits(wordBits, parity != Parity::none);
		setStopBits(stopBits);
		setHandsake(handsake);
		return Result::ErrorCodes::ok;
	}
	else
		return Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Configura la paritat.
/// @param    usart: Registres de hardware del dispositiu.
/// @param    parity: Opcions de paritat.
///
 void UARTDevice::setParity(
    Parity parity) const {

    auto CR1 = _usart->CR1;
    if (parity == Parity::none)
    	Bits::clear(CR1, USART_CR1_PCE);
    else {
    	Bits::set(CR1, USART_CR1_PCE);
    	if (parity == Parity::even)
    		Bits::clear(CR1, USART_CR1_PS);
    	else
    		Bits::set(CR1, USART_CR1_PS);
    }
    _usart->CR1 = CR1;
}


/// ----------------------------------------------------------------------
/// @brief    Configura el nombre de bits de parada
/// @param    usart: Registres de harware del dispositiu.
/// @param    stopBits: Opcions dels bits de parada.
///
void UARTDevice::setStopBits(
    StopBits stopBits) const {

    auto CR2 = _usart->CR2;
    switch (stopBits) {
        case StopBits::sb0p5:
            Bits::clear(CR2, USART_CR2_STOP_1);
            Bits::set(CR2, USART_CR2_STOP_0);
            break;

        case StopBits::sb1:
        	Bits::clear(CR2, USART_CR2_STOP_1);
        	Bits::clear(CR2, USART_CR2_STOP_0);
            break;

        case StopBits::sb1p5:
        	Bits::set(CR2, USART_CR2_STOP_1);
        	Bits::set(CR2, USART_CR2_STOP_0);
            break;

        case StopBits::sb2:
        	Bits::set(CR2, USART_CR2_STOP_1);
        	Bits::clear(CR2, USART_CR2_STOP_0);
            break;
    }
    _usart->CR2 = CR2;
}


/// ----------------------------------------------------------------------
/// @brief    Configura nombre de bits de paraula.
/// @param    usart: Registres de herdware del dispositiu.
/// @param    wordBits: Opcions dels bits de paraula.
/// \params   useParity: True si utilitza bit de paritat
///
#if defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
void htl::uart::UARTDevice::setWordBits(
    WordBits wordBits,
    bool useParity) const {

	auto numBits = useParity? 1 : 0;
	switch (wordBits) {
		case WordBits::wb8:
			numBits += 8;
			break;

		case WordBits::wb9:
			numBits += 9;
			break;
	}

	auto a = startAtomic();
	auto CR1 = _usart->CR1;
	if (numBits == 8)
		clear(CR1, USART_CR1_M);
	else
		set(CR1, USART_CR1_M);
	_usart->CR1 = CR1;
	endAtomic(a);
}

#elif defined(EOS_PLATFORM_STM32G0)
void UARTDevice::setWordBits(
    WordBits wordBits,
    bool useParity) const {

	auto numBits = useParity? 1 : 0;
	switch (wordBits) {
		case WordBits::wb7:
			numBits += 7;
			break;

		case WordBits::wb8:
			numBits += 8;
			break;

		case WordBits::wb9:
			numBits += 9;
			break;
	}

	auto a = Atomic::start();

	auto CR1 = _usart->CR1;
	switch (numBits) {
		case 7:
			Bits::clear(CR1, USART_CR1_M0);
			Bits::set(CR1, USART_CR1_M1);
			break;

		default:
		case 8:
			Bits::clear(CR1, USART_CR1_M0);
			Bits::clear(CR1, USART_CR1_M1);
			break;

		case 9:
			Bits::set(CR1, USART_CR1_M0);
			Bits::clear(CR1, USART_CR1_M1);
			break;
	}
	_usart->CR1 = CR1;

	Atomic::end(a);
}
#else
#error "Unknown platform"
#endif // defined(EOS_PLATFORM_XXX)


/// ----------------------------------------------------------------------
/// @brief    Configura el protocol.
/// @param    usart: Registres de hardware del dispositiu.
/// @param    handsake: Opcions de protocol.
///
void UARTDevice::setHandsake(
    Handsake handsake) const {

    auto CR3 = _usart->CR3;
    switch (handsake) {
        case Handsake::none:
        	eos::Bits::clear(CR3, USART_CR3_RTSE | USART_CR3_CTSE);
            break;

        case Handsake::ctsrts:
        	eos::Bits::set(CR3, USART_CR3_RTSE | USART_CR3_CTSE);
            break;
    }
    _usart->CR3 = CR3;
}


#if defined(EOS_PLATFORM_STM32F0) || \
	defined(EOS_PLATFORM_STM32F7) || \
	defined(EOS_PLATFORM_STM32G0)
/// ----------------------------------------------------------------------
/// @brief    Asigna el valor del timeout per recepcio.
/// @param    timeout: El temps.
/// @param    El resultat de l'operacio.
///
eos::Result UARTDevice::setRxTimeout(
    unsigned timeout) const {

	if (_state == State::ready) {

		if (isRTOAvailable()) {
			if (timeout == 0)
				Bits::clear(_usart->CR2, USART_CR2_RTOEN);
			else {
				Bits::set(_usart->CR2, USART_CR2_RTOEN);
				_usart->RTOR = timeout;
			}
		}

		return eos::Result::ErrorCodes::ok;
	}
	else
		return eos::Result::ErrorCodes::errorState;
}
#endif // defined(EOS_PLATFORM_XXX)


/// ----------------------------------------------------------------------
/// @brief    Asigna els valor de temporitzacio.
/// @param    baudMode: Les opcions del baud rate
/// @param    rate: El valor de velocitat.
/// @param    overSampling: Tipus de mostreig
/// \return   El resultat de l'operacio.
///
Result UARTDevice::setTimming(
	BaudMode baudMode,
	uint32_t rate,
	OverSampling overSampling) const {

	if (_state == State::ready) {

		switch (baudMode) {
			case BaudMode::b1200:
				rate = 1200;
				break;

			case BaudMode::b2400:
				rate = 2400;
				break;

			case BaudMode::b4800:
				rate = 4800;
				break;

			case BaudMode::b9600:
				rate = 9600;
				break;

			case BaudMode::b19200:
				rate = 19200;
				break;

			case BaudMode::b38400:
				rate = 38400;
				break;

			case BaudMode::b57600:
				rate = 57600;
				break;

			case BaudMode::b115200:
				rate = 115200;
				break;

			default:
				break;
		}

		unsigned fclk = htl::clock::ClockDevice::pInst->getClockFrequency(getUARTClock());

		unsigned div;
		if (baudMode == BaudMode::div)
			div = rate;
		else {
			if (overSampling == OverSampling::os8)
				div = (fclk + fclk + (rate / 2)) / rate;
			else
				div = (fclk + (rate / 2)) / rate;
		}

		if (overSampling == OverSampling::os8) {
			unsigned temp = (uint16_t)(div & 0xFFF0U);
			temp |= (uint16_t)((div & (uint16_t)0x000FU) >> 1U);
			_usart->BRR = temp;
		}
		else
			_usart->BRR = div;

		return Result::ErrorCodes::ok;
	}
	else
		return Result::ErrorCodes::errorState;
}


#if defined(EOS_PLATFORM_STM32F7) || \
	defined(EOS_PLATFORM_STM32G0)
/// ----------------------------------------------------------------------
/// @brief    Selecciona la font del relloge del generador de bauds
/// @param    clockSource: La font.
/// \return   El resultat de l'operacio.
///
Result UARTDevice::setClockSource(
	ClockSource source) const {

	if(_state == State::ready){

		setClockSourceImpl(source);
		return Result::ErrorCodes::ok;
	}
	else
		return Result::ErrorCodes::errorState;
}
#endif // defined(EOS_PLATFORM_XXX)


/// ----------------------------------------------------------------------
/// @brief    Transmiteix un bloc de dades.
/// @param    buffer: El bloc de dades.
/// @param    length: La longitut del bloc en bytes.
/// @param    blockTime: Temps maxim de bloqueig.
///
Result UARTDevice::transmit(
	const uint8_t *buffer,
	uint32_t length,
	Ticks blockTime) {

	if (_state == State::ready) {

		auto expireTime = Ticks::now() + blockTime;
		bool error = false;

		_state = State::transmiting;

		enable();
		enableTransmission();

		while (length-- > 0) {
			if (!waitTransmissionBufferEmpty(expireTime)) {
				error = true;
				break;
			}
			writeData(*buffer++);
		}

	    error = !waitTransmissionComplete(expireTime);

		disableTransmission();
		disable();

		_state = State::ready;

		return error ? Result::ErrorCodes::timeout : Result::ErrorCodes::ok;
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return Result::ErrorCodes::busy;

	else
		return Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Inicia la transmissio d'un bloc de dades per interrupcions.
/// @param    buffer: Buffer de dades.
/// @param    length: El nombre de bytes a transmetre.
/// \return   El resultat de l'operacio
///
#if HTL_UART_OPTION_IRQ == 1
Result UARTDevice::transmit_IRQ(
	const uint8_t *buffer,
	uint32_t length) {

	if (_state == State::ready) {

		_state = State::transmiting;

		_txBuffer = buffer;
		_txCount = 0;
        _txMaxCount = length;

        enable();
        enableTransmissionIRQ();

		return eos::Result::ErrorCodes::ok;
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return eos::Result::ErrorCodes::busy;

	else
		return eos::Result::ErrorCodes::errorState;
}
#endif // HTL_UART_OPTION_IRQ == 1


#if HTL_UART_OPTION_DMA == 1
/// ----------------------------------------------------------------------
/// @brief    Transmiteix un bloc de dades utilitzant DMA.
/// @param    devDMA: Dispositiu DMA.
/// @param    buffer: Buffer de dades.
/// @param    length: El nombre de bytes a transmetre.
/// \return   El resultat de l'operacio
///
Result UARTDevice::transmit_DMA(
    htl::dma::DMADevice *devDMA,
    const uint8_t *buffer,
    uint32_t length) {

    if (_state == State::ready) {

        _state = State::transmiting;

        _txBuffer = buffer;
        _txCount = 0;
        _txMaxCount = length;

        enable();
        enableTransmissionDMA();

        // Inicia la transferencia per DMA
        //
        devDMA->enableNotificationEvent(_dmaNotificationEvent);
        devDMA->start(buffer, (uint8_t*)&(_usart->TDR), _txMaxCount);

        return Result::ErrorCodes::ok;
    }

    else if ((_state == State::transmiting) || (_state == State::receiving))
        return Result::ErrorCodes::busy;

    else
        return Result::ErrorCodes::errorState;
}
#endif // HTL_UART_OPTION_DMA == 1


/// ----------------------------------------------------------------------
/// @brief    Aborta la transmissio.
///
Result UARTDevice::abortTransmission() {

	if (_state == State::transmiting) {
		disableTransmission();
		disable();
		_state = State::ready;
		return Result::ErrorCodes::ok;
	}
	else
		return Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Reb en bloc de dades.
/// @param    buffer: Buffer de recepcio de dades.
/// @param    bufferSize: Tamany del buffer en bytes.
/// @param    blockTime: Temps maxim de bloqueig.
/// \return   El resultat.
///
Result UARTDevice::receive(
	uint8_t *buffer,
	uint32_t bufferSize,
	Ticks blockTime) {

	if (_state == State::ready) {

		_state = State::receiving;

		auto expireTime = eos::Ticks::now() + blockTime;
		bool error = false;

		enable();
		enableReception();

		while (bufferSize-- > 0) {

			if (!waitReceptionBufferFull(expireTime)) {
				error = true;
				break;
			}
			*buffer++ = readData();
		}

		disableTransmission();

		_state = State::ready;

		return error ? Result::ErrorCodes::timeout : Result::ErrorCodes::ok;
	}
	else if ((_state == State::transmiting) || (_state == State::receiving))
		return Result::ErrorCodes::busy;

	else
		return Result::ErrorCodes::errorState;
}


#if HTL_UART_OPTION_IRQ == 1
/// ----------------------------------------------------------------------
/// @brief    Inicia la recepcio d'un bloc de dades per interrupcions.
/// @param    buffer: Buffer de dades.
/// @param    bufferSize: Tamany del buffer en bytes.
/// \return   El resultat de l'operacio.
///
Result UARTDevice::receive_IRQ(
	uint8_t *buffer,
	uint32_t bufferSize) {

	if (_state == State::ready) {

		_state = State::receiving;

		_rxBuffer = buffer;
		_rxCount = 0;
		_rxMaxCount = bufferSize;

		enable();
		enableReceptionIRQ();

		return eos::Result::ErrorCodes::ok;
	}

	else if ((_state == State::transmiting) || (_state == State::receiving))
		return eos::Result::ErrorCodes::busy;

	else
		return eos::Result::ErrorCodes::errorState;
}
#endif // HTL_UART_OPTION_IRQ == 1


#if HTL_UART_OPTION_DMA == 1
/// ----------------------------------------------------------------------
/// @brief    Reb un bloc de dades utilitzan DMA.
/// @param    devDMA: El dispositiu DMA.
/// @param    buffer: El buffer de dades.
/// @param    bufferSize: El tamany del buffer en bytes.
/// \return   El resultat de l'operacio.
///
Result UARTDevice::receive_DMA(
    htl::dma::DMADevice *devDMA,
    uint8_t *buffer,
    uint32_t bufferSize) {

	return Result::ErrorCodes::error;
}
#endif // HTL_UART_OPTION_DMA == 1


/// ----------------------------------------------------------------------
/// @brief    Aborta la recepcio.
///
Result UARTDevice::abortReception() {

	if (_state == State::receiving) {
		disableReception();
		disable();
		_state = State::ready;
		return Result::ErrorCodes::ok;
	}
	else
		return Result::ErrorCodes::errorState;
}


#if HTL_UART_OPTION_IRQ == 1
/// ----------------------------------------------------------------------
/// @brief    Procesa les interrupcions.
///
void UARTDevice::interruptService() {

	if (_state == State::transmiting)
		txInterruptService();
	else if (_state == State::receiving)
		rxInterruptService();
}
#endif // HTL_UART_OPTION_IRQ == 1


#if HTL_UART_OPTION_IRQ == 1
/// ----------------------------------------------------------------------
/// @brief    Procesa les interrupcions per la transmissio
///
#if defined(EOS_PLATFORM_STM32F4)
void UARTDevice::txInterruptService() {

	auto CR1 = _usart->CR1;
	auto SR = _usart->SR;

	// Interrupcio 'TXE'
	//
	if (isSet(CR1, USART_CR1_TXEIE) && isSet(SR, USART_SR_TXE)) {
		if (_txCount < _txMaxCount) {
			_usart->DR = _txBuffer[_txCount++];
			if (_txCount == _txMaxCount) {
				auto a = startAtomic();
				clear(_usart->CR1, USART_CR1_TXEIE); // Deshabilita interrupcio TXE
				set(_usart->CR1, USART_CR1_TCIE);    // Habilita interrupcio TC
				endAtomic(a);
			}
		}
	}

	// Interrupcio 'TC'. Nomes en l'ultim caracter transmes.
	//
	if (isSet(CR1, USART_CR1_TCIE) && isSet(SR, USART_SR_TC)) {
		disableTransmission();
		notifyTxCompleted(_txBuffer, _txCount, true);
		_state = State::ready;
	}
}

#elif defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F7)
void htl::uart::UARTDevice::txInterruptService() {

	auto CR1 = _usart->CR1;
	auto ISR = _usart->ISR;

	// Interrupcio 'TXE'
	//
	if (isSet(CR1, USART_CR1_TXEIE) && isSet(ISR, USART_ISR_TXE)) {
		if (_txCount < _txMaxCount) {
			_usart->TDR = _txBuffer[_txCount++];
			if (_txCount == _txMaxCount) {
				auto a = startAtomic();
				clear(_usart->CR1, USART_CR1_TXEIE); // Deshabilita interrupcio TXE
				set(_usart->CR1, USART_CR1_TCIE);    // Habilita interrupcio TC
				endAtomic(a);
			}
		}
	}

	// Interrupcio 'TC'. Nomes en l'ultim caracter transmes.
	//
	if (isSet(CR1, USART_CR1_TCIE) && isSet(ISR, USART_ISR_TC)) {
		disableTransmission();
		raiseTxCompletedNotification(_txBuffer, _txCount, true);
		_state = State::ready;
	}
}

#elif defined(EOS_PLATFORM_STM32G0)
void UARTDevice::txInterruptService() {

	auto CR1 = _usart->CR1;
	auto ISR = _usart->ISR;

	// Interrupcio 'TXE' (Transmission buffer empty)
	//
	if (Bits::isSet(CR1, USART_CR1_TXEIE_TXFNFIE) &&
		Bits::isSet(ISR, USART_ISR_TXE_TXFNF)) {
		if (_txCount < _txMaxCount) {
			_usart->TDR = _txBuffer[_txCount++];
			if (_txCount == _txMaxCount) {
				auto a = Atomic::start();
				eos::Bits::clear(_usart->CR1, USART_CR1_TXEIE_TXFNFIE);  // Deshabilita interrupcio TXE
				eos::Bits::set(_usart->CR1, USART_CR1_TCIE);             // Habilita interrupcio TC
				Atomic::end(a);
			}
		}
	}

	// Interrupcio 'TC'. (Transmission complete)
	//
	if (Bits::isSet(CR1, USART_CR1_TCIE) &&
		Bits::isSet(ISR, USART_ISR_TC)) {
		disableTransmission();
		raiseTxCompletedNotification(_txBuffer, _txCount, true);
		_state = State::ready;
	}
}
#else
#error "Unknown platform"
#endif // defined(SOS_PLATFORM_XXX)
#endif // HTL_UART_OPTION_IRQ == 1


#if HTL_UART_OPTION_IRQ == 1
/// ----------------------------------------------------------------------
/// @brief    Procesa les interrupcions per la recepcio.
///
#if defined(EOS_PLATFORM_STM32F4)
void UARTDevice::rxInterruptService() {

	auto CR1 = _usart->CR1;
	auto SR = _usart->SR;

	/// Interrupcio 'RXNE'
	//
	if (isSet(CR1, USART_CR1_RXNEIE) && isSet(SR, USART_SR_RXNE)) {
		if (_rxCount < _rxMaxCount) {
			_rxBuffer[_rxCount++] = _usart->DR;
			if (_rxCount == _rxMaxCount) {
				disableReception();
				notifyRxCompleted(_rxBuffer, _rxCount, true);
				_state = State::ready;
			}
		}
	}

	// Interrupcio 'IDLE'
	//
	if (isSet(CR1, USART_CR1_IDLEIE) && isSet(SR, USART_SR_IDLE)) {
		if (_rxCount > 0) {
			disableReception();
			notifyRxCompleted(_rxBuffer, _rxCount, true);
			_state = State::ready;
		}
	}
}

#elif defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F7)
void UARTDevice::rxInterruptService() {

	auto CR1 = _usart->CR1;
	auto ISR = _usart->ISR;

	/// Interrupcio 'RXNE'
	//
	if (isSet(CR1, USART_CR1_RXNEIE) && isSet(ISR, USART_ISR_RXNE)) {
		if (_rxCount < _rxMaxCount) {
			_rxBuffer[_rxCount++] = _usart->RDR;
			if (_rxCount == _rxMaxCount) {
				disableReception();
				raiseRxCompletedNotification(_rxBuffer, _rxCount, true);
				_state = State::ready;
			}
		}
	}

	// Interrupcio 'IDLE'
	//
	if (isSet(CR1, USART_CR1_IDLEIE) && isSet(ISR, USART_ISR_IDLE)) {
		_usart->ICR = USART_ICR_IDLECF;
		if (_rxCount > 0) {
			disableReception();
			raiseRxCompletedNotification(_rxBuffer, _rxCount, true);
			_state = State::ready;
		}
	}

	// Interrupcio 'RTO'
	//
	if (isSet(CR1, USART_CR1_RTOIE) && isSet(ISR, USART_ISR_RTOF)) {
		_usart->ICR = USART_ICR_RTOCF;
		disableReception();
		raiseRxCompletedNotification(_rxBuffer, _rxCount, true);
		_state = State::ready;
	}
}

#elif defined(EOS_PLATFORM_STM32G0)
void UARTDevice::rxInterruptService() {

	auto CR1 = _usart->CR1;
	auto ISR = _usart->ISR;

	/// Interrupcio 'RXNE'
	//
	if (eos::Bits::isSet(CR1, USART_CR1_RXNEIE_RXFNEIE) &&
		eos::Bits::isSet(ISR, USART_ISR_RXNE_RXFNE)) {
		if (_rxCount < _rxMaxCount) {
			_rxBuffer[_rxCount++] = _usart->RDR;
			if (_rxCount == _rxMaxCount) {
				disableReception();
				raiseRxCompletedNotification(_rxBuffer, _rxCount, true);
				_state = State::ready;
			}
		}
	}

	// Interrupcio 'IDLE'
	//
	if (eos::Bits::isSet(CR1, USART_CR1_IDLEIE) &&
		eos::Bits::isSet(ISR, USART_ISR_IDLE)) {
		_usart->ICR = USART_ICR_IDLECF;
		if (_rxCount > 0) {
			disableReception();
			raiseRxCompletedNotification(_rxBuffer, _rxCount, true);
			_state = State::ready;
		}
	}

	// Interrupcio 'RTO'
	//
	if (eos::Bits::isSet(CR1, USART_CR1_RTOIE) &&
		eos::Bits::isSet(ISR, USART_ISR_RTOF)) {
		_usart->ICR = USART_ICR_RTOCF;
		disableReception();
		raiseRxCompletedNotification(_rxBuffer, _rxCount, true);
		_state = State::ready;
	}
}
#else
#error "Unknown platform"
#endif // defined(EOS_PLATFORM_XXX
#endif // HTL_UART_OPTION_IRQ == 1


#if HTL_UART_OPTION_DMA == 1
/// ----------------------------------------------------------------------
/// @brief    Reb les notificacions del DMA
/// @param    sender: El dispositiu DMA que genera l'event.
/// @param    args: Parametres del event.
///
void UARTDevice::dmaNotificationEventHandler(
	htl::dma::DMADevice *sender,
	htl::dma::DMADevice::NotificationEventArgs *args) {

    switch (args->id) {

        // Transmissio complerta de tots els bytes.
        //
        case htl::dma::DMADevice::NotificationID::completed: {
            _txCount = _txMaxCount;
            _usart->ICR = USART_ICR_TCCF;
            auto a = Atomic::start();
            Bits::set(_usart->CR1, USART_CR1_TCIE);
            Atomic::end(a);
            sender->disableNotificationEvent();
            break;
        }

        // Error en la transmissio DMA.
        //
        case htl::dma::DMADevice::NotificationID::error:
            break;

        default:
        	break;
    }
}
#endif // HTL_UART_OPTION_DMA == 1


/// ----------------------------------------------------------------------
/// @brief    Genera un event de notificacio 'TxComplete'
/// @param    buffer: El buffer de dades.
/// @param    length: El nombre de bytes de dades.
/// @param    irq: true si ve d'una interrupcio.
///
void UARTDevice::raiseTxCompletedNotification(
	const uint8_t *buffer,
	uint32_t length,
	bool irq) {

	if (_notificationEventRaiser) {

		NotificationEventArgs args = {
			.id = NotificationID::txCompleted,
			.irq = irq,
			.txCompleted {
				.buffer = buffer,
				.length = length
			}
		};

		_notificationEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Genera un event de notificacio 'RxComplete'
/// @param    buffer: El buffer de dades.
/// @param    length: El nombre de bytes de dades.
/// @param    irq: true si ve d'una interrupcio.
///
void UARTDevice::raiseRxCompletedNotification(
	const uint8_t *buffer,
	uint32_t length,
	bool irq) {

	if (_notificationEventRaiser) {

		NotificationEventArgs args = {
			.id = NotificationID::rxCompleted,
			.irq = irq,
			.rxCompleted {
				.buffer = buffer,
				.length = length
			}
		};

		_notificationEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Espera que s'hagi completat la transmissio
/// @param    timeout: El temps maxim d'espera en ticks.
/// \return   True si tot es correcte, false en cas de timeout.
///
bool UARTDevice::waitTransmissionComplete(
	Ticks expireTime) {

#if defined(EOS_PLATFORM_STM32F4)
	while (!isSet(_usart->SR, USART_SR_TC)) {
#else
	while (!Bits::isSet(_usart->ISR, USART_ISR_TC)) {
#endif
		if (expireTime.hasExpiredNow())
			return false;
	}

	//usart->ICR = USART_ICR_TCCF;

	return true;
}


/// ----------------------------------------------------------------------
/// @brief    Espera que el buffer de transmissio estigui buit.
/// @param    expireTime: El limit de temps.
/// \return   True si tot es correcte, false en cas de timeout.
///
bool UARTDevice::waitTransmissionBufferEmpty(
	Ticks expireTime) {

#if defined(EOS_PLATFORM_STM32G0)
	while (!Bits::isSet(_usart->ISR, USART_ISR_TXE_TXFNF)) {
#elif defined(EOS_PLATFORM_STM32F4)
	while (!isSet(_usart->SR, USART_SR_TXE)) {
#else
	while (!isSet(_usart->ISR, USART_ISR_TXE)) {
#endif
		if (expireTime.hasExpiredNow())
			return false;
	}

	return true;
}


/// ----------------------------------------------------------------------
/// @brief    Espera que el buffer de recepcio estigui ple
/// @param    expireTime: El limit de temps.
/// \return   True si tot es correcte, false en cas de timeout.
///
bool UARTDevice::waitReceptionBufferFull(
	Ticks expireTime) {

#if defined(EOS_PLATFORM_STM32G0)
	while ((_usart->ISR & USART_ISR_RXNE_RXFNE) == 0) {
#elif defined(EOS_PLATFORM_STM32F4)
	while ((_usart->SR & USART_SR_RXNE) == 0) {
#else
	while ((_usart->ISR & USART_ISR_RXNE) == 0) {
#endif
		if (expireTime.hasExpiredNow())
			return false;
	}

	return true;
}


/// ----------------------------------------------------------------------
/// @brief    Habilita el dispositiu.
///
void UARTDevice::enable() const {

	Bits::set(_usart->CR1,
		USART_CR1_UE);  // Habilita el dispositiu
}


/// ----------------------------------------------------------------------
/// @brief    Desabilita el dispositiu.
///
void UARTDevice::disable() const {

	Bits::clear(_usart->CR1,
		USART_CR1_UE |  // Desabilita el dispositiu
		USART_CR1_TE |  // Desabilita la transmissio
		USART_CR1_RE);  // Deshabilita la recepcio
}


/// ----------------------------------------------------------------------
/// @brief    Habilita la transmissio de dades.
///
void UARTDevice::enableTransmission() const {

	auto a = Atomic::start();
	Bits::set(_usart->CR1,
		USART_CR1_TE);       // Habilita la tramsmissio
	Atomic::end(a);
}


#if HTL_UART_OPTION_IRQ == 1
/// ----------------------------------------------------------------------
/// @brief    Habilita la transmissio de dades en modus IRQ
///
#if defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
void htl::uart::UARTDevice::enableTransmissionIRQ() const {

	auto a = startAtomic();

	set(_usart->CR1,
		USART_CR1_TXEIE |          // Habilita interrupcio TXE
		USART_CR1_TE);             // Habilita la transmissio
	endAtomic(a);
}
#elif defined(EOS_PLATFORM_STM32G0)
void UARTDevice::enableTransmissionIRQ() const {

	auto a = Atomic::start();

	Bits::set(_usart->CR1,
		USART_CR1_TXEIE_TXFNFIE |  // Habilita interrupcio TXE
		USART_CR1_TE);             // Habilita la transmissio

	Atomic::end(a);
}
#else
#error "Unknown platform"
#endif // defined(EOS_PLATFORM_XXX)
#endif // HTL_UART_OPTION_IRQ == 1


#if HTL_UART_OPTION_DMA == 1
/// ----------------------------------------------------------------------
/// @brief    Habilita la transmissio de dades en modus DMA
///
void UARTDevice::enableTransmissionDMA() const {

	//TODO: Comprovar si es necesari
	_usart->ICR = USART_ICR_TCCF;  // Borra el flag TC

	auto a = Atomic::start();

	Bits::set(_usart->CR1,
    	USART_CR1_TE);            // Habilita transmissio
	Bits::set(_usart->CR3,
    	USART_CR3_DMAT);          // Habilita DMA

    Atomic::end(a);
}
#endif // HTL_UART_OPTION_DMA == 1


/// ----------------------------------------------------------------------
/// @brief    Deshabilita la transmissio
///
void UARTDevice::disableTransmission() const {

	auto a = Atomic::start();

	Bits::clear(_usart->CR1,
#if defined(EOS_PLATFORM_STM32G0)
		USART_CR1_TXEIE_TXFNFIE | // Deshabilita interrupcio TXE
#else
		USART_CR1_TXEIE |         // Deshabilita interrupcio TXE
#endif
		USART_CR1_TCIE);          // Deshabilita interrupcio TC

#if HTL_UART_OPTION_DMA == 1
	Bits::clear(_usart->CR3,
		USART_CR3_DMAT);          // Desabilita el DMA
#endif

	// TODO: Asegurar-se que l'ultim byte s'ha transmes abans de deshabilitar
	// la transmissio

	Bits::clear(_usart->CR1,
		USART_CR1_TE);            // Desabilita transmissio

	Atomic::end(a);
}


/// ----------------------------------------------------------------------
/// @brief    Habilita la recepcio.
///
void UARTDevice::enableReception() const {

#if !defined(EOS_PLATFORM_STM32F4)
	_usart->ICR = USART_ICR_RTOCF; // Borra el flag RTO
#endif

	auto a = Atomic::start();
	Bits::set(_usart->CR1,
		USART_CR1_RE);            // Habilita la recepcio
	Atomic::end(a);
}


#if HTL_UART_OPTION_IRQ == 1
/// ----------------------------------------------------------------------
/// @brief    Habilita la recepcio en modus IRQ.
/// @param    usart: Registres de hardware del dispoositiu.
///
void UARTDevice::enableReceptionIRQ() const {

#if !defined(EOS_PLATFORM_STM32F4)
	Bits::set(_usart->ICR,
		USART_ICR_RTOCF |           // Borra el flag RTO
		USART_ICR_IDLECF);          // Borra el flag IDLE
#endif

	auto a = Atomic::start();

	Bits::set(_usart->CR1,
		USART_CR1_PEIE |            // Habilita interrupcio PE
#if defined(EOS_PLATFORM_STM32G0)
		USART_CR1_RXNEIE_RXFNEIE |  // Habilita interrupcio RXNE
#else
		USART_CR1_RXNEIE |          // Habilita interrupcio RXNE
#endif
		USART_CR1_RE);              // Habilita la recepcio

	// Activa RTO si es posible, si no, activa IDLE
	// Notes:  Si RTO no esta suportat RTOEN sempre estara a zero per hardware
	//
#if defined(EOS_PLATFORM_STM32F4)
	set(_usart->CR1, USART_CR1_IDLEIE);       // Habilita interrupcio IDLE
#else
	if (_usart->CR2 & USART_CR2_RTOEN)
		Bits::set(_usart->CR1, USART_CR1_RTOIE);    // Habilita interrupcio RTO
	else
		Bits::set(_usart->CR1, USART_CR1_IDLEIE);   // Habilita interrupcio IDLE
#endif

	Atomic::end(a);
}
#endif // HTL_UART_OPTION_IRQ == 1


/// ----------------------------------------------------------------------
/// @brief    Deshabilita la recepcio.
///
void UARTDevice::disableReception() const {

	auto a = Atomic::start();

	Bits::clear(_usart->CR1,
#if defined(EOS_PLATFORM_STM32G0)
		USART_CR1_RXNEIE_RXFNEIE | // Deshabilita interrupcio RXNE
#else
		USART_CR1_RXNEIE |         // Deshabilita interrupcio RXNE
#endif
#if !defined(EOS_PLATFORM_STM32F4)
		USART_CR1_RTOIE |          // Deshabilita interrupcio RTO
#endif
		USART_CR1_IDLEIE |         // Deshabilita interrupcio IDLE
		USART_CR1_PEIE);           // Deshabilita interrupcio PE

#if HTL_UART_OPTION_DMA == 1
	Bits::clear(_usart->CR3,
		USART_CR3_DMAT);           // Desabilita el DMA
#endif

	Bits::clear(_usart->CR1,
		USART_CR1_RE);             // Deshabilita recepcio

	Atomic::end(a);
}


/// ----------------------------------------------------------------------
/// @brief    Escriu el registre de transmissio des dades.
/// @param    usart: Registres de hardware del dispositiu.
/// @param    data: Les dades a transmetre.
//
void UARTDevice::writeData(
	uint8_t data) const {

#if defined(EOS_PLATFORM_STM32F4)
	_usart->DR = data;
#else
	_usart->TDR = data;
#endif
}


/// ----------------------------------------------------------------------
/// @brief    Llegeix el registre de recepcio dades.
/// @param    usart: Registres de hardware del dispositiu.
/// \return   Les dades rebudes.
//
uint8_t UARTDevice::readData() const {

#if defined(EOS_PLATFORM_STM32F4)
	return _usart->DR;
#else
	return _usart->RDR;
#endif
}


#if (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)
/// ----------------------------------------------------------------------
/// @brief    Comprova si el fifo esta disposnible en la uart
/// \return   El resultat de l'operacio.
///
bool htl::uart::UARTDevice::isFifoAvailable() const {

	return false;
}
#endif // (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)


#if (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)
/// ----------------------------------------------------------------------
/// @brief    Comprova si el fifo esta activat
/// \return   El resultatd e l'operacio.
///
bool htl::uart::UARTDevice::isFifoEnabled() const {

	return isSet(_uart->CR1, USART_CR1_FIFOEN);
}
#endif // (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)
