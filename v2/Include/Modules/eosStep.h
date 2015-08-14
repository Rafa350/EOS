#ifndef __EOSSTEP_H
#define	__EOSSTEP_H

#ifndef __EOS_H
#include "eos.h"
#endif


// Control de motor pas  pas
//
#ifdef eosUSE_STEP

extern void eosStpMove(UINT8 id, unsigned upRamp, unsigned dwRamo, unsigned speed, int steps);
extern BOOL eosStpIsBusy(UINT8 id);

extern void sysStpInitialize(void);
extern void sysStpTickInterrupt(void);

#endif


#endif	

