#ifndef __EOSOUTPUTS_H
#define	__EOSOUTPUTS_H

#ifndef __EOS_H
#include "eos.h"
#endif


// Sortides digitals
//
#ifdef eosUSE_OUTPUTS

extern void eosOutSet(UINT8 id, BOOL state);
extern void eosOutToggle(UINT8 id);
extern void eosOutPulse(UINT8 id, unsigned timeOut);
extern void eosOutBlink(UINT8 id, unsigned timeOut);
extern void eosOutAllOFF(void);

#define eosOutSetON(id)                eosOutSet(id, TRUE)
#define eosOutSetOFF(id)               eosOutSet(id, FALSE)

extern void sysOutInitialize(void);
extern void sysOutLoop(void);
extern void sysOutTickInterrupt(void);

#endif

#endif	

