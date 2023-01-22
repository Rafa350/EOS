#pragma once
#ifndef __htl__
#define __htl__


#include "eos.h"
#include "eosAssert.h"


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


// Comprova l'esistencia dels m oduls TIM
//
#ifdef TIM1_BASE
	#define HTL_TIM1_EXIST
#endif
#ifdef TIM2_BASE
	#define HTL_TIM2_EXIST
#endif
#ifdef TIM3_BASE
	#define HTL_TIM3_EXIST
#endif
#ifdef TIM4_BASE
	#define HTL_TIM4_EXIST
#endif
#ifdef TIM5_BASE
	#define HTL_TIM5_EXIST
#endif
#ifdef TIM6_BASE
	#define HTL_TIM6_EXIST
#endif
#ifdef TIM7_BASE
	#define HTL_TIM7_EXIST
#endif
#ifdef TIM8_BASE
	#define HTL_TIM8_EXIST
#endif
#ifdef TIM9_BASE
	#define HTL_TIM9_EXIST
#endif
#ifdef TIM10_BASE
	#define HTL_TIM10_EXIST
#endif
#ifdef TIM11_BASE
	#define HTL_TIM11_EXIST
#endif
#ifdef TIM12_BASE
	#define HTL_TIM12_EXIST
#endif
#ifdef TIM13_BASE
	#define HTL_TIM13_EXIST
#endif
#ifdef TIM14_BASE
	#define HTL_TIM14_EXIST
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
#ifdef UART4_BASE
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


namespace htl {
}


#endif // __htl__
