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


#ifdef eosOPT_SYSMAIN
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


// Modul USB Host
//
#if defined(EOS_USE_USBHOST) && defined(__PIC32MX)
extern void sysUsbHostInitialize(void);
extern void sysUsbHostLoop(void);
#endif

#if defined(eosUSE_LED)
#include "Modules/Debugger/eosDebugger.h"
#endif

#if defined(eosUSE_INPUTS) || \
    defined(eosUSE_OUTPUTS) || \
    defined(eosUSE_VARIABLES) || \
    defined(eosUSE_TIMERS)
#include "Modules/Plc/eosPLC.h"
#endif


#endif	

