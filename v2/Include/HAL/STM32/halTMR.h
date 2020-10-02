#ifndef __STM32_halTMR__
#define __STM32_halTMR__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


// Identificador del timer
#define HAL_TMR_TIMER_1           0
#define HAL_TMR_TIMER_2           1
#define HAL_TMR_TIMER_3           2
#define HAL_TMR_TIMER_4           3
#define HAL_TMR_TIMER_5           4
#define HAL_TMR_TIMER_6           5
#define HAL_TMR_TIMER_7           6
#define HAL_TMR_TIMER_8           7
#define HAL_TMR_TIMER_9           8
#define HAL_TMR_TIMER_10          9
#define HAL_TMR_TIMER_11          10
#define HAL_TMR_TIMER_12          11
#define HAL_TMR_TIMER_13          12
#define HAL_TMR_TIMER_14          13

// Opcions: Modus 16 o 32 bits
#define HAL_TMR_MODE_pos          0
#define HAL_TMR_MODE_bits         0b1
#define HAL_TMR_MODE_mask         (HAL_TMR_MODE_bits << HAL_TMR_MODE_pos)

#define HAL_TMR_MODE_16           (0 << HAL_TMR_MODE_pos)
#define HAL_TMR_MODE_32           (1 << HAL_TMR_MODE_pos)

// Opcions: Clock divider
#define HAL_TMR_CLKDIV_pos        1
#define HAL_TMR_CLKDIV_bits       0b11
#define HAL_TMR_CLKDIV_mask       (HAL_TMR_CLKDIV_bits << HAL_TMR_CLKDIV_pos)

#define HAL_TMR_CLKDIV_1          (0 << HAL_TMR_CLKDIV_pos)
#define HAL_TMR_CLKDIV_2          (1 << HAL_TMR_CLKDIV_pos)
#define HAL_TMR_CLKDIV_4          (2 << HAL_TMR_CLKDIV_pos)

// Opcions: Count direction
#define HAL_TMR_DIRECTION_pos     3
#define HAL_TMR_DIRECTION_bits    0b1
#define HAL_TMR_DIRECTION_mask    (1 << HAL_TMR_DIRECTION_pos)

#define HAL_TMR_DIRECTION_UP      (0 << HAL_TMR_DIRECTION_pos)
#define HAL_TMR_DIRECTION_DOWN    (1 << HAL_TMR_DIRECTION_pos)

// Identificador dels events
#define HAL_TMR_EVENT_BRK         0x01
#define HAL_TMR_EVENT_CC          0x02
#define HAL_TMR_EVENT_COM         0x04
#define HAL_TMR_EVENT_TRG         0x08
#define HAL_TMR_EVENT_UP          0x10
#define HAL_TMR_EVENT_ALL         0x1F


typedef uint32_t TMRTimer;
typedef uint32_t TMROptions;

typedef struct __TMRData* TMRHandler;

typedef void (*TMRInterruptFunction)(TMRHandler handler, void* params);

struct __TMRData {
	TIM_TypeDef* regs;
	TMRInterruptFunction isrFunction;
	void* isrParams;
};
typedef struct __TMRData TMRData;

typedef struct {
	TMRTimer timer;
	uint32_t prescaler;
	uint32_t period;
	TMROptions options;
} TMRInitializeInfo;

TMRHandler halTMRInitialize(TMRData* data, const TMRInitializeInfo* info);
void halTMRShutdown(TMRHandler handler);

void halTMRStartTimer(TMRHandler handler);
void halTMRStopTimer(TMRHandler handler);

void halTMRSetInterruptFunction(TMRHandler handler, TMRInterruptFunction function, void* params);
void halTMRInterruptHandler(TMRHandler handler);

void halTMREnableInterruptSources(TMRHandler handler, uint32_t events);
uint32_t halTMRDisableInterruptSources(TMRHandler handler, uint32_t events);
bool halTMRGetInterruptSourceFlag(TMRHandler handler, uint32_t event);
void halTMRClearInterruptSourceFlag(TMRHandler handler, uint32_t event);


#define halTMRDelay(time)         HAL_Delay(time)


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halTMR__
