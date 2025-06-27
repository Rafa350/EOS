#pragma once
#ifndef __eosMSCStorage_RAM__
#define __eosMSCStorage_RAM__


#include "Controllers/USBDevice/eosUSBDeviceClassMSC.h"


namespace eos {

	class MSCStorage_RAM: public MSCStorage {
		private:
			uint8_t * const _storage;
			unsigned const _storageSize;
			USBD_StorageTypeDef _callTable;

			static int8_t init(uint8_t lun);
			static int8_t getCapacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
			static int8_t isReady(uint8_t lun);
			static int8_t isWriteProtected(uint8_t lun);
			static int8_t read(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
			static int8_t write(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
			static int8_t getMaxLun(void);

		public:
			MSCStorage_RAM(uint8_t *storage, unsigned storageSize);

			USBD_StorageTypeDef* getDescriptor() const override;
	};

}


#endif // __eosMSCStorage_RAM__



