#include "Controllers/TouchPad/eosTouchPad.h"


using namespace eos;


TouchPad::TouchPad(
	ITouchPadDriver *driver):

	driver(driver) {

}


void TouchPad::queryState(
	const TouchPadState &state) {

	driver->queryState();
}
