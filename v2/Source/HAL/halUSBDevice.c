#include "HardwareProfile.h"
#include "peripheral/int/plib_int.h"
#include "driver/usb/usbfs/drv_usbfs.h"
#include "usb/usb_device.h"
#include <sys/attribs.h>


static SYS_MODULE_OBJ drvUSBObject;
static SYS_MODULE_OBJ usbDevObject0;
static uint8_t __attribute__((aligned(512))) endPointTable[DRV_USBFS_ENDPOINTS_NUMBER * 32];

extern const USB_DEVICE_FUNCTION_REGISTRATION_TABLE funcRegistrationTable[];
extern const USB_DEVICE_MASTER_DESCRIPTOR usbMasterDescriptor;


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul USB en modus dispositiu.
///
void halUSBDeviceSetup(void) {

    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_USB1, INT_PRIORITY_LEVEL4);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_USB1, INT_SUBPRIORITY_LEVEL0);

    DRV_USBFS_INIT usbInitData;
    usbInitData.endpointTable = endPointTable;
    usbInitData.interruptSource = INT_SOURCE_USB_1;
    usbInitData.moduleInit.sys.powerState = SYS_MODULE_POWER_RUN_FULL;
    usbInitData.operationMode = DRV_USBFS_OPMODE_DEVICE;
    usbInitData.operationSpeed = USB_SPEED_FULL;
    usbInitData.stopInIdle = false;
    usbInitData.suspendInSleep = false;
    usbInitData.usbID = USB_ID_1;
    drvUSBObject = DRV_USBFS_Initialize(DRV_USBFS_INDEX_0, (SYS_MODULE_INIT*) &usbInitData);
    
    
    USB_DEVICE_INIT usbDevInitData;
    usbDevInitData.moduleInit.sys.powerState = SYS_MODULE_POWER_RUN_FULL;
    usbDevInitData.registeredFuncCount = 1;
    usbDevInitData.registeredFunctions = (USB_DEVICE_FUNCTION_REGISTRATION_TABLE*) funcRegistrationTable;
    usbDevInitData.usbMasterDescriptor = (USB_DEVICE_MASTER_DESCRIPTOR*) &usbMasterDescriptor;
    usbDevInitData.deviceSpeed = USB_SPEED_FULL;
    usbDevInitData.driverIndex = DRV_USBFS_INDEX_0;
    usbDevInitData.usbDriverInterface = DRV_USBFS_DEVICE_INTERFACE;
    usbDevObject0 = USB_DEVICE_Initialize(USB_DEVICE_INDEX_0, (SYS_MODULE_INIT*) &usbDevInitData);
    
    APP_Initialize();
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del modul USB. Cal cridar-la 
/// periodicament.
//
void halUSBTask(void) {

    DRV_USBFS_Tasks(drvUSBObject);
    USB_DEVICE_Tasks(usbDevObject0);
    
    APP_Tasks();
}

	
/// ----------------------------------------------------------------------
/// \bried Funcio ISR del modul USB.
///
void __ISR(_USB_1_VECTOR, ipl4AUTO) isrUSB0Handler(void) {
    
    DRV_USBFS_Tasks_ISR(drvUSBObject);
}
