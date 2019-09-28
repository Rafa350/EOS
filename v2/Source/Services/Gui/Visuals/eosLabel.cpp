#include "eos.h"
#include "Services/Gui/eosGuiMessageQueue.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosLabel.h"
#include "Services/Gui/eosVisual.h"
#include "System/Core/eosString.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


struct LabelStyle {
	Color textColor;
	Color backgroundColor;
	String fontName;
};

static const LabelStyle style = {
	.textColor = COLOR_Yellow,
	.backgroundColor = COLOR_Gray,
	.fontName = "Tahoma"
};

static const LabelStyle *pStyle = &style;


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
///
Label::Label():

	textColor(pStyle->textColor),
	backgroundColor(pStyle->backgroundColor),
	horizontalTextAlign(HorizontalTextAlign::center),
	verticalTextAlign(VerticalTextAlign::center),
	fontName(pStyle->fontName),
	fontHeight(12),
	fontStyle(FontStyle::regular),
	text(String("")) {

	setHorizontalAlignment(HorizontalAlignment::center);
	setVerticalAlignment(VerticalAlignment::center);
}


/// ----------------------------------------------------------------------
/// \brief Calcula la mida desitjada del visual.
/// \param availableSize: Tamany disponible.
///
Size Label::measureOverride(
	const Size &availableSize) const {

	if (text.isEmpty())

		return Size();

	else {

		const uint8_t *fontResource =  Font::getFontResource(fontName, fontHeight, fontStyle);
		Font *font = new Font(fontResource);

		int measuredWidth = 0;
		for (int i = 0; text[i]; i++)
			measuredWidth += font->getCharAdvance(text[i]);
		int measuredHeight = font->getFontHeight();

		delete font;

		return Size(measuredWidth, measuredHeight);
	}
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
/// \brief Asigna el nom del font.
/// \param fontname: El nom del font.
///
void Label::setFontName(
	const String &fontName) {

	if (this->fontName != fontName) {
		this->fontName = fontName;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el tamany del font.
/// \param fontname: El tamany del font.
///
void Label::setFontHeight(
	int fontHeight) {

	if (this->fontHeight != fontHeight) {
		this->fontHeight = fontHeight;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna L'estil del font.
/// \param fontname: L'estil del font.
///
void Label::setFontStyle(
	FontStyle fontStyle) {

	if (this->fontStyle != fontStyle) {
		this->fontStyle = fontStyle;
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

	// Inicia el renderitzat
	//
	Graphics &g = context.beginRender(this);

	// Obte les mides de l'area de dibuix
	//
	const Size &s = getBounds().getSize();
	int width = s.getWidth();
	int height = s.getHeight();

	// Dibuixa el fons
	//
	g.setColor(backgroundColor);
	g.fillRectangle(0, 0, width, height);

	// Dibuixa el text
	//
	const uint8_t *fontResource =  Font::getFontResource(fontName, fontHeight, fontStyle);
	Font *font = new Font(fontResource);
	g.setFont(font);
	g.setColor(textColor);
	g.setTextAlign(horizontalTextAlign, verticalTextAlign);
	g.drawText(width / 2, height / 2, text, 0, -1);
	delete font;

	// Finalitza el renderitzat.
	//
	context.endRender();
}
