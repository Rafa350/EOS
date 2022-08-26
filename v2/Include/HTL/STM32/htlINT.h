#pragma once
#ifndef __STM32_htlINT__
#define __STM32_htlINT__


// HAL includes
//
#include "HTL/htl.h"


namespace htl {

	enum class INTPriority {
		_0,
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
		_15
	};

	enum class INTSubPriority {
		_0,
		_1,
		_2,
		_3,
	};

	enum class INTVector {
		vDAC =  TIM6_DAC_IRQn,
		vDAM2D =  DMA2D_IRQn,
		exti0 = EXTI0_IRQn,
		exti1 = EXTI1_IRQn,
		exti2 = EXTI2_IRQn,
		exti3 = EXTI3_IRQn,
		exti4 = EXTI4_IRQn,
		exti5 = EXTI9_5_IRQn,
		exti6 = EXTI9_5_IRQn,
		exti7 = EXTI9_5_IRQn,
		exti8 = EXTI9_5_IRQn,
		exti9 = EXTI9_5_IRQn,
		exti10 = EXTI15_10_IRQn,
		exti11 = EXTI15_10_IRQn,
		exti12 = EXTI15_10_IRQn,
		exti13 = EXTI15_10_IRQn,
		exti14 = EXTI15_10_IRQn,
		exti15 = EXTI15_10_IRQn,
		ltdc = LTDC_IRQn,
		ltdcError = LTDC_ER_IRQn,
		spi1 = SPI1_IRQn,
		spi2 = SPI2_IRQn,
		spi3 = SPI3_IRQn,
		spi4 = SPI4_IRQn,
		spi5 = SPI5_IRQn,
		spi6 = SPI6_IRQn,
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
		uart1 = USART1_IRQn,
		uart2 = USART2_IRQn,
		uart3 = USART3_IRQn,
		uart4 = UART4_IRQn,
		uart5 = UART5_IRQn,
		uart6 = USART6_IRQn,
		uart7 = UART7_IRQn,
		uart8 = UART8_IRQn,
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
