#ifndef SYSTEM_CONFIG_H
#define	SYSTEM_CONFIG_H


// Parametres del sistema
//
#define SYS_CLK_FREQUENCY                       (80000000ul)
#define SYS_DEVCON_PIC32MX_MAX_PB_FREQ          (80000000ul)

// Parametres configuracio del modul USB
//
#define USB_DEVICE_HID_INSTANCES_NUMBER          1
#define USB_DEVICE_HID_QUEUE_DEPTH_COMBINED      2
#define USB_DEVICE_INSTANCES_NUMBER              1
#define USB_DEVICE_CLIENTS_NUMBER                1
#define USB_DEVICE_EP0_BUFFER_SIZE               64
#define DRV_USB_INSTANCES_NUMBER                 1
#define DRV_USB_INTERRUPT_MODE                   true
#define DRV_USB_ENDPOINTS_NUMBER                 2
#define DRV_USB_DEVICE_SUPPORT                   true
#define DRV_USB_HOST_SUPPORT                     false


#endif

