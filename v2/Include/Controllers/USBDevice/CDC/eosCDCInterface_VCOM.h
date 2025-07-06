#pragma once
#ifndef __eosCDCInterface_VCOM__
#define __eosCDCInterfece_VCOM__


#include "Controllers/USBDevice/CDC/eosUSBDeviceClassCDC.h"


namespace eos {

	class CDCInterface_VCOM: public CDCInterface {
		private:
			CDCLineCoding _lineCoding;

		private:
			void setLineCoding(uint8_t *data, unsigned dataSize);
			void getLineCoding(uint8_t *data, unsigned dataSize);

		public:
			int8_t initialize(USBDeviceClassCDC *cdc) override;
			int8_t deinitialize(USBDeviceClassCDC *cdc) override;

			int8_t control(CDCRequestID requestID, uint8_t *data, unsigned dataSize) override;

			void rxDataAvailable(const uint8_t *buffer, unsigned length) override;
			void txDataCompleted(const uint8_t *buffer, unsigned length, uint8_t epnum) override;
	};

}


#endif // __eosCDCInterface_VCOM__

