#pragma once
#ifndef __STM32F4_htlINT_Vectors__
#define __STM32F4_htlINT_Vectors__


// HAL includes
//
#include "HTL/STM32/htl.h"


// Platform check
//
#if !defined(EOS_PLATFORM_STM32F4)
	#error "Valid for STM32F4 platform only"
#endif


namespace htl {

	namespace irq {

		enum class VectorID {
			#ifdef HTL_DAC_EXIST
			dac = TIM6_DAC_IRQn,
			#endif

			#ifdef HTL_DMA2D_EXIST
			dma2d = DMA2D_IRQn,
			#endif

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

			#ifdef HTL_LTDC_EXIST
			ltdc = LTDC_IRQn,
			ltdc_ER = LTDC_ER_IRQn,
			#endif

			#ifdef HTL_SPI1_EXIST
			spi1 = SPI1_IRQn,
			#endif
			#ifdef HTL_SPI2_EXIST
			spi2 = SPI2_IRQn,
			#endif
			#ifdef HTL_SPI3_EXIST
			spi3 = SPI3_IRQn,
			#endif
			#ifdef HTL_SPI4_EXIST
			spi4 = SPI4_IRQn,
			#endif
			#ifdef HTL_SPI5_EXIST
			spi5 = SPI5_IRQn,
			#endif
			#ifdef HTL_SPI6_EXIST
			spi6 = SPI6_IRQn,
			#endif

			#ifdef HTL_TMR1_EXIST
			tmr1_BRK = TIM1_BRK_TIM9_IRQn,
			tmr1_CC = TIM1_CC_IRQn,
			tmr1_TRG = TIM1_TRG_COM_TIM11_IRQn,
			tmr1_UP = TIM1_UP_TIM10_IRQn,
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
			tmr6 = TIM6_DAC_IRQn,
			#endif
			#ifdef HTL_TMR7_EXIST
			tmr7 = TIM7_IRQn,
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
			tmr14 = TIM8_TRG_COM_TIM14_IRQn,
			#endif

			#ifdef HTL_UART1_EXIST
			uart1 = USART1_IRQn,
			#endif
			#ifdef HTL_UART2_EXIST
			uart2 = USART2_IRQn,
			#endif
			#ifdef HTL_UART3_EXIST
			uart3 = USART3_IRQn,
			#endif
			#ifdef HTL_UART4_EXIST
			uart4 = UART4_IRQn,
			#endif
			#ifdef HTL_UART5_EXIST
			uart5 = UART5_IRQn,
			#endif
			#ifdef HTL_UART6_EXIST
			uart6 = USART6_IRQn,
			#endif
			#ifdef HTL_UART7_EXIST
			uart7 = UART7_IRQn,
			#endif
			#ifdef HTL_UART8_EXIST
			uart8 = UART8_IRQn,
			#endif

			#ifdef HTL_I2C1_EXIST
			i2c1_EV = I2C1_EV_IRQn,
			i2c1_ER = I2C1_ER_IRQn,
			#endif
			#ifdef HTL_I2C2_EXIST
			i2c2_EV = I2C2_EV_IRQn,
			i2c2_ER = I2C2_ER_IRQn,
			#endif
			#ifdef HTL_I2C3_EXIST
			i2c3_EV = I2C3_EV_IRQn,
			i2c3_ER = I2C3_ER_IRQn,
			#endif
			#ifdef HTL_I2C4_EXIST
			i2c4_EV = I2C4_EV_IRQn,
			i2c4_ER = I2C4_ER_IRQn,
			#endif
		};
	}
}


#endif // __STM32F4_htlINT_Vectors__
