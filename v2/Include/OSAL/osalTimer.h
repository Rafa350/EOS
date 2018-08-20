#ifndef __osalTimer__
#define __osalTimer__


// EOS/OSAL includes
//
#include "osal/osal.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct TIMER *HTimer;
typedef uint32_t TimerOptions;
typedef void (*TimerCallback)(HTimer hTimer);

typedef struct {
	TimerOptions options;
	TimerCallback callback;
	void *context;
} TimerInitializeInfo;

#define OSAL_TIMER_BLOCK               ((unsigned) -1)
#define OSAL_TIMER_NOBLOCK             ((unsigned) 0)

#define OSAL_TIMER_AUTO_POS            0
#define OSAL_TIMER_AUTO_BITS           0b1
#define OSAL_TIMER_AUTO_MASK 	       (OSAL_TIMER_AUTO_BITS << OSAL_TIMER_AUTO_POS)
    
#define OSAL_TIMER_AUTO_OFF            ((TimerOptions)0 << OSAL_TIMER_AUTO_POS)
#define OSAL_TIMER_AUTO_ON             ((TimerOptions)1 << OSAL_TIMER_AUTO_POS)


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
