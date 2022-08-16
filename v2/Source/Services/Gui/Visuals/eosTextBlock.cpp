#include "eos.h"
#include "Services/Gui/eosMsgQueue.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/eosVisual.h"
#include "Services/Gui/Visuals/eosTextBlock.h"
#include "System/eosString.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosText.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


struct TextBlockStyle {
	Color foregroundColor;
    Color backgroundColor;
	const char *fontName;
	int fontHeight;
	FontStyle fontStyle;
};

static const TextBlockStyle style = {
	.foregroundColor = Colors::black,
	.backgroundColor = Colors::yellow,
	.fontName = "Consolas",
	.fontHeight = 18,
	.fontStyle = FontStyle::regular
};

static const TextBlockStyle *pStyle = &style;


/// ----------------------------------------------------------------------
/// \brief    Contructor de l'objecte.
///
TextBlock::TextBlock():

	_ft(Font(String(pStyle->fontName), pStyle->fontHeight, pStyle->fontStyle), TextAlign::center) {

	setHorizontalAlignment(HorizontalAlignment::center);
	setVerticalAlignment(VerticalAlignment::center);
}


/// ----------------------------------------------------------------------
/// \brief    Calcula la mida desitjada del visual.
/// \param    availableSize: Tamany disponible.
///
Size TextBlock::measureOverride(
	const Size& availableSize) const {

	return _ft.getBounds();
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el font.
/// \param    value: El font.
///
void TextBlock::setFont(
	const Font& value) {

	if (_ft.getFont() != value)
		_ft.setFont(value);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la brotxa del primer pla del font.
/// \param    value: La brotxa.
///
void TextBlock::setTextForeground(
	const Brush& value) {

	if (_ft.getForeground() != value) {
		_ft.setForeground(value);
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la brotxa del font del font.
/// \param    value: La brotxa.
///
void TextBlock::setTextBackground(
	const Brush& value) {

	if (_ft.getBackground() != value) {
		_ft.setBackground(value);
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'aliniacio horitzontal del text.
/// \param    value: L'aliniacio.
///
void TextBlock::setTextAlign(
	TextAlign value) {

	if (_ft.getAlign() != value) {
		_ft.setAlign(value);
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el text.
/// \param    value: El text.
///
void TextBlock::setText(
	const String& value) {

	if (_ft.getText() != value) {
		_ft.setText(value);
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Renderitza la imatge.
/// \param    context: Context de renderitzat.
///
void TextBlock::onRender(
	RenderContext *context) {

	// Inicia el renderitzat
	//
	Graphics& g = context->beginRender(this);

	// Dibuixa el fons.
	//
	g.paintRectangle(Pen(), getBackground(), Rect(getBounds().getSize()));

	// Dibuixa el text
	//
	int x = 0;
	int y = 0;
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wswitch"
	#pragma GCC diagnostic ignored "-Wswitch-default"
	switch (getVerticalAlignment()) {
		case VerticalAlignment::center:
			y = (getBounds().getHeight() - _ft.getBounds().getHeight()) / 2;
			break;

		case VerticalAlignment::bottom:
			y = getBounds().getHeight() - _ft.getBounds().getHeight();
			break;
	}
	#pragma GCC diagnostic pop
	g.paintText(Point(x, y), _ft);

	// Finalitza el renderitzat.
	//
	context->endRender();
}
