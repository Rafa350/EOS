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

	setPosition(0, 0);
	setSize(DISPLAY_IMAGE_WIDTH, DISPLAY_IMAGE_HEIGHT);
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

	int x1 = 0;
	int y1 = 0;
	int x2 = getWidth() - 1;
	int y2 = getHeight() - 1;

	g->setColor(color);
	g->fillRectangle(x1, y1, x2, y2);

	context->endRender();
}
