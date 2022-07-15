#ifndef __STM32_htlEXTI__
#define __STM32_htlEXTI__


// EOS includes
//
#include "eos.h"
#include "HAL/STM32/halEXTI.h"


#ifdef __cplusplus

namespace htl {

	enum class EXTILine: halEXTILine {
		line0 = HAL_EXTI_LINE_0,
		line1 = HAL_EXTI_LINE_1,
		line2 = HAL_EXTI_LINE_2,
		line3 = HAL_EXTI_LINE_3,
		line4 = HAL_EXTI_LINE_4,
		line5 = HAL_EXTI_LINE_5,
		line6 = HAL_EXTI_LINE_6,
		line7 = HAL_EXTI_LINE_7,
		line8 = HAL_EXTI_LINE_8,
		line9 = HAL_EXTI_LINE_9,
		line10 = HAL_EXTI_LINE_10,
		line11 = HAL_EXTI_LINE_11,
		line12 = HAL_EXTI_LINE_12,
		line13 = HAL_EXTI_LINE_13,
		line14 = HAL_EXTI_LINE_14,
		line15 = HAL_EXTI_LINE_15
	};

	enum class EXTIPort: halEXTIOptions {
		portA = HAL_EXTI_PORT_A,
		portB = HAL_EXTI_PORT_B,
		portC = HAL_EXTI_PORT_C,
		portD = HAL_EXTI_PORT_D,
		portE = HAL_EXTI_PORT_E,
		portF = HAL_EXTI_PORT_F,
		portG = HAL_EXTI_PORT_G,
		portH = HAL_EXTI_PORT_H,
		portI = HAL_EXTI_PORT_I,
		portJ = HAL_EXTI_PORT_J,
		portK = HAL_EXTI_PORT_K
	};

	enum class EXTIMode: halEXTIOptions {
		none      = HAL_EXTI_MODE_NONE,
		interrupt = HAL_EXTI_MODE_INT,
		event     = HAL_EXTI_MODE_EVENT
	};

	enum class EXTITrigger: halEXTIOptions {
		rissing  = HAL_EXTI_TRIGGER_RISING,
		falling  = HAL_EXTI_TRIGGER_FALLING,
		changing = HAL_EXTI_TRIGGER_CHANGING
	};

	enum class EXTIEvent {
		unknown,
		change
	};

    typedef void *EXTIInterruptParam ;
    typedef void (*EXTIInterruptFunction)(EXTIEvent event, EXTIInterruptParam);


	template <EXTILine line_>
	struct EXTIInfo {
		static const uint32_t addr;
		static const uint32_t ln;
	};

	template <EXTILine line_>
	class EXTI_x {
		private:
			using Info = EXTIInfo<line_>;
			constexpr static const uint32_t _addr = Info::addr;
			constexpr static const uint32_t _ln = Info::ln;

        private:
            static EXTIInterruptFunction _isrFunction;
            static EXTIInterruptParam _isrParam;

			EXTI_x() = default;
			EXTI_x(const EXTI_x &) = delete;
			EXTI_x(const EXTI_x &&) = delete;
			~EXTI_x();

			EXTI_x & operator = (const EXTI_x &) = delete;
			EXTI_x & operator = (const EXTI_x &&) = delete;

			inline static void enableClock() {

			}

			inline static void disableClock() {

			}

		public:
			static void init(
				EXTIPort port,
				EXTIMode mode,
				EXTITrigger trigger) {

				halEXTIInitializeLine(halEXTILine(line_), halEXTIOptions(port) | halEXTIOptions(mode) | halEXTIOptions(trigger));

				/*EXTI_TypeDef *regs = reinterpret_cast<EXTI_TypeDef*>(_addr);

				// Configura el registre IMR (Interrupt Mask Register);
				//
			    if (mode == EXTIMode::interrupt)
			    	regs->IMR |= 1 << _ln;
			    else
			    	regs->IMR &= ~(1 << _ln);

				// Configura el registre EMR (Event Mask Register);
				//
			    if (mode == EXTIMode::event)
			    	regs->EMR |= 1 << _ln;
			    else
			    	regs->EMR &= ~(1 << _ln);

				// Configura el registre RTSR (Rising Trigger Selection Register)
				//
				if ((trigger == EXTITrigger::rissing) || (trigger == EXTITrigger::changing))
					regs->RTSR |= 1 << _ln;
				else
					regs->RTSR &= ~(1 << _ln);

				// Configura el registre FTSR (Falling Trigger Selection Register)
				//
				if ((trigger == EXTITrigger::falling) || (trigger == EXTITrigger::changing))
					regs->FTSR |= 1 << _ln;
				else
					regs->FTSR &= ~(1 << _ln);

				//XXXXXXXXXXXXXXXXXXXX*/
			}

			static void setInterruptFunction(
				halEXTIInterruptFunction function,
				void *params) {

				halEXTISetInterruptFunction(halEXTILine(line_), function, params);
			}

			static void setInterruptFunction(
				EXTIInterruptFunction function,
				EXTIInterruptParam param = nullptr) {

				_isrFunction = function;
                _isrParam = param;
            }

			static void enableInterrupt() {

				EXTI_TypeDef *regs = reinterpret_cast<EXTI_TypeDef*>(_addr);

				regs->IMR |= 1 << _ln;
			}

			static bool disableInterrupt() {

				EXTI_TypeDef *regs = reinterpret_cast<EXTI_TypeDef*>(_addr);

				bool state = (regs->IMR & (1 << _ln)) != 0;
				regs->IMR &= ~(1 << _ln);
				return state;
			}

            inline static bool getInterruptFlag() {

            	EXTI_TypeDef *regs = reinterpret_cast<EXTI_TypeDef*>(_addr);
                return (regs->PR & (1 << _ln)) != 0;
            }

            inline static void clearInterruptFlag() {

            	EXTI_TypeDef *regs = reinterpret_cast<EXTI_TypeDef*>(_addr);
                regs->PR &= ~(1 << _ln);
            }

			static void interruptHandler(
				EXTIEvent event) {

				if (_isrFunction != nullptr)
                    _isrFunction(event, _isrParam);
            }
	};

    template <EXTILine line_> EXTIInterruptFunction EXTI_x<line_>::_isrFunction = nullptr;
    template <EXTILine line_> EXTIInterruptParam EXTI_x<line_>::_isrParam = nullptr;


	template <>
	struct EXTIInfo<EXTILine::line0> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 0;
	};

	template <>
	struct EXTIInfo<EXTILine::line1> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 1;
	};

	template <>
	struct EXTIInfo<EXTILine::line2> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 2;
	};

	template <>
	struct EXTIInfo<EXTILine::line3> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 3;
	};

	template <>
	struct EXTIInfo<EXTILine::line4> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 4;
	};

	template <>
	struct EXTIInfo<EXTILine::line5> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 5;
	};

	template <>
	struct EXTIInfo<EXTILine::line6> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 6;
	};

	template <>
	struct EXTIInfo<EXTILine::line7> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 7;
	};

	template <>
	struct EXTIInfo<EXTILine::line8> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 8;
	};

	template <>
	struct EXTIInfo<EXTILine::line9> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 9;
	};

	template <>
	struct EXTIInfo<EXTILine::line10> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 10;
	};

	template <>
	struct EXTIInfo<EXTILine::line11> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 11;
	};

	template <>
	struct EXTIInfo<EXTILine::line12> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 12;
	};

	template <>
	struct EXTIInfo<EXTILine::line13> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 13;
	};

	template <>
	struct EXTIInfo<EXTILine::line14> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 14;
	};

	template <>
	struct EXTIInfo<EXTILine::line15> {
		constexpr static const uint32_t addr = EXTI_BASE;
		constexpr static const uint32_t ln = 15;
	};

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

#endif


#ifdef __cplusplus
extern "C" {
#endif
extern void EXTI_0_InterruptHandler();
extern void EXTI_1_InterruptHandler();
extern void EXTI_2_InterruptHandler();
extern void EXTI_3_InterruptHandler();
extern void EXTI_4_InterruptHandler();
extern void EXTI_5_6_7_8_9_InterruptHandler();
extern void EXTI_10_11_12_13_14_15_InterruptHandler();
#ifdef __cplusplus
}


#endif

#endif // __STM32_htlEXTI__
