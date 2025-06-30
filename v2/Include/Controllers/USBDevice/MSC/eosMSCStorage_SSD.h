#pragma once
#ifndef __eosMSCStorage_SSD__
#define __eosMSCStorage_SSD__


#include "Controllers/USBDevice/MSC/eosUSBDeviceClassMSC.h"


namespace eos {

	class MSCStorage_SSD: public MSCStorage {
		private:
			int8_t _prevStatus = 0;
			USBD_StorageTypeDef _callTable;

		private:
			bool isCardPresent() const;
			bool isCardBusy() const;

		public:
			MSCStorage_SSD();

			int8_t init(uint8_t lun) override;
			int8_t getCapacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size) override;
			int8_t isReady(uint8_t lun) override;
			int8_t isWriteProtected(uint8_t lun) override;
			int8_t read(uint8_t lun, uint8_t *buffer, uint32_t blkStart, uint16_t blkCount) override;
			int8_t write(uint8_t lun, uint8_t *buffer, uint32_t blkStart, uint16_t blkCount) override;
			int8_t getMaxLun() override;

			USBD_StorageTypeDef * getDescriptor() const override;
	};

}


#endif // __eosMSCStorage_SSD__



