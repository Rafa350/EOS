#ifndef __STM32_halUSBDevice__
#define __STM32_halUSBDevice__


// EOS includes
//
#include "eos.h"
#include "hal/hal.h"
#include "hal/halUSB.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    
} USBDeviceInitializeInfo;


void halUSBDeviceInitialize(USBId id, const USBDeviceInitializeInfo *info);


#ifdef __cplusplus
}
#endif


#endif // __STM32_halUSBDevice__
