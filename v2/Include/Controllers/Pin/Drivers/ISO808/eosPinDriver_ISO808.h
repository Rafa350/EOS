#pragma once
#ifndef __eosPinDriver_ISO808__
#define __eosPinDriver_ISO808__


// EOS includes
//
#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"


namespace eos {
    
    class Device_ISO808;

    class PinDriver_ISO808 final: public PinDriver {
		private:
			Device_ISO808 * const _dev;
			uint8_t const _pinMask;

		public:
			PinDriver_ISO808(Device_ISO808 *dev, uint8_t pinNumber);
			void set() override;
			void clear() override;
			void toggle() override;
			void write(bool pinState) override;
			bool read() override;
    };

}


#endif // __eosPinDriver_ISO808__
