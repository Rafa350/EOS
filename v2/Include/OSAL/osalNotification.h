#pragma once
#ifndef __osalNotification__
#define __osalNotificacion__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct OSAL_NOTIFICATION_DATA *HNotification;


HNotification osalNotificationCreate();

bool osalNotificationWait(HNotification hNotification, unsigned index, unsigned blockTime);
void osalNotificationRelease(HNotification hNotification, unsigned index);
void osalNotificationReleaseISR(HNotification hNotification, unsigned index);


#ifdef	__cplusplus
}
#endif


#endif // __osalNotification__

