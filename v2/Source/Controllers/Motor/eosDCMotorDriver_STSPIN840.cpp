#include "eos.h"
#include "Controllers/Motor/eosDCMotorDriver_STSPIN840.h"


using namespace eos;


DCMotorDriver_STSPIN840::DCMotorDriver_STSPIN840(
	STSPIN840_Device *dev):

	_dev {dev} {

}


void DCMotorDriver_STSPIN840::implForward(
	unsigned speed) {

}


void DCMotorDriver_STSPIN840::implBackward(
	unsigned speed) {

}


void DCMotorDriver_STSPIN840::implStop() {

}
