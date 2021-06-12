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
	textColor(COLOR_Red) {

	text = "Hola capullo.";
}


void TextBox::setText(
	const String &text) {

	if (this->text != text) {
		this->text = text;
		invalidate();
	}
}


void TextBox::clearText() {

	if (!text.isEmpty()) {
		text = "";
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

	const int radius = 5;
	const Size &s = getBounds().getSize();
	int x2 = s.getWidth() - 1;
	int y2 = s.getHeight() - 1;

	Graphics &g = context->beginRender(this);

	g.fillRoundedRectangle(0, 0, x2, y2, radius, radius, COLOR_DarkSeaGreen);

	g.setTextAlign(HorizontalTextAlign::left, VerticalTextAlign::center);
	g.drawText(0, y2 / 2, textColor, text, 0, -1);

	context->endRender();
}
