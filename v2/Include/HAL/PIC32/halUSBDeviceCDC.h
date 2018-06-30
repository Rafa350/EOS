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
    

typedef void (*USBDeviceCallback)(USBPort port, void *pParam);

typedef struct {
    USBDeviceCallback pCallback;
    void *pParam;
} USBDeviceCDCInitializeInfo;


void halUSBDeviceCDCInitialize(const USBDeviceCDCInitializeInfo *pInfo);
void halUSBDeviceCDCTask();


#ifdef __cplusplus
}
#endif


#endif // __PIC32_halUSBDeviceCDC__
