#pragma once
#ifndef __STM32_htlUART__
#define __STM32_htlUART__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlINT.h"


// Detecta les opcions suportades
//
#if defined(EOS_PLATFORM_STM32F0)
	#define HTL_UART_7BIT_SUPPORT 0
	#define HTL_UART_LINMODE_SUPPORT 0
	#define HTL_UART_SMARTCARD_SUPPORT 0
#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	#define HTL_UART_7BIT_SUPPORT 1
	#define HTL_UART_LINMODE_SUPPORT 1
	#define HTL_UART_SMARTCARD_SUPPORT 1
#elif defined(EOS_PLATFORM_STM32G0)
	#define HTL_UART_7BIT_SUPPORT 0
	#define HTL_UART_LINMODE_SUPPORT 0
	#define HTL_UART_SMARTCARD_SUPPORT 0
#else
	#error "Unknown platform"
#endif


namespace htl {

	namespace uart {

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

		enum class FirstBit {
			lsb,
			msb
		};

		enum class Parity {
			none,
			even,
			odd
		};

		enum class WordBits {
			#if HTL_UART_7BIT_SUPPORT == 1
				_7,
			#endif
			_8
		};

		enum class StopBits {
			_0p5,
			_1,
			_1p5,
			_2
		};

		enum class BaudMode {
			_1200,
			_2400,
			_4800,
			_9600,
			_19200,
			_38400,
			_57600,
			_115200,
			div,
			rate,
			automatic
		};

		enum class Handsake {
			none,
			ctsrts
		};

		enum class ClockSource {
			pclk,
			sysclk,
			hsi,
			lse,
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

		using ITxCompletedEvent = eos::ICallbackP2<const uint8_t*, uint16_t>;
		using IRxCompletedEvent = eos::ICallbackP2<const uint8_t*, uint16_t>;

		template <typename instance_> using TxCompletedEvent = eos::CallbackP2<instance_, const uint8_t*, uint16_t>;
		template <typename instance_> using RxCompletedEvent = eos::CallbackP2<instance_, const uint8_t*, uint16_t>;

		namespace internal {

			template <DeviceID>
			struct HardwareInfo;

			template <DeviceID, PinFunction, typename>
			struct UARTPinFunctionID;
		}

		class UARTDevice {
			public:
				enum class State {
					reset,
					ready,
					transmiting,
					receiving
				};
				enum class Result {
					ok,
					error,
					busy
				};
			private:
				USART_TypeDef * const _usart;
				State _state;
				uint8_t *_rxBuffer;
				uint16_t _rxSize;
				uint16_t _rxCount;
				const uint8_t *_txBuffer;
				uint16_t _txSize;
				uint16_t _txCount;
				ITxCompletedEvent *_txCompletedEvent;
				IRxCompletedEvent *_rxCompletedEvent;
				bool _txCompletedEventEnabled;
				bool _rxCompletedEventEnabled;
			private:
				UARTDevice(const UARTDevice &) = delete;
				UARTDevice & operator = (const UARTDevice &) = delete;
			protected:
				UARTDevice(USART_TypeDef *usart);
				void interruptService();
				virtual void activate() = 0;
				virtual void deactivate() = 0;
			public:
				inline void enable() {
					_usart->CR1 |= USART_CR1_UE;
				}
				inline void disable() {
					_usart->CR1 &= ~USART_CR1_UE;
				}
				inline void enableTX() {
					ATOMIC_SET_BIT(_usart->CR1, USART_CR1_TE);
				}
				inline void enableRX() {
					ATOMIC_SET_BIT(_usart->CR1, USART_CR1_RE);
				}
				inline void disableTX() {
					ATOMIC_CLEAR_BIT(_usart->CR1, USART_CR1_TE);
				}
				inline void disableRX() {
					ATOMIC_CLEAR_BIT(_usart->CR1, USART_CR1_RE);
				}
				Result initialize();
				Result deinitialize();
				void setProtocol(WordBits wordBits, Parity parity, StopBits stopBits, Handsake handlsake);
				void setTimming(BaudMode baudMode, ClockSource clockSource, uint32_t rate, OverSampling oversampling);
				inline void setTxCompletedEvent(ITxCompletedEvent &event, bool enabled = true) {
					_txCompletedEvent = &event;
					_txCompletedEventEnabled = enabled;
				}
				inline void setRxCompletedEvent(IRxCompletedEvent &event, bool enabled = true) {
					_rxCompletedEvent = &event;
					_rxCompletedEventEnabled = enabled;
				}
				inline void enableTxCompletedEvent() {
					_txCompletedEventEnabled = true;
				}
				inline void enableRxCompletedEvent() {
					_rxCompletedEventEnabled = _rxCompletedEvent != nullptr;
				}
				inline void disableTxCompletedEvent() {
					_txCompletedEventEnabled = _txCompletedEvent != nullptr;
				}
				inline void disableRxCompletedEvent() {
					_rxCompletedEventEnabled = false;
				}
				inline bool isTxCompletedEventEnabled() const {
					return _txCompletedEventEnabled;
				}
				inline bool isRxCompletedEventEnabled() const {
					return _rxCompletedEventEnabled;
				}
				Result transmit(const uint8_t *data, uint16_t dataLength);
				Result receive(uint8_t *data, uint16_t dataSize);
				State getState() const {
					return _state;
				}
		};

		typedef UARTDevice *UARTDeviceHandler;


		template <DeviceID deviceID_>
		class UARTDeviceX final: public UARTDevice {
			private:
				using HI = internal::HardwareInfo<deviceID_>;
			private:
				static constexpr uint32_t _usartAddr = HI::usartAddr;
				static constexpr uint32_t _rccEnableAddr = HI::rccEnableAddr;
				static constexpr uint32_t _rccEnablePos = HI::rccEnablePos;
				static UARTDeviceX _device;
			public:
				static constexpr DeviceID deviceID = deviceID_;
			private:
				UARTDeviceX() :
					UARTDevice {reinterpret_cast<USART_TypeDef*>(_usartAddr)} {
				}
			protected:
				void activate() override {
					uint32_t *p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p |= 1 << _rccEnablePos;
					__DSB();
				}
				void deactivate() override{
					uint32_t *p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p &= ~(1 << _rccEnablePos);
				}
			public:
				static constexpr UARTDeviceX * getHandler() {
					return &_device;
				}
				inline static void interruptHandler() {
					getHandler()->interruptService();
				}
				template <typename pin_>
				void initPinTX() {
					gpio::PinFunctionID pinFunctionID = internal::UARTPinFunctionID<deviceID_, PinFunction::tx, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, pinFunctionID);
				}
				template <typename pin_>
				void initPinRX() {
					gpio::PinFunctionID pinFunctionID = internal::UARTPinFunctionID<deviceID_, PinFunction::rx, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, pinFunctionID);
				}
				template <typename pin_>
				void initPinCTS() {
					gpio::PinFunctionID pinFunctionID = internal::UARTPinFunctionID<deviceID_, PinFunction::cts, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, pinFunctionID);
				}
				template <typename pin_>
				void initPinRTS() {
					gpio::PinFunctionID pinFunctionID = internal::UARTPinFunctionID<deviceID_, PinFunction::rts, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, pinFunctionID);
				}
				void setRxTimeout(uint32_t lostBits) {
					if constexpr(HI::supportedRxTimeout) {
						USART_TypeDef *usart = reinterpret_cast<USART_TypeDef*>(_usartAddr);
						if (lostBits > 0) {
							usart->RTOR |= (lostBits << USART_RTOR_RTO_Pos) & USART_RTOR_RTO_Msk;
							usart->CR2 |= USART_CR2_RTOEN;
						}
						else
							usart->CR2 &= ~USART_CR2_RTOEN;
					}
				}
		};

		template <DeviceID deviceID_>
		UARTDeviceX<deviceID_> UARTDeviceX<deviceID_>::_device;


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
			using UARTDevice7 = UART_x<UARTChannel::_7>;
		#endif
		#ifdef HTL_UART8_EXIST
			using UARTDevice8 = UART_x<UARTChannel::_8>;
		#endif

		namespace internal {

			#ifdef HTL_UART1_EXIST
			template <>
			struct HardwareInfo<DeviceID::_1> {
				static constexpr uint32_t usartAddr = USART1_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
				static constexpr uint32_t rccEnablePos = RCC_APBENR2_USART1EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_UART2_EXIST
			template <>
			struct HardwareInfo<DeviceID::_2> {
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
			struct HardwareInfo<DeviceID::_3> {
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
			struct HardwareInfo<DeviceID::_4> {
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
			struct HardwareInfo<DeviceID::_5> {
				static constexpr uint32_t usartAddr = UART5_BASE;
				static constexpr INTVector vector = INTVector::uart5;
				static constexpr bool supportedRxTimeout = true;
			};
			#endif

			#ifdef HTL_UART6_EXIST
			template <>
			struct HardwareInfo<DeviceID::_6> {
				static constexpr uint32_t usartAddr = USART6_BASE;
				static constexpr INTVector vector = INTVector::uart6;
				static constexpr bool supportedRxTimeout = true;
			};
			#endif

			#ifdef HTL_UART7_EXIST
			template <>
			struct HardwareInfo<DeviceID::_7> {
				static constexpr uint32_t usartAddr = UART7_BASE;
				static constexpr INTVector vector = INTVector::uart7;
				static constexpr bool supportedRxTimeout = true;
			};
			#endif

			#ifdef HTL_UART8_EXIST
			template <>
			struct HardwareInfo<DeviceID::_8> {
				static constexpr uint32_t usartAddr = UART8_BASE;
				static constexpr INTVector vector = INTVector::uart8;
				static constexpr bool supportedRxTimeout = true;
			};
			#endif
		}
	}
}


#if defined(EOS_PLATFORM_STM32G030)
    #include "htl/STM32/G0/htlUART_AF_G030.h"
    
#elif defined(EOS_PLATFORM_STM32G031)
    #include "htl/STM32/G0/htlUART_AF_G031.h"
    
#elif defined(EOS_PLATFORM_STM32G051)
    #include "htl/STM32/G0/htlUART_AF_G051.h"

#elif defined(EOS_PLATFORM_STM32G071)
    #include "htl/STM32/G0/htlUART_AF_G071.h"

#elif defined(EOS_PLATFORM_STM32F030)
    #include "htl/STM32/F0/htlUART_AF_F030.h"
    
#elif defined(EOS_PLATFORM_STM32F4)
    #include "htl/STM32/F4/htlUART_AF_F4.h"
    
#elif defined(EOS_PLATFORM_STM32F7)
    #include "htl/STM32/F7/htlUART_AF_F7.h"
    
#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlUART__

