#ifndef __USBD_CONF_H
#define __USBD_CONF_H


// EOS includes
//
#include "eos.h"
#include "osal/osalMemory.h"

// STM32 / HAL includes
//
#if defined(EOS_STM32F4)
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#elif defined(STM32F7)
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#endif


// Memory options
//
#define USBD_malloc		osalMemoryAlloc
#define USBD_free		osalMemoryFree
#define USBD_memset		memset
#define USBD_memcpy		memcpy

// General options
//
#define USBD_MAX_NUM_INTERFACES               1
#define USBD_MAX_NUM_CONFIGURATION            1
#define USBD_MAX_STR_DESC_SIZ                 0x100
#define USBD_SUPPORT_USER_STRING              0
#define USBD_SELF_POWERED                     1
#define USBD_DEBUG_LEVEL                      0


#endif // __USBD_CONF_H


