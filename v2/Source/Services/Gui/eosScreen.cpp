#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosScreen.h"
#include "System/Graphics/eosDisplay.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Asigna el color.
/// \param[in] color: El color.
///
void Screen::setColor(
	const Color &color) {

	if (this->color != color) {
		this->color = color;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Renderitza el visual.
/// \param[in] display: El display on dibuixar.
///
void Screen::onRender(
	Display *display) {

	display->clear(color);
}
