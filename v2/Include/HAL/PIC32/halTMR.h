#ifndef __PIC32_halTMR__
#define __PIC32_halTMR__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif

    
typedef uint8_t TMRTimer;
typedef uint32_t TMROptions;
typedef void (*TMRInterruptCallback)(TMRTimer timer, void *params);


//#define HAL_TMR_USE_T1_INTERRUPT    
#define HAL_TMR_USE_T2_INTERRUPT    
#define HAL_TMR_USE_T3_INTERRUPT    
#define HAL_TMR_USE_T4_INTERRUPT    
#define HAL_TMR_USE_T5_INTERRUPT    

#define HAL_TMR_TIMER_1           ((TMRTimer) 0)
#define HAL_TMR_TIMER_2           ((TMRTimer) 1)
#define HAL_TMR_TIMER_3           ((TMRTimer) 2)
#define HAL_TMR_TIMER_4           ((TMRTimer) 3)
#define HAL_TMR_TIMER_5           ((TMRTimer) 4)
#define HAL_TMR_TIMER_MAX         5

// Modus 16 o 32 bits
#define HAL_TMR_MODE_POS          0
#define HAL_TMR_MODE_BITS         0b1
#define HAL_TMR_MODE_MASK         (HAL_TMR_MODE_BITS << HAL_TMR_MODE_POS)

#define HAL_TMR_MODE_16           (0 << HAL_TMR_MODE_POS)
#define HAL_TMR_MODE_32           (1 << HAL_TMR_MODE_POS)

// Clock source
#define HAL_TMR_CLKSRC_POS        1
#define HAL_TMR_CLKSRC_BITS       0b1
#define HAL_TMR_CLKSRC_MASK       (HAL_TMR_CLKSRC_BITS << HAL_TMR_CLKSRC_POS)

#define HAL_TMR_CLKSRC_PCLK       (0 << HAL_TMR_CLKSRC_POS)
#define HAL_TMR_CLKSRC_EXT        (1 << HAL_TMR_CLKSRC_POS)

// Clock divider (Prescaler PIC32)
#define HAL_TMR_CLKDIV_POS        2
#define HAL_TMR_CLKDIV_BITS       0b111
#define HAL_TMR_CLKDIV_MASK       (HAL_TMR_CLKDIV_BITS << HAL_TMR_CLKDIV_POS)

#define HAL_TMR_CLKDIV_1          (0 << HAL_TMR_CLKDIV_POS)
#define HAL_TMR_CLKDIV_2          (1 << HAL_TMR_CLKDIV_POS)
#define HAL_TMR_CLKDIV_4          (2 << HAL_TMR_CLKDIV_POS)
#define HAL_TMR_CLKDIV_8          (3 << HAL_TMR_CLKDIV_POS)
#define HAL_TMR_CLKDIV_16         (4 << HAL_TMR_CLKDIV_POS)
#define HAL_TMR_CLKDIV_32         (5 << HAL_TMR_CLKDIV_POS)
#define HAL_TMR_CLKDIV_64         (6 << HAL_TMR_CLKDIV_POS)
#define HAL_TMR_CLKDIV_256        (7 << HAL_TMR_CLKDIV_POS)

// Enable interrupt
#define HAL_TMR_INTERRUPT_POS     5
#define HAL_TMR_INTERRUPT_BITS    0b1
#define HAL_TMR_INTERRUPT_MASK    (HAL_TMR_INTERRUPT_BITS << HAL_TMR_INTERRUPT_POS)

#define HAL_TMR_INTERRUPT_DISABLE (0 << HAL_TMR_INTERRUPT_POS)
#define HAL_TMR_INTERRUPT_ENABLE  (1 << HAL_TMR_INTERRUPT_POS)


typedef struct {
	TMRTimer timer;
    uint32_t period;
	TMROptions options;
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


#endif // __PIC32_halTMR__
