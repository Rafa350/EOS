#pragma once
#ifndef __eosSCSIProcessor__
#define __eosSCSIProcessor__


#include "eos.h"
#include "Controllers/USBDevice/MSC/eosUSBDeviceClassMSC.h"
#include "Controllers/USBDevice/MSC/eosMSCDefinitions.h"


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

namespace eos {

	class MSCStorage;

	class SCSIProcessor {
		private:
			enum class MediumState {
				unlocked,
				locked,
				ejected
			};

		private:
			MSCStorage *_storage;
			USBD_HandleTypeDef *_pdev;
			uint8_t _inEpAdd;
			uint8_t _outEpAdd;
			USBD_MSC_BOT_HandleTypeDef *_msc;
			USBD_SCSI_SenseTypeDef _sense[SENSE_LIST_DEEPTH];
			unsigned _senseTail;
			unsigned _senseHead;
            USBD_MSC_BOT_LUN_TypeDef _scsi_blk[MSC_BOT_MAX_LUN];
			MediumState _mediumState;

		private:
			bool testUnitReady(uint8_t lun, const uint8_t *cmd);
			bool inquiry(uint8_t lun, const uint8_t *cmd);
			bool readFormatCapacity(uint8_t lun, const uint8_t *cmd);
			bool readCapacity10(uint8_t lun, const uint8_t *cmd);
			bool readCapacity16(uint8_t lun, const uint8_t *cmd);
			bool requestSense(uint8_t lun, const uint8_t *cmd);
			bool startStopUnit(int8_t lun, const uint8_t *cmd);
			bool allowPreventMediumRemoval(uint8_t lun, const uint8_t *cmd);
			bool modeSense6(uint8_t lun, const uint8_t *cmd);
			bool modeSense10(uint8_t lun, const uint8_t *cmd);
			bool write10(uint8_t lun, const uint8_t *cmd);
			bool write12(uint8_t lun, const uint8_t *cmd);
			bool read10(uint8_t lun, const uint8_t *cmd);
			bool read12(uint8_t lun, const uint8_t *cmd);
			bool verify10(uint8_t lun, const uint8_t *cmd);
			bool reportLuns(uint8_t lun, const uint8_t *cmd);
			bool receiveDiagnosticResults(uint8_t lun, const uint8_t *cmd);
			bool checkAddressRange(uint8_t lun, uint32_t blk_offset, uint32_t blk_nbr);
			bool processRead(uint8_t lun);
			bool processWrite(uint8_t lun);
			bool updateBotData(const uint8_t *buffer, uint16_t length);

		public:
			SCSIProcessor(MSCStorage *storage, USBD_HandleTypeDef *_pdev,
				uint8_t inEpAddr, uint8_t outEpAddr, USBD_MSC_BOT_HandleTypeDef *msc);

			void initialize();
			bool processCmd(uint8_t lun, const uint8_t *cmd);
			void senseCode(uint8_t lun, uint8_t sKey, uint8_t ASC);
	};

}


#endif // __eosSCSIProcessor__
