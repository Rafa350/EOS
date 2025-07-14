#include "eos.h"

#ifdef USE_CDC_DEVICE


#include "Controllers/USBDevice/CDC/eosCDCDefinitions.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"
#include "usbd_desc.h"
#include "usbd_conf.h"


#define USBD_VID                      0x0483
#define USBD_PID                      0x5740
#define USBD_LANGID_STRING            0x409
#define USBD_MANUFACTURER_STRING      "STMicroelectronics"
#define USBD_PRODUCT_HS_STRING        "STM32 Virtual ComPort in HS Mode"
#define USBD_PRODUCT_FS_STRING        "STM32 Virtual ComPort in FS Mode"
#define USBD_CONFIGURATION_HS_STRING  "VCP Config"
#define USBD_INTERFACE_HS_STRING      "VCP Interface"
#define USBD_CONFIGURATION_FS_STRING  "VCP Config"
#define USBD_INTERFACE_FS_STRING      "VCP Interface"


uint8_t USBD_DeviceDescriptor[USB_LEN_DEV_DESC] __ALIGN_END = {
  0x12,                         /* bLength */
  USB_DESC_TYPE_DEVICE,         /* bDescriptorType */
  0x00,                         /* bcdUSB */
  0x02,
  0x02,                         /* bDeviceClass */
  0x02,                         /* bDeviceSubClass */
  0x00,                         /* bDeviceProtocol */
  USB_MAX_EP0_SIZE,             /* bMaxPacketSize */
  LOBYTE(USBD_VID),             /* idVendor */
  HIBYTE(USBD_VID),             /* idVendor */
  LOBYTE(USBD_PID),             /* idVendor */
  HIBYTE(USBD_PID),             /* idVendor */
  0x00,                         /* bcdDevice rel. 2.00 */
  0x02,
  USBD_IDX_MFC_STR,             /* Index of manufacturer string */
  USBD_IDX_PRODUCT_STR,         /* Index of product string */
  USBD_IDX_SERIAL_STR,          /* Index of serial number string */
  USBD_MAX_NUM_CONFIGURATION    /* bNumConfigurations */
};                              /* USB_DeviceDescriptor */

uint8_t USBD_CDC_DeviceQualifierDescriptor[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END = {
	  USB_LEN_DEV_QUALIFIER_DESC,
	  USB_DESC_TYPE_DEVICE_QUALIFIER,
	  0x00,
	  0x02,
	  0x00,
	  0x00,
	  0x00,
	  0x40,
	  0x01,
	  0x00,
};

__ALIGN_BEGIN uint8_t USBD_CDC_ConfigurationDescriptor[USB_CDC_CONFIG_DESC_SIZ] __ALIGN_END = {

	// Configuration Descriptor
	0x09,                                       /* bLength: Configuration Descriptor size */
	USB_DESC_TYPE_CONFIGURATION,                /* bDescriptorType: Configuration */
	USB_CDC_CONFIG_DESC_SIZ,                    /* wTotalLength */
	0x00,
	0x02,                                       /* bNumInterfaces: 2 interfaces */
	0x01,                                       /* bConfigurationValue: Configuration value */
	0x00,                                       /* iConfiguration: Index of string descriptor
												 describing the configuration */
	#if (USBD_SELF_POWERED == 1U)
	0xC0,                                       /* bmAttributes: Bus Powered according to user configuration */
	#else
	0x80,                                       /* bmAttributes: Bus Powered according to user configuration */
	#endif /* USBD_SELF_POWERED */
	USBD_MAX_POWER,                             /* MaxPower (mA) */

	// Interface Descriptor
	0x09,                                       /* bLength: Interface Descriptor size */
	USB_DESC_TYPE_INTERFACE,                    /* bDescriptorType: Interface */
	// Interface descriptor type
	0x00,                                       /* bInterfaceNumber: Number of Interface */
	0x00,                                       /* bAlternateSetting: Alternate setting */
	0x01,                                       /* bNumEndpoints: One endpoint used */
	0x02,                                       /* bInterfaceClass: Communication Interface Class */
	0x02,                                       /* bInterfaceSubClass: Abstract Control Model */
	0x01,                                       /* bInterfaceProtocol: Common AT commands */
	0x00,                                       /* iInterface */

	// Header Functional Descriptor
	0x05,                                       /* bLength: Endpoint Descriptor size */
	0x24,                                       /* bDescriptorType: CS_INTERFACE */
	0x00,                                       /* bDescriptorSubtype: Header Func Desc */
	0x10,                                       /* bcdCDC: spec release number */
	0x01,

	// Call Management Functional Descriptor
	0x05,                                       /* bFunctionLength */
	0x24,                                       /* bDescriptorType: CS_INTERFACE */
	0x01,                                       /* bDescriptorSubtype: Call Management Func Desc */
	0x00,                                       /* bmCapabilities: D0+D1 */
	0x01,                                       /* bDataInterface */

	// ACM Functional Descriptor
	0x04,                                       /* bFunctionLength */
	0x24,                                       /* bDescriptorType: CS_INTERFACE */
	0x02,                                       /* bDescriptorSubtype: Abstract Control Management desc */
	0x02,                                       /* bmCapabilities */

	// Union Functional Descriptor
	0x05,                                       /* bFunctionLength */
	0x24,                                       /* bDescriptorType: CS_INTERFACE */
	0x06,                                       /* bDescriptorSubtype: Union func desc */
	0x00,                                       /* bMasterInterface: Communication class interface */
	0x01,                                       /* bSlaveInterface0: Data Class Interface */

	// Endpoint 2 Descriptor
	0x07,                                       /* bLength: Endpoint Descriptor size */
	USB_DESC_TYPE_ENDPOINT,                     /* bDescriptorType: Endpoint */
	CDC_CMD_EP,                                 /* bEndpointAddress */
	0x03,                                       /* bmAttributes: Interrupt */
	LOBYTE(CDC_CMD_PACKET_SIZE),                /* wMaxPacketSize */
	HIBYTE(CDC_CMD_PACKET_SIZE),
	CDC_FS_BINTERVAL,                           /* bInterval */

	// Data class interface descriptor
	0x09,                                       /* bLength: Endpoint Descriptor size */
	USB_DESC_TYPE_INTERFACE,                    /* bDescriptorType: */
	0x01,                                       /* bInterfaceNumber: Number of Interface */
	0x00,                                       /* bAlternateSetting: Alternate setting */
	0x02,                                       /* bNumEndpoints: Two endpoints used */
	0x0A,                                       /* bInterfaceClass: CDC */
	0x00,                                       /* bInterfaceSubClass */
	0x00,                                       /* bInterfaceProtocol */
	0x00,                                       /* iInterface */

	// Endpoint OUT Descriptor
	0x07,                                       /* bLength: Endpoint Descriptor size */
	USB_DESC_TYPE_ENDPOINT,                     /* bDescriptorType: Endpoint */
	CDC_OUT_EP,                                 /* bEndpointAddress */
	0x02,                                       /* bmAttributes: Bulk */
	LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),        /* wMaxPacketSize */
	HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),
	0x00,                                       /* bInterval */

	// Endpoint IN Descriptor
	0x07,                                       /* bLength: Endpoint Descriptor size */
	USB_DESC_TYPE_ENDPOINT,                     /* bDescriptorType: Endpoint */
	CDC_IN_EP,                                  /* bEndpointAddress */
	0x02,                                       /* bmAttributes: Bulk */
	LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),        /* wMaxPacketSize */
	HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),
	0x00                                        /* bInterval */
};

__ALIGN_BEGIN uint8_t USBD_LangIDDescriptor[USB_LEN_LANGID_STR_DESC] __ALIGN_END = {
  USB_LEN_LANGID_STR_DESC,
  USB_DESC_TYPE_STRING,
  LOBYTE(USBD_LANGID_STRING),
  HIBYTE(USBD_LANGID_STRING),
};

__ALIGN_BEGIN uint8_t USBD_StringSerial[USB_SIZ_STRING_SERIAL] __ALIGN_END = {
  USB_SIZ_STRING_SERIAL,
  USB_DESC_TYPE_STRING,
};

__ALIGN_BEGIN uint8_t USBD_StrDesc[USBD_MAX_STR_DESC_SIZ] __ALIGN_END;

const char* USBD_Strings[] = {
};


#endif
