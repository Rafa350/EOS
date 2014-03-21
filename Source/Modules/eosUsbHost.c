#include "eos.h"


#if defined(eosUSE_USBHOST) && defined(__PIC32MX)


#include "usb/usb.h"
#include "usb/usb_host_msd.h"
#include "usb/usb_host_msd_scsi.h"


static BOOL deviceAttached = FALSE;


/*************************************************************************
 *
 *       Inicialitzacio del modul
 *
 *       Funcio:
 *           void sysUsbHostInitialize(void)
 *
 *************************************************************************/

void sysUsbHostInitialize(void) {

    USBInitialize(0);
}


/*************************************************************************
 *
 *       Gestiona el modul
 *
 *       Funcio:
 *           void sysUsbHostLoop(void)
 *
 *
 *************************************************************************/

void sysUsbHostLoop(void) {

    USBTasks();

    if (USBHostMSDSCSIMediaDetect()) {

        deviceAttached = TRUE;
        eosOutSet(1, TRUE);
    }
    else
        eosOutSet(1, FALSE);
}


BOOL USB_ApplicationEventHandler(BYTE address, USB_EVENT event, void *data, DWORD size) {

    switch( event ) {
        case EVENT_VBUS_REQUEST_POWER:
            // The data pointer points to a byte that represents the amount of power
            // requested in mA, divided by two.  If the device wants too much power,
            // we reject it.
            return TRUE;

        case EVENT_VBUS_RELEASE_POWER:
            // Turn off Vbus power.
            // The PIC24F with the Explorer 16 cannot turn off Vbus through software.

            //This means that the device was removed
            deviceAttached = FALSE;
            return TRUE;

        case EVENT_HUB_ATTACH:
            return TRUE;

        case EVENT_UNSUPPORTED_DEVICE:
            return TRUE;

        case EVENT_CANNOT_ENUMERATE:
            return TRUE;

        case EVENT_CLIENT_INIT_ERROR:
            return TRUE;

        case EVENT_OUT_OF_MEMORY:
            return TRUE;

        case EVENT_UNSPECIFIED_ERROR:
            return TRUE;

        default:
            break;
    }

    return FALSE;
}


#endif