#pragma once
#ifndef __eosDevice_RGB__
#define __eosDevice_RGB__


#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "HTL/htlGPIO.h"


namespace eos {

    class Device_RGB {
        public:
            using Pin = htl::gpio::PinDevice;

        private:
            Pin const *_pinLCDE;
            Pin const *_pinBKLE;

        public:
            void initialize(Pin *pinLCDE, Pin *pinBKLE);
            void deinitialize();

            void hardwareReset();

            void enable();
            void disable();
    };

}


#endif // __eosDevice_RGB__

