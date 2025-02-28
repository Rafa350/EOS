#pragma once
#ifndef __STM32_htlUART__
#define __STM32_htlUART__


/// \file      htlUART.h
/// \author    Rafael Serrano (rsr.openware@gmail.com)
/// \brief     UART device manager.


// HTL main include
//
#include "HTL/STM32/htl.h"


// Default options
//
#ifndef HTL_UART_OPTION_IRQ
    #define HTL_UART_OPTION_IRQ HTL_UART_DEFAULT_OPTION_IRQ
#endif

#ifndef HTL_UART_OPTION_DMA
    #define HTL_UART_OPTION_DMA HTL_UART_DEFAULT_OPTION_DMA
#endif


// HTL aditional includes
//
#include "HTL/STM32/htlGPIO.h"
#if HTL_UART_OPTION_DMA == 1
#include "HTL/STM32/htlDMA.h"
#endif


namespace htl {

	namespace uart {

        class UARTDevice;

        /// Identificador del dispositiu.
        ///
		enum class DeviceID {
			#ifdef HTL_UART1_EXIST
				uart1,
			#endif
			#ifdef HTL_UART2_EXIST
				uart2,
			#endif
			#ifdef HTL_UART3_EXIST
				uart3,
			#endif
			#ifdef HTL_UART4_EXIST
				uart4,
			#endif
			#ifdef HTL_UART5_EXIST
				uart5,
			#endif
			#ifdef HTL_UART6_EXIST
				uart6,
			#endif
			#ifdef HTL_UART7_EXIST
				uart7,
			#endif
			#ifdef HTL_UART8_EXIST
				uart8,
			#endif
		};

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

        /// Nombre de bits de paraula.
        ///
		enum class WordBits {
			#if defined(EOS_PLATFORM_STM32G0)
			word7,
			#endif
			word8,
			word9
		};

        /// Nombre de bits de parada.
        ///
		enum class StopBits {
			_0p5,
			_1,
			_1p5,
			_2
		};

        /// Velocitat de transmissio.
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

		enum class ClockSource {
            #if defined(EOS_PLATFORM_STM32F0) || \
			    defined(EOS_PLATFORM_STM32F4) || \
				defined(EOS_PLATFORM_STM32F7)
			pclk,
			sysclk,
			hsi,
			lse,
            #elif defined(EOS_PLATFORM_STM32G0)
			pclk,
			sysclk,
			hsi16,
			lse,
            #endif
			automatic
		};

		enum class OverSampling {
			_8,
			_16
		};

		enum class PinFunction {
			tx,
			rx,
			cts,
			rts,
			de
		};

		/// Identificador de la notificacio
		///
		enum class NotifyID {
			null,
			rxCompleted, ///< Recepcio complerta.
			txCompleted, ///< Transmissio complerta.
			error        ///< Error de comunicacio.
		};

		/// Parametres de la notificacio.
		///
		struct NotifyEventArgs {
			bool irq;                      ///< Indica si es notifica desde una interrupcio.
			union {
				struct {
					const uint8_t *buffer; ///< Dades transmeses.
					unsigned length;       ///< Nombre de bytes transmessos.
				} txCompleted;             ///< Parametres de 'TxComplete'
				struct {
					const uint8_t *buffer; ///< Dades rebudes.
					unsigned length;       ///< Nombre de bytes rebuts.
				} rxCompleted;             ///< Parametres de 'RxComplete'
			};
		};

		using NotifyEventRaiser = eos::NotifyEventRaiser<NotifyID, NotifyEventArgs>;
		using INotifyEvent = NotifyEventRaiser::IEvent;
		template <typename Instance_> using NotifyEvent = NotifyEventRaiser::Event<Instance_>;

		namespace internal {

			template <DeviceID>
			struct UARTTraits;

			template <DeviceID, PinFunction, gpio::PortID, gpio::PinID>
			struct PinFunctionInfo;

		}

        /// Clase que implementa el dispositiu de comunicacio UART.
        ///
		class UARTDevice {
			public:
#if HTL_UART_OPTION_DMA == 1
                using DevDMA = htl::dma::DMADevice;
#endif

                /// Estats en que es troba el dispositiu.
                ///
				enum class State {
					invalid,     ///< Objecte no valid.
					reset,       ///< Creat, pero sense inicialitzar.
					ready,       ///< Inicialitzat in preparat per operar.
					transmiting, ///< Transmeten dades.
					receiving    ///< Rebent dades.
				};

			private:
#if HTL_UART_OPTION_DMA == 1
				using DMANotifyEvent = htl::dma::NotifyEvent<UARTDevice>;
				using DMANotifyEventArgs = htl::dma::NotifyEventArgs;
#endif

			private:
				USART_TypeDef * const _usart;   ///< Instancia del dispositiu.
				State _state;                   ///< Estat actual.
				uint8_t *_rxBuffer;             ///< Buffer de recepcio.
				unsigned _rxCount;              ///< Contador de bytes rebuts.
				unsigned _rxMaxCount;           ///< Maxim del contador de bytes rebuts.
				const uint8_t *_txBuffer;       ///< Buffer de transmissio.
				unsigned _txCount;              ///< Contador de bytes transmesos.
				unsigned _txMaxCount;           ///< Maxim del contador de bytes rebuts.
				NotifyEventRaiser _erNotify;    ///< Event de notificacio
#if HTL_UART_OPTION_DMA == 1
				DMANotifyEvent _dmaNotifyEvent; ///< Event de notificacio del DMA.
#endif

			private:
				UARTDevice(const UARTDevice &) = delete;
				UARTDevice & operator = (const UARTDevice &) = delete;

				void notifyTxCompleted(const uint8_t *buffer, unsigned length, bool irq);
				void notifyRxCompleted(const uint8_t *buffer, unsigned length, bool irq);
#if HTL_UART_OPTION_DMA == 1
				void dmaNotifyEventHandler(DevDMA *devDMA, DMANotifyEventArgs &args);
#endif

			protected:
				UARTDevice(USART_TypeDef *usart);
#if HTL_UART_OPTION_IRQ == 1
				void interruptService();
#endif
				virtual void activate() = 0;
				virtual void deactivate() = 0;

			public:
				eos::Result initialize();
				eos::Result deinitialize();

				eos::Result setProtocol(WordBits wordBits, Parity parity,
				        StopBits stopBits, Handsake handlsake);
				eos::Result setTimming(BaudMode baudMode, ClockSource clockSource,
				        uint32_t rate, OverSampling oversampling);
				eos::Result setRxTimeout(unsigned timeout);

				inline void setNotifyEvent(INotifyEvent &event, bool enabled = true) {
					_erNotify.set(event, enabled);
				}
				inline void enableNotifyEvent() {
					_erNotify.enable();
				}
				inline void disableNotifyEvent() {
					_erNotify.disable();
				}

				eos::Result transmit(const uint8_t *buffer, unsigned length, unsigned timeout);
				eos::Result receive(uint8_t *buffer, unsigned bufferSize, unsigned timeout);

#if HTL_UART_OPTION_IRQ == 1
				eos::Result transmit_IRQ(const uint8_t *buffer, unsigned length);
				eos::Result receive_IRQ(uint8_t *buffer, unsigned bufferSize);
#endif
#if HTL_UART_OPTION_DMA == 1
				eos::Result transmit_DMA(dma::DMADevice *devDMA, const uint8_t *buffer, unsigned length);
				eos::Result receive_DMA(dma::DMADevice *devDMA, uint8_t *buffer, unsigned bufferSize);
#endif
				eos::Result abortTransmission();
				eos::Result abortReception();

				inline State getState() const { return _state; }
                inline bool isValid() const { return _state != State::invalid; }
				inline bool isReady() const { return _state == State::ready; }
				inline bool isBusy() const { return _state != State::ready; }
		};


		template <DeviceID deviceID_>
		class UARTDeviceX final: public UARTDevice {
			private:
				using UARTTraits = internal::UARTTraits<deviceID_>;

			private:
				static constexpr auto _usartAddr = UARTTraits::usartAddr;
				static constexpr auto _rccEnableAddr = UARTTraits::rccEnableAddr;
				static constexpr auto _rccEnablePos = UARTTraits::rccEnablePos;
				static UARTDeviceX _instance;

			public:
				static constexpr auto deviceID = deviceID_;
				static constexpr UARTDeviceX *pInst = &_instance;
				static constexpr UARTDeviceX &rInst = _instance;

			private:
				UARTDeviceX() :
					UARTDevice {reinterpret_cast<USART_TypeDef*>(_usartAddr)} {
				}

			protected:
				void activate() override {
					auto p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p |= 1 << _rccEnablePos;
					__DSB();
				}

				void deactivate() override {
					auto p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p &= ~(1 << _rccEnablePos);
				}

			public:
#if HTL_UART_OPTION_IRQ == 1
				inline static void interruptHandler() {
					_instance.interruptService();
				}
#endif

				template <typename pin_>
				inline void initPinTX() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::tx, pin_::portID, pin_::pinID>::value;
					pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}

				template <typename pin_>
				inline void initPinRX() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::rx, pin_::portID, pin_::pinID>::value;
					pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}

				template <typename pin_>
				inline void initPinCTS() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::cts, pin_::portID, pin_::pinID>::value;
					pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}

				template <typename pin_>
				inline void initPinRTS() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::rts, pin_::portID, pin_::pinID>::value;
					pin_:initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}
		};

		template <DeviceID deviceID_>
		UARTDeviceX<deviceID_> UARTDeviceX<deviceID_>::_instance;


		#ifdef HTL_UART1_EXIST
			using UARTDevice1 = UARTDeviceX<DeviceID::uart1>;
		#endif
		#ifdef HTL_UART2_EXIST
			using UARTDevice2 = UARTDeviceX<DeviceID::uart2>;
		#endif
		#ifdef HTL_UART3_EXIST
			using UARTDevice3 = UARTDeviceX<DeviceID::uart3>;
		#endif
		#ifdef HTL_UART4_EXIST
			using UARTDevice4 = UARTDeviceX<DeviceID::uart4>;
		#endif
		#ifdef HTL_UART5_EXIST
			using UARTDevice5 = UARTDeviceX<DeviceID::uart5>;
		#endif
		#ifdef HTL_UART6_EXIST
			using UARTDevice6 = UARTDeviceX<DeviceID::uart6>;
		#endif
		#ifdef HTL_UART7_EXIST
			using UARTDevice7 = UARTDeviceX<DeviceID::uart7>;
		#endif
		#ifdef HTL_UART8_EXIST
			using UARTDevice8 = UARTDeviceX<DeviceID::uart8>;
		#endif

#ifdef EOS_PLATFORM_STM32F4
		namespace internal {

			#ifdef HTL_UART1_EXIST
			template <>
			struct UARTTraits<DeviceID::uart1> {
				static constexpr uint32_t usartAddr = USART1_BASE;
                #if defined(EOS_PLATFORM_STM32F7)
                static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
                static constexpr uint32_t rccEnablePos = RCC_APB2ENR_USART1EN_Pos;
				#elif defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
				static constexpr uint32_t rccEnablePos = RCC_APBENR2_USART1EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_UART2_EXIST
			template <>
			struct UARTTraits<DeviceID::uart2> {
				static constexpr uint32_t usartAddr = USART2_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_USART2EN_Pos;
				static constexpr bool supportedRxTimeout = false;
				#elif defined(EOS_PLATFORM_STM32F0)
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr bool supportedRxTimeout = true;
				#else
				#error Plataforma no soportada
				#endif
			};
			#endif

			#ifdef HTL_UART3_EXIST
			template <>
			struct UARTTraits<DeviceID::uart3> {
				static constexpr uint32_t usartAddr = USART3_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_USART3EN_Pos;
				static constexpr bool supportedRxTimeout = false;
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr bool supportedRxTimeout = true;
				#else
				#error Plataforma no soportada
				#endif
			};
			#endif

			#ifdef HTL_UART4_EXIST
			template <>
			struct UARTTraits<DeviceID::uart4> {
				static constexpr uint32_t usartAddr = USART4_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_USART4EN_Pos;
				static constexpr bool supportedRxTimeout = false;
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr bool supportedRxTimeout = true;
				#else
				#error Plataforma no soportada
				#endif
			};
			#endif

			#ifdef HTL_UART5_EXIST
			template <>
			struct UARTTraits<DeviceID::uart5> {
				static constexpr uint32_t usartAddr = USART5_BASE;
				static constexpr bool supportedRxTimeout = true;
                #if defined(EOS_PLATFORM_STM32F4)
                #elif defined(EOS_PLATFORM_STM32F7)
                static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
                static constexpr uint32_t rccEnablePos = RCC_APB1ENR_UART5EN_Pos;
                #endif
			};
			#endif

			#ifdef HTL_UART6_EXIST
			template <>
			struct UARTTraits<DeviceID::uart6> {
				static constexpr uint32_t usartAddr = USART6_BASE;
				static constexpr bool supportedRxTimeout = true;
                #if defined(EOS_PLATFORM_STM32F4)
                #elif defined(EOS_PLATFORM_STM32F7)
                static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
                static constexpr uint32_t rccEnablePos = RCC_APB2ENR_USART6EN_Pos;
                #endif
			};
			#endif

			#ifdef HTL_UART7_EXIST
			template <>
			struct UARTTraits<DeviceID::uart7> {
				static constexpr USART_TypeDef *usart = UART7;
				static constexpr bool supportedRxTimeout = true;
                #if defined(EOS_PLATFORM_STM32F4)
                #elif defined(EOS_PLATFORM_STM32F7)
                static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
                static constexpr uint32_t rccEnablePos = RCC_APB1ENR_UART7EN_Pos;
                #endif
			};
			#endif

			#ifdef HTL_UART8_EXIST
			template <>
			struct UARTTraits<DeviceID::uart8> {
				static constexpr USART_TypeDef *usart = UART8;
				static constexpr bool supportedRxTimeout = true;
                #if defined(EOS_PLATFORM_STM32F4)
                #elif defined(EOS_PLATFORM_STM32F7)
                static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
                static constexpr uint32_t rccEnablePos = RCC_APB1ENR_UART8EN_Pos;
                #endif
			};
			#endif
		}
		#endif
	}
}


#if defined(EOS_PLATFORM_STM32G030)
    #include "htl/STM32/G0/htlUART_Traits.h"
    #include "htl/STM32/G0/G030/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32G031)
    #include "htl/STM32/G0/htlUART_Traits.h"
    #include "htl/STM32/G0/G031/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32G051)
    #include "htl/STM32/G0/htlUART_Traits.h"
    #include "htl/STM32/G0/G051/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32G071)
	#include "htl/STM32/G0/htlUART_Traits.h"
    #include "htl/STM32/G0/G071/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32G0B1)
    #include "htl/STM32/G0/htlUART_Traits.h"
    #include "htl/STM32/G0/G0B1/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32F030)
	#include "htl/STM32/F0/htlUART_Traits.h"
    #include "htl/STM32/F0/F030/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32F429)
	#include "htl/STM32/F4/htlUART_Traits.h"
    #include "htl/STM32/F4/F429/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32F7)
    #include "htl/STM32/F7/htlUART_Pins.h"

#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlUART__
