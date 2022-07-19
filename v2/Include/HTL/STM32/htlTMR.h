#pragma once
#ifndef __STM32_htlTMR__
#define __STM32_htlTMR__


// EOS includes
//
#include "eos.h"
#include "HAL/STM32/halTMR.h"


namespace htl {
    
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
		mode32 = HAL_TMR_MODE_32
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

	enum class TMREvent {
		update
	};

	using TMRInterruptParam = void*;
	using TMRInterruptFunction = void (*)(TMREvent, TMRInterruptParam);

	template <TMRTimer timer_>
	struct TMRInfo {
		static const uint32_t addr;
	};

	template <TMRTimer timer_>
	class TMR_x {
		private:
			using Info = TMRInfo<timer_>;
			constexpr static const uint32_t _addr = Info::addr;

		private:
			static halTMRData _data;
			static halTMRHandler _handler;

		private:
			TMR_x() = delete;
			TMR_x(const TMR_x &) = delete;
			TMR_x(const TMR_x &&) = delete;
            ~TMR_x() = delete;
            
			TMR_x & operator = (const TMR_x &) = delete;
			TMR_x & operator = (const TMR_x &&) = delete;

		public:
			inline static void init(const halTMRSettings &settings) {
				_handler = halTMRInitialize(&_data, &settings);
			}

			inline static void deInit() {
				halTMRDeinitialize(_handler);
			}

			inline static void start() {
				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);
				regs->CR1 |= TIM_CR1_CEN;
			}

			inline static void stop() {
				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);
				regs->CR1 &= ~TIM_CR1_CEN;
			}
	};

	using TMR_1 = TMR_x<TMRTimer::timer1>;
	using TMR_2 = TMR_x<TMRTimer::timer2>;
	using TMR_3 = TMR_x<TMRTimer::timer3>;
	using TMR_4 = TMR_x<TMRTimer::timer4>;
	using TMR_5 = TMR_x<TMRTimer::timer5>;
	using TMR_6 = TMR_x<TMRTimer::timer6>;
	using TMR_7 = TMR_x<TMRTimer::timer7>;
	using TMR_8 = TMR_x<TMRTimer::timer8>;
	using TMR_9 = TMR_x<TMRTimer::timer9>;
	using TMR_10 = TMR_x<TMRTimer::timer10>;
	using TMR_11 = TMR_x<TMRTimer::timer11>;
	using TMR_12 = TMR_x<TMRTimer::timer12>;
	using TMR_13 = TMR_x<TMRTimer::timer13>;
	using TMR_14 = TMR_x<TMRTimer::timer14>;

	template <>
	struct TMRInfo<TMRTimer::timer1> {
		static const uint32_t addr = TIM1_BASE;
	};

	template <>
	struct TMRInfo<TMRTimer::timer2> {
		static const uint32_t addr = TIM2_BASE;
	};

	template <>
	struct TMRInfo<TMRTimer::timer3> {
		static const uint32_t addr = TIM3_BASE;
	};

	template <>
	struct TMRInfo<TMRTimer::timer4> {
		static const uint32_t addr = TIM4_BASE;
	};

	template <>
	struct TMRInfo<TMRTimer::timer5> {
		static const uint32_t addr = TIM5_BASE;
	};

	template <>
	struct TMRInfo<TMRTimer::timer6> {
		static const uint32_t addr = TIM6_BASE;
	};

	template <>
	struct TMRInfo<TMRTimer::timer7> {
		static const uint32_t addr = TIM7_BASE;
	};

	template <>
	struct TMRInfo<TMRTimer::timer8> {
		static const uint32_t addr = TIM8_BASE;
	};

	template <>
	struct TMRInfo<TMRTimer::timer9> {
		static const uint32_t addr = TIM9_BASE;
	};

	template <>
	struct TMRInfo<TMRTimer::timer10> {
		static const uint32_t addr = TIM10_BASE;
	};

	template <>
	struct TMRInfo<TMRTimer::timer11> {
		static const uint32_t addr = TIM11_BASE;
	};

	template <>
	struct TMRInfo<TMRTimer::timer12> {
		static const uint32_t addr = TIM12_BASE;
	};

	template <>
	struct TMRInfo<TMRTimer::timer13> {
		static const uint32_t addr = TIM13_BASE;
	};

	template <>
	struct TMRInfo<TMRTimer::timer14> {
		static const uint32_t addr = TIM14_BASE;
	};
}


#endif // __STM32_htlTMR__
