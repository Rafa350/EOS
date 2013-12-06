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


// Modul de sortides digitals
//
#ifdef EOS_USE_OUTPUTS

#ifndef __halOutInitialize
#define __halOutInitialize()      halOutInitialize()
#endif

#ifndef __halOutWrite
#define __halOutWrite(o, s)       halOutWrite(o, s)
#endif

extern void eosOutSet(UINT8 outputId, BOOL state);
extern BOOL eosOutGet(UINT8 outputId);
extern void eosOutToggle(UINT8 outputId);
extern void eosOutPulse(UINT8 outputId, UINT16 timeOut);
extern void eosOutAllOFF(void);

extern void sysOutInitialize(void);
extern void sysOutLoop(void);
extern void sysOutTickInterrupt(void);

extern void halOutInitialize(void);
extern void halOutWrite(UINT8 outputId, BOOL state);
#endif

// Modul d'entrades digitals
//
#ifdef EOS_USE_INPUTS

#ifndef __halInpInitialize
#define __halInpInitialize()      halInpInitialize()
#endif

#ifndef __halInpRead
#define __halInpRead(i)           halInpRead(i)
#endif

extern BOOL eosInpGet(UINT8 inputId);
extern BOOL eosInpPosEdge(UINT8 inputId);
extern BOOL eosInpNegEdge(UINT8 inputId);

extern void sysInpInitialize(void);
extern void sysInpLoop(void);
extern void sysInpTickInterrupt(void);

extern void halInpInitialize(void);
extern BOOL halInpRead(UINT8 inputId);
#endif

// Modul de temporitzadors
//
#ifdef EOS_USE_TIMERS
extern void eosTimStart(UINT8 timerId, UINT16 time);
extern BOOL eosTinGet(UINT8 timerId);
extern void eosTimPauer(UINT8 timerId);
extern void eosTimContinue(UINT8 timerId);

extern void sysTimInitialize(void);
extern void sysTimLoop(void);
extern void sysTimTickInterrupt(void);
#endif

#endif	

