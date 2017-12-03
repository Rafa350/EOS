#include "Controllers/TouchPad/eosTouchPad.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
/// \param driver: El driver del touchpad.
///
TouchPad::TouchPad(
	ITouchPadDriver *driver):

	driver(driver) {

}


/// ----------------------------------------------------------------------
/// \brief Obte l'estat del touchpad.
/// \param state: Buffer on deixar les dades.
/// \return True si hi han dades.
///
bool TouchPad::getState(
	TouchPadState &state) {

	return driver->getState(state);
}
