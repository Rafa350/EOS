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

	Graphics *g = context->beginRender(this);

	int x1 = 0;
	int y1 = 0;
	int x2 = getWidth() - 1;
	int y2 = getHeight() - 1;

	g->setColor(backgroundColor);
	g->fillRectangle(x1, y1, x2, y2);

	g->setColor(borderColor);
	g->drawRectangle(x1, y1, x2, y2);

	context->endRender();
}
