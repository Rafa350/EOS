#pragma once
#ifndef __STM32_htlTMR__
#define __STM32_htlTMR__


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"


namespace htl {

	namespace tmr {

		enum class DeviceID {
			#ifdef HTL_TMR1_EXIST
				_1,
			#endif
			#ifdef HTL_TMR2_EXIST
				_2,
			#endif
			#ifdef HTL_TMR3_EXIST
				_3,
			#endif
			#ifdef HTL_TMR4_EXIST
				_4,
			#endif
			#ifdef HTL_TMR5_EXIST
				_5,
			#endif
			#ifdef HTL_TMR6_EXIST
				_6,
			#endif
			#ifdef HTL_TMR7_EXIST
				_7,
			#endif
			#ifdef HTL_TMR8_EXIST
				_8,
			#endif
			#ifdef HTL_TMR9_EXIST
				_9,
			#endif
			#ifdef HTL_TMR10_EXIST
				_10,
			#endif
			#ifdef HTL_TMR11_EXIST
				_11,
			#endif
			#ifdef HTL_TMR12_EXIST
				_12,
			#endif
			#ifdef HTL_TMR13_EXIST
				_13,
			#endif
			#ifdef HTL_TMR14_EXIST
				_14,
			#endif
			#ifdef HTL_TMR15_EXIST
				_15,
			#endif
			#ifdef HTL_TMR16_EXIST
				_16,
			#endif
			#ifdef HTL_TMR17_EXIST
				_17,
			#endif
		};

		enum class CountDirection {
			up,
			down,
			bidi
		};

		enum class CountResolution {
			_16,
			_32
		};

		/*enum class ClockSource {
			pclk1,
			pclk2,
			pllqclk
		};*/

		enum class ClockDivider {
			_1,
			_2,
			_4
		};

		enum class Channel {
			_1,
			_2,
			_3,
			_4
		};

		enum class ChannelPolarity {
			activeHigh,
			activeLow
		};

		enum class PinFunction {
			ch1,
			ch2,
			ch3,
			ch4
		};


		enum class NotifyID {
			null,
			trigger,
			update,
			error
		};

		struct NotifyEventArgs {
			NotifyID id;
			bool isr;
			union {
				struct {
				} trigger;
				struct {
				} update;
			};
		};

		class TMRDevice;
		using INotifyEvent = eos::ICallbackP2<TMRDevice*, NotifyEventArgs&>;
		template <typename Instance_> using NotifyEvent = eos::CallbackP2<Instance_, TMRDevice*, NotifyEventArgs&>;


		namespace internal {

			template <DeviceID>
			struct HardwareInfo;
		}


		class TMRDevice {
			public:
				enum class State {
					reset,
					ready,
					busy,
					busyIRQ,
					busyDMA
				};

			private:
				TIM_TypeDef * const _tim;
				State _state;
				INotifyEvent *_notifyEvent;
				bool _notifyEventEnabled;

			private:
				TMRDevice(const TMRDevice &) = delete;
				TMRDevice & operator = (const TMRDevice &) = delete;
				void notifyTrigger();
				void notifyUpdate();

			protected:
				TMRDevice(TIM_TypeDef *tim);
				virtual void activate() = 0;
				virtual void deactivate() = 0;
				void interruptService();
				State getState() const { return _state; }

			public:
				inline eos::Result initialize(ClockDivider divider, unsigned prescaler) {
					return initialize(divider, prescaler, 0, 0);
				}
				eos::Result initialize(ClockDivider divider, unsigned prescaler, unsigned limit, unsigned repeat);
				eos::Result deinitialize();

				eos::Result setPrescaler(unsigned value);
				eos::Result setLimit(unsigned value);
				eos::Result setRepeat(unsigned value);
				eos::Result setCountDirection(CountDirection value);
				inline unsigned getCounter() const { return _tim->CNT; }

				eos::Result configurePwmChannel(Channel channel, ChannelPolarity polarity, unsigned compare);
				void enableChannel(Channel channel);
				void disableChannel(Channel channel);

				void setNotifyEvent(INotifyEvent &event, bool enabled = true);
				inline void enableNotifyEvent() {
					_notifyEventEnabled = _notifyEvent != nullptr;
				}
				inline void disableNotifyEvent() {
					_notifyEventEnabled = false;
				}
				eos::Result start();
				eos::Result start_IRQ();
				eos::Result stop();
		};

		namespace internal {

			template <DeviceID, PinFunction, typename>
			struct PinFunctionInfo;

		}

		template <DeviceID deviceID_>
		class TMRDeviceX: public TMRDevice {
			private:
				using HI = internal::HardwareInfo<deviceID_>;
				static constexpr uint32_t _timAddr = HI::timAddr;
				static constexpr uint32_t _rccAddr = HI::rccAddr;
				static constexpr uint32_t _enablePos = HI::enablePos;
				static TMRDeviceX _instance;

			public:
				static constexpr DeviceID deviceID = deviceID_;
				static constexpr TMRDeviceX *pInst = &_instance;
				static constexpr TMRDeviceX &rInst = _instance;

			private:
				TMRDeviceX() :
					TMRDevice(reinterpret_cast<TIM_TypeDef*>(_timAddr)) {
				}

			protected:
				void activate() override {
					uint32_t *p = reinterpret_cast<uint32_t*>(_rccAddr);
					*p |= 1 << _enablePos;
					__DSB();
				}
				void deactivate() override {
					uint32_t *p = reinterpret_cast<uint32_t*>(_rccAddr);
					*p &= ~(1 << _enablePos);
				}

			public:
				inline static void interruptHandler() {
					_instance.interruptService();
				}

				template <typename pin_>
				inline void initPinCH1() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::ch1, pin_>::alt;
					pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}

				template <typename pin_>
				inline void initPinCH2() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::ch2, pin_>::alt;
					pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}

				template <typename pin_>
				inline void initPinCH3() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::ch3, pin_>::alt;
					pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}

				template <typename pin_>
				inline void initPinCH4() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::ch4, pin_>::alt;
					pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}
		};

		template <DeviceID deviceID_>
		TMRDeviceX<deviceID_> TMRDeviceX<deviceID_>::_instance;


		#ifdef HTL_TMR1_EXIST
		using TMRDevice1 = TMRDeviceX<DeviceID::_1>;
		#endif
		#ifdef HTL_TMR2_EXIST
		using TMRDevice2 = TMRDeviceX<DeviceID::_2>;
		#endif
		#ifdef HTL_TMR3_EXIST
		using TMRDevice3 = TMRDeviceX<DeviceID::_3>;
		#endif
		#ifdef HTL_TMR4_EXIST
		using TMRDevice4 = TMRDeviceX<DeviceID::_4>;
		#endif
		#ifdef HTL_TMR5_EXIST
		using TMRDevice5 = TMRDeviceX<DeviceID::_5>;
		#endif
		#ifdef HTL_TMR6_EXIST
		using TMRDevice6 = TMRDeviceX<DeviceID::_6>;
		#endif
		#ifdef HTL_TMR7_EXIST
		using TMRDevice7 = TMRDeviceX<DeviceID::_7>;
		#endif
		#ifdef HTL_TMR8_EXIST
		using TMRDevice8 = TMRDeviceX<DeviceID::_8>;
		#endif
		#ifdef HTL_TMR9_EXIST
		using TMRDevice9 = TMRDeviceX<DeviceID::_9>;
		#endif
		#ifdef HTL_TMR10_EXIST
		using TMRDevice10 = TMRDeviceX<DeviceID::_10>;
		#endif
		#ifdef HTL_TMR11_EXIST
		using TMRDevice11 = TMRDeviceX<DeviceID::_11>;
		#endif
		#ifdef HTL_TMR12_EXIST
		using TMRDevice12 = TMRDeviceX<DeviceID::_12>;
		#endif
		#ifdef HTL_TMR13_EXIST
		using TMRDevice13 = TMRDeviceX<DeviceID::_13>;
		#endif
		#ifdef HTL_TMR14_EXIST
		using TMRDevice14 = TMRDeviceX<DeviceID::_14>;
		#endif
		#ifdef HTL_TMR15_EXIST
		using TMRDevice15 = TMRDeviceX<DeviceID::_15>;
		#endif
		#ifdef HTL_TMR16_EXIST
		using TMRDevice16 = TMRDeviceX<DeviceID::_16>;
		#endif
		#ifdef HTL_TMR17_EXIST
		using TMRDevice17 = TMRDeviceX<DeviceID::_17>;
		#endif


		namespace internal {

			#ifdef HTL_TMR1_EXIST
			template <>
			struct HardwareInfo<DeviceID::_1> {
				static constexpr uint32_t timAddr = TIM1_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
				static constexpr uint32_t enablePos = RCC_APBENR2_TIM1EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F0)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t enablePos = RCC_APB2ENR_TIM1EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t enablePos = RCC_APB2ENR_TIM1EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_TMR2_EXIST
			template <>
			struct HardwareInfo<DeviceID::_2> {
				static constexpr uint32_t timAddr = TIM2_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t enablePos = RCC_APBENR1_TIM2EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t enablePos = RCC_APB1ENR_TIM2EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_TMR3_EXIST
			template <>
			struct HardwareInfo<DeviceID::_3> {
				static constexpr uint32_t timAddr = TIM3_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t enablePos = RCC_APBENR1_TIM3EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F0)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t enablePos = RCC_APB1ENR_TIM3EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t enablePos = RCC_APB1ENR_TIM3EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_TMR4_EXIST
			template <>
			struct HardwareInfo<DeviceID::_4> {
				static constexpr uint32_t timAddr = TIM4_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t enablePos = RCC_APB1ENR_TIM4EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_TMR5_EXIST
			template <>
			struct HardwareInfo<DeviceID::_5> {
				static constexpr uint32_t timAddr = TIM5_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t enablePos = RCC_APB1ENR_TIM5EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_TMR6_EXIST
			template <>
			struct HardwareInfo<DeviceID::_6> {
				static constexpr uint32_t timAddr = TIM6_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t enablePos = RCC_APBENR1_TIM6EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F0)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t enablePos = RCC_APB1ENR_TIM6EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t enablePos = RCC_APB1ENR_TIM6EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_TMR7_EXIST
			template <>
			struct HardwareInfo<DeviceID::_7> {
				static constexpr uint32_t timAddr = TIM7_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t enablePos = RCC_APBENR1_TIM7EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t enablePos = RCC_APB1ENR_TIM7EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_TMR8_EXIST
			template <>
			struct HardwareInfo<DeviceID::_8> {
				static constexpr uint32_t timAddr = TIM8_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t enablePos = RCC_APB2ENR_TIM8EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_TMR9_EXIST
			template <>
			struct HardwareInfo<DeviceID::_9> {
				static constexpr uint32_t timAddr = TIM9_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t enablePos = RCC_APB2ENR_TIM9EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_TMR10_EXIST
			template <>
			struct HardwareInfo<DeviceID::_10> {
				static constexpr uint32_t timAddr = TIM10_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t enablePos = RCC_APB2ENR_TIM10EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_TMR11_EXIST
			template <>
			struct HardwareInfo<DeviceID::_11> {
				static constexpr uint32_t timAddr = TIM11_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t enablePos = RCC_APB2ENR_TIM11EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_TMR12_EXIST
			template <>
			struct HardwareInfo<DeviceID::_12> {
				static constexpr uint32_t timAddr = TIM12_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t enablePos = RCC_APB1ENR_TIM12EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_TMR13_EXIST
			template <>
			struct HardwareInfo<DeviceID::_13> {
				static constexpr uint32_t timAddr = TIM13_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t enablePos = RCC_APB1ENR_TIM13EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_TMR14_EXIST
			template <>
			struct HardwareInfo<DeviceID::_14> {
				static constexpr uint32_t timAddr = TIM14_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
				static constexpr uint32_t enablePos = RCC_APBENR2_TIM14EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F0)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t enablePos = RCC_APB1ENR_TIM14EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t enablePos = RCC_APB1ENR_TIM14EN_Pos;
				#endif
			};
			#endif
		}
	}
}

#if defined(EOS_PLATFORM_STM32G030)
    #include "htl/STM32/G0/G030/htlTMR_Pins.h"
	#include "htl/STM32/G0/htlTMR_Traits.h"

#elif defined(EOS_PLATFORM_STM32G031)
    #include "htl/STM32/G0/G031/htlTMR_Pins.h"
	#include "htl/STM32/G0/htlTMR_Traits.h"

#elif defined(EOS_PLATFORM_STM32G071)
    #include "htl/STM32/G0/G071/htlTMR_Pins.h"
	//#include "htl/STM32/G0/htlTMR_Traits.h"

#elif defined(EOS_PLATFORM_STM32G0B1)
    #include "htl/STM32/G0/G0B1/htlTMR_Pins.h"
	#include "htl/STM32/G0/htlTMR_Traits.h"

#elif defined(EOS_PLATFORM_STM32F030)
    #include "htl/STM32/F0/F030/htlTMR_Pins.h"

#elif defined(EOS_PLATFORM_STM32F4)
    #include "htl/STM32/F4/htlTMR_Pins.h"
	#include "htl/STM32/F4/htlTMR_Traits.h"

#elif defined(EOS_PLATFORM_STM32F7)
    #include "htl/STM32/F7/htlTMR_Pins.h"

#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlTMR__
