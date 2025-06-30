#pragma once
#ifndef __eosUSBDeviceClassMSC__
#define __eosUSBDeviceClassMSC__


#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"

#include "usbd_msc.h"


namespace eos {

	class MSCStorage {
		public:
			virtual int8_t init(uint8_t lun) = 0;
			virtual int8_t getCapacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size) = 0;
			virtual int8_t isReady(uint8_t lun) = 0;
			virtual int8_t isWriteProtected(uint8_t lun) = 0;
			virtual int8_t read(uint8_t lun, uint8_t *buf, uint32_t blkStart, uint16_t blkCount) = 0;
			virtual int8_t write(uint8_t lun, uint8_t *buf, uint32_t blkStart, uint16_t blkCount) = 0;
			virtual int8_t getMaxLun() = 0;
			virtual USBD_StorageTypeDef* getDescriptor() const = 0;
	};

	class USBDeviceClassMSC: public USBDeviceClass {
		private:
			MSCStorage *_storage;

		public:
			USBDeviceClassMSC(USBDeviceDriver *drvUSBD, MSCStorage *storage);

			void initialize() override;
	};
}


#endif // __eosUSBDeviceClassMSC__
