#pragma once
#ifndef __eosMSCDefinitions__
#define __eosMSCDefinitions__


#include "eos.h"


#ifndef MSC_MEDIA_PACKET
#define MSC_MEDIA_PACKET             512U
#endif

#define MSC_MAX_FS_PACKET            0x40U
#define MSC_MAX_HS_PACKET            0x200U

#define BOT_GET_MAX_LUN              0xFE
#define BOT_RESET                    0xFF
#define USB_MSC_CONFIG_DESC_SIZ      32

#ifndef MSC_EPIN_ADDR
#define MSC_EPIN_ADDR                0x81U
#endif

#ifndef MSC_EPOUT_ADDR
#define MSC_EPOUT_ADDR               0x01U
#endif

#ifndef MSC_BOT_MAX_LUN
#define MSC_BOT_MAX_LUN              0x2U
#endif

#define USBD_BOT_IDLE                      0U       /* Idle state */
#define USBD_BOT_DATA_OUT                  1U       /* Data Out state */
#define USBD_BOT_DATA_IN                   2U       /* Data In state */
#define USBD_BOT_LAST_DATA_IN              3U       /* Last Data In Last */
#define USBD_BOT_SEND_DATA                 4U       /* Send Immediate data */
#define USBD_BOT_NO_DATA                   5U       /* No data Stage */

#define USBD_BOT_CBW_SIGNATURE             0x43425355U
#define USBD_BOT_CSW_SIGNATURE             0x53425355U
#define USBD_BOT_CBW_LENGTH                31U
#define USBD_BOT_CSW_LENGTH                13U
#define USBD_BOT_MAX_DATA                  256U

/* CSW Status Definitions */
#define USBD_CSW_CMD_PASSED                0x00U
#define USBD_CSW_CMD_FAILED                0x01U
#define USBD_CSW_PHASE_ERROR               0x02U

/* BOT Status */
#define USBD_BOT_STATUS_NORMAL             0U
#define USBD_BOT_STATUS_RECOVERY           1U
#define USBD_BOT_STATUS_ERROR              2U


#define USBD_DIR_IN                        0U
#define USBD_DIR_OUT                       1U
#define USBD_BOTH_DIR                      2U


#define SENSE_LIST_DEEPTH                           4U

#define SCSI_FORMAT_UNIT                            0x04U
#define SCSI_INQUIRY                                0x12U
#define SCSI_MODE_SELECT6                           0x15U
#define SCSI_MODE_SELECT10                          0x55U
#define SCSI_MODE_SENSE6                            0x1AU
#define SCSI_MODE_SENSE10                           0x5AU
#define SCSI_ALLOW_MEDIUM_REMOVAL                   0x1EU
#define SCSI_READ6                                  0x08U
#define SCSI_READ10                                 0x28U
#define SCSI_READ12                                 0xA8U
#define SCSI_READ16                                 0x88U

#define SCSI_READ_CAPACITY10                        0x25U
#define SCSI_READ_CAPACITY16                        0x9EU

#define SCSI_REQUEST_SENSE                          0x03U
#define SCSI_START_STOP_UNIT                        0x1BU
#define SCSI_TEST_UNIT_READY                        0x00U
#define SCSI_WRITE6                                 0x0AU
#define SCSI_WRITE10                                0x2AU
#define SCSI_WRITE12                                0xAAU
#define SCSI_WRITE16                                0x8AU

#define SCSI_VERIFY10                               0x2FU
#define SCSI_VERIFY12                               0xAFU
#define SCSI_VERIFY16                               0x8FU

#define SCSI_READ_FORMAT_CAPACITIES                 0x23U
#define SCSI_RECEIVE_DIAGNOSTIC_RESULTS             0x1CU
#define SCSI_SEND_DIAGNOSTIC                        0x1DU
#define SCSI_REPORT_LUNS                            0xA0U

#define NO_SENSE                                    0U
#define RECOVERED_ERROR                             1U
#define NOT_READY                                   2U
#define MEDIUM_ERROR                                3U
#define HARDWARE_ERROR                              4U
#define ILLEGAL_REQUEST                             5U
#define UNIT_ATTENTION                              6U
#define DATA_PROTECT                                7U
#define BLANK_CHECK                                 8U
#define MSC_VENDOR_SPECIFIC                         9U
#define COPY_ABORTED                                10U
#define ABORTED_COMMAND                             11U
#define VOLUME_OVERFLOW                             13U
#define MISCOMPARE                                  14U

#define INVALID_CDB                                 0x20U
#define INVALID_FIELD_IN_COMMAND                    0x24U
#define PARAMETER_LIST_LENGTH_ERROR                 0x1AU
#define INVALID_FIELD_IN_PARAMETER_LIST             0x26U
#define ADDRESS_OUT_OF_RANGE                        0x21U
#define MEDIUM_NOT_PRESENT                          0x3AU
#define MEDIUM_HAVE_CHANGED                         0x28U
#define WRITE_PROTECTED                             0x27U
#define UNRECOVERED_READ_ERROR                      0x11U
#define WRITE_FAULT                                 0x03U

#define READ_FORMAT_CAPACITY_DATA_LEN               0x0CU
#define READ_CAPACITY10_DATA_LEN                    0x08U
#define REQUEST_SENSE_DATA_LEN                      0x12U
#define STANDARD_INQUIRY_DATA_LEN                   0x24U
#define BLKVFY                                      0x04U

#define SCSI_MEDIUM_UNLOCKED                        0x00U
#define SCSI_MEDIUM_LOCKED                          0x01U
#define SCSI_MEDIUM_EJECTED                         0x02U

#define MODE_SENSE6_LEN                    0x04U
#define MODE_SENSE10_LEN                   0x08U
#define LENGTH_INQUIRY_PAGE00              0x06U
#define LENGTH_INQUIRY_PAGE80              0x08U
#define LENGTH_FORMAT_CAPACITIES           0x14U
#define DIAGNOSTIC_DATA_LEN                0x08U
#define LOG_PAGE_DATA_LEN                  0x10U


namespace eos {

	typedef struct _SENSE_ITEM {
	  uint8_t Skey;
	  union  {
		struct _ASCs {
		  uint8_t ASC;
		  uint8_t ASCQ;
		} b;
		uint8_t ASC;
		uint8_t *pData;
	  } w;
	} USBD_SCSI_SenseTypeDef;

	struct USBD_MSC_BOT_CBWTypeDef {
		uint32_t dSignature;
		uint32_t dTag;
		uint32_t dDataLength;
		uint8_t  bmFlags;
		uint8_t  bLUN;
		uint8_t  bCBLength;
		uint8_t  CB[16];
		uint8_t  ReservedForAlign;
	};

	struct USBD_MSC_BOT_CSWTypeDef {
		uint32_t dSignature;
		uint32_t dTag;
		uint32_t dDataResidue;
		uint8_t  bStatus;
		uint8_t  ReservedForAlign[3];
	};

	struct USBD_MSC_BOT_LUN_TypeDef {
	  uint16_t size;
	  uint32_t nbr;
	  uint32_t addr;
	  uint32_t len;
	};

	struct USBD_MSC_BOT_HandleTypeDef {
		uint32_t                 max_lun;
		uint32_t                 interface;
		uint8_t                  bot_state;
		uint8_t                  bot_status;
		uint32_t                 bot_data_length;
		uint8_t                  bot_data[MSC_MEDIA_PACKET];
		USBD_MSC_BOT_CBWTypeDef  cbw;
		USBD_MSC_BOT_CSWTypeDef  csw;
	};

}

//namespace eos {
	namespace internal {

		// Valors obtinguts de 'USB Mass Storage Class specification'
		//
		struct MSCRequest_RequestID {
			static constexpr uint8_t botGetMaxLun = 0xFE;
			static constexpr uint8_t botReset     = 0xFF;
		};

	}

	enum class MSCRequestID {
		botGetMaxLun = internal::MSCRequest_RequestID::botGetMaxLun,
		botReset     = internal::MSCRequest_RequestID::botReset
	};

	inline MSCRequestID getMSCRequestID(USBD_SetupReqTypedef *request) {
		return request->getClassRequestID<MSCRequestID>();
	}

//}


#endif // __eosMSCDefinitions__
