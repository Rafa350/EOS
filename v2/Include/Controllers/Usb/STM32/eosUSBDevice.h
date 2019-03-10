#ifndef __STM32_eosUSBDevice__
#define __STM32_eosUSBDevice__


// EOS includes
//
#include "eos.h"


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
