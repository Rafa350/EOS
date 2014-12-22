#ifndef __EOS_H
#define	__EOS_H


#include "xc.h"
#include "GenericTypeDefs.h"
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

typedef struct {
    void *object;
    void (*method)(void *object, void *params);
} eosEvent;

extern void eosMain(void);
#define eosSetError(code, str)

#define eosGetInterruptState()    PLIB_INT_IsEnabled(INT_ID_0)
#define eosEnableInterrupts()     PLIB_INT_Enable(INT_ID_0)
#define eosDisableInterrupts()    PLIB_INT_Disable(INT_ID_0)

#define eosEnterCriticalSection()
#define eosExitCriticalSection()

#define eosEnableWatchdog()       EnableWDT()
#define eosDisableWatchdog()      DisablWDT()
#define eosClearWatchdog()        ClearWDT()
#define __ISR_Entry(v)            v##_ISR(void)

#define eosCheckError(e)            ((e) >= eos_ERROR_BASE)
#define eosCheckSuccess(e)          ((e) == eos_RESULT_SUCCESS)
#define eosCheckPending(e)          ((e) == eos_RESULT_PENDING)


#endif	

