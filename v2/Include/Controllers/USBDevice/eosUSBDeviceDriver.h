#pragma once
#ifndef __eosUSBDeviceDriver__
#define __eosUSBDeviceDriver__


#include "eos.h"
#include "System/Collections/eosIntrusiveForwardList.h"
#include "System/eosResults.h"

#include "usbd_desc.h"
#include "usbd_def.h"


namespace eos {

	class USBDevice;
	class USBDeviceClass;

    using USBDeviceClassList = IntrusiveForwardList<USBDeviceClass, 0>;
    using USBDeviceClassListNode = IntrusiveForwardListNode<USBDeviceClass, 0>;

	class USBDeviceDriver final {
		public:
			enum class State {
				invalid,
				reset,
				ready,
				running
			};

		private:
			State _state;
			USBDeviceClassList _classes;
			USBD_HandleTypeDef _usbd;

		public:
			USBDeviceDriver();

			Result registerClass(USBDeviceClass *devClass);

			Result initialize(USBD_DescriptorsTypeDef *descriptors);
			Result start();
			Result stop();

			inline State getState() const {	return _state; }
			inline USBD_HandleTypeDef * getHandle() { return &_usbd; }
	};

	class USBDeviceClass: public USBDeviceClassListNode {
		protected:
			USBDeviceDriver * const _drvUSBD;

		protected:
			USBDeviceClass(USBDeviceDriver *drvUSBD);

		public:
			virtual void initialize() = 0;
	};
}


#endif // __eosUSBDeviceDriver__
