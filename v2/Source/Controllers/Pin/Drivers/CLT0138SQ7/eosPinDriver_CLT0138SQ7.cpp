#include "eos.h"
#include "Controllers/Pin/Drivers/CLT0138SQ7/eosPinDriver_CLT0138SQ7.h"
#include "Controllers/Pin/Drivers/CLT0138SQ7/eosDevice_CLT0138SQ7.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    hDevice: Handler del dispositiu CTL0138SQ7
/// \param    pinNumber: El numero de pin.
///
PinDriver_CLT0138SQ7::PinDriver_CLT0138SQ7(
	Device_CLT0138SQ7 *dev,
	unsigned pinNumber):

	_dev {dev},
	_pinMask {uint8_t(1 << pinNumber)} {

}


void PinDriver_CLT0138SQ7::set() {

}


void PinDriver_CLT0138SQ7::clear() {

}


void PinDriver_CLT0138SQ7::toggle() {

}


void PinDriver_CLT0138SQ7::write(
	bool state) {

}


bool PinDriver_CLT0138SQ7::read() {

	return (_dev->read() & _pinMask) != 0;
}
