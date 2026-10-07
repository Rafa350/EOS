module;


#include "hardware.h"
#include "eosBits.h"
#include "HTL/htlGPIO.h"
#include "eosEvents.h"


export module Eos.Hardware.UART.__CLASSES;


import Eos.Configuration;
import Eos.Hardware.Clock;
import Eos.Hardware.DMA;
import Eos.Hardware.UART.__PLATFORM_TRAITS;
import Eos.System.Core.Ticks;
import Eos.Result;
import Eos.Types;


export namespace eos::hardware::uart {

	/// Clase que implementa el dispositiu de comunicacio UART.
	///
	class UARTDevice: private NonCopyableClass {
		public:
			using ClockSource = PlatformTraits::ClockSource;

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
			using WordBits = PlatformTraits::WordBits;

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

			// Mostreig den la recepcio de dades
			//
			enum class OverSampling {
				os8,
				os16
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
						const UInt8 *buffer; ///< Dades transmeses.
						UInt32 length;       ///< Nombre de bytes transmessos.
					} txCompleted;             ///< Parametres de 'TxComplete'
					struct {
						const UInt8 *buffer; ///< Dades rebudes.
						UInt32 length;       ///< Nombre de bytes rebuts.
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

			enum class ErrorCode {
				ok,
				busy,
				timeout,
				error,
				errorParam,
				errorState,
			};
			using Result = SimpleResultX<ErrorCode, ErrorCode::ok>;

		private:
			using DMANotificationEvent = dma::DMADevice::NotificationEvent<UARTDevice>;
			using DMANotificationEventArgs = dma::DMADevice::NotificationEventArgs;

		private:
			USART_TypeDef * const _usart;   ///< Instancia del dispositiu.
			State _state;                   ///< Estat actual.
			UInt8 *_rxBuffer;             ///< Buffer de recepcio.
			UInt32 _rxCount;              ///< Contador de bytes rebuts.
			UInt32 _rxMaxCount;           ///< Maxim del contador de bytes rebuts.
			const UInt8 *_txBuffer;       ///< Buffer de transmissio.
			UInt32 _txCount;              ///< Contador de bytes transmesos.
			UInt32 _txMaxCount;           ///< Maxim del contador de bytes rebuts.
			NotificationEventRaiser _notificationEventRaiser;   ///< Event de notificacio
			DMANotificationEvent _dmaNotificationEvent; ///< Event de notificacio del DMA.

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
			void enableTransmissionIRQ() const;
			void enableTransmissionDMA() const;

			void enableReception() const;
			void disableReception() const;
			void enableReceptionIRQ() const;
			void enableReceptionDMA() const;

			void writeData(UInt8 data) const;
			UInt8 readData() const;
			bool waitTransmissionComplete(Ticks expireTime);
			bool waitTransmissionBufferEmpty(Ticks expireTime);
			bool waitReceptionBufferFull(Ticks expireTime);

#if (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)
			constexpr virtual bool isFIFOAvailable() const = 0;
			bool isFIFOEnabled() const;
#endif
			constexpr virtual bool isRTOAvailable() const = 0;

			virtual clock::Clock::ClockID getUARTClock() const = 0;

			void raiseTxCompletedNotification(const UInt8 *buffer, UInt32 length, bool irq);
			void raiseRxCompletedNotification(const UInt8 *buffer, UInt32 length, bool irq);
			void dmaNotificationEventHandler(dma::DMADevice *devDMA, dma::DMADevice::NotificationEventArgs *args);

		protected:
			UARTDevice(UInt32 usartAddr);

			virtual void activateImpl() const = 0;
#if HTL_UART_OPTION_DEACTIVATE == 1
			virtual void deactivateImpl() const = 0;
#endif
#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			virtual void setClockSourceImpl(ClockSource source) const = 0;
#endif

			void interruptService();
			void txInterruptService();
			void rxInterruptService();

		public:
			Result initialize();
#if HTL_UART_OPTION_DEACTIVATE == 1
			Result deinitialize();
#endif
			Result setProtocol(WordBits wordBits, Parity parity,
					StopBits stopBits, Handsake handlsake) const;
			Result setTimming(BaudMode baudMode, UInt32 rate, OverSampling oversampling) const;
#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			Result setClockSource(ClockSource clockSource) const;
#endif
#if defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			Result setRxTimeout(unsigned timeout) const;
#endif

			void enableNotificationEvent(INotificationEvent &event) {
				_notificationEventRaiser.enable(event);
			}
			void disableNotificationEvent() {
				_notificationEventRaiser.disable();
			}

			Result transmit(const UInt8 *buffer, UInt32 length, eos::Ticks blockTime);
			Result receive(UInt8 *buffer, UInt32 bufferSize, eos::Ticks blockTime);

			Result transmit_IRQ(const UInt8 *buffer, UInt32 length);
			Result receive_IRQ(UInt8 *buffer, UInt32 bufferSize);

			Result transmit_DMA(dma::DMADevice *devDMA, const UInt8 *buffer, UInt32 length);
			Result receive_DMA(dma::DMADevice *devDMA, UInt8 *buffer, UInt32 bufferSize);

			Result abortTransmission();
			Result abortReception();

			State getState() const { return _state; }
			bool isReady() const { return _state == State::ready; }
			bool isBusy() const { return _state != State::ready; }
	};
}


using namespace eos;
using namespace eos::hardware::uart;


/// ---------------------------------------------------------------------------
/// @brief    Crida a __DSB desde aquest modul C++20
///
void DSB() {

	__DSB();
}
