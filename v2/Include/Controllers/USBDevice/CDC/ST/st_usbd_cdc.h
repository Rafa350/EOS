#pragma once
#ifndef __st_usbd_cdc__
#define __st_usbd_cdc__


#ifndef CDC_IN_EP
#define CDC_IN_EP                                   0x81U  /* EP1 for data IN */
#endif /* CDC_IN_EP */
#ifndef CDC_OUT_EP
#define CDC_OUT_EP                                  0x01U  /* EP1 for data OUT */
#endif /* CDC_OUT_EP */
#ifndef CDC_CMD_EP
#define CDC_CMD_EP                                  0x82U  /* EP2 for CDC commands */
#endif /* CDC_CMD_EP  */

#ifndef CDC_HS_BINTERVAL
#define CDC_HS_BINTERVAL                            0x10U
#endif /* CDC_HS_BINTERVAL */

#ifndef CDC_FS_BINTERVAL
#define CDC_FS_BINTERVAL                            0x10U
#endif /* CDC_FS_BINTERVAL */

#ifndef CDC_CMD_PACKET_SIZE
#define CDC_CMD_PACKET_SIZE                         8U  /* Control Endpoint Packet size */
#endif /* CDC_CMD_PACKET_SIZE */

/* CDC Endpoints parameters: you can fine tune these values depending on the needed baudrates and performance. */
#define CDC_DATA_HS_MAX_PACKET_SIZE                 512U  /* Endpoint IN & OUT Packet size */
#define CDC_DATA_FS_MAX_PACKET_SIZE                 64U  /* Endpoint IN & OUT Packet size */

#define USB_CDC_CONFIG_DESC_SIZ                     67U
#define CDC_DATA_HS_IN_PACKET_SIZE                  CDC_DATA_HS_MAX_PACKET_SIZE
#define CDC_DATA_HS_OUT_PACKET_SIZE                 CDC_DATA_HS_MAX_PACKET_SIZE

#define CDC_DATA_FS_IN_PACKET_SIZE                  CDC_DATA_FS_MAX_PACKET_SIZE
#define CDC_DATA_FS_OUT_PACKET_SIZE                 CDC_DATA_FS_MAX_PACKET_SIZE

#define CDC_REQ_MAX_DATA_SIZE                       0x7U


#define CDC_SEND_ENCAPSULATED_COMMAND               0x00U
#define CDC_GET_ENCAPSULATED_RESPONSE               0x01U
#define CDC_SET_COMM_FEATURE                        0x02U
#define CDC_GET_COMM_FEATURE                        0x03U
#define CDC_CLEAR_COMM_FEATURE                      0x04U
#define CDC_SET_LINE_CODING                         0x20U
#define CDC_GET_LINE_CODING                         0x21U
#define CDC_SET_CONTROL_LINE_STATE                  0x22U
#define CDC_SEND_BREAK                              0x23U


struct USBD_CDC_LineCodingTypeDef {
	uint32_t bitrate;
	uint8_t  format;
	uint8_t paritytype;
	uint8_t datatype;
};


struct USBD_CDC_HandleTypeDef {
	uint32_t data[CDC_DATA_HS_MAX_PACKET_SIZE / 4U];      /* Force 32-bit alignment */
	uint8_t cmdOpCode;
	uint8_t cmdLength;
	uint8_t *rxBuffer;
	uint8_t *txBuffer;
	uint32_t rxLength;
	uint32_t txLength;
	volatile uint32_t txState;
	volatile uint32_t rxState;
};


#endif  // __st_usbd_cdc__

