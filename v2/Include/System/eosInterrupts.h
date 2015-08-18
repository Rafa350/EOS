#ifndef __EOS_INTERRUPTS_H
#define	__EOS_INTERRUPTS_H


#include "peripheral/int/plib_int.h"


#define eosInterruptEnable()                PLIB_INT_Enable(INT_ID_0)
#define eosInterruptRestore(e)              if (e) PLIB_INT_Enable(INT_ID_0)
#define eosInterruptSourceEnable(s)         PLIB_INT_SourceEnable(INT_ID_0, s)
#define eosInterruptSourceRestore(s, e)     if (e) PLIB_INT_SourceEnable(INT_ID_0, s)
#define eosInterruptSourceFlagClear(s)      PLIB_INT_SourceFlagClear(INT_ID_0, s)
#define eosInterruptSourceFlagGet(s)        PLIB_INT_SourceFlagGet(INT_ID_0, s)

extern bool eosInterruptDisable();
extern bool eosInterruptSourceDisable(INT_SOURCE source);


#endif	

