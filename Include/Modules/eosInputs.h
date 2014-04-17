#ifndef __EOSINPUTS_H
#define	__EOSINPUTS_H

#ifndef __EOS_H
#include "eos.h"
#endif


// Entrades digitals
//
#ifdef eosUSE_INPUTS

extern BOOL eosInpGet(UINT8 id);
extern BOOL eosInpPosEdge(UINT8 id);
extern BOOL eosInpNegEdge(UINT8 id);

extern void sysInpInitialize(void);
extern void sysInpLoop(void);
extern void sysInpTickInterrupt(void);

#endif


#endif	

