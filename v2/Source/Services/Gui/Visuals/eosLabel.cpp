#include "eos.h"
#include "Services/Gui/eosGuiMessageQueue.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosLabel.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosGraphics.h"
#include "string.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
///
Label::Label():

	color(COLOR_White),
	backgroundColor(COLOR_Transparent),
	horizontalTextAlign(HorizontalTextAlign::center),
	verticalTextAlign(VerticalTextAlign::middle),
	text(0) {

}


/// ----------------------------------------------------------------------
/// \brief Asigna el color del text.
/// \param newColor: El color.
///
void Label::setColor(
	const Color &newColor) {

	if (color != newColor) {
		color = newColor;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna l'aliniacio horitzontal del text.
/// \param newAlign: L'aliniacio.
///
void Label::setHorizontalTextAlign(
	HorizontalTextAlign newAlign) {

	if (horizontalTextAlign != newAlign) {
		horizontalTextAlign = newAlign;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna l'aliniacio vertical del text.
/// \param newAlign: L'aliniacio.
///
void Label::setVerticalTextAlign(
	VerticalTextAlign newAlign) {

	if (verticalTextAlign != newAlign) {
		verticalTextAlign = newAlign;
		invalidate();
	}
}



/// ----------------------------------------------------------------------
/// \brief Asigna el text.
/// \param newText: El text.
///
void Label::setText(
	const char *newText) {

	if (strcmp(text, newText) != 0) {
		text = newText;
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

	g.setColor(color);
	g.setTextAlign(horizontalTextAlign, verticalTextAlign);
	g.drawText(s.getWidth() / 2, s.getHeight() / 2, text, 0, -1);

	context.endRender();
}


void Label::onDispatch(
	const Message &msg) {

	switch (msg.msgId) {
		case MsgId::touchPadEvent:
			setText("caca");
			break;

		default:
			Visual::onDispatch(msg);
			break;
	}
}
