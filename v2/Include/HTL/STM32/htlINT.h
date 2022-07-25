#ifndef __STM32_htlINT__
#define __STM32_htlINT__


// HAL includes
//
#include "eos.h"


namespace htl {

	enum class INTPriority {
		p0,
		p1,
		p2,
		p3,
		p4,
		p5,
		p6,
		p7,
		p8,
		p9,
		p10,
		p11,
		p12,
		p13,
		p14,
		p15
	};

	enum class INTSubPriority {
		s0,
		s1,
		s2,
		s3,
	};

	enum class INTVector {
		vDAC =  TIM6_DAC_IRQn,
		vDAM2D =  DMA2D_IRQn,
		vEXTI0 = EXTI0_IRQn,
		vEXTI1 = EXTI1_IRQn,
		vEXTI2 = EXTI2_IRQn,
		vEXTI3 = EXTI3_IRQn,
		vEXTI4 = EXTI4_IRQn,
		vEXTI5 = EXTI9_5_IRQn,
		vEXTI6 = EXTI9_5_IRQn,
		vEXTI7 = EXTI9_5_IRQn,
		vEXTI8 = EXTI9_5_IRQn,
		vEXTI9 = EXTI9_5_IRQn,
		vEXTI10 = EXTI15_10_IRQn,
		vEXTI11 = EXTI15_10_IRQn,
		vEXTI12 = EXTI15_10_IRQn,
		vEXTI13 = EXTI15_10_IRQn,
		vEXTI14 = EXTI15_10_IRQn,
		vEXTI15 = EXTI15_10_IRQn,
		vLTDC = LTDC_IRQn,
		vLTDC_ER = LTDC_ER_IRQn,
		vSPI1 = SPI1_IRQn,
		vSPI2 = SPI2_IRQn,
		vSPI3 = SPI3_IRQn,
		vSPI4 = SPI4_IRQn,
		vSPI5 = SPI5_IRQn,
		vSPI6 = SPI6_IRQn,
		vTMR1_BRK = TIM1_BRK_TIM9_IRQn,
		vTMR1_CC = TIM1_CC_IRQn,
		vTMR1_TRG = TIM1_TRG_COM_TIM11_IRQn,
		vTMR1_UP = TIM1_UP_TIM10_IRQn,
		vTMR2 = TIM2_IRQn,
		vTMR3 = TIM3_IRQn,
		vTMR4 = TIM4_IRQn,
		vTMR5 = TIM5_IRQn,
		vTMR6 = TIM6_DAC_IRQn,
		vTMR7 = TIM7_IRQn,
		vTMR8_BRK = TIM8_BRK_TIM12_IRQn,
		vTMR8_CC = TIM8_CC_IRQn,
		vTMR8_TRG = TIM8_TRG_COM_TIM14_IRQn,
		vTMR8_UP = TIM8_UP_TIM13_IRQn,
		vTMR9 = TIM1_BRK_TIM9_IRQn,
		vTMR10 = TIM1_UP_TIM10_IRQn,
		vTMR11 = TIM1_TRG_COM_TIM11_IRQn,
		vTMR12 = TIM8_BRK_TIM12_IRQn,
		vTMR13 = TIM8_UP_TIM13_IRQn,
		vTMR14 = TIM8_TRG_COM_TIM14_IRQn,
		vUART1 = USART1_IRQn,
		vUART2 = USART2_IRQn,
		vUART3 = USART3_IRQn,
		vUART4 = UART4_IRQn,
		vUART5 = UART5_IRQn,
		vUART6 = USART6_IRQn,
		vUART7 = UART7_IRQn,
		vUART8 = UART8_IRQn,
	};

	template <int dummy>
	class INT_x {
		public:
			static void setInterruptVectorPriority(
				INTVector vector,
				INTPriority priority,
				INTSubPriority subPriority) {

				uint32_t priorityGroup = NVIC_GetPriorityGrouping();
			    NVIC_SetPriority((IRQn_Type)vector, NVIC_EncodePriority(priorityGroup, (uint32_t)priority, (uint32_t)subPriority));
			}

			inline static void enableInterrupts() {

				__enable_irq();
			}

			inline static bool disableInterrupts() {

				bool state = __get_PRIMASK() == 0;
				__disable_irq();
				return state;
			}

			inline static void restoreInterrupts(
				bool state) {

				if (state)
					enableInterrupts();
			}

			inline static void enableInterruptVector(
				INTVector vector) {

				NVIC_EnableIRQ((IRQn_Type) vector);
			}

			inline static void disableInterruptVector(
				INTVector vector) {

				NVIC_DisableIRQ((IRQn_Type) vector);
			}
	};

	using INT_1 = INT_x<1>;

}


#endif // __STM32_htlINT__
