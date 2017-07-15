#ifndef __halTMR__
#define __halTMR__

#ifdef	__cplusplus
extern "C" {
#endif


#include <stdint.h>


#define HAL_TMR_USE_T1_INTERRUPT    0
#define HAL_TMR_USE_T2_INTERRUPT    1
#define HAL_TMR_USE_T3_INTERRUPT    1
#define HAL_TMR_USE_T4_INTERRUPT    1
#define HAL_TMR_USE_T5_INTERRUPT    1

#define HAL_TMR_T1                  0
#define HAL_TMR_T2                  1
#define HAL_TMR_T3                  2
#define HAL_TMR_T4                  3
#define HAL_TMR_T5                  4

#define HAL_TMR_MODE16              0
#define HAL_TMR_MODE32              1

#define HAL_TMR_PS1                 0
#define HAL_TMR_PS2                 1
#define HAL_TMR_PS4                 2
#define HAL_TMR_PS8                 3
#define HAL_TMR_PS16                4
#define HAL_TMR_PS32                5
#define HAL_TMR_PS64                6
#define HAL_TMR_PS256               7


typedef uint8_t TMRTimer;
typedef void (*TMRInterruptCallback)(uint8_t timer, void *param);


void halTMRInitializeTimer(TMRTimer timer, uint8_t mode, uint8_t prescale,
        unsigned period, TMRInterruptCallback callback, void *param);
void halTMRStartTimer(TMRTimer timer);
void halTMRStopTimer(TMRTimer timer);

void halTMRDelay(uint32_t time);


#ifdef	__cplusplus
}
#endif

#endif // __halTMR__
