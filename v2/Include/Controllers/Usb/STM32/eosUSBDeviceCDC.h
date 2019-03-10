#ifndef __STM32_eosUSBDeviceCDC__
#define __STM32_eosUSBDeviceCDC__


// EOS includes
//
#include "eos.h"
#include "hal/hal.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    
} USBDeviceInitializeCDCInfo;


void halUSBDeviceCDCInitialize(USBPort port, const USBDeviceCDCInitializeInfo *info);


#ifdef __cplusplus
}
#endif


#endif // __STM32_eosUSBDeviceCDC__
