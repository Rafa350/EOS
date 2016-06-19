#include "HardwareProfile.h"
#include "peripheral/int/plib_int.h"
#include "driver/usb/usbfs/drv_usbfs.h"
#include "usb/usb_device.h"
#include <sys/attribs.h>


static SYS_MODULE_OBJ drvUSBObject;
static SYS_MODULE_OBJ usbDevObject0;
static uint8_t __attribute__((aligned(512))) endPointTable[DRV_USBFS_ENDPOINTS_NUMBER * 32];

static const DRV_USBFS_INIT usbInitData = {
    .endpointTable = endPointTable,
    .interruptSource = INT_SOURCE_USB_1,
    .moduleInit.sys.powerState = SYS_MODULE_POWER_RUN_FULL,
    .operationMode = DRV_USBFS_OPMODE_DEVICE,
    .operationSpeed = USB_SPEED_FULL,
    .stopInIdle = false,
    .suspendInSleep = false,
    .usbID = USB_ID_1
};

static const USB_DEVICE_INIT usbDevInitData = {
    .moduleInit.sys.powerState = SYS_MODULE_POWER_RUN_FULL,
    .registeredFuncCount = 1,
    .registeredFunctions = (USB_DEVICE_FUNCTION_REGISTRATION_TABLE*) functionRegistrationTable,
    .usbMasterDescriptor = (USB_DEVICE_MASTER_DESCRIPTOR*) &usbMasterDescriptor,
    .deviceSpeed = USB_SPEED_FULL,
    .driverIndex = DRV_USBFS_INDEX_0,
    .usbDriverInterface = DRV_USBFS_DEVICE_INTERFACE
};


extern const USB_DEVICE_FUNCTION_REGISTRATION_TABLE functionRegistrationTable[];
extern const USB_DEVICE_MASTER_DESCRIPTOR usbMasterDescriptor;


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul USB en modus dispositiu.
///
void halUSBDeviceSetup(void) {

    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_USB1, INT_PRIORITY_LEVEL4);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_USB1, INT_SUBPRIORITY_LEVEL0);

    drvUSBObject = DRV_USBFS_Initialize(DRV_USBFS_INDEX_0, (SYS_MODULE_INIT*) &usbInitData);
    usbDevObject0 = USB_DEVICE_Initialize(USB_DEVICE_INDEX_0, (SYS_MODULE_INIT*) &usbDevInitData);
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del modul USB. Cal cridar-la 
/// periodicament.
//
void halUSBDeviceTask(void) {

    DRV_USBFS_Tasks(drvUSBObject);
    USB_DEVICE_Tasks(usbDevObject0);
}

	
/// ----------------------------------------------------------------------
/// \bried Funcio ISR del modul USB.
///
void __ISR(_USB_1_VECTOR, ipl4AUTO) isrUSBHandler(void) {
    
    DRV_USBFS_Tasks_ISR(drvUSBObject);
}
