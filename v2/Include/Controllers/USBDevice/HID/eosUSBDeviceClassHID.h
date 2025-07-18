#pragma once
#ifndef __eosUSBDeviceClassHID__
#define __eosUSBDeviceClassHID__


#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"
#include "Controllers/USBDevice/HID/eosHIDDefinitions.h"
#include "System/eosResults.h"


namespace eos {

	class USBDeviceClassCDC;

	class USBDeviceClassHID final: public USBDeviceClass {

		private:
			static constexpr uint8_t _inEpAddr = HID_EPIN_ADDR;

		public:
			USBDeviceClassHID(USBDeviceDriver *drvUSBD, uint8_t iface);

			Result initialize();

			int8_t classInitialize(uint8_t cfgidx) override;
			int8_t classDeinitialize(uint8_t cfgidx) override;

			int8_t classSetup(USBD_SetupReqTypedef *req) override;
			int8_t classEP0TxSent() override;
			int8_t classEP0RxReady() override;
			int8_t classSOF() override;
			int8_t classDataIn(uint8_t epnum) override;
			int8_t classDataOut(uint8_t epnum) override;
			int8_t classIsoINIncomplete(uint8_t epnum) override;
			int8_t classIsoOUTIncomplete(uint8_t epnum) override;
			bool classGetDeviceQualifierDescriptor(uint8_t *&data, unsigned &length) override;

			bool usesEndPoint(uint8_t epAddr) const override;
	};
}


#endif // __eosUSBDeviceClassHID__
