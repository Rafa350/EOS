#pragma once
#ifndef __STM32G0B1_htlINT_Vector__
#define __STM32G0B1_htlINT_Vector__


// HAL includes
//
#include "HTL/STM32/htl.h"


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
            spi2 = SPI2_3_IRQn,
            spi3 = SPI2_3_IRQn,

            tmr1_CC = TIM1_CC_IRQn,
            tmr1_BRK_UP_TRG_COM = TIM1_BRK_UP_TRG_COM_IRQn,
            tmr2 = TIM2_IRQn,
            tmr3 = TIM3_TIM4_IRQn,
            tmr4 = TIM3_TIM4_IRQn,
            tmr6 = TIM6_DAC_LPTIM1_IRQn,
            tmr7 = TIM7_LPTIM2_IRQn,
            tmr14 = TIM14_IRQn,

            uart1 = USART1_IRQn,
            uart2 = USART2_LPUART2_IRQn,
            uart3 = USART3_4_5_6_LPUART1_IRQn,
            uart4 = USART3_4_5_6_LPUART1_IRQn,
            uart5 = USART3_4_5_6_LPUART1_IRQn,
            uart6 = USART3_4_5_6_LPUART1_IRQn,

            i2c1 = I2C1_IRQn,
            i2c2 = I2C2_3_IRQn,
            i2c3 = I2C2_3_IRQn,

            dma11 = DMA1_Channel1_IRQn,
            dma12 = DMA1_Channel2_3_IRQn,
            dma13 = DMA1_Channel2_3_IRQn,
			dma14 = DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQn,
			dma15 = DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQn,
			dma16 = DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQn,
			dma17 = DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQn,

            dmamux1 = DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQn
        };
	}
}


#endif // __STM32G0B1_htlINT_Vector__
