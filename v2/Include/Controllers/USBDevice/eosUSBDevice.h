#pragma once
#ifndef __eosUSBDevice__
#define __eosUSBDevice__


#include "eos.h"

#include "usbd_desc.h"
#include "usbd_def.h"


namespace eos {

	class USBDeviceClass;

	class USBDevice {
		public:
			enum class State {
				invalid,
				reset,
				ready,
				running
			};

		private:
			State _state;
			USBD_HandleTypeDef _usbd;

		public:
			USBDevice();

			void initialize(USBD_DescriptorsTypeDef *descriptors);
			void start();

			inline State getState() const {	return _state; }
			inline USBD_HandleTypeDef * getHandle() { return &_usbd; }
	};
}


#endif // __eosUSBDevice__
