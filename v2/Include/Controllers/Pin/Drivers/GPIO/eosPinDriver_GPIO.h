#pragma once
#ifndef __eosPinDriver_GPIO__
#define __eosPinDriver_GPIO__


// EOS includes
//
#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "HTL/htlGPIO.h"


namespace eos {

    /// \brief Clase que implementa del driver del pin amb acces directe a GPIO
    ///
    class PinDriver_GPIO final: public PinDriver {
        public:
            using Pin = htl::gpio::PinDevice;

        private:
            const Pin * const _pin;

        public:
            PinDriver_GPIO(Pin *pin);
            void set() override;
            void clear() override;
            void toggle() override;
            void write(bool state) override;
            bool read() override;
    };


    /// \brief Clase que implementa el driver del pin
    ///
    template <typename pin_>
    class PinDriverX_GPIO final: public PinDriver {
        public:
            void set() override {
                pin_::set();
            }

            void clear() override {
                pin_::clear();
            }

            void toggle() override {
                pin_::toggle();
            }

            void write(bool state) override {
                pin_::write(state);
            }

            bool read() override {
                return pin_::read();
            }
    };
    
}


#endif // __eosPinDriver_GPIO__
