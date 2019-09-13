#include "eos.h"
#include "Services/Gui/eosGuiMessageQueue.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosLabel.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"
#include "string.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
///
Label::Label():

	textColor(COLOR_White),
	backgroundColor(COLOR_Transparent),
	horizontalTextAlign(HorizontalTextAlign::center),
	verticalTextAlign(VerticalTextAlign::middle),
	text(0) {

}


/// ----------------------------------------------------------------------
/// \brief Asigna el color del text.
/// \param color: El color.
///
void Label::setTextColor(
	const Color &color) {

	if (textColor != color) {
		textColor = color;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el color del fons.
/// \param color: El color.
///
void Label::setBackgroundColor(
	const Color &color) {

	if (backgroundColor != color) {
		backgroundColor = color;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna l'aliniacio horitzontal del text.
/// \param align: L'aliniacio.
///
void Label::setHorizontalTextAlign(
	HorizontalTextAlign align) {

	if (horizontalTextAlign != align) {
		horizontalTextAlign = align;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna l'aliniacio vertical del text.
/// \param align: L'aliniacio.
///
void Label::setVerticalTextAlign(
	VerticalTextAlign align) {

	if (verticalTextAlign != align) {
		verticalTextAlign = align;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el text.
/// \param text: El text.
///
void Label::setText(
	const char *text) {

	if (strcmp(this->text, text) != 0) {
		this->text = text;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Renderitza la imatge.
/// \param context: Context de renderitzat.
///
void Label::onRender(
	RenderContext &context) {

	Graphics &g = context.beginRender(this);

	const Size &s = getSize();

	g.setColor(backgroundColor);
	g.fillRectangle(getRect());

	g.setColor(textColor);
	g.setTextAlign(horizontalTextAlign, verticalTextAlign);
	g.drawText(s.getWidth() / 2, s.getHeight() / 2, text, 0, -1);

	context.endRender();
}
