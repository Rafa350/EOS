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

			virtual int8_t classInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx) = 0;
			virtual int8_t classDeinit(USBD_HandleTypeDef *pdev, uint8_t cfgidx) = 0;
			virtual int8_t classSetup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req) = 0;
			virtual int8_t classEP0TxSent() = 0;
			virtual int8_t classEP0RxReady(USBD_HandleTypeDef *pdev) = 0;
			virtual int8_t classDataIn(USBD_HandleTypeDef *pdev, uint8_t epnum) = 0;
			virtual int8_t classDataOut(USBD_HandleTypeDef *pdev, uint8_t epnum) = 0;
			virtual int8_t* classGetHSCfgDesc(uint16_t *length) = 0;
			virtual int8_t* classGetFSCfgDesc(uint16_t *length) = 0;
			virtual int8_t* classGetOtherSpeedCfgDesc(uint16_t *length) = 0;
			virtual int8_t* classGetDeviceQualifierDescriptor(uint16_t *length) = 0;
	};
}


#endif // __eosUSBDeviceDriver__
