#pragma once
#ifndef __STM32_htlEXTI__
#define __STM32_htlEXTI__


// EOS includes
//
#include "eos.h"


namespace htl {

	enum class EXTILine {
		line0,
		line1,
		line2,
		line3,
		line4,
		line5,
		line6,
		line7,
		line8,
		line9,
		line10,
		line11,
		line12,
		line13,
		line14,
		line15
	};

	enum class EXTIPort {
		portA,
		portB,
		portC,
		portD,
		portE,
		portF,
		portG,
		portH,
		portI,
		portJ,
		portK
	};

	enum class EXTIMode {
		none,
		interrupt,
		event,
		all
	};

	enum class EXTITrigger {
		rissing,
		falling,
		all
	};

	enum class EXTIEvent {
		unknown,
		change
	};

    using EXTIInterruptParam = void*;
    using EXTIInterruptFunction =  void (*)(EXTIEvent event, EXTIInterruptParam);

    void EXTI_init(EXTILine, EXTIPort, EXTIMode, EXTITrigger);

	template <EXTILine line_>
	class EXTI_x final {

        private:
            static EXTIInterruptFunction _isrFunction;
            static EXTIInterruptParam _isrParam;

			EXTI_x() = default;
			EXTI_x(const EXTI_x &) = delete;
			EXTI_x(const EXTI_x &&) = delete;
			~EXTI_x() = delete;

			EXTI_x & operator = (const EXTI_x &) = delete;
			EXTI_x & operator = (const EXTI_x &&) = delete;

			static void enableClock() {

				RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
			    __DSB();
			}

			static void disableClock() {

				RCC->APB2ENR &= ~RCC_APB2ENR_SYSCFGEN;
			}

		public:
			static void init(
				EXTIPort port,
				EXTIMode mode,
				EXTITrigger trigger) {

				enableClock();
				//EXTI_init(line_, port, mode, trigger);

				// Configura el port a explorar
				//
				uint32_t temp = SYSCFG->EXTICR[uint32_t(line_) >> 2];
				temp &= ~(0xF << (4 * (uint32_t(line_) & 0x03)));
				temp |= (uint32_t(port) & 0xF) << (4 * (uint32_t(line_) & 0x03));
				SYSCFG->EXTICR[uint32_t(line_) >> 2] = temp;

				// Configura el registre IMR (Interrupt Mask Register);
				//
			    if ((mode == EXTIMode::interrupt) || (mode == EXTIMode::all))
			    	EXTI->IMR |= 1 << uint32_t(line_);
			    else
			    	EXTI->IMR &= ~(1 << uint32_t(line_));

				// Configura el registre EMR (Event Mask Register);
				//
			    if ((mode == EXTIMode::event) || (mode == EXTIMode::all))
			    	EXTI->EMR |= 1 << uint32_t(line_);
			    else
			    	EXTI->EMR &= ~(1 << uint32_t(line_));

				// Configura el registre RTSR (Rising Trigger Selection Register)
				//
				if ((trigger == EXTITrigger::rissing) || (trigger == EXTITrigger::all))
					EXTI->RTSR |= 1 << uint32_t(line_);
				else
					EXTI->RTSR &= ~(1 << uint32_t(line_));

				// Configura el registre FTSR (Falling Trigger Selection Register)
				//
				if ((trigger == EXTITrigger::falling) || (trigger == EXTITrigger::all))
					EXTI->FTSR |= 1 << uint32_t(line_);
				else
					EXTI->FTSR &= ~(1 << uint32_t(line_));
			}

			static void deInit() {

				disableClock();
			}

			static void setInterruptFunction(
				EXTIInterruptFunction function,
				EXTIInterruptParam param = nullptr) {

				_isrFunction = function;
                _isrParam = param;
            }

			static void enableInterrupt() {

				EXTI->IMR |= 1 << uint32_t(line_);
			}

			static bool disableInterrupt() {

				bool state = (EXTI->IMR & (1 << uint32_t(line_))) != 0;
				EXTI->IMR &= ~(1 << uint32_t(line_));
				return state;
			}

            inline static bool getInterruptFlag() {

                return (EXTI->PR & (1 << uint32_t(line_))) != 0;
            }

            inline static void clearInterruptFlag() {

                EXTI->PR &= ~(1 << uint32_t(line_));
            }

			inline static void interruptHandler(
				EXTIEvent event) {

				if (_isrFunction != nullptr)
                    _isrFunction(event, _isrParam);
            }
	};

    template <EXTILine line_> EXTIInterruptFunction EXTI_x<line_>::_isrFunction = nullptr;
    template <EXTILine line_> EXTIInterruptParam EXTI_x<line_>::_isrParam = nullptr;

	using EXTI_0 = EXTI_x<EXTILine::line0>;
	using EXTI_1 = EXTI_x<EXTILine::line1>;
	using EXTI_2 = EXTI_x<EXTILine::line2>;
	using EXTI_3 = EXTI_x<EXTILine::line3>;
	using EXTI_4 = EXTI_x<EXTILine::line4>;
	using EXTI_5 = EXTI_x<EXTILine::line5>;
	using EXTI_6 = EXTI_x<EXTILine::line6>;
	using EXTI_7 = EXTI_x<EXTILine::line7>;
	using EXTI_8 = EXTI_x<EXTILine::line8>;
	using EXTI_9 = EXTI_x<EXTILine::line9>;
	using EXTI_10 = EXTI_x<EXTILine::line10>;
	using EXTI_11 = EXTI_x<EXTILine::line11>;
	using EXTI_12 = EXTI_x<EXTILine::line12>;
	using EXTI_13 = EXTI_x<EXTILine::line13>;
	using EXTI_14 = EXTI_x<EXTILine::line14>;
	using EXTI_15 = EXTI_x<EXTILine::line15>;
}


#endif // __STM32_htlEXTI__
