#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosWidged.h"
#include "System/Graphics/eosDisplay.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Asigna el color del perfil.
/// \param[in] color: El color.
///
void Widget::setBorderColor(
	const Color &color) {

	if (borderColor != color) {
		borderColor = color;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Renderitzat per defecte del widget.
/// \param[in]: El display.
///
void Widget::onRender(
	Display *display) {

	display->setColor(borderColor);
	display->fillRectangle(
		getX(),
		getY(),
		getX() + getWidth() - 1,
		getY() + getHeight() - 1);
}
