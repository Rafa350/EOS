#include "eos.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosLabel.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
///
Label::Label():

	color(COLOR_White),
	horizontalTextAlign(HorizontalTextAlign::center),
	verticalTextAlign(VerticalTextAlign::middle),
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
/// \param color: L'aliniacio.
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
	RenderContext &context) {

	Graphics &g = context.beginRender(this);

	const Size &s = getSize();

	g.setColor(color);
	g.setTextAlign(horizontalTextAlign, verticalTextAlign);
	g.drawText(s.getWidth() / 2, s.getHeight() / 2, text, 0, -1);

	context.endRender();
}
