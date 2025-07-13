#pragma once
#ifndef __eosMSCStorage_SSD__
#define __eosMSCStorage_SSD__


#include "Controllers/USBDevice/MSC/eosUSBDeviceClassMSC.h"


namespace eos {

	class MSCStorage_SSD final: public MSCStorage {
		private:
			int8_t _prevStatus;

		private:
			bool isCardPresent() const;
			bool isCardBusy() const;

		public:
			MSCStorage_SSD();

			Result initialize() override;

			int8_t getCapacity(uint8_t lun, unsigned &blkQuantity, unsigned &blkSize) override;
			unsigned getMaxLun() override;
			int8_t const * getInquiryData() override;

			bool isReady(uint8_t lun) override;
			bool isWriteProtected(uint8_t lun) override;

			Result read(uint8_t lun, uint8_t *buffer, uint32_t blkStart, uint16_t blkCount) override;
			Result write(uint8_t lun, uint8_t *buffer, uint32_t blkStart, uint16_t blkCount) override;
	};

}


#endif // __eosMSCStorage_SSD__



