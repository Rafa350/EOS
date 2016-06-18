#ifndef __EOS_HAL_USBDEVICE_H
#define	__EOS_HAL_USBDEVICE_H


#ifdef	__cplusplus
extern "C" {
#endif


void halUSBDeviceSetup(void);
void halUSBDeviceTask(void);

void halUSBDeviceCDCSetup(void);
void halUSBDeviceCDCTask(void);


#ifdef	__cplusplus
}
#endif


#endif

