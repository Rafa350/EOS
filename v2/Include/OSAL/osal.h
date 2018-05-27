#ifndef __osal__
#define __osal__


#include "eos.h"
#include "eosAssert.h"

#include <stdint.h>


#if defined (__GNUC__) && defined(STM32)
	#define __ASM            __asm
  	#define __INLINE         inline
	#define __STATIC_INLINE  static inline

	#include "stdint.h"
	#include "cmsis_gcc.h"
#endif

#define OSAL_CHECK_PARAMETERS

// Resultat de les crides al API
//
#define OSAL_RESULT_OK                 ((uint8_t) 0)
#define OSAL_RESULT_TRUE               ((uint8_t) 1)
#define OSAL_RESULT_FALSE              ((uint8_t) 2)
#define OSAL_RESULT_ERROR              ((uint8_t) 200)
#define OSAL_RESULT_ERROR_PARAMETER    ((uint8_t) 201)
#define OSAL_RESULT_ERROR_TIMEOUT      ((uint8_t) 202)
#define OSAL_RESULT_ERROR_RESOURCE     ((uint8_t) 203)
#define OSAL_RESULT_ERROR_MEMORY       ((uint8_t) 204)


typedef uint8_t OsalResult;


#endif // __osal__
