#ifndef __EOS_H
#define	__EOS_H


#include "xc.h"
#include "GenericTypeDefs.h"
#include "peripheral/int/plib_int.h"


#ifndef __EOSCONFIG_H
#include "eosconfig.h"
#endif


// Codis de retorn de les funcions de la llibreria
//
#define eos_RESULT_BASE           0
#define eos_RESULT_SUCCESS        (eos_RESULT_BASE + 0)
#define eos_RESULT_PENDING        (eos_RESULT_BASE + 1)
#define eos_RESULT_FIRST          (eos_RESULT_BASE + 2)

// Codis d'error de les funcions de la llibreria
//
#define eos_ERROR_BASE            500
#define eos_ERROR_PARAM_NULL      (eos_ERROR_BASE + 0)
#define eos_ERROR_PARAM_RANGE     (eos_ERROR_BASE + 1)
#define eos_ERROR_PARAM_INVALID   (eos_ERROR_BASE + 2)
#define eos_ERROR_ALLOC           (eos_ERROR_BASE + 3)
#define eos_ERROR_OPERATION       (eos_ERROR_BASE + 4)
#define eos_ERROR_FIRST           (eos_ERROR_BASE + 500)

// Definicio de tipus base de la llibraria
//
typedef unsigned eosResult;       // Resultat d'una funcio
typedef struct {} *eosHandle;     // Handler d'un objecte
typedef void (*eosCallback)(void *context); // Funcio callback


#ifdef eosOPT_SYSMAIN
extern void eosMain(void);
#endif
extern void eosTickInterrupt(void);
extern void eosDelay(unsigned);

#define eosGetInterruptState()    PLIB_INT_IsEnabled(INT_ID_0)
#define eosEnableInterrupts()     PLIB_INT_Enable(INT_ID_0)
#define eosDisableInterrupts()    PLIB_INT_Disable(INT_ID_0)
#define eosEnableWatchdog()       EnableWDT()
#define eosDisableWatchdog()      DisablWDT()
#define eosClearWatchdog()        ClearWDT()


#endif	

