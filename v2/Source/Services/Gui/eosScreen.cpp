#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/eosScreen.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
///
Screen::Screen() {

	setPosition(Point(0, 0));
	setSize(Size(DISPLAY_IMAGE_WIDTH, DISPLAY_IMAGE_HEIGHT));
}


/// ----------------------------------------------------------------------
/// \brief Asigna el color.
/// \param color: El color.
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
/// \param context: El context de renderitzat.
///
void Screen::onRender(
	RenderContext *context) {

	Graphics *g = context->beginRender(this);

	Rect r = getRect();

	g->setColor(color);
	g->fillRectangle(r);

	context->endRender();
}
