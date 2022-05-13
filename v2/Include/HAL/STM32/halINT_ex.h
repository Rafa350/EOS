#ifndef __STM32_halINT_ex__
#define __STM32_halINT_ex__


#ifdef __cplusplus


// HAL includes
//
#include "HAL/STM32/halINT.h"


namespace eos {

	enum class INTPriority {
		priority0 = HAL_INT_PRIORITY_0,
		priority1 = HAL_INT_PRIORITY_1,
		priority2 = HAL_INT_PRIORITY_2,
		priority3 = HAL_INT_PRIORITY_3,
		priority4 = HAL_INT_PRIORITY_4,
		priority5 = HAL_INT_PRIORITY_5,
		priority6 = HAL_INT_PRIORITY_6,
		priority7 = HAL_INT_PRIORITY_7,
		priority8 = HAL_INT_PRIORITY_8,
		priority9 = HAL_INT_PRIORITY_9,
		priority10 = HAL_INT_PRIORITY_10,
		priority11 = HAL_INT_PRIORITY_11,
		priority12 = HAL_INT_PRIORITY_12,
		priority13 = HAL_INT_PRIORITY_13,
		priority14 = HAL_INT_PRIORITY_14,
		priority15 = HAL_INT_PRIORITY_15
	};

	enum class INTSubPriority {
		subPriority0 = HAL_INT_SUBPRIORITY_0,
		subPriority1 = HAL_INT_SUBPRIORITY_1,
		subPriority2 = HAL_INT_SUBPRIORITY_2,
		subPriority3 = HAL_INT_SUBPRIORITY_3,
	};

	enum class INTVector {
		vectorDAC = HAL_INT_VECTOR_DAC,
		vectorDAM2D = HAL_INT_VECTOR_DMA2D,
		vectorEXTI0 = HAL_INT_VECTOR_EXTI0,
		vectorEXTI1 = HAL_INT_VECTOR_EXTI1,
		vectorEXTI2 = HAL_INT_VECTOR_EXTI2,
		vectorEXTI3 = HAL_INT_VECTOR_EXTI3,
		vectorEXTI4 = HAL_INT_VECTOR_EXTI4,
		vectorEXTI5 = HAL_INT_VECTOR_EXTI5,
		vectorEXTI6 = HAL_INT_VECTOR_EXTI6,
		vectorEXTI7 = HAL_INT_VECTOR_EXTI7,
		vectorEXTI8 = HAL_INT_VECTOR_EXTI8,
		vectorEXTI9 = HAL_INT_VECTOR_EXTI9,
		vectorEXTI10 = HAL_INT_VECTOR_EXTI10,
		vectorEXTI11 = HAL_INT_VECTOR_EXTI11,
		vectorEXTI12 = HAL_INT_VECTOR_EXTI12,
		vectorEXTI13 = HAL_INT_VECTOR_EXTI13,
		vectorEXTI14 = HAL_INT_VECTOR_EXTI14,
		vectorEXTI15 = HAL_INT_VECTOR_EXTI15,
		vectorLTDC = HAL_INT_VECTOR_LTDC,
		vectorLTDC_ER = HAL_INT_VECTOR_LTDC_ER,
		vectorSPI1 = HAL_INT_VECTOR_SPI1,
		vectorSPI2 = HAL_INT_VECTOR_SPI2,
		vectorSPI3 = HAL_INT_VECTOR_SPI3,
		vectorSPI4 = HAL_INT_VECTOR_SPI4,
		vectorSPI5 = HAL_INT_VECTOR_SPI5,
		vectorSPI6 = HAL_INT_VECTOR_SPI6,
		vectorTMR1_BRK = HAL_INT_VECTOR_TMR1_BRK,
		vectorTMR1_CC = HAL_INT_VECTOR_TMR1_CC,
		vectorTMR1_TRG = HAL_INT_VECTOR_TMR1_TRG,
		vectorTMR1_UP = HAL_INT_VECTOR_TMR1_UP,
		vectorTMR2 = HAL_INT_VECTOR_TMR2,
		vectorTMR3 = HAL_INT_VECTOR_TMR3,
		vectorTMR4 = HAL_INT_VECTOR_TMR4,
		vectorTMR5 = HAL_INT_VECTOR_TMR5,
		vectorTMR6 = HAL_INT_VECTOR_TMR6,
		vectorTMR7 = HAL_INT_VECTOR_TMR7,
		vectorTMR8_BRK = HAL_INT_VECTOR_TMR8_BRK,
		vectorTMR8_CC = HAL_INT_VECTOR_TMR8_CC,
		vectorTMR8_TRG = HAL_INT_VECTOR_TMR8_TRG,
		vectorTMR8_UP = HAL_INT_VECTOR_TMR8_UP,
		vectorTMR9 = HAL_INT_VECTOR_TMR9,
		vectorTMR10 = HAL_INT_VECTOR_TMR10,
		vectorTMR11 = HAL_INT_VECTOR_TMR11,
		vectorTMR12 = HAL_INT_VECTOR_TMR12,
		vectorTMR13 = HAL_INT_VECTOR_TMR13,
		vectorTMR14 = HAL_INT_VECTOR_TIM14,
		vectorUART1 = HAL_INT_VECTOR_UART1,
		vectorUART2 = HAL_INT_VECTOR_UART2,
		vectorUART3 = HAL_INT_VECTOR_UART3,
		vectorUART4 = HAL_INT_VECTOR_UART4,
		vectorUART5 = HAL_INT_VECTOR_UART5,
		vectorUART6 = HAL_INT_VECTOR_UART6,
		vectorUART7 = HAL_INT_VECTOR_UART7,
		vectorUART8 = HAL_INT_VECTOR_UART8,
	};

	class INTAdapter {
		public:
			inline static void setInterruptVectorPriority(INTVector vector, INTPriority priority, INTSubPriority subPriority) {
				halINTSetInterruptVectorPriority((uint32_t)vector, (uint32_t) priority, (uint32_t) subPriority);
			}

			inline static void enableInterruptVector(INTVector vector) {
				halINTEnableInterruptVector((uint32_t)vector);
			}

			inline static void enableInterruptSource(uint32_t source) {
				halINTEnableInterruptSource(source);
			}

			inline static bool disableInterruptSource(uint32_t source) {
				return halINTDisableInterruptSource(source);
			}

			inline static void restoreInterruptSource(uint32_t source, bool state) {
				halINTRestoreInterruptSource(source, state);
			}
	};

	typedef INTAdapter INT;

}

#endif // __cplusplus


#endif // __STM32_halINT_ex__
