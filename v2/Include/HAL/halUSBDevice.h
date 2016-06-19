#ifndef __EOS_HAL_USBDEVICE_H
#define	__EOS_HAL_USBDEVICE_H


#include "stdint.h"


#ifdef	__cplusplus
extern "C" {
#endif

    
typedef void (*UsbDeviceCallback)(uint8_t index, void *param);


void halUSBDeviceSetup(void);
void halUSBDeviceTask(void);

void halUSBDeviceCDCSetup(UsbDeviceCallback callback, void *param);
void halUSBDeviceCDCTask(void);


#ifdef	__cplusplus
}
#endif


#endif

