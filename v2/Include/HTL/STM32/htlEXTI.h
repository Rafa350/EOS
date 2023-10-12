#pragma once
#ifndef __STM32_htlEXTI__
#define __STM32_htlEXTI__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlINT.h"


namespace htl {

	namespace exti {

		enum class EXTILine {
			line0,   // Px0
			line1,   // Px1
			line2,   // Px2
			line3,   // Px3
			line4,   // Px4
			line5,   // Px5
			line6,   // Px6
			line7,   // Px7
			line8,   // Px8
			line9,   // Px9
			line10,  // Px10
			line11,  // Px11
			line12,  // Px12
			line13,  // Px13
			line14,  // Px14
			line15,  // Px15
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
			change
		};

		using EXTIInterruptParam = void*;
		using EXTIInterruptFunction =  void (*)(EXTIEvent event, EXTIInterruptParam);

		template <EXTILine>
		struct EXTITrait {
		};

		#ifdef EOS_PLATFORM_STM32F4
		template <EXTILine line_>
		class EXTI_x final {
			private:
				using ExtiTrait = EXTITrait<line_>;

			public:
				static constexpr EXTILine line = line_;

			private:
				static EXTIInterruptFunction _isrFunction;
				static EXTIInterruptParam _isrParam;

				EXTI_x() = default;
				EXTI_x(const EXTI_x &) = delete;
				EXTI_x(const EXTI_x &&) = delete;
				~EXTI_x() = delete;

				EXTI_x & operator = (const EXTI_x &) = delete;
				EXTI_x & operator = (const EXTI_x &&) = delete;

				inline static void activate() {
					RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
					__DSB();
				}

				inline static void deactivate() {
					RCC->APB2ENR &= ~RCC_APB2ENR_SYSCFGEN;
				}

				static void setPort(
					htl::gpio::PortId portId) {

					uint32_t temp = SYSCFG->EXTICR[uint32_t(line_) >> 2];
					temp &= ~(0xF << (4 * (uint32_t(line_) & 0x03)));
					temp |= (uint32_t(portId) & 0xF) << (4 * (uint32_t(line_) & 0x03));
					SYSCFG->EXTICR[uint32_t(line_) >> 2] = temp;
				}

				static void setMode(
					EXTIMode mode) {

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
				}

				static void setTrigger(
					EXTITrigger trigger) {

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

			public:
				static void initialize(
					htl::gpio::PortID portId,
					EXTIMode mode,
					EXTITrigger trigger) {

					activate();
					setPort(portId);
					setMode(mode);
					setTrigger(trigger);
				}

				static void deinitialize() {

					deactivate();
				}

				static void setInterruptFunction(
					EXTIInterruptFunction function,
					EXTIInterruptParam param = nullptr) {

					_isrFunction = function;
					_isrParam = param;
				}

				inline static void enableInterrupt() {

					EXTI->IMR |= 1 << uint32_t(line_);
				}

				static bool disableInterrupt() {

					bool state = (EXTI->IMR & (1 << uint32_t(line_))) != 0;
					EXTI->IMR &= ~(1 << uint32_t(line_));
					return state;
				}

				static bool isInterruptEnabled() {

					return (EXTI->IMR & (1 << uint32_t(line_))) != 0;
				}

				inline static bool getInterruptFlag() {

					return (EXTI->PR & (1 << uint32_t(line_))) != 0;
				}

				inline static void clearInterruptFlag() {

					EXTI->PR |= 1 << uint32_t(line_);
				}

				static void interruptHandler(
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


		template <>
		struct EXTITrait<EXTILine::line13> {
			static constexpr INTVector vector = INTVector::exti13;
		};
		#endif


		namespace internal {

			class Activator final {
				private:
					#if defined(EOS_PLATFORM_STM32F7)
					static constexpr uint32_t _rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
					static constexpr uint32_t _rccEnablePos = RCC_APB2ENR_SYSCFGEN_Pos;
					#elif defined(EOS_PLATFORM_STM32G0)
					static constexpr uint32_t _rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
					static constexpr uint32_t _rccEnablePos = RCC_APBENR2_SYSCFGEN_Pos;
					#endif
				private:
					static unsigned _activated;
				public:
					static void activate() {
						if (_activated == 0) {
							uint32_t *p = reinterpret_cast<uint32_t*>(_rccEnableAddr);
							*p |= 1 << _rccEnablePos;
							__DSB();
						}
						_activated++;
					}
					static void deactivate() {
						if (_activated == 1) {
							uint32_t *p = reinterpret_cast<uint32_t*>(_rccEnableAddr);
							*p &= ~(1 << _rccEnablePos);
							_activated--;
						}
					}
			};
		}

		class ExINT {
			private:
				using Activator = internal::Activator;
			private:
				EXTILine _line;
			protected:
				inline void activate() {
					Activator::activate();
				}
				inline void deactivate() {
					Activator::deactivate();
				}
				void setPort(EXTILine line, htl::gpio::PortID portID);
				void setMode(EXTILine line, EXTIMode mode);
				void setTrigger(EXTILine line, EXTITrigger trigger);
				void interruptService();
			public:
				ExINT(EXTILine line): _line {line} {}
				void init(htl::gpio::PortID portID, EXTIMode mode, EXTITrigger trigger);
				void deinitialize();
		};

		template <EXTILine line_>
		class ExINT_x final: public ExINT {
			private:
				static ExINT_x _dev;
			public:
				ExINT_x(): ExINT(line_) {}
				inline static void interruptHandler() {
					getHandler()->interruptService();
				}
				static constexpr ExINT_x * getHandler() {
					return &_dev;
				}
		};

		template <EXTILine line_>
		ExINT_x<line_> ExINT_x<line_>::_dev;

		using ExINT_0 = ExINT_x<EXTILine::line0>;
		using ExINT_1 = ExINT_x<EXTILine::line1>;
		using ExINT_2 = ExINT_x<EXTILine::line2>;
		using ExINT_3 = ExINT_x<EXTILine::line3>;
		using ExINT_4 = ExINT_x<EXTILine::line4>;
		using ExINT_5 = ExINT_x<EXTILine::line5>;
		using ExINT_6 = ExINT_x<EXTILine::line6>;
		using ExINT_7 = ExINT_x<EXTILine::line7>;
		using ExINT_8 = ExINT_x<EXTILine::line8>;
		using ExINT_9 = ExINT_x<EXTILine::line9>;
		using ExINT_10 = ExINT_x<EXTILine::line10>;
		using ExINT_11 = ExINT_x<EXTILine::line11>;
		using ExINT_12 = ExINT_x<EXTILine::line12>;
		using ExINT_13 = ExINT_x<EXTILine::line13>;
		using ExINT_14 = ExINT_x<EXTILine::line14>;
		using ExINT_15 = ExINT_x<EXTILine::line15>;
	}
}


#endif // __STM32_htlEXTI__
