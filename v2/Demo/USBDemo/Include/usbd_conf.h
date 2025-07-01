#pragma once
#ifndef __USBD_CONF_H
#define __USBD_CONF_H


#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define USBD_MAX_NUM_INTERFACES               1
#define USBD_MAX_NUM_CONFIGURATION            1
#define USBD_MAX_STR_DESC_SIZ                 0x100
#define USBD_SELF_POWERED                     1
#define USBD_DEBUG_LEVEL                      0

/* MSC Class Config */
#define MSC_MEDIA_PACKET                      512

#ifdef __cplusplus
extern "C" {
	void* appUSBDmalloc(size_t size);
	void appUSBDfree(void *p);
};
#endif

#define USBD_malloc               appUSBDmalloc
#define USBD_free                 appUSBDfree
#define USBD_memset               memset
#define USBD_memcpy               memcpy
#define USBD_Delay                HAL_Delay

/* DEBUG macros */
#if (USBD_DEBUG_LEVEL > 0)
#define  USBD_UsrLog(...)   printf(__VA_ARGS__);\
                            printf("\n");
#else
#define USBD_UsrLog(...)
#endif

#if (USBD_DEBUG_LEVEL > 1)

#define  USBD_ErrLog(...)   printf("ERROR: ") ;\
                            printf(__VA_ARGS__);\
                            printf("\n");
#else
#define USBD_ErrLog(...)
#endif

#if (USBD_DEBUG_LEVEL > 2)
#define  USBD_DbgLog(...)   printf("DEBUG : ") ;\
                            printf(__VA_ARGS__);\
                            printf("\n");
#else
#define USBD_DbgLog(...)
#endif


#endif /* __USBD_CONF_H */

