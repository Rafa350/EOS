#ifndef __EOSDEBUGGER_H
#define	__EOSDEBUGGER_H

#ifndef __EOS_H
#include "eos.h"
#endif


// Indicador d'estat
//
#ifdef eosUSE_LED

extern void sysLedInitialize(void);
extern void sysLedTickInterrupt(void);

#endif


#endif	

