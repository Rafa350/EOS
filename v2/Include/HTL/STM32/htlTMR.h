#pragma once
#ifndef __STM32_htlTMR__
#define __STM32_htlTMR__


// EOS includes
//
#include "HTL/htl.h"


namespace htl {
    
	enum class TMRTimer {
		_1,
		_2,
		_3,
		_4,
		_5,
		_6,
		_7,
		_8,
		_9,
		_10,
		_11,
		_12,
		_13,
		_14,
	};

	enum class TMRDirection {
		up,
		down
	};

	enum class TMRResolution {
        _16,
        _32
    };

	enum class TMRClockDivider {
		_1,
		_2,
		_4
	};

	enum class TMREvent {
		update,
		trigger,
		com
	};

	using TMRInterruptParam = void*;
	using TMRInterruptFunction = void (*)(TMREvent, TMRInterruptParam);

	template <TMRTimer>
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

			inline static void activate() {

				if constexpr(timer_ == TMRTimer::_1)
		            RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
				if constexpr(timer_ == TMRTimer::_2)
					RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
				if constexpr(timer_ == TMRTimer::_3)
					RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
				if constexpr(timer_ == TMRTimer::_4)
					RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
				if constexpr(timer_ == TMRTimer::_5)
					RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
				if constexpr(timer_ == TMRTimer::_6)
					RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
				if constexpr(timer_ == TMRTimer::_7)
					RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
				if constexpr(timer_ == TMRTimer::_8)
					RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
				if constexpr(timer_ == TMRTimer::_9)
					RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
				if constexpr(timer_ == TMRTimer::_10)
					RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
				if constexpr(timer_ == TMRTimer::_11)
					RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
				if constexpr(timer_ == TMRTimer::_12)
					RCC->APB1ENR |= RCC_APB1ENR_TIM12EN;
				if constexpr(timer_ == TMRTimer::_13)
					RCC->APB1ENR |= RCC_APB1ENR_TIM13EN;
				if constexpr(timer_ == TMRTimer::_14)
					RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
				__DSB();
			}

			inline static void deactivate() {

				if constexpr(timer_ == TMRTimer::_1)
					RCC->APB2ENR &= ~RCC_APB2ENR_TIM1EN;
				if constexpr(timer_ == TMRTimer::_2)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM2EN;
				if constexpr(timer_ == TMRTimer::_3)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM3EN;
				if constexpr(timer_ == TMRTimer::_4)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN;
				if constexpr(timer_ == TMRTimer::_5)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM5EN;
				if constexpr(timer_ == TMRTimer::_6)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM6EN;
				if constexpr(timer_ == TMRTimer::_7)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM7EN;
				if constexpr(timer_ == TMRTimer::_8)
					RCC->APB2ENR &= ~RCC_APB2ENR_TIM8EN;
				if constexpr(timer_ == TMRTimer::_9)
					RCC->APB2ENR &= ~RCC_APB2ENR_TIM9EN;
				if constexpr(timer_ == TMRTimer::_10)
					RCC->APB2ENR &= ~RCC_APB2ENR_TIM10EN;
				if constexpr(timer_ == TMRTimer::_11)
					RCC->APB2ENR &= ~RCC_APB2ENR_TIM11EN;
				if constexpr(timer_ == TMRTimer::_12)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM12EN;
				if constexpr(timer_ == TMRTimer::_13)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM13EN;
				if constexpr(timer_ == TMRTimer::_14)
					RCC->APB1ENR &= ~RCC_APB1ENR_TIM14EN;
			}

		public:
			/// \brief Activa el modul
			///
			static void init() {

				activate();
			}

			/// \brief Desactiva el modul
			///
			static void deInit() {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);
				regs->CR1 &= ~TIM_CR1_CEN;
				regs->DIER &= ~(TIM_DIER_UIE | TIM_DIER_TIE | TIM_DIER_COMIE);

				deactivate();
			}

			static constexpr void setDirection(
				TMRDirection direction) {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);
				if (direction == TMRDirection::down)
					regs->CR1 |= TIM_CR1_DIR;
				else
					regs->CR1 &= ~TIM_CR1_DIR;
			}

			static void setResolution(TMRResolution) {

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
						case TMRClockDivider::_1:
							break;

						case TMRClockDivider::_2:
							temp |= TIM_CR1_CKD_0;
							break;

						case TMRClockDivider::_4:
							temp |= TIM_CR1_CKD_1;
							break;
					}
					regs->CR1 = temp;
				}
			}

			inline static void start() {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_addr);
				regs->CR1 |= TIM_CR1_CEN;
			}

			inline static void stop() {

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

			static constexpr bool disableInterrupt(
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

	using TMR_1 = TMR_x<TMRTimer::_1>;
	using TMR_2 = TMR_x<TMRTimer::_2>;
	using TMR_3 = TMR_x<TMRTimer::_3>;
	using TMR_4 = TMR_x<TMRTimer::_4>;
	using TMR_5 = TMR_x<TMRTimer::_5>;
	using TMR_6 = TMR_x<TMRTimer::_6>;
	using TMR_7 = TMR_x<TMRTimer::_7>;
	using TMR_8 = TMR_x<TMRTimer::_8>;
	using TMR_9 = TMR_x<TMRTimer::_9>;
	using TMR_10 = TMR_x<TMRTimer::_10>;
	using TMR_11 = TMR_x<TMRTimer::_11>;
	using TMR_12 = TMR_x<TMRTimer::_12>;
	using TMR_13 = TMR_x<TMRTimer::_13>;
	using TMR_14 = TMR_x<TMRTimer::_14>;

	template <>
	struct TMRTrait<TMRTimer::_1> {
		static constexpr uint32_t addr = TIM1_BASE;
		static constexpr bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::_2> {
		static constexpr uint32_t addr = TIM2_BASE;
		static constexpr bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::_3> {
		static constexpr uint32_t addr = TIM3_BASE;
		static constexpr bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::_4> {
		static constexpr uint32_t addr = TIM4_BASE;
		static constexpr bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::_5> {
		static constexpr uint32_t addr = TIM5_BASE;
		static constexpr bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::_6> {
		static constexpr uint32_t addr = TIM6_BASE;
		static constexpr bool suportsClockDivider = false;
	};

	template <>
	struct TMRTrait<TMRTimer::_7> {
		static constexpr uint32_t addr = TIM7_BASE;
		static constexpr bool suportsClockDivider = false;
	};

	template <>
	struct TMRTrait<TMRTimer::_8> {
		static constexpr uint32_t addr = TIM8_BASE;
		static constexpr bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::_9> {
		static constexpr uint32_t addr = TIM9_BASE;
		static constexpr bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::_10> {
		static constexpr uint32_t addr = TIM10_BASE;
		static constexpr bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::_11> {
		static constexpr uint32_t addr = TIM11_BASE;
		static constexpr bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::_12> {
		static constexpr uint32_t addr = TIM12_BASE;
		static constexpr bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::_13> {
		static constexpr uint32_t addr = TIM13_BASE;
		static constexpr bool suportsClockDivider = true;
	};

	template <>
	struct TMRTrait<TMRTimer::_14> {
		static constexpr uint32_t addr = TIM14_BASE;
		static constexpr bool suportsClockDivider = true;
	};
}


#endif // __STM32_htlTMR__
