#pragma once


// EOS includes
//
#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "HTL/htlGPIO.h"


namespace eos {

    /// \brief Clase que implementa del driver del pin amb acces directe a GPIO
    ///
    class PinDriver_GPIO final: public PinDriver {
        private:
            htl::gpio::Pin * const _pin;
        public:
            PinDriver_GPIO(htl::gpio::Pin *pin);
            void set() override;
            void clear() override;
            void toggle() override;
            void write(bool state) override;
            bool read() override;
    };
    
}
