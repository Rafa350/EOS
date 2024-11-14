#pragma once
#ifndef __STM32_htlUART__
#define __STM32_htlUART__


/// \file      htlUART.h
/// \author    Rafael Serrano (rsr.openware@gmail.com)
/// \brief     UART device manager.


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlDMA.h"


namespace htl {

	namespace uart {

        class UARTDevice;

        /// Identificador del dispositiu.
        ///
		enum class DeviceID {
			#ifdef HTL_UART1_EXIST
				_1,
			#endif
			#ifdef HTL_UART2_EXIST
				_2,
			#endif
			#ifdef HTL_UART3_EXIST
				_3,
			#endif
			#ifdef HTL_UART4_EXIST
				_4,
			#endif
			#ifdef HTL_UART5_EXIST
				_5,
			#endif
			#ifdef HTL_UART6_EXIST
				_6,
			#endif
			#ifdef HTL_UART7_EXIST
				_7,
			#endif
			#ifdef HTL_UART8_EXIST
				_8,
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
			#if defined(EOS_PLATFORM_STM32F4) || \
			    defined(EOS_PLATFORM_STM32F7)
				_7,
			#endif
			_8,
			_9
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
			_1200,    ///< 1200 baud.
			_2400,    ///< 2400 baud.
			_4800,    ///< 4800 baud.
			_9600,    ///< 9600 baud.
			_19200,   ///< 19200 baud.
			_38400,   ///< 38600 baud.
			_57600,   ///< 57600 baud.
			_115200,  ///< 115200 baud.
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
            #if defined(EOS_PLATFORM_STM32F4)
			pclk,
			sysclk,
			hsi,
			lse,
            #elif defined(EOS_PLATFORM_STM32F7)
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
			rxComplete, ///< Recepcio complerta.
			txComplete, ///< Transmissio complerta.
			error       ///< Error de comunicacio.
		};

		/// Parametres de la notificacio.
		///
		struct NotifyEventArgs {
		    UARTDevice * const instance;   ///< La instancia del dispositiu.
			NotifyID id;                   ///< Identificador de la notificacio.
			bool irq;                      ///< Indica si es notifica desde una interrupcio.
			union {
				struct {
					const uint8_t *buffer; ///< Dades transmeses.
					unsigned length;       ///< Nombre de bytes transmessos.
				} TxComplete;              ///< Parametres de 'TxComplete'
				struct {
					const uint8_t *buffer; ///< Dades rebudes.
					unsigned length;       ///< Nombre de bytes rebuts.
				} RxComplete;              ///< Parametres de 'RxComplete'
			};
		};

		using NotifyEventRaiser = eos::EventRaiser<NotifyID, NotifyEventArgs>;
		using INotifyEvent = eos::ICallbackP1<NotifyEventArgs&>;
		template <typename Instance_> using NotifyEvent =
		        eos::CallbackP1<Instance_, NotifyEventArgs&>;


		namespace internal {

			template <DeviceID>
			struct UARTTraits;

			template <DeviceID, PinFunction, typename>
			struct PinFunctionInfo;

		}

		enum class Results {
		    success,
		    busy,
		    timeout,
		    error
		};

		using Result = eos::SimpleResult<Results>;


		/// Clase que implementa el dispositiu de comunicacio UART.
        ///
		class UARTDevice {
			public:
                using DevDMA = htl::dma::DMADevice;

                /// Estats en que es troba el dispositiu.
                ///
				enum class State {
					reset,       ///< Creat, pero sense inicialitzar.
					ready,       ///< Inicialitzat in preparat per operar.
					transmiting, ///< Transmeten dades.
					receiving    ///< Rebent dades.
				};

			private:
				using DMANotifyEvent = htl::dma::NotifyEvent<UARTDevice>;
				using DMANotifyEventArgs = htl::dma::NotifyEventArgs;

			private:
				USART_TypeDef * const _usart;   ///< Instancia del dispositiu.
				State _state;                   ///< Estat actual.
				uint8_t *_rxBuffer;             ///< Buffer de recepcio.
				unsigned _rxCount;              ///< Contador de bytes rebuts.
				unsigned _rxMaxCount;           ///< Maxim del contador de bytes rebuts.
				const uint8_t *_txBuffer;       ///< Buffer de transmissio.
				unsigned _txCount;              ///< Contador de bytes transmesos.
				unsigned _txMaxCount;           ///< Maxim del contador de bytes rebuts.
				INotifyEvent *_notifyEvent;     ///< Event de notificacio.
				bool _notifyEventEnabled;       ///< Habilitacio del event de notificacio.
				DMANotifyEvent _dmaNotifyEvent; ///< Event de notificacio del DMA.

			private:
				UARTDevice(const UARTDevice &) = delete;
				UARTDevice & operator = (const UARTDevice &) = delete;

				void notifyTxComplete(const uint8_t *buffer, unsigned length, bool irq);
				void notifyRxComplete(const uint8_t *buffer, unsigned length, bool irq);
				void dmaNotifyEventHandler(DevDMA *devDMA, DMANotifyEventArgs &args);

				void rxInterruptService();
				void txInterruptService();

			protected:
				UARTDevice(USART_TypeDef *usart);
				void interruptService();
				virtual void activate() = 0;
				virtual void deactivate() = 0;

			public:
				Result initialize();
				Result deinitialize();

				void setProtocol(WordBits wordBits, Parity parity,
				        StopBits stopBits, Handsake handlsake);
				void setTimming(BaudMode baudMode, ClockSource clockSource,
				        uint32_t rate, OverSampling oversampling);
				void setRxTimeout(uint32_t timeout);

				void setNotifyEvent(INotifyEvent &event, bool enabled = true);

				/// Habilita l'event de notificacio.
				///
				inline void enableNotifyEvent() {
					_notifyEventEnabled = _notifyEvent != nullptr;
				}

				/// Deshabilita l'event de notificacio.
				///
				inline void disableNotifyEvent() {
					_notifyEventEnabled = false;
				}

				Result transmit(const uint8_t *buffer, unsigned length, Tick timeout);
				Result receive(uint8_t *buffer, unsigned bufferSize, Tick timeout);
				Result transmit_IRQ(const uint8_t *buffer, unsigned length);
				Result receive_IRQ(uint8_t *buffer, unsigned bufferSize);
				Result transmit_DMA(dma::DMADevice *devDMA, const uint8_t *buffer, unsigned length);
				Result receive_DMA(dma::DMADevice *devDMA, uint8_t *buffer, unsigned bufferSize);

				inline State getState() const { return _state; }
                inline bool isReady() const { return _state == State::ready; }
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
				inline static void interruptHandler() {
					_instance.interruptService();
				}

				template <typename pin_>
				inline void initPinTX() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::tx, pin_>::alt;
					pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}

				template <typename pin_>
				inline void initPinRX() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::rx, pin_>::alt;
					pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}

				template <typename pin_>
				inline void initPinCTS() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::cts, pin_>::alt;
					pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}

				template <typename pin_>
				inline void initPinRTS() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::rts, pin_>::alt;
					pin_:initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}
		};

		template <DeviceID deviceID_>
		UARTDeviceX<deviceID_> UARTDeviceX<deviceID_>::_instance;


		#ifdef HTL_UART1_EXIST
			using UARTDevice1 = UARTDeviceX<DeviceID::_1>;
		#endif
		#ifdef HTL_UART2_EXIST
			using UARTDevice2 = UARTDeviceX<DeviceID::_2>;
		#endif
		#ifdef HTL_UART3_EXIST
			using UARTDevice3 = UARTDeviceX<DeviceID::_3>;
		#endif
		#ifdef HTL_UART4_EXIST
			using UARTDevice4 = UARTDeviceX<DeviceID::_4>;
		#endif
		#ifdef HTL_UART5_EXIST
			using UARTDevice5 = UARTDeviceX<DeviceID::_5>;
		#endif
		#ifdef HTL_UART6_EXIST
			using UARTDevice6 = UARTDeviceX<DeviceID::_6>;
		#endif
		#ifdef HTL_UART7_EXIST
			using UARTDevice7 = UARTDeviceX<DeviceID::_7>;
		#endif
		#ifdef HTL_UART8_EXIST
			using UARTDevice8 = UARTDeviceX<DeviceID::_8>;
		#endif

		namespace internal {

			#ifdef HTL_UART1_EXIST
			template <>
			struct UARTTraits<DeviceID::_1> {
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
			struct UARTTraits<DeviceID::_2> {
				static constexpr uint32_t usartAddr = USART2_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_USART2EN_Pos;
				static constexpr bool supportedRxTimeout = false;
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr bool supportedRxTimeout = true;
				#else
				#error Plataforma no soportada
				#endif
			};
			#endif

			#ifdef HTL_UART3_EXIST
			template <>
			struct UARTTraits<DeviceID::_3> {
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
			struct UARTTraits<DeviceID::_4> {
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
			struct UARTTraits<DeviceID::_5> {
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
			struct UARTTraits<DeviceID::_6> {
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
			struct UARTTraits<DeviceID::_7> {
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
			struct UARTTraits<DeviceID::_8> {
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
	}
}


#if defined(EOS_PLATFORM_STM32G030)
    #include "htl/STM32/G0/G030/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32G031)
    #include "htl/STM32/G0/G031/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32G051)
    #include "htl/STM32/G0/G051/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32G071)
    #include "htl/STM32/G0/G071/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32G0B1)
    #include "htl/STM32/G0/G0B1/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32F030)
    #include "htl/STM32/F0/F030/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32F4)
    #include "htl/STM32/F4/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32F7)
    #include "htl/STM32/F7/htlUART_Pins.h"

#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlUART__
