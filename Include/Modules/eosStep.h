#ifndef __EOSSTEP_H
#define	__EOSSTEP_H

#ifndef __EOS_H
#include "eos.h"
#endif


// Control de motor pas  pas
//
#ifdef eosUSE_STEP

extern BOOL eosStpMove(UINT8 id, unsigned upRamp, unsigned dwRamo, unsigned speed, int steps);

extern void sysStpInitialize(void);
extern void sysStpTickInterrupt(void);

#endif


#endif	

