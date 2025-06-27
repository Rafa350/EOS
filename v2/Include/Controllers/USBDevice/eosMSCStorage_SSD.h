#pragma once
#ifndef __eosMSCStorage_SSD__
#define __eosMSCStorage_SSD__


#include "Controllers/USBDevice/eosUSBDeviceClassMSC.h"


namespace eos {

	class MSCStorage_SSD: public MSCStorage {
		public:
			USBD_StorageTypeDef * getDescriptor() const override;
	};

}


#endif // __eosMSCStorage_SSD__



