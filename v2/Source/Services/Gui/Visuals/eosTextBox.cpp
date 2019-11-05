#include "eos.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosTextBox.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/graphics/eosGraphics.h"



using namespace eos;


TextBox::TextBox() {

}


void TextBox::onRender(
	 RenderContext *context) {

	const int radius = 5;
	const Size &s = getBounds().getSize();
	int x2 = s.getWidth() - 1;
	int y2 = s.getHeight() - 1;

	Graphics &g = context->beginRender(this);

	g.setColor(COLOR_DarkSeaGreen);
	g.fillRoundedRectangle(0, 0, x2, y2, radius, radius);

	context->endRender();
}
