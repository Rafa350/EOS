#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/eosScreen.h"
#include "System/Graphics/eosColor.h"


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
/// \param[in] context: El context de renderitzat.
///
void Screen::onRender(
	RenderContext *context) {

	context->beginRender(this);
	context->fillRectangle(0, 0, getWidth(), getHeight(), color);
	context->endRender();
}
