#ifndef __EOS_H
#define	__EOS_H

#include "xc.h"
#include "GenericTypeDefs.h"

#ifndef __EOSCONFIG_H
#include "eosconfig.h"
#endif

#ifdef __PIC32MX
#ifdef EOS_USE_HARMONY
#include "peripheral/int/plib_int.h"
#else
#include "plib.h"
#endif
#endif


#ifndef __halInitialize
#define __halInitialize()         halInitialize()
#endif


#ifdef EOS_USE_SYSMAIN
extern void eosMain(void);
#endif
extern void eosTickInterrupt(void);
extern void eosDelay(unsigned);
extern void* eosAlloc(unsigned size);
extern void* eosRealloc(void *p, unsigned size);
extern void* eosAllocString(const char *s);
extern void eosFree(void *p);

extern void halInitialize(void);

#if defined(_PIC18)
#define eosEnableInterrupts()     ei()
#define eosDisableInterrupts()    di()
#define eosEnableWatchdog()       WDTCONbits.SWDTEN = 1
#define eosDisableWatchdog()      WDTCONbits.SWDTEN = 0
#define eosClearWatchdog()        CLRWDT()
#elif defined(__PIC32MX)
#ifdef EOS_USE_HARMONY
#define eosEnableInterrupts()     PLIB_INT_Enable(INT_ID_0)
#define eosDisableInterrupts()    PLIB_INT_Disable(INT_ID_0)
#define eosEnableWatchdog()       EnableWDT()
#define eosDisableWatchdog()      DisablWDT()
#define eosClearWatchdog()        ClearWDT()
#else
#define eosEnableInterrupts()     INTEnableInterrupts()
#define eosDisableInterrupts()    INTDisableInterrupts()
#define eosEnableWatchdog()       EnableWDT()
#define eosDisableWatchdog()      DisablWDT()
#define eosClearWatchdog()        ClearWDT()
#endif
#endif


// Modul de sortides digitals
//
#ifdef EOS_USE_OUTPUTS

#ifndef __halOutPortWrite
#define __halOutPortWrite(id, state)   halOutPortWrite(id, state)
#endif

extern void eosOutSet(UINT8 id, BOOL state);
extern BOOL eosOutGet(UINT8 id);
extern void eosOutToggle(UINT8 id);
extern void eosOutPulse(UINT8 id, unsigned timeOut);
extern void eosOutAllOFF(void);

#define eosOutSetON(id)                eosOutSet(id, TRUE)
#define eosOutSetOFF(id)               eosOutSet(id, FALSE)

extern void sysOutInitialize(void);
extern void sysOutLoop(void);
extern void sysOutTickInterrupt(void);

extern void halOutPortWrite(UINT8 id, BOOL state);
#endif

// Modul d'entrades digitals
//
#ifdef EOS_USE_INPUTS

#ifndef __halInpPortRead
#define __halInpPortRead(id)           halInpPortRead(id)
#endif

extern BOOL eosInpGet(UINT8 id);
extern BOOL eosInpPosEdge(UINT8 id);
extern BOOL eosInpNegEdge(UINT8 id);

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
extern void eosTimStart(UINT8 id, unsigned time);
extern BOOL eosTinGet(UINT8 id);
extern void eosTimPause(UINT8 id);
extern void eosTimContinue(UINT8 id);

extern void sysTimInitialize(void);
extern void sysTimLoop(void);
extern void sysTimTickInterrupt(void);
#endif

// Modul de variables
//
#ifdef EOS_USE_VARIABLES

#ifndef __halVarSave
#define __halVarSave(data, size)       halVarSave(data, size)
#endif

#ifndef __halVarRestore
#define __halVarRestore(data, size)    halVarRestore(data, size)
#endif

typedef struct {
    UINT8 varId;
    unsigned value;
} VARINIT;

extern void eosVarSet(UINT8 id, unsigned value);
extern unsigned eosVarGet(UINT8 id);
extern void eosVarSave(void);
extern void eosVarRestore(void);
extern void eosVarSetTable(VARINIT *data, UINT8 dataLen);
#ifdef _PIC18
extern void eosVarSetTableROM(VARINIT *data, UINT8 dataLen);
#endif

extern void sysVarInitialize(void);

extern void halVarSave(void *data, unsigned dataSize);
extern void halVarRestore(void *data, unsigned dataSize);
#endif

// Modul USB Host
//
#if defined(EOS_USE_USBHOST) && defined(__PIC32MX)
extern void sysUsbHostInitialize(void);
extern void sysUsbHostLoop(void);
#endif

// Modul indicador d'estat
//
#ifdef EOS_USE_LEDSTATUS

#ifndef __halLedPortWrite
#define __halLedPortWrite(state)       halLedPortWrite(state)
#endif

extern void sysLedInitialize(void);
extern void sysLedTickInterrupt(void);

extern void halLedPortWrite(BOOL state);
#endif


#endif	

