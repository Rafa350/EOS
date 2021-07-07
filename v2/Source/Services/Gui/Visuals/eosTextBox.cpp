#include "eos.h"
#include "Services/Gui/eosMsgQueue.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosTextBox.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"



using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
TextBox::TextBox():
	_textColor(COLOR_Red) {
}


/// ---------------------------------------------------------------------
/// \brief    Asigna el text
/// \param    text: El text.
///
void TextBox::setText(
	const String &value) {

	if (_text != value) {
		_text = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Borra el text.
///
void TextBox::clearText() {

	if (!_text.isEmpty()) {
		_text = "";
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \bried    Asigna el color del text.
/// \param    value: El color.
///
void TextBox::setTextColor(
	Color value) {

	if (_textColor != value) {
		_textColor = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant cal procesar un missatge.
/// \param    keyCode: El codi de la tecla
/// \param    ch: El caracter de la tecla.
///
void TextBox::onKeyboardPress(
	KeyCode keyCode,
	char ch) {
}


/// ----------------------------------------------------------------------
/// \brief    Renderitza la imatge del visual.
/// \param    contet: Context de renderitzaqt.
///
void TextBox::onRender(
	RenderContext *context) {

	const Size &s = getBounds().getSize();
	int x2 = s.getWidth() - 1;
	int y2 = s.getHeight() - 1;

	Graphics &g = context->beginRender(this);

	g.fillRectangle(0, 0, x2, y2, getBackground().getColor());

	g.setTextAlign(HorizontalTextAlign::left, VerticalTextAlign::center);
	g.drawText(0, y2 / 2, _textColor, _text, 0, -1);

	context->endRender();
}
