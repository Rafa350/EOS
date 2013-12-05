#ifndef __EOS_H
#define	__EOS_H

#include "xc.h"

#ifndef __HARDWAREPROFILE_H
#include "hardwareprofile.h"
#endif

#ifndef __EOSCONFIG_H
#include "eosconfig.h"
#endif


#ifdef EOS_USE_SYSMAIN
extern void eosMain(void);
#endif
extern void eosTick(void);
extern void eosInterrupt(void);


// Gestio dels ports de sortida digital
//
#ifdef EOS_USE_OUTPUTS
extern void eosOutSet(UINT8 out, BOOL s);
extern BOOL eosOutGet(UINT8 out);
extern void eosOutToggle(UINT8 out);
extern void eosOutPulse(UINT8 out, UINT16 timeOut);
extern void eosOutAllOFF(void);

extern void sysOutInitialize(void);
extern void sysOutTick(void);
extern void sysOutInterrupt(void);
extern void sysOutLoop(void);
#endif

// Gestio dels ports d'entrada digital
//
#ifdef EOS_USE_INPUTS
extern BOOL eosInpGet(UINT8 inp);
extern BOOL eosInpPosEdge(UINT8 inp);
extern BOOL eosInpNegEdge(UINT8 inp);

extern void sysInpInitialize(void);
extern void sysInpTick(void);
extern void sysInpInterrupt(void);
extern void sysInpLoop(void);
#endif


#endif	

