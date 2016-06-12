#include <xc.h>
#include <sys/attribs.h>
#include "system_definitions.h"


extern SYS_MODULE_OBJ drvUSBObject;
	
	
void __ISR(_USB_1_VECTOR, ipl4AUTO) _IntHandlerUSBInstance0(void) {
    
    DRV_USBFS_Tasks_ISR(drvUSBObject);
}
