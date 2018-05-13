#ifndef __osalTimer__
#define __osalTimer__


// EOS includes
//
#include "eos.h"
#include "osal/osal.h"

// Stdlib includes
//
#include "stdint.h"


#ifdef	__cplusplus
extern "C" {
#endif


#define OSAL_TIMER_BLOCK     ((unsigned) -1)
#define OSAL_TIMER_NOBLOCK   ((unsigned) 0)


typedef void *TimerHandler;

typedef void (*TimerCallback)(TimerHandler handler);

typedef struct {
	unsigned autoreload;
	TimerCallback callback;
	void *context;
} TimerInitializeInfo;


uint8_t osalTimerCreate(const TimerInitializeInfo *info, TimerHandler *handler);
uint8_t osalTimerDestroy(TimerHandler handler, unsigned blockTime);

uint8_t osalTimerStart(TimerHandler handler, unsigned time, unsigned blockTime);
uint8_t osalTimerStop(TimerHandler handler, unsigned blockTime);

uint8_t osalTimerIsActive(TimerHandler handler);
uint8_t osalTimerGetContext(TimerHandler handler, void **context);


#ifdef	__cplusplus
}
#endif


#endif // __osalTimer__
