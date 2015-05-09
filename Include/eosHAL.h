#ifndef __EOS_HAL_H
#define	__EOS_HAL_H


// Ports IO
#define halPort_PORTA   0
#define halPort_PORTB   1
#define halPort_PORTC   2
#define halPort_PORTD   3
#define halPort_PORTE   4

void halPortSetupInput(unsigned port, unsigned pin);
void halPortSetupOutput(unsigned port, unsigned pin);
void halPortSet(unsigned port, unsigned pin, unsigned state);
unsigned halPortGet(unsigned port, unsigned pin);
void halPortToggle(unsigned port, unsigned pin);


#endif

