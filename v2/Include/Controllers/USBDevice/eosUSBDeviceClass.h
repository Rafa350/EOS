#pragma once
#ifndef __eosUSBDeviceClass__
#define __eosUSBDeviceClass__


#include "eos.h"
#include "Controllers//USBDevice/eosUSBDevice.h"

#include "usbd_def.h"


namespace eos {

	class USBDeviceClass {
		protected:
			USBDevice * const _devUSBD;
			USBD_ClassTypeDef * const _usbdClass;

		protected:
			USBDeviceClass(USBDevice *devUSBD, USBD_ClassTypeDef *usbdClass);

		public:
			inline USBD_ClassTypeDef * getClass() const {
				return _usbdClass;
			}
	};
}


#endif // __eosUSBDeviceClass__
