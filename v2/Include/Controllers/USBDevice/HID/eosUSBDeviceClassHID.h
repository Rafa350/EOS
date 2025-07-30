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

			int8_t classSetup(USBD_SetupReqTypedef *req);// override;
			int8_t classEP0TxSent() override;
			int8_t classEP0RxReady() override;
			int8_t classSOF() override;
			int8_t classDataIn(EpAddr epAddr) override;
			int8_t classDataOut(EpAddr epAddr) override;
			int8_t classIsoINIncomplete(EpAddr epAddr) override;
			int8_t classIsoOUTIncomplete(EpAddr epAddr) override;

			bool usesEndPoint(EpAddr epAddr) const override;
	};
}


#endif // __eosUSBDeviceClassHID__
