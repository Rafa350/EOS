#ifndef __osal__
#define __osal__


#include "eos.h"


#if defined (__GNUC__)
	#define __ASM            __asm
  	#define __INLINE         inline
	#define __STATIC_INLINE  static inline

	#include "stdint.h"
	#include "cmsis_gcc.h"
#endif


#define OSAL_CHECK_PARAMETERS

// Codis d'error
//
#define OSAL_STATUS_OK                 ((uint8_t) 0)
#define OSAL_STATUS_TRUE               ((uint8_t) 1)
#define OSAL_STATUS_FALSE              ((uint8_t) 2)
#define OSAL_STATUS_ERROR              ((uint8_t) 200)
#define OSAL_STATUS_ERROR_PARAMETER    ((uint8_t) 201)
#define OSAL_STATUS_ERROR_TIMEOUT      ((uint8_t) 202)
#define OSAL_STATUS_ERROR_RESOURCE     ((uint8_t) 203)
#define OSAL_STATUS_ERROR_MEMORY       ((uint8_t) 204)


#endif // __osal__
