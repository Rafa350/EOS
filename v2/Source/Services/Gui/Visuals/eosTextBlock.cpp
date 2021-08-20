#include "eos.h"
#include "Services/Gui/eosMsgQueue.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/eosVisual.h"
#include "Services/Gui/Visuals/eosTextBlock.h"
#include "System/eosString.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosFont.h"
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
	.foregroundColor = COLOR_Black,
	.backgroundColor = COLOR_Yellow,
	.fontName = "Tahoma",
	.fontHeight = 12,
	.fontStyle = FontStyle::regular
};

static const TextBlockStyle *pStyle = &style;


/// ----------------------------------------------------------------------
/// \brief    Contructor de l'objecte.
///
TextBlock::TextBlock():

	_foreground(Brush(BrushStyle::solid, pStyle->foregroundColor)),
	_font(Font(String(pStyle->fontName), pStyle->fontHeight, pStyle->fontStyle)),
	_horizontalTextAlign(HorizontalTextAlign::center),
	_verticalTextAlign(VerticalTextAlign::center) {

	setHorizontalAlignment(HorizontalAlignment::center);
	setVerticalAlignment(VerticalAlignment::center);
}


/// ----------------------------------------------------------------------
/// \brief    Calcula la mida desitjada del visual.
/// \param    availableSize: Tamany disponible.
///
Size TextBlock::measureOverride(
	const Size& availableSize) const {

	if (_text.isEmpty())

		return Size();

	else {

		int measuredWidth = 0;
		for (int i = 0; _text[i]; i++)
			measuredWidth += _font.getCharAdvance(_text[i]);
		int measuredHeight = _font.getFontHeight();

		return Size(measuredWidth, measuredHeight);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el font.
/// \param    value: El font.
///
void TextBlock::setFont(
	const Font& value) {

	if (_font != value) {
		_font = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la brotxa del primer pla.
/// \param    value: La brotxa.
///
void TextBlock::setForeground(
	const Brush& value) {

	if (_foreground != value) {
		_foreground = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'aliniacio horitzontal del text.
/// \param    value: L'aliniacio.
///
void TextBlock::setHorizontalTextAlign(
	HorizontalTextAlign value) {

	if (_horizontalTextAlign != value) {
		_horizontalTextAlign = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'aliniacio vertical del text.
/// \param    value: L'aliniacio.
///
void TextBlock::setVerticalTextAlign(
	VerticalTextAlign value) {

	if (_verticalTextAlign != value) {
		_verticalTextAlign = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el text.
/// \param    value: El text.
///
void TextBlock::setText(
	const String& value) {

	if (_text != value) {
		_text = value;
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
	Graphics &g = context->beginRender(this);

	// Obte les mides de l'area de dibuix
	//
	const Size &s = getBounds().getSize();
	int width = s.getWidth();
	int height = s.getHeight();

	// Dibuixa el fons.
	//
	g.paintRectangle(Pen(), getBackground(), Rect(0, 0, width, height));

	// Dibuixa el text
	//
	g.setFont(_font);
	g.setTextAlign(_horizontalTextAlign, _verticalTextAlign);
	g.drawText(width / 2, height / 2, _foreground.getColor(), _text, 0, -1);

	// Finalitza el renderitzat.
	//
	context->endRender();
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant hi ha que despatxar un missatge..
/// \param    msg: El missatge a despatxar.
///
#if eosGuiService_TouchPadEnabled
void TextBlock::onDispatch(
	const Message& msg) {

	// Si es un missatge del touchpad, el retransmet al pare
	//
	if (msg.msgId == MsgId::touchPadEvent) {
		Visual *pParent = getParent();
		if (pParent != nullptr)
			pParent->dispatch(msg);
	}

	// En cas contrari els procesa normalment
	//
	else
		Visual::onDispatch(msg);
}
#endif
