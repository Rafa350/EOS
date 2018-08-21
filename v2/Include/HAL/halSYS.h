#ifndef __halSYS__
#define	__halSYS__


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


#endif // __halSYS__


