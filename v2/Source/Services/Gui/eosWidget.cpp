#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/eosWidged.h"
#include "System/Graphics/eosGraphics.h"


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
/// \brief Asigna l'amplada del marc.
/// \param[in] thickness: Amplada del marc.
///
void Widget::setBorderThickness(
	int thickness) {

	if (borderThickness != thickness) {
		borderThickness = thickness;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el color del fons.
/// \param[in] color: El color.
///
void Widget::setBackgroundColor(
	const Color &color) {

	if (backgroundColor != color) {
		backgroundColor = color;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Renderitzat per defecte del widget.
/// \param[in] graphics: El display.
///
void Widget::onRender(
	RenderContext *context) {

	context->beginRender(this);
	context->fillRectangle(0, 0, getWidth(), getHeight(), backgroundColor);
	context->drawRectangle(0, 0, getWidth(), getHeight(), borderColor);
	context->endRender();
}
