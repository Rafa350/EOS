#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosScreen.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosSize.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
///
Screen::Screen() {

	setPosition(Point(0, 0));
	setSize(Size(DISPLAY_IMAGE_WIDTH, DISPLAY_IMAGE_HEIGHT));
}
