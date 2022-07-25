#pragma once
#ifndef __STM32_htlTMR__
#define __STM32_htlTMR__


// EOS includes
//
#include "eos.h"


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

	enum class TMRDirection {
		up,
		down
	};

	enum class TMRClockDivider {
		div1,
		div2,
		div4
	};

	enum class TMREvent {
		update,
		trigger,
		com
	};

	using TMRInterruptParam = void*;
	using TMRInterruptFunction = void (*)(TMREvent, TMRInterruptParam);

	template <TMRTimer timer_>
	struct TMRTrait {
	};

	template <TMRTimer timer_>
	class TMR_x final {
		private:
			using Trait = TMRTrait<timer_>;
			static constexpr uint32_t _addr = Trait::addr;
			static constexpr bool _suportsClockDivider = Trait::suportsClockDivider;

		private:
			static TMRInterruptFunction _isrFunction;
			static TMRInterruptParam _isrParam;

		private:
			TMR_x() = delete;
			TMR_x(const TMR_x &) = delete;
			TMR_x(const TMR_x &&) = delete;
            ~TMR_x() = delete;
            
			TMR_x & operator = (const TMR_x &) = delete;
			TMR_x & operator = (const TMR_x &&) = delete;

			static void enableClock() {

				if constexpr(timer_ == TMRTimer::timer1)
		            RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
				if constexpr(timer_ == TMRTimer::timer2)
					RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
				if constexpr(timer_ == TMRTimer::timer3)
					RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
				if constexpr(timer_ == TMRTimer::timer4)
					RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
				if constexpr(timer_ == TMRTimer::timer5)
					RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
				if constexpr(timer_ == TMRTimer::timer6)
					RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
				if constexpr(timer_ == TMRTimer::timer7)
					RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
				if constexpr(timer_ == TMRTimer::timer8)
					RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
				if constexpr(timer_ == TMRTimer::timer9)
					RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
				if constexpr(timer_ == TMRTimer::timer10)
					RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
				if constexpr(timer_ == TMRTimer::timer11)
					RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
				if constexpr(timer_ == TMRTimer::timer12)
					RCC->APB1ENR |= RCC_APB1ENR_TIM12EN;
				if constexpr(timer_ == TMRTimer::timer13)
					RCC->APB1ENR |= RCC_APB1ENR_TIM13EN;
				if constexpr(timer_ == TMRTimer::timer14)
					RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
				__DSB();
			}

			static void disableClock() {

				if constexpr(timer_ == TMRTimer::timer1)
					RCC->APB2ENR &= ~RCC_APB2ENR_TIM1EN;
				if constexpr(timer_ == TMRTimer::timer2)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM2EN;
				if constexpr(timer_ == TMRTimer::timer3)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM3EN;
				if constexpr(timer_ == TMRTimer::timer4)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN;
				if constexpr(timer_ == TMRTimer::timer5)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM5EN;
				if constexpr(timer_ == TMRTimer::timer6)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM6EN;
				if constexpr(timer_ == TMRTimer::timer7)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM7EN;
				if constexpr(timer_ == TMRTimer::timer8)
					RCC->APB2ENR &= ~RCC_APB2ENR_TIM8EN;
				if constexpr(timer_ == TMRTimer::timer9)
					RCC->APB2ENR &= ~RCC_APB2ENR_TIM9EN;
				if constexpr(timer_ == TMRTimer::timer10)
					RCC->APB2ENR &= ~RCC_APB2ENR_TIM10EN;
				if constexpr(timer_ == TMRTimer::timer11)
					RCC->APB2ENR &= ~RCC_APB2ENR_TIM11EN;
				if constexpr(timer_ == TMRTimer::timer12)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM12EN;
				if constexpr(timer_ == TMRTimer::timer13)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM13EN;
				if constexpr(timer_ == TMRTimer::timer14)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM14EN;
			}

		public:
			/// \brief Activa el modul
			///
			static void init() {

				enableClock();
			}

			/// \brief Desactiva el modul
			///
			static void deInit() {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);
				regs->CR1 &= ~TIM_CR1_CEN;
				regs->DIER &= ~(TIM_DIER_UIE | TIM_DIER_TIE | TIM_DIER_COMIE);

				disableClock();
			}

			static constexpr void setDirection(
				TMRDirection direction) {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);
				if (direction == TMRDirection::down)
					regs->CR1 |= TIM_CR1_DIR;
				else
					regs->CR1 &= ~TIM_CR1_DIR;
			}

			static void setPeriod(
				uint32_t period) {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);
				regs->ARR = period;
			}

			static void setPrescaler(
				uint32_t prescaler) {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);
				regs->PSC = prescaler;
			}

			static constexpr void setClockDivider(
				TMRClockDivider clockDivider) {

				if constexpr (_suportsClockDivider) {
					TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);

					uint32_t temp = regs->CR1;
					temp &= ~TIM_CR1_CKD;
					switch (clockDivider) {
						case TMRClockDivider::div1:
							break;

						case TMRClockDivider::div2:
							temp |= TIM_CR1_CKD_0;
							break;

						case TMRClockDivider::div4:
							temp |= TIM_CR1_CKD_1;
							break;
					}
					regs->CR1 = temp;
				}
			}

			static void start() {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);
				regs->CR1 |= TIM_CR1_CEN;
			}

			static void stop() {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);
				regs->CR1 &= ~TIM_CR1_CEN;
			}

			static void setInterruptFunction(
				TMRInterruptFunction function,
				TMRInterruptParam param) {

				_isrFunction = function;
				_isrParam = param;
			}

			static constexpr void enableInterrupt(
				TMREvent event) {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);
				switch (event) {
					case TMREvent::update:
						regs->DIER |= TIM_DIER_UIE;
						break;

					case TMREvent::trigger:
						regs->DIER |= TIM_DIER_TIE;
						break;

					case TMREvent::com:
						regs->DIER |= TIM_DIER_COMIE;
						break;
				}
			}

			static bool disableInterrupt(
				TMREvent event) {

				bool status = false;

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);
				switch (event) {
					case TMREvent::update:
						status = (regs->DIER & TIM_DIER_UIE) != 0;
						regs->DIER &= ~TIM_DIER_UIE;
						break;

					case TMREvent::trigger:
						status = (regs->DIER & TIM_DIER_TIE) != 0;
						regs->DIER &= ~TIM_DIER_TIE;
						break;

					case TMREvent::com:
						status = (regs->DIER & TIM_DIER_COMIE) != 0;
						regs->DIER &= ~TIM_DIER_COMIE;
						break;
				}

				return status;
			}

            static bool getInterruptFlag(
            	TMREvent event) {

            	TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);
				switch (event) {
					case TMREvent::update:
						return (regs->SR & TIM_SR_UIF) != 0;

					case TMREvent::trigger:
						return (regs->SR & TIM_SR_TIF) != 0;

					case TMREvent::com:
						return (regs->SR & TIM_SR_COMIF) != 0;

					default:
						return false;
				}
            }

            static constexpr void clearInterruptFlag(
            	TMREvent event) {

            	TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);
				switch (event) {
					case TMREvent::update:
						regs->SR &= ~TIM_SR_UIF;
						break;

					case TMREvent::trigger:
						regs->SR &= ~TIM_SR_TIF;
						break;

					case TMREvent::com:
						regs->SR &= ~TIM_SR_COMIF;
						break;
				}
            }

			static void interruptHandler(
				TMREvent event) {

				if (_isrFunction != nullptr)
                    _isrFunction(event, _isrParam);
            }
	};

	template <TMRTimer timer_> TMRInterruptFunction TMR_x<timer_>::_isrFunction = nullptr;
	template <TMRTimer timer_> TMRInterruptParam TMR_x<timer_>::_isrParam = nullptr;

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
	struct TMRTrait<TMRTimer::timer1> {
		static const uint32_t addr = TIM1_BASE;
		static const bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::timer2> {
		static const uint32_t addr = TIM2_BASE;
		static const bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::timer3> {
		static const uint32_t addr = TIM3_BASE;
		static const bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::timer4> {
		static const uint32_t addr = TIM4_BASE;
		static const bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::timer5> {
		static const uint32_t addr = TIM5_BASE;
		static const bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::timer6> {
		static const uint32_t addr = TIM6_BASE;
		static const bool suportsClockDivider = false;
	};

	template <>
	struct TMRTrait<TMRTimer::timer7> {
		static const uint32_t addr = TIM7_BASE;
		static const bool suportsClockDivider = false;
	};

	template <>
	struct TMRTrait<TMRTimer::timer8> {
		static const uint32_t addr = TIM8_BASE;
		static const bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::timer9> {
		static const uint32_t addr = TIM9_BASE;
		static const bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::timer10> {
		static const uint32_t addr = TIM10_BASE;
		static const bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::timer11> {
		static const uint32_t addr = TIM11_BASE;
		static const bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::timer12> {
		static const uint32_t addr = TIM12_BASE;
		static const bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::timer13> {
		static const uint32_t addr = TIM13_BASE;
		static const bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::timer14> {
		static const uint32_t addr = TIM14_BASE;
		static const bool suportsClockDivider = true;
	};
}


#endif // __STM32_htlTMR__
