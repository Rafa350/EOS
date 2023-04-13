#pragma once
#ifndef __STM32_htlTMR__
#define __STM32_htlTMR__


// EOS includes
//
#include "HTL/htl.h"


namespace htl {
    
	enum class TMRTimer {
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
	};

	enum class TMRType {
		basic,
		general,
		advanced
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

	enum class TMRInterrupt {
		brk,
		update,
		trigger,
		com,
		cc1,
		cc2,
		cc3,
		cc4
	};

	enum class TMRFlag {
		update,
		trigger,
		com
	};

	using TMRInterruptParam = void*;
	using TMRInterruptFunction = void (*)(TMRInterruptParam);

	template <TMRTimer>
	struct TMRTrait {
	};

	template <TMRTimer timer_>
	class TMR_x final {
		private:
			using Trait = TMRTrait<timer_>;
			static constexpr uint32_t _timAddr = Trait::timAddr;
			static constexpr uint32_t _rccAddr = Trait::rccAddr;
			static constexpr uint32_t _enablePos = Trait::enablePos;

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

				uint32_t *p = reinterpret_cast<uint32_t*>(_rccAddr);
				*p |= 1 << _enablePos;
				__DSB();
			}

			inline static void deactivate() {

				uint32_t *p = reinterpret_cast<uint32_t*>(_rccAddr);
				*p &= ~(1 << _enablePos);
			}

		public:
			/// \brief Activa el modul
			///
			static void initialize() {

				activate();
			}

			/// \brief Desactiva el modul
			///
			static void deinitialize() {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_timAddr);
				regs->CR1 &= ~TIM_CR1_CEN;
				regs->DIER &= ~(TIM_DIER_UIE | TIM_DIER_TIE | TIM_DIER_COMIE);

				deactivate();
			}

			static constexpr void setDirection(
				TMRDirection direction) {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_timAddr);
				if (direction == TMRDirection::down)
					regs->CR1 |= TIM_CR1_DIR;
				else
					regs->CR1 &= ~TIM_CR1_DIR;
			}

			static void setResolution(TMRResolution) {

			}

			static void setPeriod(
				uint32_t period) {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_timAddr);
				regs->ARR = period;
			}

			static void setPrescaler(
				uint32_t prescaler) {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_timAddr);
				regs->PSC = prescaler;
			}

			/// \brief Selecciona el divisor del rellotje
			///
			static constexpr void setClockDivider(
				TMRClockDivider clockDivider) {

				if constexpr (Trait::type != TMRType::basic) {
					TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_timAddr);

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

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_timAddr);
				regs->CR1 |= TIM_CR1_CEN;
			}

			inline static void stop() {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_timAddr);
				regs->CR1 &= ~TIM_CR1_CEN;
			}

			static void setInterruptFunction(
				TMRInterruptFunction function,
				TMRInterruptParam param) {

				_isrFunction = function;
				_isrParam = param;
			}

			static constexpr void enableInterrupt(
				TMRInterrupt interrupt) {

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_timAddr);
				switch (interrupt) {
					case TMRInterrupt::update:
						regs->DIER |= TIM_DIER_UIE;
						break;

					case TMRInterrupt::trigger:
						regs->DIER |= TIM_DIER_TIE;
						break;

					case TMRInterrupt::com:
						regs->DIER |= TIM_DIER_COMIE;
						break;

					default:
						break;
				}
			}

			static constexpr bool disableInterrupt(
				TMRInterrupt interrupt) {

				bool status = false;

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_timAddr);
				switch (interrupt) {
					case TMRInterrupt::update:
						status = (regs->DIER & TIM_DIER_UIE) != 0;
						regs->DIER &= ~TIM_DIER_UIE;
						break;

					case TMRInterrupt::trigger:
						status = (regs->DIER & TIM_DIER_TIE) != 0;
						regs->DIER &= ~TIM_DIER_TIE;
						break;

					case TMRInterrupt::com:
						status = (regs->DIER & TIM_DIER_COMIE) != 0;
						regs->DIER &= ~TIM_DIER_COMIE;
						break;
				}

				return status;
			}

			static bool isInterruptEnabled(
				TMRInterrupt interrupt) {

				bool status = false;

				TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_timAddr);
				switch (interrupt) {
					case TMRInterrupt::update:
						status = (regs->DIER & TIM_DIER_UIE) != 0;
						break;

					case TMRInterrupt::trigger:
						status = (regs->DIER & TIM_DIER_TIE) != 0;
						break;

					case TMRInterrupt::com:
						status = (regs->DIER & TIM_DIER_COMIE) != 0;
						break;
				}

				return status;
			}

            static bool getFlag(
            	TMRFlag flag) {

            	TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_timAddr);
				switch (flag) {
					case TMRFlag::update:
						return (regs->SR & TIM_SR_UIF) != 0;

					case TMRFlag::trigger:
						return (regs->SR & TIM_SR_TIF) != 0;

					case TMRFlag::com:
						return (regs->SR & TIM_SR_COMIF) != 0;

					default:
						return false;
				}
            }

            static constexpr void clearFlag(
            	TMRFlag flag) {

            	TIM_TypeDef *regs = reinterpret_cast<TIM_TypeDef*>(_timAddr);
				switch (flag) {
					case TMRFlag::update:
						regs->SR &= ~TIM_SR_UIF;
						break;

					case TMRFlag::trigger:
						regs->SR &= ~TIM_SR_TIF;
						break;

					case TMRFlag::com:
						regs->SR &= ~TIM_SR_COMIF;
						break;
				}
            }

			static void interruptHandler() {

				if (_isrFunction != nullptr)
                    _isrFunction(_isrParam);
            }
	};

	template <TMRTimer timer_> TMRInterruptFunction TMR_x<timer_>::_isrFunction = nullptr;
	template <TMRTimer timer_> TMRInterruptParam TMR_x<timer_>::_isrParam = nullptr;


	#ifdef HTL_TMR1_EXIST
		using TMR_1 = TMR_x<TMRTimer::_1>;
	#endif
	#ifdef HTL_TMR2_EXIST
		using TMR_2 = TMR_x<TMRTimer::_2>;
	#endif
	#ifdef HTL_TMR3_EXIST
		using TMR_3 = TMR_x<TMRTimer::_3>;
	#endif
	#ifdef HTL_TMR4_EXIST
		using TMR_4 = TMR_x<TMRTimer::_4>;
	#endif
	#ifdef HTL_TMR5_EXIST
		using TMR_5 = TMR_x<TMRTimer::_5>;
	#endif
	#ifdef HTL_TMR6_EXIST
		using TMR_6 = TMR_x<TMRTimer::_6>;
	#endif
	#ifdef HTL_TMR7_EXIST
		using TMR_7 = TMR_x<TMRTimer::_7>;
	#endif
	#ifdef HTL_TMR8_EXIST
		using TMR_8 = TMR_x<TMRTimer::_8>;
	#endif
	#ifdef HTL_TMR9_EXIST
		using TMR_9 = TMR_x<TMRTimer::_9>;
	#endif
	#ifdef HTL_TMR10_EXIST
		using TMR_10 = TMR_x<TMRTimer::_10>;
	#endif
	#ifdef HTL_TMR11_EXIST
		using TMR_11 = TMR_x<TMRTimer::_11>;
	#endif
	#ifdef HTL_TMR12_EXIST
		using TMR_12 = TMR_x<TMRTimer::_12>;
	#endif
	#ifdef HTL_TMR13_EXIST
		using TMR_13 = TMR_x<TMRTimer::_13>;
	#endif
	#ifdef HTL_TMR14_EXIST
		using TMR_14 = TMR_x<TMRTimer::_14>;
	#endif

#ifdef HTL_TMR1_EXIST
	template <>
	struct TMRTrait<TMRTimer::_1> {
		static constexpr uint32_t timAddr = TIM1_BASE;
		static constexpr TMRType type = TMRType::advanced;
		#if defined(EOS_PLATFORM_STM32F0)
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
	struct TMRTrait<TMRTimer::_2> {
		static constexpr uint32_t timAddr = TIM2_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
			static constexpr uint32_t enablePos = RCC_APB1ENR_TIM2EN_Pos;
		#endif
	};
#endif

#ifdef HTL_TMR3_EXIST
	template <>
	struct TMRTrait<TMRTimer::_3> {
		static constexpr uint32_t timAddr = TIM3_BASE;
		#if defined(EOS_PLATFORM_STM32F0)
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
	struct TMRTrait<TMRTimer::_4> {
		static constexpr uint32_t timAddr = TIM4_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
			static constexpr uint32_t enablePos = RCC_APB1ENR_TIM4EN_Pos;
		#endif
	};
#endif

#ifdef HTL_TMR5_EXIST
	template <>
	struct TMRTrait<TMRTimer::_5> {
		static constexpr uint32_t timAddr = TIM5_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
			static constexpr uint32_t enablePos = RCC_APB1ENR_TIM5EN_Pos;
		#endif
	};
#endif

#ifdef HTL_TMR6_EXIST
	template <>
	struct TMRTrait<TMRTimer::_6> {
		static constexpr uint32_t timAddr = TIM6_BASE;
		static constexpr TMRType type = TMRType::basic;
		#if defined(EOS_PLATFORM_STM32F0)
			static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
			static constexpr uint32_t enablePos = RCC_APB1ENR_TIM6EN_Pos;
		#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
			static constexpr uint32_t enablePos = RCC_APB1ENR_TIM6EN_Pos;
		#endif
	};
#endif

#ifdef HTL_TMR7_EXIST7
	template <>
	struct TMRTrait<TMRTimer::_7> {
		static constexpr uint32_t timAddr = TIM7_BASE;
		static constexpr TMRType type = TMRType::basic;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
			static constexpr uint32_t enablePos = RCC_APB1ENR_TIM7EN_Pos;
		#endif
	};
#endif

#ifdef HTL_TMR8_EXIST
	template <>
	struct TMRTrait<TMRTimer::_8> {
		static constexpr uint32_t timAddr = TIM8_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
			static constexpr uint32_t enablePos = RCC_APB2ENR_TIM8EN_Pos;
		#endif
	};
#endif

#ifdef HTL_TMR9_EXIST
	template <>
	struct TMRTrait<TMRTimer::_9> {
		static constexpr uint32_t timAddr = TIM9_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
			static constexpr uint32_t enablePos = RCC_APB2ENR_TIM9EN_Pos;
		#endif
	};
#endif

#ifdef HTL_TMR10_EXIST
	template <>
	struct TMRTrait<TMRTimer::_10> {
		static constexpr uint32_t timAddr = TIM10_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
			static constexpr uint32_t enablePos = RCC_APB2ENR_TIM10EN_Pos;
		#endif
	};
#endif

#ifdef HTL_TMR11_EXIST
	template <>
	struct TMRTrait<TMRTimer::_11> {
		static constexpr uint32_t timAddr = TIM11_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
			static constexpr uint32_t enablePos = RCC_APB2ENR_TIM11EN_Pos;
		#endif
	};
#endif

#ifdef HTL_TMR12_EXIST
	template <>
	struct TMRTrait<TMRTimer::_12> {
		static constexpr uint32_t timAddr = TIM12_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
			static constexpr uint32_t enablePos = RCC_APB1ENR_TIM12EN_Pos;
		#endif
	};
#endif

#ifdef HTL_TMR13_EXIST
	template <>
	struct TMRTrait<TMRTimer::_13> {
		static constexpr uint32_t timAddr = TIM13_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
			static constexpr uint32_t enablePos = RCC_APB1ENR_TIM13EN_Pos;
		#endif
	};
#endif

#ifdef HTL_TMR14_EXIST
	template <>
	struct TMRTrait<TMRTimer::_14> {
		static constexpr uint32_t timAddr = TIM14_BASE;
		static constexpr TMRType type = TMRType::general;
		#if defined(EOS_PLATFORM_STM32F0)
			static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
			static constexpr uint32_t enablePos = RCC_APB1ENR_TIM14EN_Pos;
		#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
			static constexpr uint32_t enablePos = RCC_APB1ENR_TIM14EN_Pos;
		#endif
	};
#endif

}


#endif // __STM32_htlTMR__
