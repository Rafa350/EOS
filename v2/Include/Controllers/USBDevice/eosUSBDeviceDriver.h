#pragma once
#ifndef __eosUSBDeviceDriver__
#define __eosUSBDeviceDriver__


#include "eos.h"
#include "Controllers/USBDevice/ST/st_usbd_def.h"
#include "System/Collections/eosIntrusiveForwardList.h"
#include "System/eosResults.h"

#include "usbd_desc.h"


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

			virtual int8_t classInit(uint8_t cfgidx) = 0;
			virtual int8_t classDeinit(uint8_t cfgidx) = 0;

			virtual int8_t classSetup(USBD_SetupReqTypedef *req) = 0;

			virtual int8_t classEP0TxSent() = 0;
			virtual int8_t classEP0RxReady() = 0;
			virtual int8_t classSOF() = 0;
			virtual int8_t classDataIn(uint8_t epnum) = 0;
			virtual int8_t classDataOut(uint8_t epnum) = 0;
			virtual int8_t classIsoINIncomplete(uint8_t epnum) = 0;
			virtual int8_t classIsoOUTIncomplete(uint8_t epnum) = 0;
			virtual uint8_t* classGetHSConfigurationDescriptor(uint16_t *length) = 0;
			virtual uint8_t* classGetFSConfigurationDescriptor(uint16_t *length) = 0;
			virtual uint8_t* classGetOtherSpeedConfigurationDescriptor(uint16_t *length) = 0;
			virtual uint8_t* classGetDeviceQualifierDescriptor(uint16_t *length) = 0;
	};
}


#endif // __eosUSBDeviceDriver__
