#pragma once
#ifndef __eosPinDriver_CLT0138SQ7__
#define __eosPinDriver_CLT0138SQ7__


#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"


namespace eos {
    
    class Device_CLT0138SQ7;

    class PinDriver_CLT0138SQ7 final: public PinDriver {
    	private:
    		Device_CLT0138SQ7 * const _dev;
    		uint8_t const _pinMask;

    	public:
    		PinDriver_CLT0138SQ7(Device_CLT0138SQ7 *dev, uint8_t pinNumber);
            void set() override;
            void clear() override;
            void toggle() override;
            void write(bool state) override;
            bool read() override;
    };
}


#endif // __eosPinDriver_CLT0138SQ7__
