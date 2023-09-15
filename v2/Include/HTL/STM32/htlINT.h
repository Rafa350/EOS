#pragma once
#ifndef __STM32_htlINT__
#define __STM32_htlINT__


// HAL includes
//
#include "HTL/STM32/htl.h"


namespace htl {

	namespace irq {

		enum class Priority {
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

		enum class SubPriority {
			_0,
			_1,
			_2,
			_3,
		};

		enum class VectorID {
			#ifdef HTL_DAC_EXIST
				dac = TIM6_DAC_IRQn,
			#endif
			#ifdef HTL_DMA2D_EXIST
				dma2d = DMA2D_IRQn,
			#endif
			#if defined(EOS_PLATFORM_STM32F0)
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
			#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
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
			#elif defined(EOS_PLATFORM_STM32G0)
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
			#endif
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
				#if defined(EOS_PLATFORM_STM32G0)
					tmr1_CC = TIM1_CC_IRQn,
					tmr1_BRK_UP_TRG_COM = TIM1_BRK_UP_TRG_COM_IRQn,
				#elif defined(EOS_PLATFORM_STM32F0)
					tmr1_BRK = TIM1_BRK_UP_TRG_COM_IRQn,
					tmr1_CC = TIM1_CC_IRQn,
					tmr1_TRG = TIM1_BRK_UP_TRG_COM_IRQn,
					tmr1_UP = TIM1_BRK_UP_TRG_COM_IRQn,
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
					tmr1_BRK = TIM1_BRK_TIM9_IRQn,
					tmr1_CC = TIM1_CC_IRQn,
					tmr1_TRG = TIM1_TRG_COM_TIM11_IRQn,
					tmr1_UP = TIM1_UP_TIM10_IRQn,
				#endif
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
				#if defined(EOS_PLATFORM_STM32G0)
				tmr6 = TIM6_DAC_LPTIM1_IRQn,
				#else
				tmr6 = TIM6_DAC_IRQn,
				#endif
			#endif
			#ifdef HTL_TMR7_EXIST
				#if defined(EOS_PLATFORM_STM32G0)
				tmr7 = TIM7_LPTIM2_IRQn,
				#else
				tmr7 = TIM7_IRQn,
				#endif
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
				#if defined(EOS_PLATFORM_STM32F0)
					tmr14 = TIM14_IRQn,
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
					tmr14 = TIM8_TRG_COM_TIM14_IRQn,
				#elif defined(EOS_PLATFORM_STM32G0)
					tmr14 = TIM14_IRQn,
				#endif
			#endif
			#ifdef HTL_UART1_EXIST
				uart1 = USART1_IRQn,
			#endif
			#ifdef HTL_UART2_EXIST
				uart2 = USART2_IRQn,
			#endif
			#ifdef HTL_UART3_EXIST
				#if defined(EOS_PLATFORM_STM32G0)
				uart3 = USART3_4_LPUART1_IRQn,
				#else
				uart3 = USART3_IRQn,
				#endif
			#endif
			#ifdef HTL_UART4_EXIST
				#if defined(EOS_PLATFORM_STM32G0)
				uart4 = USART3_4_LPUART1_IRQn,
				#else
				uart4 = UART4_IRQn,
				#endif
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
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
					i2c1_EV = I2C1_EV_IRQn,
					i2c1_ER = I2C1_ER_IRQn,
				#elif defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32G0)
					i2c1 = I2C1_IRQn,
				#endif
			#endif
			#ifdef HTL_I2C2_EXIST
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
					i2c2_EV = I2C2_EV_IRQn,
					i2c2_ER = I2C2_ER_IRQn,
				#elif defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32G0)
					i2c2 = I2C2_IRQn,
				#endif
			#endif
			#ifdef HTL_I2C3_EXIST
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
					i2c3_EV = I2C3_EV_IRQn,
					i2c3_ER = I2C3_ER_IRQn,
				#elif defined(EOS_PLATFORM_STM32G0)
					i2c3 = I2C3_IRQn,
				#endif
			#endif
			#ifdef HTL_I2C4_EXIST
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
					i2c4_EV = I2C4_EV_IRQn,
					i2c4_ER = I2C4_ER_IRQn,
				#elif defined(EOS_PLATFORM_STM32G0)
					i2c4 = I2C4_IRQn,
				#endif
			#endif
		};


		void setInterruptVectorPriority(VectorID vector, Priority priority, SubPriority subPriority);

		inline void enableInterrupts() {
			__enable_irq();
		}

		inline bool disableInterrupts() {
			bool state = __get_PRIMASK() == 0;
			__disable_irq();
			return state;
		}

		inline void restoreInterrupts(
			bool state) {

			if (state)
				enableInterrupts();
		}

		inline void enableInterruptVector(
			VectorID vector) {

			NVIC_EnableIRQ((IRQn_Type) vector);
		}

		inline void disableInterruptVector(
			VectorID vector) {

			NVIC_DisableIRQ((IRQn_Type) vector);
		}
	}
}


#endif // __STM32_htlINT__
