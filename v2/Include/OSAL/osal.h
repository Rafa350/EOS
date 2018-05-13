#ifndef __osal__
#define __osal__


#include "eos.h"


#define OSAL_CHECK_PARAMETERS

// Codis d'error
//
#define OSAL_STATUS_OK                 ((uint8_t) 0)
#define OSAL_STATUS_ERROR_PARAMETER    ((uint8_t) 100)
#define OSAL_STATUS_ERROR_TIMEOUT      ((uint8_t) 101)
#define OSAL_STATUS_ERROR_RESOURCE     ((uint8_t) 102)
#define OSAL_STATUS_ERROR_MEMORY       ((uint8_t) 103)


#endif // __osal__
