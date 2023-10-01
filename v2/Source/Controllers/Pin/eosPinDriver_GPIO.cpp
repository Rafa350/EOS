#include "eos.h"
#include "Controllers/Pin/eosPinDriver_GPIO.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    pin: Handler del pin.
///
PinDriver_GPIO::PinDriver_GPIO(
	htl::gpio::PinHandler hPin):
	_hPin {hPin} {

}


/// ----------------------------------------------------------------------
/// \brief    Posa el pin a estat set.
///
void PinDriver_GPIO::set() {

	_hPin->set();
}


/// ----------------------------------------------------------------------
/// \brief    Posa el pin a estat clear
///
void PinDriver_GPIO::clear() {

	_hPin->clear();
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat del pin
///
void PinDriver_GPIO::toggle() {

	_hPin->toggle();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu l'estat del pin.
/// \param    state: L'estat///
void PinDriver_GPIO::write(
	bool pinState) {

	_hPin->write(pinState);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix l'eatat del pin.
/// \return   L'estat
///
bool PinDriver_GPIO::read() const {

	return _hPin->read();
}
