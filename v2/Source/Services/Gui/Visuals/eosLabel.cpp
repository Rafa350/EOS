#include "eos.h"
#include "Services/Gui/eosGuiMessageQueue.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosLabel.h"
#include "System/Core/eosString.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
///
Label::Label():

	textColor(COLOR_White),
	backgroundColor(COLOR_Transparent),
	horizontalTextAlign(HorizontalTextAlign::center),
	verticalTextAlign(VerticalTextAlign::middle),
	textFont(nullptr),
	text() {

}


/// ----------------------------------------------------------------------
/// \brief Calcula la mida desitjada del visual.
/// \param availableSize: Tamany disponible.
///
Size Label::measureOverride(
	const Size &availableSize) const {

	if ((textFont != nullptr) && !text.isEmpty()) {
		int width = 0;
		for (int i = 0; text[i]; i++)
			width += textFont->getCharAdvance(text[i]);

		int height = textFont->getFontHeight();

		return Size(width, height);
	}
	else
		return Size(0, 0);
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
/// \brief Asigna al font del text.
/// \param font: El font.
///
void Label::setTextFont(
	Font *textFont) {

	if (this->textFont != textFont) {
		this->textFont = textFont;
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
	const String &text) {

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

	g.setColor(backgroundColor);
	g.fillRectangle(getRect());

	g.setColor(textColor);
	g.setTextAlign(horizontalTextAlign, verticalTextAlign);
	if (textFont != nullptr)
		g.setFont(textFont);
	g.drawText(s.getWidth() / 2, s.getHeight() / 2, text, 0, -1);

	context.endRender();
}
