#ifndef __STM32_halUSBDeviceCDC__
#define __STM32_halUSBDeviceCDC__


// EOS includes
//
#include "eos.h"
#include "hal/hal.h"
#include "hal/halUSB.h"
#include "hal/halUSBDevice.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    
} USBDeviceInitializeCDCInfo;


void halUSBDeviceCDCInitialize(USBPort port, const USBDeviceCDCInitializeInfo *info);


#ifdef __cplusplus
}
#endif


#endif // __STM32_halUSBDeviceCDC__
