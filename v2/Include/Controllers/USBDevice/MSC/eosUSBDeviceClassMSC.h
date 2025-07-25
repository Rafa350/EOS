#pragma once
#ifndef __eosUSBDeviceClassMSC__
#define __eosUSBDeviceClassMSC__


#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"
#include "Controllers/USBDevice/MSC/eosMSCDefinitions.h"
#include "System/eosResults.h"


namespace eos {

	class MSCStorage {
		public:
			virtual Result initialize() = 0;

			virtual int8_t getCapacity(uint8_t lun, unsigned &blkQuantity, unsigned &blkSize) = 0;
			virtual unsigned getMaxLun() = 0;
			virtual int8_t const * getInquiryData() = 0;

			virtual bool isReady(uint8_t lun) = 0;
			virtual bool isWriteProtected(uint8_t lun) = 0;

			virtual Result read(uint8_t lun, uint8_t *buffer, uint32_t blkStart, uint16_t blkCount) = 0;
			virtual Result write(uint8_t lun, uint8_t *buffer, uint32_t blkStart, uint16_t blkCount) = 0;
	};

	class SCSIProcessor;

	struct USBDeviceClassMSCConfiguration {
		EpAddr const inEpAddr;
		EpAddr const outEpAddr;
		MSCStorage * const storage;
	};

	class USBDeviceClassMSC final: public USBDeviceClass {
		private:
			MSCStorage * const _storage;
			SCSIProcessor * const _scsi;
			EpAddr const _inEpAddr;
			EpAddr const _outEpAddr;
			USBD_MSC_BOT_HandleTypeDef _msc;

		private:
			void botInitialize();
			void botDeInitialize();
			void botReset();
			void botDataIn(EpAddr epAddr);
			void botDataOut(EpAddr epAddr);
			void botSendCSW(uint8_t cswStatus);
			void botCplClrFeature(EpAddr epAddr);
			void botSendData(uint8_t *buffer, unsigned length);
			void botCBWDecode();
			void botAbort();

		protected:
			Result initializeImpl() override;

		public:
			USBDeviceClassMSC(USBDeviceDriver *drvUSBD, const USBDeviceClassMSCConfiguration *configuration);

			int8_t classInitialize(uint8_t configIdx) override;
			int8_t classDeinitialize(uint8_t configIdx) override;

			int8_t classSetup(USBD_SetupReqTypedef *req) override;

			int8_t classEP0TxSent() override;
			int8_t classEP0RxReady() override;
			int8_t classSOF() override;
			int8_t classDataIn(EpAddr epAddr) override;
			int8_t classDataOut(EpAddr epAddr) override;
			int8_t classIsoINIncomplete(EpAddr epAddr) override;
			int8_t classIsoOUTIncomplete(EpAddr epAddr) override;

			bool buildInterfaceDescriptors(uint8_t *buffer, unsigned bufferSize, bool hs, unsigned &length) override;

			bool usesEndPoint(EpAddr epAddr) const override;
			bool usesIface(uint8_t iface) const override;
};
}


#endif // __eosUSBDeviceClassMSC__
