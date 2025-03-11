#pragma once
#ifndef __STM32F030_htlINT_Vectors__
#define __STM32F030_htlINT_Vectors__


// HAL includes
//
#include "HTL/STM32/htl.h"


// Platform check
//
#if !defined(EOS_PLATFORM_STM32F030)
	#error "Valid for STM32F030 platform only"
#endif


namespace htl {

	namespace irq {

		enum class VectorID {

			usart1 = USART1_IRQn,
			usart2 = USART2_IRQn,

			spi1 = SPI1_IRQn,
			spi2 = SPI2_IRQn,

			tmr3 = TIM3_IRQn,
			tmr6 = TIM6_IRQn,
			tmr14 = TIM14_IRQn,
			tmr15 = TIM15_IRQn,
			tmr16 = TIM16_IRQn,
			tmr17 = TIM17_IRQn
		};

	}

}


#endif // __STM32F030_htlINT_Vectors__

