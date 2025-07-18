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
		uint8_t iface;
		uint8_t inEpAddr;
		uint8_t outEpAddr;
	};

	class USBDeviceClassMSC final: public USBDeviceClass {
		private:
			MSCStorage *_storage;
			SCSIProcessor *_scsi;
			uint8_t const _inEpAddr;
			uint8_t const _outEpAddr;
			USBD_MSC_BOT_HandleTypeDef _msc;

		private:
			void botInitialize();
			void botDeInitialize();
			void botReset();
			void botDataIn(uint8_t epAddr);
			void botDataOut(uint8_t epAddr);
			void botSendCSW(uint8_t cswStatus);
			void botCplClrFeature(uint8_t epnum);
			void botSendData(uint8_t *buffer, unsigned length);
			void botCBWDecode();
			void botAbort();

		protected:
			Result initializeImpl() override;

		public:
			USBDeviceClassMSC(USBDeviceDriver *drvUSBD, const USBDeviceClassMSCConfiguration *configuration, MSCStorage *storage);

			int8_t classInitialize(uint8_t cfgidx) override;
			int8_t classDeinitialize(uint8_t cfgidx) override;

			int8_t classSetup(USBD_SetupReqTypedef *req) override;

			int8_t classEP0TxSent() override;
			int8_t classEP0RxReady() override;
			int8_t classSOF() override;
			int8_t classDataIn(uint8_t epAddr) override;
			int8_t classDataOut(uint8_t epAddr) override;
			int8_t classIsoINIncomplete(uint8_t epnum) override;
			int8_t classIsoOUTIncomplete(uint8_t epnum) override;
			unsigned classGetInterfaceDescriptors(uint8_t *buffer, unsigned bufferSize, bool hs) override;
			bool classGetHSConfigurationDescriptor(uint8_t *&data, unsigned &length) override;
			bool classGetFSConfigurationDescriptor(uint8_t *&data, unsigned &length) override;
			bool classGetOtherSpeedConfigurationDescriptor(uint8_t *&data, unsigned &length) override;
			bool classGetDeviceQualifierDescriptor(uint8_t *&data, unsigned &length) override;

			bool usesEndPoint(uint8_t epAddr) const override;
	};
}


#endif // __eosUSBDeviceClassMSC__
