#include "eos.h"
#include "Controllers/Motor/eosDCMotorDriver.h"


using namespace eos;


void DCMotorDriver::forward(
	unsigned speed) {

	implForward(speed);
}


void DCMotorDriver::backward(
	unsigned speed) {

	implBackward(speed);
}


void DCMotorDriver::stop() {

	implStop();
}
