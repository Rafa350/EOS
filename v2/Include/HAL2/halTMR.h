#ifndef __hal2TMR__
#define	__hal2TMR__


// HAL includes
//
#include "HAL2/hal.h"


#define HAL_TMR_TIMER_1         hal::TMR::Timer::timer1
#define HAL_TMR_TIMER_2         hal::TMR::Timer::timer2
#define HAL_TMR_TIMER_3         hal::TMR::Timer::timer3
#define HAL_TMR_TIMER_4         hal::TMR::Timer::timer4
#define HAL_TMR_TIMER_5         hal::TMR::Timer::timer5


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL2/PIC32/halTMR.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL2/STM32/halTMR.h"

#endif


#endif // __hal2TMR__
