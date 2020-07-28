#ifndef __PIC32_halTMR__
#define __PIC32_halTMR__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif
    
typedef struct  __attribute__((packed , aligned(4))) {
    __T1CONbits_t TxCON;
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
} TMRTypeARegisters;

typedef struct  __attribute__((packed , aligned(4))) {
    __T2CONbits_t TxCON;
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
} TMRTypeBRegisters;

#define IsTypeA(timer)                  (timer == HAL_TMR_TIMER_1)
#define GetTimerARegisterPtr(timer)     ((TMRTypeARegisters*)(0xBF800600 + ((timer) * 0x0200)))
#define GetTimerBRegisterPtr(timer)     ((TMRTypeBRegisters*)(0xBF800600 + ((timer) * 0x0200)))
#define GetTimerBRegisterHiPtr(timer)   ((TMRTypeBRegisters*)(0xBF800600 + ((timer) * 0x0200) + 0x0200))


typedef uint8_t TMRTimer;
typedef uint32_t TMROptions;
typedef void (*TMRInterruptFunction)(TMRTimer timer, void* params);


//#define HAL_TMR_USE_T1_INTERRUPT
#define HAL_TMR_USE_T2_INTERRUPT
#define HAL_TMR_USE_T3_INTERRUPT
#define HAL_TMR_USE_T4_INTERRUPT
#define HAL_TMR_USE_T5_INTERRUPT

#ifdef _TMR1
#define HAL_TMR_TIMER_1           ((TMRTimer) 0)
#endif
#ifdef _TMR2
#define HAL_TMR_TIMER_2           ((TMRTimer) 1)
#endif
#ifdef _TMR3
#define HAL_TMR_TIMER_3           ((TMRTimer) 2)
#endif
#ifdef _TMR4
#define HAL_TMR_TIMER_4           ((TMRTimer) 3)
#endif
#ifdef _TMR5
#define HAL_TMR_TIMER_5           ((TMRTimer) 4)
#endif
#define HAL_TMR_TIMER_NONE        ((TMRTimer) 255)

#define HAL_TMR_TIMER_MAX         5

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

// Enable interrupt
#define HAL_TMR_INTERRUPT_pos     5
#define HAL_TMR_INTERRUPT_bits    0b1
#define HAL_TMR_INTERRUPT_mask    (HAL_TMR_INTERRUPT_bits << HAL_TMR_INTERRUPT_pos)

#define HAL_TMR_INTERRUPT_DISABLE (0 << HAL_TMR_INTERRUPT_pos)
#define HAL_TMR_INTERRUPT_ENABLE  (1 << HAL_TMR_INTERRUPT_pos)


typedef struct {
	TMRTimer timer;
    unsigned period;
	TMROptions options;
    int irqPriority;
    int irqSubPriority;
	TMRInterruptFunction isrFunction;
	void* isrParams;
} TMRInitializeInfo;


void halTMRInitialize(const TMRInitializeInfo* info);
void halTMRShutdown(TMRTimer timer);

void halTMRStartTimer(TMRTimer timer);
void halTMRStopTimer(TMRTimer timer);

void halTMRDelay(unsigned time);

void halTMRSetInterruptFunction(TMRTimer timer, TMRInterruptFunction function, void* params);
void halTMRSetInterruptPriority(TMRTimer timer, unsigned priority, unsigned subPriority);
bool halTMRGetInterruptFlag(TMRTimer timer);
void halTMRClearInterruptFlag(TMRTimer timer);
void halTMREnableInterrupt(TMRTimer timer);
void halTMRDisableInterrupt(TMRTimer timer);


#ifdef	__cplusplus
}
#endif


#endif // __PIC32_halTMR__
