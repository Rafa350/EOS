#ifndef __STM32_halEXTI_ex__
#define __STM32_halEXTI_ex__


// EOS includes
//
#include "HAL/hal.h"
#include "HAL/STM32/halEXTI.h"


namespace eos {

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

	template <EXTILine line_>
	class EXTIAdapter {
		public:
			constexpr static const EXTILine line = line_;

		private:
			EXTIAdapter() = default;
			EXTIAdapter(const EXTIAdapter &) = delete;
			EXTIAdapter(const EXTIAdapter &&) = delete;
			EXTIAdapter & operator = (const EXTIAdapter &) = delete;
			EXTIAdapter & operator = (const EXTIAdapter &&) = delete;

		public:
			inline static auto & instance() {
				static EXTIAdapter inst;
				return inst;
			}

			inline static void initialize(EXTIPort port, EXTIMode mode, EXTITrigger trigger) {
				halEXTIInitializeLine(halEXTILine(line_), halEXTIOptions(port) | halEXTIOptions(mode) | halEXTIOptions(trigger));
			}

			inline static void setInterruptFunction(halEXTIInterruptFunction function, void *params) {
			    halEXTISetInterruptFunction(halEXTILine(line_), function, params);
			}

			inline static void enableInterrupt() {
				__set_bit_pos(EXTI->IMR, halEXTILine(line_));
			}

			inline static bool disableInterrupt() {
				bool state = __check_bit_pos(EXTI->IMR, halEXTILine(line_));
				__clear_bit_pos(EXTI->IMR, halEXTILine(line_));
				return state;
			}
	};

	typedef EXTIAdapter<EXTILine::line0> EXTI_0;
	typedef EXTIAdapter<EXTILine::line1> EXTI_1;
	typedef EXTIAdapter<EXTILine::line2> EXTI_2;
	typedef EXTIAdapter<EXTILine::line3> EXTI_3;
	typedef EXTIAdapter<EXTILine::line4> EXTI_4;
	typedef EXTIAdapter<EXTILine::line5> EXTI_5;
	typedef EXTIAdapter<EXTILine::line6> EXTI_6;
	typedef EXTIAdapter<EXTILine::line7> EXTI_7;
	typedef EXTIAdapter<EXTILine::line8> EXTI_8;
	typedef EXTIAdapter<EXTILine::line9> EXTI_9;
	typedef EXTIAdapter<EXTILine::line10> EXTI_10;
	typedef EXTIAdapter<EXTILine::line11> EXTI_11;
	typedef EXTIAdapter<EXTILine::line12> EXTI_12;
	typedef EXTIAdapter<EXTILine::line13> EXTI_13;
	typedef EXTIAdapter<EXTILine::line14> EXTI_14;
	typedef EXTIAdapter<EXTILine::line15> EXTI_15;
}


#endif // __STM32_halEXTI_ex__
