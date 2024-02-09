#pragma once
#ifndef __STM32_htlUART__
#define __STM32_htlUART__


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlDMA.h"
#include "System/eosResults.h"


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
			#if defined(EOS_PLATFORM_STM32F4) || \
			    defined(EOS_PLATFORM_STM32F7)
				_7,
			#endif
			_8,
			_9
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


		enum class NotifyID {
			null,
			rxCompleted,
			txCompleted
		};

		struct NotifyEventArgs {
			NotifyID id;
			bool irq;
			union {
				struct {
					const uint8_t *buffer;
					uint16_t length;
				} TxCompleted;
				struct {
					const uint8_t *buffer;
					uint16_t length;
				} RxCompleted;
			};
		};

		class UARTDevice;
		using INotifyEvent = eos::ICallbackP2<const UARTDevice*, const NotifyEventArgs&>;
		template <typename Instance_> using NotifyEvent = eos::CallbackP2<Instance_, const UARTDevice*, const NotifyEventArgs&>;


		namespace internal {

			template <DeviceID>
			struct HardwareInfo;

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


		class UARTDevice {
			public:
				enum class State {
					reset,
					ready,
					transmiting,
					receiving
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
				INotifyEvent *_notifyEvent;
				bool _notifyEventEnabled;

			private:
				UARTDevice(const UARTDevice &) = delete;
				UARTDevice & operator = (const UARTDevice &) = delete;
				void notifyTxCompleted(const uint8_t *buffer, uint16_t count, bool irq);
				void notifyRxCompleted(const uint8_t *buffer, uint16_t count, bool irq);

			protected:
				UARTDevice(USART_TypeDef *usart);
				void interruptService();
				virtual void activate() = 0;
				virtual void deactivate() = 0;

			public:
				inline void enable() const {
					_usart->CR1 |= USART_CR1_UE;
				}
				inline void disable() const {
					_usart->CR1 &= ~USART_CR1_UE;
				}
				Result initialize();
				Result deinitialize();

				void setProtocol(WordBits wordBits, Parity parity, StopBits stopBits, Handsake handlsake);
				void setTimming(BaudMode baudMode, ClockSource clockSource, uint32_t rate, OverSampling oversampling);
				void setRxTimeout(uint32_t timeout);

				void setNotifyEvent(INotifyEvent &event, bool enabled = true);
				inline void enableNotifyEvent() {
					_notifyEventEnabled = _notifyEvent != nullptr;
				}
				inline void disableNotifyEvent() {
					_notifyEventEnabled = false;
				}

				Result transmit(const uint8_t *buffer, uint16_t size, uint32_t timeout);
				Result receive(uint8_t *buffer, uint16_t size, uint32_t timeout);
				Result transmit_IRQ(const uint8_t *buffer, uint16_t size);
				Result receive_IRQ(uint8_t *buffer, uint16_t size);
				Result transmitDMA(dma::DMADevice *devDMA, const uint8_t *buffer, uint16_t size, uint32_t timeout = 0xFFFF);
				Result receiveDMA(dma::DMADevice *devDMA, uint8_t *buffer, uint16_t size, uint32_t timeout = 0xFFFF);
                Result transmitDMA_IRQ(dma::DMADevice *devDMA, const uint8_t *buffer, uint16_t size);
                Result receiveDMA_IRQ(dma::DMADevice *devDMA, uint8_t *buffer, uint16_t size);

				State getState() const {
					return _state;
				}
		};


		template <DeviceID deviceID_>
		class UARTDeviceX final: public UARTDevice {
			private:
				using HI = internal::HardwareInfo<deviceID_>;

			private:
				static constexpr auto _usartAddr = HI::usartAddr;
				static constexpr auto _rccEnableAddr = HI::rccEnableAddr;
				static constexpr auto _rccEnablePos = HI::rccEnablePos;
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
				void deactivate() override{
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
			struct HardwareInfo<DeviceID::_1> {
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
			struct HardwareInfo<DeviceID::_6> {
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
			struct HardwareInfo<DeviceID::_7> {
				static constexpr uint32_t usartAddr = UART7_BASE;
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
			struct HardwareInfo<DeviceID::_8> {
				static constexpr uint32_t usartAddr = UART8_BASE;
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
