#pragma once
#ifndef __eosMSCStorage_RAM__
#define __eosMSCStorage_RAM__


#include "Controllers/USBDevice/MSC/eosUSBDeviceClassMSC.h"


namespace eos {

	class MSCStorage_RAM final: public MSCStorage {
		private:
			uint8_t * const _storage;
			unsigned const _storageSize;

		public:
			MSCStorage_RAM(uint8_t *storage, unsigned storageSize);

			int8_t initialize(uint8_t lun) override;

			int8_t getCapacity(uint8_t lun, uint32_t *blkQuantity, uint16_t *blkSize) override;
			int8_t getMaxLun() override;
			int8_t const * getInquiryData() override;

			int8_t isReady(uint8_t lun) override;
			int8_t isWriteProtected(uint8_t lun) override;

			int8_t read(uint8_t lun, uint8_t *buffer, uint32_t blkStart, uint16_t blkCount) override;
			int8_t write(uint8_t lun, uint8_t *buffer, uint32_t blkStart, uint16_t blkCount) override;
	};

}


#endif // __eosMSCStorage_RAM__



