#ifndef __EOS_H
#define	__EOS_H

#include "xc.h"
#include "GenericTypeDefs.h"

#ifdef __PIC32MX
#include "plib.h"
#endif

#ifndef __HARDWAREPROFILE_H
#include "hardwareprofile.h"
#endif

#ifndef __EOSCONFIG_H
#include "eosconfig.h"
#endif


#ifdef EOS_USE_SYSMAIN
extern void eosMain(void);
#endif
extern void eosTickInterrupt(void);

#if defined( __PIC18)
#define eosEnableInterrupts()     ei()
#define eosDisableInterrupts()    di()
#elif defined(__PIC32MX)
#define eosEnableInterrupts()     INTEnableInterrupts()
#define eosDisableInterrupts()    INTDisableInterrupts()
#endif


// Gestio dels ports de sortida digital
//
#ifdef EOS_USE_OUTPUTS

#ifndef __halOutInitialize
#define __halOutInitialize()      halOutInitialize()
#endif

#ifndef __halOutWrite
#define __halOutWrite(out, s)     halOutWrite(out, s)
#endif

extern void eosOutSet(UINT8 out, BOOL s);
extern BOOL eosOutGet(UINT8 out);
extern void eosOutToggle(UINT8 out);
extern void eosOutPulse(UINT8 out, UINT16 timeOut);
extern void eosOutAllOFF(void);

extern void sysOutInitialize(void);
extern void sysOutLoop(void);
extern void sysOutTickInterrupt(void);

extern void halOutInitialize(void);
extern void halOutWrite(UINT8 out, BOOL s);
#endif

// Gestio dels ports d'entrada digital
//
#ifdef EOS_USE_INPUTS

#ifndef __halInpInitialize
#define __halInpInitialize()      halInpInitialize()
#endif

#ifndef __halInpRead
#define __halInpRead(inp)         halInpRead(inp)
#endif

extern BOOL eosInpGet(UINT8 inp);
extern BOOL eosInpPosEdge(UINT8 inp);
extern BOOL eosInpNegEdge(UINT8 inp);

extern void sysInpInitialize(void);
extern void sysInpLoop(void);
extern void sysInpTickInterrupt(void);

extern void halInpInitialize(void);
extern BOOL halInpRead(UINT8 inp);
#endif


#endif	

