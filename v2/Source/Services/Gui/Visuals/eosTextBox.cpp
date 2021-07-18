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
	_visiblePos(0),
	_visibleLength(10),
	_insertPos(0) {
}


/// ---------------------------------------------------------------------
/// \brief    Asigna el text
/// \param    text: El text.
///
void TextBox::setText(
	const String& value) {

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
		_visiblePos = 0;
		_insertPos = 0;
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
	KeyFlags flags,
	char ch) {

	switch (ch) {
		default:
			if (ch >= 0x30 && ch < 0x7F) {
				_text.insert(_insertPos++, ch);
				if (_insertPos > _visiblePos + _visibleLength)
					_visiblePos++;
				invalidate();
			}
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Renderitza la imatge del visual.
/// \param    contet: Context de renderitzat.
///
void TextBox::onRender(
	RenderContext* context) {

	const Size s(getBounds().getSize());

	Graphics& g = context->beginRender(this);

	g.paintRectangle(Pen(), getBackground(), Rect(s));

	g.setTextAlign(HorizontalTextAlign::left, VerticalTextAlign::center);
	g.drawText(0, s.getHeight() / 2, getForeground().getColor(),
		_text, _visiblePos, _visibleLength);

	context->endRender();
}
