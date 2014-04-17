#ifndef __EOSTIMERS_H
#define	__EOSTIMERS_H

#ifndef __EOS_H
#include "eos.h"
#endif


// Temporitzadors
//
#ifdef eosUSE_TIMERS
extern void eosTimStart(UINT8 id, unsigned time);
extern BOOL eosTimGet(UINT8 id);
extern void eosTimPause(UINT8 id);
extern void eosTimContinue(UINT8 id);

extern void sysTimInitialize(void);
extern void sysTimLoop(void);
extern void sysTimTickInterrupt(void);
#endif


#endif	

