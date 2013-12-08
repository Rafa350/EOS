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

#ifndef __halInitialize
#define __halInitialize()         halInitialize()
#endif


#ifdef EOS_USE_SYSMAIN
extern void eosMain(void);
#endif
extern void eosTickInterrupt(void);

extern void halInitialize(void);

#if defined(_PIC18)
#define eosEnableInterrupts()     ei()
#define eosDisableInterrupts()    di()
#define eosEnableWatchdog()       WDTCONbits.SWDTEN = 1
#define eosDisableWatchdog()      WDTCONbits.SWDTEN = 0
#define eosClearWatchdog()        CLRWDT()
#elif defined(__PIC32MX)
#define eosEnableInterrupts()     INTEnableInterrupts()
#define eosDisableInterrupts()    INTDisableInterrupts()
#define eosEnableWatchdog()       EnableWDT()
#define eosDisableWatchdog()      DisablWDT()
#define eosClearWatchdog()        ClearWDT()
#endif


// Modul de sortides digitals
//
#ifdef EOS_USE_OUTPUTS

#ifndef __halOutPortWrite
#define __halOutPortWrite(o, s)   halOutPortWrite(o, s)
#endif

extern void eosOutSet(UINT8 outputId, BOOL state);
extern BOOL eosOutGet(UINT8 outputId);
extern void eosOutToggle(UINT8 outputId);
extern void eosOutPulse(UINT8 outputId, UINT16 timeOut);
extern void eosOutAllOFF(void);

extern void sysOutInitialize(void);
extern void sysOutLoop(void);
extern void sysOutTickInterrupt(void);

extern void halOutPortWrite(UINT8 outputId, BOOL state);
#endif

// Modul d'entrades digitals
//
#ifdef EOS_USE_INPUTS

#ifndef __halInpPortRead
#define __halInpPortRead(i)       halInpPortRead(i)
#endif

extern BOOL eosInpGet(UINT8 inputId);
extern BOOL eosInpPosEdge(UINT8 inputId);
extern BOOL eosInpNegEdge(UINT8 inputId);

extern void sysInpInitialize(void);
extern void sysInpLoop(void);
extern void sysInpTickInterrupt(void);

extern BOOL halInpPortRead(UINT8 inputId);
#endif

// Modul de conversio AD
//
#ifdef EOS_USE_ADC
extern UINT16 eosAdcGet(UINT8 adcId);

extern void sysAdcInitialize(void);
#endif

// Modul de temporitzadors
//
#ifdef EOS_USE_TIMERS
extern void eosTimStart(UINT8 timerId, UINT16 time);
extern BOOL eosTinGet(UINT8 timerId);
extern void eosTimPause(UINT8 timerId);
extern void eosTimContinue(UINT8 timerId);

extern void sysTimInitialize(void);
extern void sysTimLoop(void);
extern void sysTimTickInterrupt(void);
#endif

// Modul de variables
//
#ifdef EOS_USE_VARIABLES

#ifndef __halVarSave
#define __halVarSave(d, s)        halVarSave(d, s)
#endif

#ifndef __halVarRestore
#define __halVarRestore(d, s)     halVarRestore(d, s)
#endif

typedef UINT16 VARTYPE;

typedef struct {
    UINT8 varId;
    VARTYPE value;
} VARINIT;

extern void eosVarSet(UINT8 varId, VARTYPE value);
extern VARTYPE eosVarGet(UINT8 varId);
extern void eosVarSave(void);
extern void eosVarRestore(void);
extern void eosVarSetTable(VARINIT *data, UINT8 dataLen);
#ifdef _PIC18
extern void eosVarSetTableROM(VARINIT *data, UINT8 dataLen);
#endif

extern void sysVarInitialize(void);

extern void halVarSave(BYTE *data, UINT dataSize);
extern void halVarRestore(BYTE *data, UINT dataSize);
#endif

// Modul indicador d'estat
//
#ifdef EOS_USE_LEDSTATUS

#ifndef __halLedPortWrite
#define __halLedPortWrite(s)      halLedPortWrite(s)
#endif

extern void sysLedInitialize(void);
extern void sysLedTickInterrupt(void);

extern void halLedPortWrite(BOOL state);
#endif


#endif	

