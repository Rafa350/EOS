#ifndef __STM32_halSYS__
#define	__STM32_halSYS__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


void halSYSInitialize();

void halSYSInterruptEnable();
void halSYSInterruptDisable();


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halSYS__


