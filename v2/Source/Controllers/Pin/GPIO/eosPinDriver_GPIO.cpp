module;


#include "eos.h"


export module Eos.Controllers.Pin.GPIO;


export import Eos.Controllers.Pin;

import Eos.Hardware.GPIO;


export namespace eos {

	class PinDriver_GPIO final: public PinDriver {
        private:
            eos::hardware::gpio::PinDevice * const _pin;

        public:
            PinDriver_GPIO(eos::hardware::gpio::PinDevice *pin);

            void set() override;
            void clear() override;
            void toggle() override;
            void write(bool state) override;
            bool read() override;
    };


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


using namespace eos;
using namespace eos::hardware::gpio;


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    pin: El pin.
///
PinDriver_GPIO::PinDriver_GPIO(
	PinDevice *pin):

	_pin {pin} {

}


/// ----------------------------------------------------------------------
/// \brief    Posa el pin a estat set.
///
void PinDriver_GPIO::set() {

	_pin->set();
}


/// ----------------------------------------------------------------------
/// \brief    Posa el pin a estat clear
///
void PinDriver_GPIO::clear() {

	_pin->clear();
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat del pin
///
void PinDriver_GPIO::toggle() {

	_pin->toggle();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu l'estat del pin.
/// \param    state: L'estat///
void PinDriver_GPIO::write(
	bool pinState) {

	_pin->write(pinState);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix l'eatat del pin.
/// \return   L'estat
///
bool PinDriver_GPIO::read() {

	return _pin->read();
}
