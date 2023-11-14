#pragma once


#include "HTL/htl.h"


// Comprova l'existencia dels moduls GPIO
//
#ifdef GPIOA_BASE
	#define HTL_GPIOA_EXIST
#endif
#ifdef GPIOB_BASE
	#define HTL_GPIOB_EXIST
#endif
#ifdef GPIOC_BASE
	#define HTL_GPIOC_EXIST
#endif
#ifdef GPIOD_BASE
	#define HTL_GPIOD_EXIST
#endif
#ifdef GPIOE_BASE
	#define HTL_GPIOE_EXIST
#endif
#ifdef GPIOF_BASE
	#define HTL_GPIOF_EXIST
#endif
#ifdef GPIOG_BASE
	#define HTL_GPIOG_EXIST
#endif
#ifdef GPIOH_BASE
	#define HTL_GPIOH_EXIST
#endif
#ifdef GPIOI_BASE
	#define HTL_GPIOI_EXIST
#endif
#ifdef GPIOJ_BASE
	#define HTL_GPIOJ_EXIST
#endif
#ifdef GPIOK_BASE
	#define HTL_GPIOK_EXIST
#endif


// Comprova l'esistencia dels moduls TIM
//
#ifdef TIM1_BASE
	#define HTL_TMR1_EXIST
#endif
#ifdef TIM2_BASE
	#define HTL_TMR2_EXIST
#endif
#ifdef TIM3_BASE
	#define HTL_TMR3_EXIST
#endif
#ifdef TIM4_BASE
	#define HTL_TMR4_EXIST
#endif
#ifdef TIM5_BASE
	#define HTL_TMR5_EXIST
#endif
#ifdef TIM6_BASE
	#define HTL_TMR6_EXIST
#endif
#ifdef TIM7_BASE
	#define HTL_TMR7_EXIST
#endif
#ifdef TIM8_BASE
	#define HTL_TMR8_EXIST
#endif
#ifdef TIM9_BASE
	#define HTL_TMR9_EXIST
#endif
#ifdef TIM10_BASE
	#define HTL_TMR10_EXIST
#endif
#ifdef TIM11_BASE
	#define HTL_TMR11_EXIST
#endif
#ifdef TIM12_BASE
	#define HTL_TMR12_EXIST
#endif
#ifdef TIM13_BASE
	#define HTL_TMR13_EXIST
#endif
#ifdef TIM14_BASE
	#define HTL_TMR14_EXIST
#endif
#ifdef TIM15_BASE
	#define HTL_TMR15_EXIST
#endif
#ifdef TIM16_BASE
	#define HTL_TMR16_EXIST
#endif
#ifdef TIM17_BASE
	#define HTL_TMR17_EXIST
#endif


// Comprova l'existencia dels moduls I2C
//
#ifdef I2C1_BASE
	#define HTL_I2C1_EXIST
#endif
#ifdef I2C2_BASE
	#define HTL_I2C2_EXIST
#endif
#ifdef I2C3_BASE
	#define HTL_I2C3_EXIST
#endif
#ifdef I2C4_BASE
	#define HTL_I2C4_EXIST
#endif


// Comprova l'existencia dels moduls SPI
//
#ifdef SPI1_BASE
	#define HTL_SPI1_EXIST
#endif
#ifdef SPI2_BASE
	#define HTL_SPI2_EXIST
#endif
#ifdef SPI3_BASE
	#define HTL_SPI3_EXIST
#endif
#ifdef SPI4_BASE
	#define HTL_SPI4_EXIST
#endif
#ifdef SPI5_BASE
	#define HTL_SPI5_EXIST
#endif
#ifdef SPI6_BASE
	#define HTL_SPI6_EXIST
#endif


// Comprova l'existencia dels moduls UART/USART
//
#ifdef USART1_BASE
	#define HTL_UART1_EXIST
#endif
#ifdef USART2_BASE
	#define HTL_UART2_EXIST
#endif
#ifdef USART3_BASE
	#define HTL_UART3_EXIST
#endif
#ifdef USART4_BASE
	#define HTL_UART4_EXIST
#endif
#ifdef UART5_BASE
	#define HTL_UART5_EXIST
#endif
#ifdef USART6_BASE
	#define HTL_UART6_EXIST
#endif
#ifdef UART7_BASE
	#define HTL_UART7_EXIST
#endif
#ifdef UART8_BASE
	#define HTL_UART8_EXIST
#endif


#ifdef DMA1_Channel1
#define HTL_DMA1_CHANNEL1_EXISTS
#endif
#ifdef DMA1_Channel2
#define HTL_DMA1_CHANNEL2_EXISTS
#endif
#ifdef DMA1_Channel3
#define HTL_DMA1_CHANNEL3_EXISTS
#endif
#ifdef DMA1_Channel4
#define HTL_DMA1_CHANNEL4_EXISTS
#endif
#ifdef DMA1_Channel5
#define HTL_DMA1_CHANNEL5_EXISTS
#endif
#ifdef DMA1_Channel6
#define HTL_DMA1_CHANNEL6_EXISTS
#endif
#ifdef DMA1_Channel7
#define HTL_DMA1_CHANNEL7_EXISTS
#endif
#ifdef DMA2_Channel1
#define HTL_DMA2_CHANNEL1_EXISTS
#endif
#ifdef DMA2_Channel2
#define HTL_DMA2_CHANNEL2_EXISTS
#endif
#ifdef DMA2_Channel3
#define HTL_DMA2_CHANNEL3_EXISTS
#endif
#ifdef DMA2_Channel4
#define HTL_DMA2_CHANNEL4_EXISTS
#endif
#ifdef DMA2_Channel5
#define HTL_DMA2_CHANNEL5_EXISTS
#endif
#ifdef DMA2_Channel6
#define HTL_DMA2_CHANNEL6_EXISTS
#endif
#ifdef DMA2_Channel7
#define HTL_DMA2_CHANNEL7_EXISTS
#endif



// Comprova l'existencia del modul LTDC
//
#ifdef LTDC_BASE
	#define HTL_LTDC_EXIST
#endif


// Comprova l'existencia del modul DMA2D
//
#ifdef DMA2D_BASE
	#define HTL_DMA2D_EXIST
#endif


// Frequencia dels osciladors interns
//
#if defined(EOS_PLATFORM_STM32F0)
	#define CLOCK_HSI_FREQUENCY        8000000
	#define CLOCK_HSI14_FREQUENCY     14000000
	#define CLOCK_LSI_FREQUENCY          40000

#elif defined(EOS_PLATFORM_STM32F4)
	#define CLOCK_HSI_FREQUENCY       16000000
	#define CLOCK_LSI_FREQUENCY          32000

#elif defined(EOS_PLATFORM_STM32F7)
	#define CLOCK_HSI_FREQUENCY       16000000
	#define CLOCK_LSI_FREQUENCY          32000

#elif defined(EOS_PLATFORM_STM32G0)
	#define CLOCK_HSI16_FREQUENCY     16000000
	#define CLOCK_HSI48_FREQUENCY     48000000
	#ifndef CLOCK_HSE_FREQUENCY
		#define CLOCK_HSE_FREQUENCY    8000000
	#endif
	#define CLOCK_LSI_FREQUENCY          32000
	#ifndef CLOCK_LSE_FREQUENCY
		#define CLOCK_LSE_FREQUENCY      32768
	#endif

#else
	#error "Unknown platform"

#endif


#ifndef HTL_TICK_TIMER
    #define HTL_TICK_TIMER htl::tmr::TMRDevice14
#endif


namespace htl {

}
