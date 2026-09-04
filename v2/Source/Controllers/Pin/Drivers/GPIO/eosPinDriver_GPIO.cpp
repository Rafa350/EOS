#include "eos.h"
#include "Controllers/Pin/Drivers/GPIO/eosPinDriver_GPIO.h"


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
