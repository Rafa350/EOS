#ifndef __EOS_H
#define	__EOS_H


#include "xc.h"
#include "GenericTypeDefs.h"
#include "system/int/sys_int.h"
#include "system/wdt/sys_wdt.h"


// Opcions predefinides, si cal, s'han de desabilitar en eosConfig.h
//
#define eos_OPTION_CheckInputParams


#ifndef __EOS_CONFIG_H
#include "eosConfig.h"
#endif

#ifndef __EOS_HAL_H
#include "eosHal.h"
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
#define eosInterruptEnable()           SYS_INT_Enable()
#define eosInterruptDisable()          SYS_INT_Disable()
#define eosInterruptRestore(state)     if (state) SYS_INT_Enable()
#define eosInterruptSourceEnable(source)    SYS_INT_SourceEnable(source)
#define eosInterruptSourceDisable(source)   SYS_INT_SourceDisable(source)
#define eosInterruptSourceRestore(source, state) if (state) SYS_INT_SourceEnable(source)
#define __ISR_Entry(v)            v##_ISR(void)

// Gestio del watchdog
//
#define eosWatchdogEnable()            SYS_WDT_Enable(false)
#define eosWatchdogDisable()           SYS_WDT_Disable()
#define eosWatchdogClearg()            SYS_WDT_TimeClear()

#define eosCheckError(e)            ((e) >= eos_ERROR_BASE)
#define eosCheckSuccess(e)          ((e) == eos_RESULT_SUCCESS)
#define eosCheckPending(e)          ((e) == eos_RESULT_PENDING)


#endif	

