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
/// \brief    Asigna la brotxa del primer pla.
/// \param    value: La brotxa.
///
void TextBlock::setForeground(
	const Brush& value) {

	if (_ft.getForeground() != value) {
		_ft.setForeground(value);
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
	g.paintText(Point(0, 0), _ft);

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
