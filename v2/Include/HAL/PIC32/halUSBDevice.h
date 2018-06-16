#ifndef __PIC32_halUSBDevice__
#define __PIC32_halUSBDevice__


// EOS includes
//
#include "eos.h"
#include "hal/hal.h"
#include "hal/halUSB.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    USBId id;
} USBDeviceInitializeInfo;


void halUSBDeviceInitialize(const USBDeviceInitializeInfo *info);
void halUSBDeviceTask();


#ifdef __cplusplus
}
#endif


#endif // __PIC32_halUSBDevice__
