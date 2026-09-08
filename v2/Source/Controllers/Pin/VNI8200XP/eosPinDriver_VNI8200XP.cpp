#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Pin/Drivers/VNI8200XP/eosPinDriver_VNI8200XP.h"
#include "Controllers/Pin/Drivers/VNI8200XP/eosDevice_VNI8200XP.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Construtor del objecte.
/// \param    dev: El dispositiu
/// \param    pinNumber: El numero del pin.
///
PinDriver_VNI8200XP::PinDriver_VNI8200XP(
	Device_VNI8200XP *dev,
	unsigned pinNumber):

	_dev {dev},
	_pinMask {uint8_t(1 << pinNumber)} {

	eosAssert(dev != nullptr);
	eosAssert(pinNumber < 8);
}


/// ----------------------------------------------------------------------
/// \brief    Canvia l'estat de la sortida a ON.
///
void PinDriver_VNI8200XP::set() {

	_dev->set(_pinMask);
}


/// ----------------------------------------------------------------------
/// \brief    Canvia l'estat de la sortida a OFF.
///
void PinDriver_VNI8200XP::clear() {

	_dev->clear(_pinMask);
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat de la sortida.
///
void PinDriver_VNI8200XP::toggle() {

	_dev->toggle(_pinMask);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu l'estat de la sortida.
/// \param    pinState: L'estat a escriure.
///
void PinDriver_VNI8200XP::write(
	bool pinState) {

	_dev->write(_pinMask, pinState);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix l'estat de la sortida.
/// ºreturn   L'estat de la sortida ON/OFF
bool PinDriver_VNI8200XP::read() {

	return (_dev->read() & _pinMask) != 0;
}

