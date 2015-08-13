#ifndef __EOS_HAL_H
#define	__EOS_HAL_H


#include <stdbool.h>


// Timers
#define halTimer_TMR1   0
#define halTimer_TMR2   1
#define halTimer_TMR3   2
#define halTimer_TMR4   3
#define halTimer_TMR5   4
#define halTimer_NUM_TIMERS 5

typedef void (*halTimerInterruptCallback) (unsigned timer);

extern void halTimerSetInterruptCallback(unsigned timer, halTimerInterruptCallback callback);
extern void halTimerStart(unsigned timer);
extern void halTimerStop(unsigned timer);
extern void halTimerSetInterruptPriority(unsigned timer, unsigned priority, unsigned subPriority);
extern bool halTimerSetInterruptEnable(unsigned timer, bool enabled);


#endif

