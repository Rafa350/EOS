#pragma once
#ifndef __eosUSBDeviceClassMSC__
#define __eosUSBDeviceClassMSC__


#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"
#include "Controllers/USBDevice/MSC/eosMSCDefinitions.h"


namespace eos {


	class MSCStorage {
		public:
			virtual int8_t initialize(uint8_t lun) = 0;

			virtual int8_t getCapacity(uint8_t lun, uint32_t *blkQuantity, uint16_t *blkSize) = 0;
			virtual int8_t getMaxLun() = 0;
			virtual int8_t const * getInquiryData() = 0;

			virtual int8_t isReady(uint8_t lun) = 0;
			virtual int8_t isWriteProtected(uint8_t lun) = 0;

			virtual int8_t read(uint8_t lun, uint8_t *buffer, uint32_t blkStart, uint16_t blkCount) = 0;
			virtual int8_t write(uint8_t lun, uint8_t *buffer, uint32_t blkStart, uint16_t blkCount) = 0;
	};

	class SCSIProcessor;

	class USBDeviceClassMSC final: public USBDeviceClass {
		private:
			MSCStorage *_storage;
			USBD_MSC_BOT_HandleTypeDef _msc;
			SCSIProcessor *_scsi;
			static constexpr uint8_t _inEpAdd  = MSC_EPIN_ADDR;
			static constexpr uint8_t _outEpAdd = MSC_EPOUT_ADDR;

		private:
			// BOT layer
			void botInit();
			void botDeInit();
			void botReset();
			void botDataIn(uint8_t epnum);
			void botDataOut(uint8_t epnum);
			void botSendCSW(uint8_t CSW_Status);
			void botCplClrFeature(uint8_t epnum);
			void botSendData(uint8_t *buffer, unsigned length);
			void botCBWDecode();
			void botAbort();


		public:
			USBDeviceClassMSC(USBDeviceDriver *drvUSBD, MSCStorage *storage);

			void initialize() override;

			int8_t classInit(uint8_t cfgidx) override;
			int8_t classDeinit(uint8_t cfgidx) override;

			int8_t classSetup(USBD_SetupReqTypedef *req) override;

			int8_t classEP0TxSent() override;
			int8_t classEP0RxReady() override;
			int8_t classSOF() override;
			int8_t classDataIn(uint8_t epnum) override;
			int8_t classDataOut(uint8_t epnum) override;
			int8_t classIsoINIncomplete(uint8_t epnum) override;
			int8_t classIsoOUTIncomplete(uint8_t epnum) override;
			uint8_t* classGetHSConfigurationDescriptor(uint16_t *length) override;
			uint8_t* classGetFSConfigurationDescriptor(uint16_t *length) override;
			uint8_t* classGetOtherSpeedConfigurationDescriptor(uint16_t *length) override;
			uint8_t* classGetDeviceQualifierDescriptor(uint16_t *length) override;
	};
}


#endif // __eosUSBDeviceClassMSC__
