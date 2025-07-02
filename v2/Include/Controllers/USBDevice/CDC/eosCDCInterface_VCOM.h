#pragma once
#ifndef __eosCDCInterface_VCOM__
#define __eosCDCInterfece_VCOM__


#include "Controllers/USBDevice/CDC/eosUSBDeviceClassCDC.h"


namespace eos {

	class CDCInterface_VCOM: public CDCInterface {
		public:
			int8_t initialize(USBDeviceClassCDC *cdc) override;
			int8_t deinitialize(USBDeviceClassCDC *cdc) override;

			int8_t control(ControlCmd cc, uint8_t *data, uint16_t dataSize) override;

			int8_t rxDataAvailable(uint8_t *data, uint32_t *length) override;
			int8_t txDataCompleted(uint8_t *data, uint32_t *length, uint8_t epnum) override;
	};

}


#endif // __eosCDCInterface_VCOM__

