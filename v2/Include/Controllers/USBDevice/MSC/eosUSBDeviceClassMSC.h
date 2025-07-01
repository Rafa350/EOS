#pragma once
#ifndef __eosUSBDeviceClassMSC__
#define __eosUSBDeviceClassMSC__


#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"
#include "Controllers/USBDevice/MSC/ST/st_usbd_msc.h"


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

	class USBDeviceClassMSC final: public USBDeviceClass {
		private:
			MSCStorage *_storage;

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
