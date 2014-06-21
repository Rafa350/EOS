#ifndef __EOS_H
#define	__EOS_H


#include "xc.h"
#include "GenericTypeDefs.h"

#ifndef __EOSCONFIG_H
#include "eosconfig.h"
#endif

#ifdef __PIC32MX
#ifdef eosOPT_HARMONY
#include "peripheral/int/plib_int.h"
#else
#include "plib.h"
#endif
#endif


// Codis de retorn de les funcions de la llibreria
//
#define eos_RESULT_BASE      0
#define eos_RESULT_SUCCESS   (eos_RESULT_BASE + 0)
#define eos_RESULT_FIRST     (eos_RESULT_BASE + 1)

// Codis d'error de les funcions de la llibreria
//
#define eos_ERROR_BASE       500
#define eos_ERROR_PARAMS     (eos_ERROR_BASE + 0)
#define eos_ERROR_ALLOC      (eos_ERROR_BASE + 1)
#define eos_ERROR_FIRST      (eos_ERROR_BASE + 500)

// Definicio de tipus base de la llibraria
//
typedef UINT16 eosResult;    // Resultat d'una funcio
typedef void* eosHandle;     // Handler d'un objecte


#ifdef eosOPT_SYSMAIN
extern void eosMain(void);
#endif
extern void eosTickInterrupt(void);
extern void eosDelay(unsigned);
extern void* eosAlloc(unsigned size);
extern void* eosRealloc(void *p, unsigned size);
extern void* eosAllocString(const char *s);
extern void eosFree(void *p);

#if defined(_PIC18)
#define eosEnableInterrupts()     ei()
#define eosDisableInterrupts()    di()
#define eosEnableWatchdog()       WDTCONbits.SWDTEN = 1
#define eosDisableWatchdog()      WDTCONbits.SWDTEN = 0
#define eosClearWatchdog()        CLRWDT()
#elif defined(__PIC32MX)
#ifdef eosOPT_HARMONY
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
#if defined(eosUSE_USBHOST) && defined(__PIC32MX)
extern void sysUsbHostInitialize(void);
extern void sysUsbHostLoop(void);
#endif

// Modul LED
//
#if defined(eosUSE_LED) && !defined(__EOSLED_H)
#include "Modules/eosLed.h"
#endif

// Modul INPUTS
//
#if defined(eosUSE_INPUTS) && !defined(__EOSINPUTS_H)
#include "Modules/eosInputs.h"
#endif

// Modul OUTPUTS
//
#if defined(eosUSE_OUTPUTS) && !defined(__EOSOUTPUTS_H)
#include "Modules/eosOutputs.h"
#endif

// Modul TIMERS
//
#if defined(eosUSE_TIMERS) && !defined(__EOSTIMERS_H)
#include "Modules/eosTimers.h"
#endif

// Modul STEP
//
#if defined(eosUSE_STEP) && !defined(__EOSSTEP_H)
#include "Modules/eosStep.h"
#endif

#if defined(eosUSE_INPUTS) || \
    defined(eosUSE_VARIABLES) || \
    defined(eosUSE_TIMERS)
#include "Modules/eosModules.h"
#endif


#endif	

