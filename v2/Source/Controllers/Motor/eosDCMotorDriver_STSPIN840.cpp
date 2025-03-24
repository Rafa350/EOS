#include "eos.h"
#include "Controllers/Motor/eosDCMotorDriver_STSPIN840.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    dev: El dispositiu
///
DCMotorDriver_STSPIN840::DCMotorDriver_STSPIN840(
	STSPIN840_Device *dev):

	_dev {dev} {

}


/// ----------------------------------------------------------------------
/// \brief    Arranca el motor cap endevant.
/// \param    speed: Percentatge de la velocitat maxima. (0..100)
///
void DCMotorDriver_STSPIN840::implForward(
	unsigned speed) {

	_dev->setDirection(eos::STSPIN840_Device::Direction::forward);
	_dev->enable();
	_dev->pwmStart(speed);
}


/// ----------------------------------------------------------------------
/// \brief    Arranca el motor cap enrere
/// \param    speed: Percentatge de la velocitat maxima. (0..100)
///
void DCMotorDriver_STSPIN840::implBackward(
	unsigned speed) {

	_dev->setDirection(eos::STSPIN840_Device::Direction::backward);
	_dev->enable();
	_dev->pwmStart(speed);
}


/// ----------------------------------------------------------------------
/// \brief    Atura el motor.
///
void DCMotorDriver_STSPIN840::implStop() {

	_dev->pwmStop();
	_dev->disable();
}
