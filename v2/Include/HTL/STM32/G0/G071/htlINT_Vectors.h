#pragma once
#ifndef __STM32G071_htlINT_Vectors__
#define __STM32G071_htlINT_Vectors__


// HAL includes
//
#include "HTL/STM32/htl.h"


// Platform check
//
#if !defined(EOS_PLATFORM_STM32G071)
	#error "Valid for STM32G071 platform only"
#endif


namespace htl {
	namespace irq {
		enum class VectorID {

			exti0 = EXTI0_1_IRQn,
			exti1 = EXTI0_1_IRQn,
			exti2 = EXTI2_3_IRQn,
			exti3 = EXTI2_3_IRQn,
			exti4 = EXTI4_15_IRQn,
			exti5 = EXTI4_15_IRQn,
			exti6 = EXTI4_15_IRQn,
			exti7 = EXTI4_15_IRQn,
			exti8 = EXTI4_15_IRQn,
			exti9 = EXTI4_15_IRQn,
			exti10 = EXTI4_15_IRQn,
			exti11 = EXTI4_15_IRQn,
			exti12 = EXTI4_15_IRQn,
			exti13 = EXTI4_15_IRQn,
			exti14 = EXTI4_15_IRQn,
			exti15 = EXTI4_15_IRQn,

			spi1 = SPI1_IRQn,
			spi2 = SPI2_IRQn,

			#ifdef HTL_TMR1_EXIST
			tmr1_CC = TIM1_CC_IRQn,
			tmr1_BRK_UP_TRG_COM = TIM1_BRK_UP_TRG_COM_IRQn,
			#endif
			#ifdef HTL_TMR2_EXIST
			tmr2 = TIM2_IRQn,
			#endif
			#ifdef HTL_TMR3_EXIST
			tmr3 = TIM3_IRQn,
			#endif
			#ifdef HTL_TMR4_EXIST
			tmr4 = TIM4_IRQn,
			#endif
			#ifdef HTL_TMR5_EXIST
			tmr5 = TIM5_IRQn,
			#endif
			#ifdef HTL_TMR6_EXIST
			tmr6 = TIM6_DAC_LPTIM1_IRQn,
			#endif
			#ifdef HTL_TMR7_EXIST
			tmr7 = TIM7_LPTIM2_IRQn,
			#endif
			#ifdef HTL_TMR8_EXIST
			tmr8_BRK = TIM8_BRK_TIM12_IRQn,
			tmr8_CC = TIM8_CC_IRQn,
			tmr8_TRG = TIM8_TRG_COM_TIM14_IRQn,
			tmr8_UP = TIM8_UP_TIM13_IRQn,
			#endif
			#ifdef HTL_TMR9_EXIST
			tmr9 = TIM1_BRK_TIM9_IRQn,
			#endif
			#ifdef HTL_TMR10_EXIST
			tmr10 = TIM1_UP_TIM10_IRQn,
			#endif
			#ifdef HTL_TMR11_EXIST
			tmr11 = TIM1_TRG_COM_TIM11_IRQn,
			#endif
			#ifdef HTL_TMR12_EXIST
			tmr12 = TIM8_BRK_TIM12_IRQn,
			#endif
			#ifdef HTL_TMR13_EXIST
			tmr13 = TIM8_UP_TIM13_IRQn,
			#endif
			#ifdef HTL_TMR14_EXIST
			tmr14 = TIM14_IRQn,
			#endif

			uart1 = USART1_IRQn,
			uart2 = USART2_IRQn,
			uart3 = USART3_4_LPUART1_IRQn,
			uart4 = USART3_4_LPUART1_IRQn,

			i2c1 = I2C1_IRQn,
			i2c2 = I2C2_IRQn,

			dma11 = DMA1_Channel1_IRQn,
			dma12 = DMA1_Channel2_3_IRQn,
			dma13 = DMA1_Channel2_3_IRQn,
			dma14 = DMA1_Ch4_7_DMAMUX1_OVR_IRQn,
			dma15 = DMA1_Ch4_7_DMAMUX1_OVR_IRQn,
			dma16 = DMA1_Ch4_7_DMAMUX1_OVR_IRQn,
			dma17 = DMA1_Ch4_7_DMAMUX1_OVR_IRQn,
			dmamux1 = DMA1_Ch4_7_DMAMUX1_OVR_IRQn,
		};
	}
}


#endif // __STM32G071_htlINT_Vectors__
