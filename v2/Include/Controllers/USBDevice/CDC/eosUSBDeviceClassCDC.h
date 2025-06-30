#pragma once
#ifndef __eosUSBDeviceClassCDC__
#define __eosUSBDeviceClassCDC__


#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"
#include "Controllers/USBDevice/CDC/ST/st_usbd_cdc.h"


namespace eos {

	class CDCInterface {
		public:
			virtual int8_t initialize() = 0;
			virtual int8_t deinitialize() = 0;

			virtual int8_t control(uint8_t cmd, uint8_t *data, uint16_t dataSize) = 0;

			virtual int8_t rxDataAvailable(uint8_t *data, uint32_t *length) = 0;
			virtual int8_t txDataCompleted(uint8_t *data, uint32_t *length, uint8_t epnum) = 0;
	};

	class USBDeviceClassCDC: public USBDeviceClass {
		private:
			CDCInterface *_interface;

		public:
			USBDeviceClassCDC(USBDeviceDriver *drvUSBD, CDCInterface *interface);

			void initialize();
	};
}


#endif // __eosUSBDeviceClassCDC__
