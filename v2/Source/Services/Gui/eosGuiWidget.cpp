#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosGuiVisuals.h"
#include "System/Graphics/eosDisplay.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Asigna el color del perfil.
/// \param[in] color: El color.
///
void Widget::setBorderColor(
	const Color &color) {

	borderColor = color;
}


void Widget::onRender(
	Display *display) {

	display->setColor(borderColor);
	display->fillRectangle(
		getX(),
		getY(),
		getX() + getWidth(),
		getY() + getHeight());
}
