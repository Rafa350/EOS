#include "eos.h"
#include "Services/Gui/eosLabel.h"
#include "Services/Gui/eosRenderContext.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
///
Label::Label():

	color(COLOR_White),
	text(0) {

}


/// ----------------------------------------------------------------------
/// \brief Asigna el color del text.
/// \param color: El color.
///
void Label::setColor(
	const Color &color) {

	if (this->color != color) {
		this->color = color;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el text.
/// \param text: El text.
///
void Label::setText(
	const char *text) {

	if (this->text != text) {
		this->text = text;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Renderitza la imatge.
/// \param context: Context de renderitzat.
///
void Label::onRender(
	RenderContext *context) {

	Graphics *graphics = context->beginRender(this);

	graphics->setColor(color);
	graphics->drawText(0, 0, text, 0, -1);

	context->endRender();
}
