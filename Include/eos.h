#ifndef __EOS_H
#define	__EOS_H


#include "xc.h"
#include "GenericTypeDefs.h"
#include "system/int/sys_int.h"
#include "system/wdt/sys_wdt.h"
#include "peripheral/int/plib_int.h"


// Opcions predefinides, si cal, s'han de desabilitar en eosConfig.h
//
#define eos_OPTION_CheckInputParams


#ifndef __EOS_CONFIG_H
#include "eosConfig.h"
#endif


// Codis de retorn de les funcions de la llibreria
//
#define eos_RESULT_BASE           0
#define eos_RESULT_SUCCESS        (eos_RESULT_BASE + 0)
#define eos_RESULT_PENDING        (eos_RESULT_BASE + 1)
#define eos_RESULT_USER           (eos_RESULT_BASE + 100)

// Codis d'error de les funcions de la llibreria
//
#define eos_ERROR_BASE            500
#define eos_ERROR_PARAM_NULL      (eos_ERROR_BASE + 0)
#define eos_ERROR_PARAM_RANGE     (eos_ERROR_BASE + 1)
#define eos_ERROR_PARAM_INVALID   (eos_ERROR_BASE + 2)
#define eos_ERROR_ALLOC           (eos_ERROR_BASE + 3)
#define eos_ERROR_OPERATION       (eos_ERROR_BASE + 4)
#define eos_ERROR_BUSY            (eos_ERROR_BASE + 5)
#define eos_ERROR_USER            (eos_ERROR_BASE + 500)


// Definicio de tipus base de la llibreria
//
typedef unsigned eosResult;       // Resultat d'una funcio
typedef void (*eosCallback)(void *sender, void *context); // Funcio callback


extern void eosMain(void);
#define eosSetError(code, str)

// Gestio de les interrupcions
//
#define eosInterruptEnable()                PLIB_INT_Enable(INT_ID_0)
#define eosInterruptRestore(e)              if (e) PLIB_INT_Enable(INT_ID_0)
#define eosInterruptSourceEnable(s)         PLIB_INT_SourceEnable(INT_ID_0, s)
#define eosInterruptSourceRestore(s, e)     if (e) PLIB_INT_SourceEnable(INT_ID_0, s)

extern bool eosInterruptDisable();
extern bool eosInterruptSourceDisable(INT_SOURCE source);

// Gestio del watchdog
//
#define eosWatchdogEnable()            SYS_WDT_Enable(false)
#define eosWatchdogDisable()           SYS_WDT_Disable()
#define eosWatchdogClearg()            SYS_WDT_TimeClear()

#define eosCheckError(e)            ((e) >= eos_ERROR_BASE)
#define eosCheckSuccess(e)          ((e) == eos_RESULT_SUCCESS)
#define eosCheckPending(e)          ((e) == eos_RESULT_PENDING)


#endif	

