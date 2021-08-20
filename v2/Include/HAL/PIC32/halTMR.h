#ifndef __PIC32_halTMR__
#define __PIC32_halTMR__


// HAL includes
//
#include "HAL/hal.h"


#ifdef	__cplusplus
extern "C" {
#endif


//#define HAL_TMR_USE_T1_INTERRUPT
#define HAL_TMR_USE_T2_INTERRUPT
#define HAL_TMR_USE_T3_INTERRUPT
#define HAL_TMR_USE_T4_INTERRUPT
#define HAL_TMR_USE_T5_INTERRUPT

// Identificador dels timers
#ifdef _TMR1
#define HAL_TMR_TIMER_1           0
#endif
#ifdef _TMR2
#define HAL_TMR_TIMER_2           1
#endif
#ifdef _TMR3
#define HAL_TMR_TIMER_3           2
#endif
#ifdef _TMR4
#define HAL_TMR_TIMER_4           3
#endif
#ifdef _TMR5
#define HAL_TMR_TIMER_5           4
#endif
#define HAL_TMR_TIMER_NONE        (halTMRTimer) -1)


// Modus 16 o 32 bits
#define HAL_TMR_MODE_pos          0
#define HAL_TMR_MODE_bits         0b1
#define HAL_TMR_MODE_mask         (HAL_TMR_MODE_bits << HAL_TMR_MODE_pos)

#define HAL_TMR_MODE_16           (0 << HAL_TMR_MODE_pos)
#define HAL_TMR_MODE_32           (1 << HAL_TMR_MODE_pos)

// Clock source
#define HAL_TMR_CLKSRC_pos        1
#define HAL_TMR_CLKSRC_bits       0b1
#define HAL_TMR_CLKSRC_mask       (HAL_TMR_CLKSRC_bits << HAL_TMR_CLKSRC_pos)

#define HAL_TMR_CLKSRC_PCLK       (0 << HAL_TMR_CLKSRC_pos)
#define HAL_TMR_CLKSRC_EXT        (1 << HAL_TMR_CLKSRC_pos)

// Clock divider (Prescaler PIC32, atencio timer tipus A/B )
#define HAL_TMR_CLKDIV_pos        2
#define HAL_TMR_CLKDIV_bits       0b111
#define HAL_TMR_CLKDIV_mask       (HAL_TMR_CLKDIV_bits << HAL_TMR_CLKDIV_pos)

#define HAL_TMR_CLKDIV_1          (0 << HAL_TMR_CLKDIV_pos)
#define HAL_TMR_CLKDIV_2          (1 << HAL_TMR_CLKDIV_pos)
#define HAL_TMR_CLKDIV_4          (2 << HAL_TMR_CLKDIV_pos)
#define HAL_TMR_CLKDIV_8          (3 << HAL_TMR_CLKDIV_pos)
#define HAL_TMR_CLKDIV_16         (4 << HAL_TMR_CLKDIV_pos)
#define HAL_TMR_CLKDIV_32         (5 << HAL_TMR_CLKDIV_pos)
#define HAL_TMR_CLKDIV_64         (6 << HAL_TMR_CLKDIV_pos)
#define HAL_TMR_CLKDIV_256        (7 << HAL_TMR_CLKDIV_pos)

#define HAL_TMR_EVENT_UPDATE      0x1
#define HAL_TMR_EVENT_ALL         0x1


typedef uint32_t halTMRTimer;
typedef uint32_t halTMROptions;
typedef struct __halTMRData* halTMRHandler;
typedef void (*halTMRInterruptFunction)(halTMRHandler hTimer, void* params, uint32_t event);

typedef struct  __attribute__((packed , aligned(4))) {
    union {
        __T1CONbits_t TAxCON;
        __T2CONbits_t TBxCON;
    };
    volatile uint32_t TxCONCLR;
    volatile uint32_t TxCONSET;
    volatile uint32_t TxCONINV;
    volatile uint32_t TMRx;
    volatile uint32_t TMRxCLR;
    volatile uint32_t TMRxSET;
    volatile uint32_t TMRxINV;
    volatile uint32_t PRx;
    volatile uint32_t PRxCLR;
    volatile uint32_t PRxSET;
    volatile uint32_t PRxINV;
} halTMRRegisters;

struct __halTMRData {
    halTMRRegisters* regs;
    halTMRInterruptFunction isrFunction;
    void* isrParams;
};
typedef struct __halTMRData halTMRData;

typedef struct {
	halTMRTimer timer;
    uint32_t period;
	halTMROptions options;
} halTMRSettings;


halTMRHandler halTMRInitialize(halTMRData* data, const halTMRSettings* settings);
void halTMRShutdown(halTMRHandler hTimer);

uint32_t halTMRGetCounter(halTMRHandler handler);
void halTMRSetCounter(halTMRHandler handler, uint32_t counter);
void halTMRSetPeriod(halTMRHandler handler, uint32_t period);

void halTMRStartTimer(halTMRHandler hTimer);
void halTMRStopTimer(halTMRHandler hTimer);

void halTMRSetInterruptFunction(halTMRHandler timer, halTMRInterruptFunction function, void* params);
void halTMRInterruptHandler(halTMRHandler handler);

void halTMREnableInterrupts(halTMRHandler timer, uint32_t events);
uint32_t halTMRDisableInterrupts(halTMRHandler timer, uint32_t events);

bool halTMRGetInterruptFlag(halTMRHandler timer, uint32_t event);
void halTMRClearInterruptFlags(halTMRHandler timer, uint32_t events);

void halTMRDelay(unsigned time);

#define __halTMRGetTMR1InterruptSourceFlag()     IFS0bits.T1IF
#define __halTMRGetTMR2InterruptSourceFlag()     IFS0bits.T2IF
#define __halTMRGetTMR3InterruptSourceFlag()     IFS0bits.T3IF
#define __halTMRGetTMR4InterruptSourceFlag()     IFS0bits.T4IF
#define __halTMRGetTMR5InterruptSourceFlag()     IFS0bits.T5IF

#define __halTMRClearTMR1InterruptSourceFlag()   IFS0bits.T1IF = 0
#define __halTMRClearTMR2InterruptSourceFlag()   IFS0bits.T2IF = 0
#define __halTMRClearTMR3InterruptSourceFlag()   IFS0bits.T3IF = 0
#define __halTMRClearTMR4InterruptSourceFlag()   IFS0bits.T4IF = 0
#define __halTMRClearTMR5InterruptSourceFlag()   IFS0bits.T5IF = 0


#ifdef	__cplusplus
}
#endif


#endif // __PIC32_halTMR__
