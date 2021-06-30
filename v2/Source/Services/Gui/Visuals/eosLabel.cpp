#include "eos.h"
#include "Services/Gui/eosMsgQueue.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/eosVisual.h"
#include "Services/Gui/Visuals/eosLabel.h"
#include "System/eosString.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


struct LabelStyle {
	Color textColor;
	Color backgroundColor;
	const char *fontName;
	int fontHeight;
	FontStyle fontStyle;
};

static const LabelStyle style = {
	.textColor = COLOR_Yellow,
	.backgroundColor = COLOR_Transparent,
	.fontName = "Tahoma",
	.fontHeight = 12,
	.fontStyle = FontStyle::regular
};

static const LabelStyle *pStyle = &style;


/// ----------------------------------------------------------------------
/// \brief    Contructor de l'objecte.
///
Label::Label():

	_textColor(pStyle->textColor),
	_backgroundColor(pStyle->backgroundColor),
	_horizontalTextAlign(HorizontalTextAlign::center),
	_verticalTextAlign(VerticalTextAlign::center),
	_fontName(pStyle->fontName),
	_fontHeight(pStyle->fontHeight),
	_fontStyle(pStyle->fontStyle) {

	setHorizontalAlignment(HorizontalAlignment::center);
	setVerticalAlignment(VerticalAlignment::center);
}


/// ----------------------------------------------------------------------
/// \brief    Calcula la mida desitjada del visual.
/// \param    availableSize: Tamany disponible.
///
Size Label::measureOverride(
	const Size &availableSize) const {

	if (_text.isEmpty())

		return Size();

	else {

		const uint8_t *fontResource =  Font::getFontResource(_fontName, _fontHeight, _fontStyle);
		Font font(fontResource);

		int measuredWidth = 0;
		for (unsigned i = 0; _text[i]; i++)
			measuredWidth += font.getCharAdvance(_text[i]);
		int measuredHeight = font.getFontHeight();

		return Size(measuredWidth, measuredHeight);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el color del text.
/// \param    value: El color.
///
void Label::setTextColor(
	Color value) {

	if (_textColor != value) {
		_textColor = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el nom del font.
/// \param    value: El nom del font.
///
void Label::setFontName(
	const String &value) {

	if (_fontName != value) {
		_fontName = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el tamany del font.
/// \param    value: El tamany del font.
///
void Label::setFontHeight(
	int value) {

	if (_fontHeight != value) {
		_fontHeight = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna L'estil del font.
/// \param    value: L'estil del font.
///
void Label::setFontStyle(
	FontStyle value) {

	if (_fontStyle != value) {
		_fontStyle = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el color del fons.
/// \param    value: El color.
///
void Label::setBackgroundColor(
	Color value) {

	if (_backgroundColor != value) {
		_backgroundColor = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'aliniacio horitzontal del text.
/// \param    value: L'aliniacio.
///
void Label::setHorizontalTextAlign(
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
void Label::setVerticalTextAlign(
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
void Label::setText(
	const String &value) {

	if (_text != value) {
		_text = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Renderitza la imatge.
/// \param    context: Context de renderitzat.
///
void Label::onRender(
	RenderContext *context) {

	// Inicia el renderitzat
	//
	Graphics &g = context->beginRender(this);

	// Obte les mides de l'area de dibuix
	//
	const Size &s = getBounds().getSize();
	int width = s.getWidth();
	int height = s.getHeight();

	// Dibuixa el fons. Si es transparent optimitza i no el dibuixa.
	//
	if (!_backgroundColor.isTransparent())
		g.fillRectangle(0, 0, width, height, _backgroundColor);

	// Dibuixa el text
	//
	const uint8_t *fontResource = Font::getFontResource(_fontName, _fontHeight, _fontStyle);
	Font font(fontResource);

	g.setFont(font);
	g.setTextAlign(_horizontalTextAlign, _verticalTextAlign);
	g.drawText(width / 2, height / 2, _textColor, _text, 0, -1);

	// Finalitza el renderitzat.
	//
	context->endRender();
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant hi ha que despatxar un missatge..
/// \param    msg: El missatge a despatxar.
///
#if eosGuiService_TouchPadEnabled
void Label::onDispatch(
	const Message &msg) {

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
