#ifndef __STM32_halTMR__
#define __STM32_halTMR__


// EOS includes
//
#include "eos.h"

// Stdlib includes
//
#include "stdint.h"


#ifdef	__cplusplus
extern "C" {
#endif


#define HAL_TMR_USE_T1_INTERRUPT    0
#define HAL_TMR_USE_T2_INTERRUPT    1
#define HAL_TMR_USE_T3_INTERRUPT    1
#define HAL_TMR_USE_T4_INTERRUPT    1
#define HAL_TMR_USE_T5_INTERRUPT    1

#define HAL_TMR_ID_1                0
#define HAL_TMR_ID_2                1
#define HAL_TMR_ID_3                2
#define HAL_TMR_ID_4                3
#define HAL_TMR_ID_5                4
#define HAL_TMR_ID_6                5
#define HAL_TMR_ID_7                6
#define HAL_TMR_ID_8                7
#define HAL_TMR_ID_9                8
#define HAL_TMR_ID_10               9
#define HAL_TMR_ID_11               10
#define HAL_TMR_ID_12               11
#define HAL_TMR_ID_13               12
#define HAL_TMR_ID_14               13
#define HAL_TMR_ID_MAX              13

#define HAL_TMR_MODE16              0
#define HAL_TMR_MODE32              1

#define HAL_TMR_PS_1                0
#define HAL_TMR_PS_2                1
#define HAL_TMR_PS_4                2
#define HAL_TMR_PS_8                3
#define HAL_TMR_PS_16               4
#define HAL_TMR_PS_32               5
#define HAL_TMR_PS_64               6
#define HAL_TMR_PS_256              7


typedef void (*TMRInterruptCallback)(uint8_t id, void *params);

typedef struct {
	uint8_t id;
	uint32_t options;
	TMRInterruptCallback intFunction;
	void *intParams;
} TMRInitializeInfo;


void halTMRInitialize(const TMRInitializeInfo *info);
void halTMRShutdown(uint8_t id);

void halTMRStartTimer(uint8_t id);
void halTMRStopTimer(uint8_t id);

void halTMRDelay(uint32_t time);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halTMR__
