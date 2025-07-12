#pragma once
#ifndef __eosCDCDefinitions__
#define __eosCDCDefinitions__


#include "eos.h"
#include "Controllers/USBDevice/eosUSBDefinitions.h"


#ifndef CDC_IN_EP
#define CDC_IN_EP                                   0x81U  /* EP1 for data IN */
#endif

#ifndef CDC_OUT_EP
#define CDC_OUT_EP                                  0x01U  /* EP1 for data OUT */
#endif

#ifndef CDC_CMD_EP
#define CDC_CMD_EP                                  0x82U  /* EP2 for CDC commands */
#endif

#ifndef CDC_HS_BINTERVAL
#define CDC_HS_BINTERVAL                            0x10U
#endif

#ifndef CDC_FS_BINTERVAL
#define CDC_FS_BINTERVAL                            0x10U
#endif

#ifndef CDC_CMD_PACKET_SIZE
#define CDC_CMD_PACKET_SIZE                         8U  /* Control Endpoint Packet size */
#endif

/* CDC Endpoints parameters: you can fine tune these values depending on the needed baudrates and performance. */
#define CDC_DATA_HS_MAX_PACKET_SIZE                 512U  /* Endpoint IN & OUT Packet size */
#define CDC_DATA_FS_MAX_PACKET_SIZE                 64U  /* Endpoint IN & OUT Packet size */

#define USB_CDC_CONFIG_DESC_SIZ                     67U
#define CDC_DATA_HS_IN_PACKET_SIZE                  CDC_DATA_HS_MAX_PACKET_SIZE
#define CDC_DATA_HS_OUT_PACKET_SIZE                 CDC_DATA_HS_MAX_PACKET_SIZE

#define CDC_DATA_FS_IN_PACKET_SIZE                  CDC_DATA_FS_MAX_PACKET_SIZE
#define CDC_DATA_FS_OUT_PACKET_SIZE                 CDC_DATA_FS_MAX_PACKET_SIZE

#define CDC_REQ_MAX_DATA_SIZE                       0x7U


//namespace eos {

	struct USBD_CDC_HandleTypeDef {
		uint32_t data[CDC_DATA_FS_MAX_PACKET_SIZE / 4U];      /* Force 32-bit alignment */
	};

	namespace internal {

		// Valors obtinguts de 'USB Comunication Device Class specification'
		//
		struct CDCRequest_RequestID {
			static constexpr uint8_t sendEncapsulatedCommand = 0x00;
			static constexpr uint8_t getEncapsulatedResponse = 0x01;
			static constexpr uint8_t setCommFeature          = 0x02;
			static constexpr uint8_t getCommFeature          = 0x03;
			static constexpr uint8_t clearCommFeature        = 0x04;
			static constexpr uint8_t setLineCoding           = 0x20;
			static constexpr uint8_t getLineCoding           = 0x21;
			static constexpr uint8_t setControlLineState     = 0x22;
			static constexpr uint8_t sendBreak               = 0x23;
		};

	}

	enum class CDCRequestID {
		sendEncapsulatedCommand = internal::CDCRequest_RequestID::sendEncapsulatedCommand,
		getEncapsulatedResponse = internal::CDCRequest_RequestID::getEncapsulatedResponse,
		setCommFeature          = internal::CDCRequest_RequestID::setCommFeature,
		getCommFeature          = internal::CDCRequest_RequestID::getCommFeature,
		clearCommFeature        = internal::CDCRequest_RequestID::clearCommFeature,
		setLineCoding           = internal::CDCRequest_RequestID::setLineCoding,
		getLineCoding           = internal::CDCRequest_RequestID::getLineCoding,
		setControlLineState     = internal::CDCRequest_RequestID::setControlLineState,
		sendBreak               = internal::CDCRequest_RequestID::sendBreak
	};

	inline CDCRequestID getCDCRequestID(USBD_SetupReqTypedef *request) {
		return request->getClassRequestID<CDCRequestID>();
	}

//}


#endif // __eosCDCDefinitions__
