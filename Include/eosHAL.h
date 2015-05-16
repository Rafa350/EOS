#ifndef __EOS_HAL_H
#define	__EOS_HAL_H


#include <stdbool.h>


// Ports IO
#define halPort_PORTA   0
#define halPort_PORTB   1
#define halPort_PORTC   2
#define halPort_PORTD   3
#define halPort_PORTE   4
#define halPort_NUM_PORTS 5

extern void halPortSetupInput(unsigned port, unsigned pin);
extern void halPortSetupOutput(unsigned port, unsigned pin);
extern void halPortSet(unsigned port, unsigned pin, bool state);
extern bool halPortGet(unsigned port, unsigned pin);
extern void halPortToggle(unsigned port, unsigned pin);

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

