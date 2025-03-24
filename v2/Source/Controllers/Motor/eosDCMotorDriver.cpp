#include "eos.h"
#include "Controllers/Motor/eosDCMotorDriver.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Arranca el motor cap endevant.
/// \param    speed: Percentatge de la velocitat maxima. (0..100)
///
void DCMotorDriver::forward(
	unsigned speed) {

	implForward(speed);
}


/// ----------------------------------------------------------------------
/// \brief    Arranca el motor cap enrere
/// \param    speed: Percentatge de la velocitat maxima. (0..100)
///
void DCMotorDriver::backward(
	unsigned speed) {

	implBackward(speed);
}


/// ----------------------------------------------------------------------
/// \brief    Atura el motor.
///
void DCMotorDriver::stop() {

	implStop();
}
