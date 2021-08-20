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


/// ----------------------------------------------------------------------
/// \brief    Borra el text.
///
void TextBox::clearText() {

	setText("");
	_visiblePos = 0;
	_insertPos = 0;
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

	String text = getText();

	switch (ch) {
		default:
			if (ch >= 0x30 && ch < 0x7F) {
				text.insert(_insertPos++, ch);
				if (_insertPos > _visiblePos + _visibleLength)
					_visiblePos++;
			}
			break;
	}

	setText(text);
}


/// ----------------------------------------------------------------------
/// \brief    Renderitza la imatge del visual.
/// \param    contet: Context de renderitzat.
///
void TextBox::onRender(
	RenderContext* context) {

	TextBlock::onRender(context);
}
