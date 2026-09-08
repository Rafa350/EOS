module;


#include "eos.h"
#include "HTL/htlGPIO.h"


export module Eos.Controllers.Pin.GPIO;


export import Eos.Controllers.Pin;


export namespace eos {

	class PinDriver_GPIO final: public PinDriver {
        private:
            htl::gpio::PinDevice * const _pin;

        public:
            PinDriver_GPIO(htl::gpio::PinDevice *pin);

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


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    pin: El pin.
///
eos::PinDriver_GPIO::PinDriver_GPIO(
	htl::gpio::PinDevice *pin):

	_pin {pin} {

}


/// ----------------------------------------------------------------------
/// \brief    Posa el pin a estat set.
///
void eos::PinDriver_GPIO::set() {

	_pin->set();
}


/// ----------------------------------------------------------------------
/// \brief    Posa el pin a estat clear
///
void eos::PinDriver_GPIO::clear() {

	_pin->clear();
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat del pin
///
void eos::PinDriver_GPIO::toggle() {

	_pin->toggle();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu l'estat del pin.
/// \param    state: L'estat///
void eos::PinDriver_GPIO::write(
	bool pinState) {

	_pin->write(pinState);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix l'eatat del pin.
/// \return   L'estat
///
bool eos::PinDriver_GPIO::read() {

	return _pin->read();
}
