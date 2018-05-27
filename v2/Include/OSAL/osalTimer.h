#ifndef __osalTimer__
#define __osalTimer__


// EOS includes
//
#include "eos.h"
#include "osal/osal.h"

// Stdlib includes
//
#include <stdbool.h>


#ifdef	__cplusplus
extern "C" {
#endif


#define OSAL_TIMER_BLOCK               ((unsigned) -1)
#define OSAL_TIMER_NOBLOCK             ((unsigned) 0)

#define OSAL_TIMER_AUTO_MASK 	       ((uint32_t)0x00000001)
#define OSAL_TIMER_AUTO_POS            1
#define OSAL_TIMER_AUTO_OFF            ((uint32_t)0 << OSAL_TIMER_AUTO_POS)
#define OSAL_TIMER_AUTO_ON             ((uint32_t)1 << OSAL_TIMER_AUTO_POS)

typedef struct TIMER *HTimer;

typedef void (*TimerCallback)(HTimer hTimer);

typedef struct {
	uint32_t options;
	TimerCallback callback;
	void *context;
} TimerInitializeInfo;


HTimer osalTimerCreate(const TimerInitializeInfo *info);
bool osalTimerDestroy(HTimer hTimer, unsigned waitTime);

bool osalTimerStart(HTimer hTimer, unsigned time, unsigned waitTime);
bool osalTimerStop(HTimer hTimer, unsigned waitTime);

bool osalTimerIsActive(HTimer hTimer);
void *osalTimerGetContext(HTimer hTimer);


#ifdef	__cplusplus
}
#endif


#endif // __osalTimer__
