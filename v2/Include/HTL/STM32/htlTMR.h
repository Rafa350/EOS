#pragma once
#ifndef __STM32_htlTMR__
#define __STM32_htlTMR__


// EOS includes
//
#include "HTL/htl.h"


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
			down
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


		enum class NotifyID {
			null,
			trigger,
			update
		};

		struct NotifyEventArgs {
			NotifyID id;
			bool isr;
			union {
				struct {
				} Trigger;
				struct {
				} Update;
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
					busy
				};
				enum class Result {
					ok,
					error,
					busy
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
			public:
				Result initBase(ClockDivider clkDiv, uint32_t prescaler, uint32_t period, uint32_t repeat = 0);
				Result initPWM(ClockDivider clkDiv, uint32_t prescaler, uint32_t period, uint32_t duty);
				Result deinitialize();
				void setPeriod(uint32_t period, bool immediate = false);
				void setNotifyEvent(INotifyEvent &event, bool enabled = true);
				inline void enableNotifyEvent() {
					_notifyEventEnabled = _notifyEvent != nullptr;
				}
				inline void disableNotifyEvent() {
					_notifyEventEnabled = false;
				}
				Result start();
				Result startInterrupt();
				Result stop();
				Result stopInterrupt();
		};

		typedef TMRDevice *TMRDeviceHandler;


		template <DeviceID deviceID_>
		class TMRDeviceX final: public TMRDevice {
			private:
				using HI = internal::HardwareInfo<deviceID_>;
				static constexpr uint32_t _timAddr = HI::timAddr;
				static constexpr uint32_t _rccAddr = HI::rccAddr;
				static constexpr uint32_t _enablePos = HI::enablePos;
				static TMRDeviceX _instance;
			public:
				static constexpr DeviceID deviceID = deviceID_;
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
				static constexpr TMRDeviceX * getHandler() {
					return &_instance;
				}
				inline static void interruptHandler() {
					getHandler()->interruptService();
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


#endif // __STM32_htlTMR__
