#pragma once
#ifndef __eosUSBDeviceClassMSC__
#define __eosUSBDeviceClassMSC__


#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceClass.h"

#include "usbd_msc.h"


namespace eos {

	class MSCStorage {
		public:
			virtual USBD_StorageTypeDef* getDescriptor() const = 0;
	};

	class USBDeviceClassMSC: public USBDeviceClass {
		public:
			USBDeviceClassMSC(USBDevice *devUSBD);

			void initialize(MSCStorage *storage);
	};
}


#endif // __eosUSBDeviceClassMSC__
