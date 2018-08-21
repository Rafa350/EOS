#ifndef __STM32_halTMR__
#define __STM32_halTMR__


// EOS includes
//
#include "eos.h"

// Standard includes
//
#include "stdint.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t TMRTimer;
typedef uint32_t TMROptions;


// Identificador del timer
#define HAL_TMR_TIMER_1           ((TMRTimer) 0)
#define HAL_TMR_TIMER_2           ((TMRTimer) 1)
#define HAL_TMR_TIMER_3           ((TMRTimer) 2)
#define HAL_TMR_TIMER_4           ((TMRTimer) 3)
#define HAL_TMR_TIMER_5           ((TMRTimer) 4)
//#define HAL_TMR_TIMER_6           ((TMRTimer) 5)
#define HAL_TMR_TIMER_7           ((TMRTimer) 6)
#define HAL_TMR_TIMER_8           ((TMRTimer) 7)
#define HAL_TMR_TIMER_9           ((TMRTimer) 8)
#define HAL_TMR_TIMER_10          ((TMRTimer) 9)
#define HAL_TMR_TIMER_11          ((TMRTimer) 10)
#define HAL_TMR_TIMER_12          ((TMRTimer) 11)
#define HAL_TMR_TIMER_13          ((TMRTimer) 12)
#define HAL_TMR_TIMER_14          ((TMRTimer) 13)
#define HAL_TMR_TIMER_MAX         13

// Modus 16 o 32 bits
#define HAL_TMR_MODE_POS          0u
#define HAL_TMR_MODE_BITS         0b1u
#define HAL_TMR_MODE_MASK         (HAL_TMR_MODE_BITS << HAL_TMR_MODE_POS)

#define HAL_TMR_MODE_16           (0u << HAL_TMR_MODE_POS)
#define HAL_TMR_MODE_32           (1u << HAL_TMR_MODE_POS)

// Clock divider
#define HAL_TMR_CLKDIV_POS        1u
#define HAL_TMR_CLKDIV_BITS       0b11u
#define HAL_TMR_CLKDIV_MASK       (HAL_TMR_CLKDIV_BITS << HAL_TMR_CLKDIV_POS)

#define HAL_TMR_CLKDIV_1          (0u << HAL_TMR_CLKDIV_POS)
#define HAL_TMR_CLKDIV_2          (1u << HAL_TMR_CLKDIV_POS)
#define HAL_TMR_CLKDIV_4          (2u << HAL_TMR_CLKDIV_POS)

// Enable interrupt
#define HAL_TMR_INTERRUPT_POS     3u
#define HAL_TMR_INTERRUPT_BITS    0b1u
#define HAL_TMR_INTERRUPT_MASK    (HAL_TMR_INTERRUPT_BITS << HAL_TMR_INTERRUPT_POS)

#define HAL_TMR_INTERRUPT_DISABLE (0u << HAL_TMR_INTERRUPT_POS)
#define HAL_TMR_INTERRUPT_ENABLE  (1u << HAL_TMR_INTERRUPT_POS)



typedef void (*TMRInterruptCallback)(TMRTimer timer, void *pParams);

typedef struct {
	TMRTimer timer;
	uint32_t prescaler;
	uint32_t period;
	TMROptions options;
	uint32_t irqPriority;
	uint32_t irqSubPriority;
	TMRInterruptCallback pIrqCall;
	void *pIrqParams;
} TMRInitializeInfo;


void halTMRInitialize(const TMRInitializeInfo *pInfo);
void halTMRShutdown(TMRTimer timer);

void halTMRStartTimer(TMRTimer timer);
void halTMRStopTimer(TMRTimer timer);

void halTMRDelay(uint32_t time);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halTMR__
