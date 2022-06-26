#ifndef __STM32_halTMR_ex__
#define __STM32_halTMR_ex__


// EOS includes
//
#include "HAL/hal.h"
#include "HAL/STM32/halTMR.h"


namespace eos {

	enum class TMRTimer {
		timer1,
		timer2,
		timer3,
		timer4,
		timer5,
		timer6,
		timer7,
		timer8,
		timer9,
		timer10,
		timer11,
		timer12,
		timer13,
		timer14,
	};

	enum class TMRMode: halTMROptions {
		mode16 = HAL_TMR_MODE_16,
		mode32 = HAL_TRM_MODE_32
	};

	enum class TMRDirection: halTMROptions {
		up = HAL_TMR_DIRECTION_UP,
		down = HAL_TMR_DIRECTION_DOWN
	};

	enum class TMRClkDiv: halTMROptions {
		clcDiv1 = HAL_TMR_CLKDIV_1,
		clcDiv2 = HAL_TMR_CLKDIV_2,
		clcDiv4 = HAL_TMR_CLKDIV_4
	};

	template <TMRTimer timer_>
	struct TMRModuleInfo {
		static const uint32_t baseAddr;
	};

	template <TMRTimer timer_>
	class TMRModule {
		private:
			using ModuleInfo = TMRModuleInfo<timer_>;
			constexpr static const uint32_t _baseAddr = ModuleInfo::baseAddr;

		private:
			halTMRData _data;
			halTMRHandler _handler;

		private:
			TMRModule() {
			}

			TMRModule(const TMRModule &) = delete;
			TMRModule(const TMRModule &&) = delete;
			TMRModule & operator = (const TMRModule &) = delete;
			TMRModule & operator = (const TMRModule &&) = delete;

		public:
			inline static auto & instance() {
				static TMRModule inst;
				return inst;
			}

			void initialize() {
				_handler = halTMRInitialize(&_data, settings);
			}

			void deinitialize() {
				halTMRDeinitialize(_handler);
			}
	};

	typedef TMRModule<TMRTimer::timer1> TMR_1;
	typedef TMRModule<TMRTimer::timer2> TMR_2;
	typedef TMRModule<TMRTimer::timer3> TMR_3;
	typedef TMRModule<TMRTimer::timer4> TMR_4;
	typedef TMRModule<TMRTimer::timer5> TMR_5;
	typedef TMRModule<TMRTimer::timer6> TMR_6;
	typedef TMRModule<TMRTimer::timer7> TMR_7;
	typedef TMRModule<TMRTimer::timer8> TMR_8;
	typedef TMRModule<TMRTimer::timer9> TMR_9;
	typedef TMRModule<TMRTimer::timer10> TMR_10;
	typedef TMRModule<TMRTimer::timer11> TMR_11;
	typedef TMRModule<TMRTimer::timer12> TMR_12;
	typedef TMRModule<TMRTimer::timer13> TMR_13;
	typedef TMRModule<TMRTimer::timer14> TMR_14;

	template <>
	struct TMRModuleInfo<TMRTimer::timer1> {
		static const uint32_t baseAddr = TIM1_BASE;
	};

	template <>
	struct TMRModuleInfo<TMRTimer::timer2> {
		static const uint32_t baseAddr = TIM2_BASE;
	};

	template <>
	struct TMRModuleInfo<TMRTimer::timer3> {
		static const uint32_t baseAddr = TIM3_BASE;
	};

	template <>
	struct TMRModuleInfo<TMRTimer::timer4> {
		static const uint32_t baseAddr = TIM4_BASE;
	};

	template <>
	struct TMRModuleInfo<TMRTimer::timer5> {
		static const uint32_t baseAddr = TIM5_BASE;
	};

	template <>
	struct TMRModuleInfo<TMRTimer::timer6> {
		static const uint32_t baseAddr = TIM6_BASE;
	};

	template <>
	struct TMRModuleInfo<TMRTimer::timer7> {
		static const uint32_t baseAddr = TIM7_BASE;
	};

	template <>
	struct TMRModuleInfo<TMRTimer::timer8> {
		static const uint32_t baseAddr = TIM8_BASE;
	};

	template <>
	struct TMRModuleInfo<TMRTimer::timer9> {
		static const uint32_t baseAddr = TIM9_BASE;
	};

	template <>
	struct TMRModuleInfo<TMRTimer::timer10> {
		static const uint32_t baseAddr = TIM10_BASE;
	};

	template <>
	struct TMRModuleInfo<TMRTimer::timer11> {
		static const uint32_t baseAddr = TIM11_BASE;
	};

	template <>
	struct TMRModuleInfo<TMRTimer::timer12> {
		static const uint32_t baseAddr = TIM12_BASE;
	};

	template <>
	struct TMRModuleInfo<TMRTimer::timer13> {
		static const uint32_t baseAddr = TIM13_BASE;
	};

	template <>
	struct TMRModuleInfo<TMRTimer::timer14> {
		static const uint32_t baseAddr = TIM14_BASE;
	};
}


#endif // __STM32_halTMR_ex__
