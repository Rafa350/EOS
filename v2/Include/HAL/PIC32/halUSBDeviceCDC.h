#ifndef __PIC32_halUSBDeviceCDC__
#define __PIC32_halUSBDeviceCDC__


// EOS includes
//
#include "eos.h"
#include "hal/hal.h"
#include "hal/halUSB.h"
#include "hal/halUSBDevice.h"


#ifdef __cplusplus
extern "C" {
#endif
    

typedef void (*USBDeviceCallback)(uint8_t index, void *param);

typedef struct {
    USBDeviceCallback callback;
    void *param;
} USBDeviceCDCInitializeInfo;


void halUSBDeviceCDCInitialize(const USBDeviceCDCInitializeInfo *info);
void halUSBDeviceCDCTask();


#ifdef __cplusplus
}
#endif


#endif // __PIC32_halUSBDeviceCDC__
