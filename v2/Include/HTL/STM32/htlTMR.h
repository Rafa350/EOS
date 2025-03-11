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
			tmr1,
#endif
#ifdef HTL_TMR2_EXIST
			tmr2,
#endif
#ifdef HTL_TMR3_EXIST
			tmr3,
#endif
#ifdef HTL_TMR4_EXIST
			tmr4,
#endif
#ifdef HTL_TMR5_EXIST
			tmr5,
#endif
#ifdef HTL_TMR6_EXIST
			tmr6,
#endif
#ifdef HTL_TMR7_EXIST
			tmr7,
#endif
#ifdef HTL_TMR8_EXIST
			tmr8,
#endif
#ifdef HTL_TMR9_EXIST
			tmr9,
#endif
#ifdef HTL_TMR10_EXIST
			tmr10,
#endif
#ifdef HTL_TMR11_EXIST
			tmr11,
#endif
#ifdef HTL_TMR12_EXIST
			tmr12,
#endif
#ifdef HTL_TMR13_EXIST
			tmr13,
#endif
#ifdef HTL_TMR14_EXIST
			tmr14,
#endif
#ifdef HTL_TMR15_EXIST
			tmr15,
#endif
#ifdef HTL_TMR16_EXIST
			tmr16,
#endif
#ifdef HTL_TMR17_EXIST
			tmr17,
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
			ch1,
			ch2,
			ch3,
			ch4
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
			bool isr;
			union {
				struct {
				} trigger;
				struct {
				} update;
			};
		};

		using NotifyEventRaiser = eos::NotifyEventRaiser<NotifyID, NotifyEventArgs>;
		using INotifyEvent = NotifyEventRaiser::IEvent;
		template <typename Instance_> using NotifyEvent = NotifyEventRaiser::Event<Instance_>;

		namespace internal {

			template <DeviceID>
			struct TMRTraits;
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
				NotifyEventRaiser _erNotify;

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
				eos::Result initialize(ClockDivider divider, unsigned prescaler, unsigned reload, unsigned repeat);
				eos::Result deinitialize();

				eos::Result setPrescaler(unsigned value);
				eos::Result setLimit(unsigned value);
				eos::Result setRepeat(unsigned value);
				eos::Result setCountDirection(CountDirection value);
				inline unsigned getCounter() const { return _tim->CNT; }

				eos::Result configurePwmChannel(Channel channel, ChannelPolarity, unsigned compare);
				eos::Result configurePwmChannel1(ChannelPolarity polarity, unsigned compare);
				eos::Result configurePwmChannel2(ChannelPolarity polarity, unsigned compare);
				eos::Result configurePwmChannel3(ChannelPolarity polarity, unsigned compare);
				eos::Result configurePwmChannel4(ChannelPolarity polarity, unsigned compare);

				void enableChannel(Channel channel);
				void disableChannel(Channel channel);

				inline void setNotifyEvent(INotifyEvent &event, bool enabled = true) {
					_erNotify.set(event, enabled);
				}
				inline void enableNotifyEvent() {
					_erNotify.enable();
				}
				inline void disableNotifyEvent() {
					_erNotify.disable();
				}
				eos::Result start();
				eos::Result start_IRQ();
				eos::Result stop();
		};

		namespace internal {

			template <DeviceID, PinFunction, htl::gpio::PortID, htl::gpio::PinID>
			struct PinFunctionInfo;

		}

		template <DeviceID deviceID_>
		class TMRDeviceX: public TMRDevice {
			private:
				using HI = internal::TMRTraits<deviceID_>;
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
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::ch1, pin_::portID, pin_::pinID>::value;
					pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}

				template <typename pin_>
				inline void initPinCH2() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::ch2, pin_::portID, pin_::pinID>::value;
					pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}

				template <typename pin_>
				inline void initPinCH3() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::ch3, pin_::portID, pin_::pinID>::value;
					pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}

				template <typename pin_>
				inline void initPinCH4() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::ch4, pin_::portID, pin_::pinID>::value;
					pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}
		};

		template <DeviceID deviceID_>
		TMRDeviceX<deviceID_> TMRDeviceX<deviceID_>::_instance;


#ifdef HTL_TMR1_EXIST
		using TMRDevice1 = TMRDeviceX<DeviceID::tmr1>;
#endif
#ifdef HTL_TMR2_EXIST
		using TMRDevice2 = TMRDeviceX<DeviceID::tmr2>;
#endif
#ifdef HTL_TMR3_EXIST
		using TMRDevice3 = TMRDeviceX<DeviceID::tmr3>;
#endif
#ifdef HTL_TMR4_EXIST
		using TMRDevice4 = TMRDeviceX<DeviceID::tmr4>;
#endif
#ifdef HTL_TMR5_EXIST
		using TMRDevice5 = TMRDeviceX<DeviceID::tmr5>;
#endif
#ifdef HTL_TMR6_EXIST
		using TMRDevice6 = TMRDeviceX<DeviceID::tmr6>;
#endif
#ifdef HTL_TMR7_EXIST
		using TMRDevice7 = TMRDeviceX<DeviceID::tmr7>;
#endif
#ifdef HTL_TMR8_EXIST
		using TMRDevice8 = TMRDeviceX<DeviceID::tmr8>;
#endif
#ifdef HTL_TMR9_EXIST
		using TMRDevice9 = TMRDeviceX<DeviceID::tmr9>;
#endif
#ifdef HTL_TMR10_EXIST
		using TMRDevice10 = TMRDeviceX<DeviceID::tmr10>;
#endif
#ifdef HTL_TMR11_EXIST
		using TMRDevice11 = TMRDeviceX<DeviceID::tmr11>;
#endif
#ifdef HTL_TMR12_EXIST
		using TMRDevice12 = TMRDeviceX<DeviceID::tmr12>;
#endif
#ifdef HTL_TMR13_EXIST
		using TMRDevice13 = TMRDeviceX<DeviceID::tmr13>;
#endif
#ifdef HTL_TMR14_EXIST
		using TMRDevice14 = TMRDeviceX<DeviceID::tmr14>;
#endif
#ifdef HTL_TMR15_EXIST
		using TMRDevice15 = TMRDeviceX<DeviceID::tmr15>;
#endif
#ifdef HTL_TMR16_EXIST
		using TMRDevice16 = TMRDeviceX<DeviceID::tmr16>;
#endif
#ifdef HTL_TMR17_EXIST
		using TMRDevice17 = TMRDeviceX<DeviceID::tmr17>;
#endif

	}
}


#if defined(EOS_PLATFORM_STM32G030)
	#include "htl/STM32/G0/htlTMR_Traits.h"
    #include "htl/STM32/G0/G030/htlTMR_Pins.h"

#elif defined(EOS_PLATFORM_STM32G031)
	#include "htl/STM32/G0/htlTMR_Traits.h"
    #include "htl/STM32/G0/G031/htlTMR_Pins.h"

#elif defined(EOS_PLATFORM_STM32G071)
	#include "htl/STM32/G0/htlTMR_Traits.h"
    #include "htl/STM32/G0/G071/htlTMR_Pins.h"

#elif defined(EOS_PLATFORM_STM32G0B1)
	#include "htl/STM32/G0/htlTMR_Traits.h"
    #include "htl/STM32/G0/G0B1/htlTMR_Pins.h"

#elif defined(EOS_PLATFORM_STM32F030)
	#include "htl/STM32/F0/htlTMR_Traits.h"
    #include "htl/STM32/F0/F030/htlTMR_Pins.h"

#elif defined(EOS_PLATFORM_STM32F429)
	#include "htl/STM32/F4/htlTMR_Traits.h"
    #include "htl/STM32/F4/F429/htlTMR_Pins.h"

#elif defined(EOS_PLATFORM_STM32F746)
	#include "htl/STM32/F7/htlTMR_Traits.h"
    #include "htl/STM32/F7/F746/htlTMR_Pins.h"

#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlTMR__
