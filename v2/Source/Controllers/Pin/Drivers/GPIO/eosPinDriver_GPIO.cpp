#include "eos.h"
#include "Controllers/Pin/Drivers/GPIO/eosPinDriver_GPIO.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    pin: El pin.
///
PinDriver_GPIO::PinDriver_GPIO(
	htl::gpio::Pin *pin):

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
