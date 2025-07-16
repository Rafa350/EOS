#include "eos.h"


#ifdef USE_MSC_DEVICE


#include "Controllers/USBDevice/MSC/eosMSCDefinitions.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"
#include "usbd_desc.h"
#include "usbd_conf.h"


#define USBD_VID                      0x0483
#define USBD_PID                      0x5720
#define USBD_LANGID_STRING            0x409
#define USBD_MANUFACTURER_STRING      "STMicroelectronics"
#define USBD_PRODUCT_HS_STRING        "Mass Storage in HS Mode"
#define USBD_PRODUCT_FS_STRING        "Mass Storage in FS Mode"
#define USBD_CONFIGURATION_HS_STRING  "MSC Config"
#define USBD_INTERFACE_HS_STRING      "MSC Interface"
#define USBD_CONFIGURATION_FS_STRING  "MSC Config"
#define USBD_INTERFACE_FS_STRING      "MSC Interface"


uint8_t deviceDescriptor[sizeof(USBD_DeviceDescriptor)] __ALIGN_END = {
	sizeof(USBD_DeviceDescriptor),     // bLength
	USB_DESC_TYPE_DEVICE,              // bDescriptorType
	0x00,                              // bcdUSB
	0x02,
	0x00,                              // bDeviceClass
	0x00,                              // bDeviceSubClass
	0x00,                              // bDeviceProtocol
	USB_MAX_EP0_SIZE,                  // bMaxPacketSize
	LOBYTE(USBD_VID),                  // idVendor
	HIBYTE(USBD_VID),                  // idVendor
	LOBYTE(USBD_PID),                  // idVendor
	HIBYTE(USBD_PID),                  // idVendor
	0x00,                              // bcdDevice rel. 2.00
	0x02,
	USBD_IDX_MFC_STR,                  // Index of manufacturer string
	USBD_IDX_PRODUCT_STR,              // Index of product string
	USBD_IDX_SERIAL_STR,               // Index of serial number string
	USBD_MAX_NUM_CONFIGURATION         // bNumConfigurations
};

uint8_t deviceQualifierDescriptor[sizeof(USBD_DeviceQualifierDescriptor)]  __ALIGN_END = {
	sizeof(USBD_DeviceQualifierDescriptor),
	USB_DESC_TYPE_DEVICE_QUALIFIER,
	0x00,
	0x02,
	0x00,
	0x00,
	0x00,
	MSC_MAX_FS_PACKET,
	0x01,
	0x00
};

uint8_t configurationDescriptor[USB_MSC_CONFIG_DESC_SIZE]  __ALIGN_END = {
	sizeof(USBD_ConfigurationDescriptor),   // bLength: Configuration Descriptor size
	USB_DESC_TYPE_CONFIGURATION,       // bDescriptorType: Configuration
	USB_MSC_CONFIG_DESC_SIZE,          // wTotalLength (LO byte)
	0x00,                              // wTotalLength (HI byte)
	0x01,                              // bNumInterfaces: 1 interface
	0x01,                              // bConfigurationValue
	0x04,                              // iConfiguration
	#if (USBD_SELF_POWERED == 1)
	0xC0,                              // bmAttributes: Bus Powered according to user configuration
	#else
	0x80,                              // bmAttributes: Bus Powered according to user configuration
	#endif
	USBD_MAX_POWER,                    // MaxPower (mA)

	// Interface 1
	0x09,                              // bLength: Interface Descriptor size
	0x04,                              // bDescriptorType:
	0x00,                              // bInterfaceNumber: Number of Interface
	0x00,                              // bAlternateSetting: Alternate setting
	0x02,                              // bNumEndpoints
	0x08,                              // bInterfaceClass: MSC Class
	0x06,                              // bInterfaceSubClass : SCSI transparent
	0x50,                              // nInterfaceProtocol
	0x05,                              // iInterface:

	// EndPoint 1
	0x07,                              // Endpoint descriptor length = 7
	0x05,                              // Endpoint descriptor type
	MSC_EPIN_ADDR,                     // Endpoint address (IN, address 1)
	0x02,                              // Bulk endpoint type
	LOBYTE(MSC_MAX_FS_PACKET),
	HIBYTE(MSC_MAX_FS_PACKET),
	0x00,                              // Polling interval in milliseconds

	// EndPoint 2
	0x07,                              // Endpoint descriptor length = 7
	0x05,                              // Endpoint descriptor type
	MSC_EPOUT_ADDR,                    // Endpoint address (OUT, address 1)
	0x02,                              // Bulk endpoint type
	LOBYTE(MSC_MAX_FS_PACKET),
	HIBYTE(MSC_MAX_FS_PACKET),
	0x00                               // Polling interval in milliseconds
};

uint8_t langIDDescriptor[USB_LEN_LANGID_STR_DESC] __ALIGN_END = {
	USB_LEN_LANGID_STR_DESC,
	USB_DESC_TYPE_STRING,
	LOBYTE(USBD_LANGID_STRING),
	HIBYTE(USBD_LANGID_STRING),
};

/*
const char *stringTable[] = {
	"manufacturer",
	"product",
	nullptr          // Es calcula insitu
};
*/

#endif
