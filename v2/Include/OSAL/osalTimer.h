#ifndef __osalTimer__
#define __osalTimer__


#ifdef	__cplusplus
extern "C" {
#endif


typedef void *TimerHandler;

typedef void (*TimerCallback)(TimerHandler *timer);

typedef struct {
	unsigned period;
	TimerCallback callback;
} TimerInitializeInfo;


TimerHandler osalTimerCreate(const TimerInitializeInfo *info);
void osalTimerDestroy(TimerHandler timer);

void osalTimerStart(TimerHandler timer);
void osalTimerStop(TimerHandler timer, unsigned blockTime);


#ifdef	__cplusplus
}
#endif


#endif // __osalTimer__
