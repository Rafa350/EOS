#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosScreen.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
///
Screen::Screen() {

	setPosition(Point(0, 0));
	setSize(Size(DISPLAY_IMAGE_WIDTH, DISPLAY_IMAGE_HEIGHT));
}


void Screen::onRender(RenderContext &context) {

	Graphics &g = context.beginRender(this);
	g.setColor(COLOR_Yellow);
	g.drawRectangle(10, 135, 110, 237);
	g.setColor(COLOR_Gray);
	g.fillRoundedRectangle(10, 135, 110, 237, 25, 25);
	g.setColor(COLOR_Red);
	g.drawRoundedRectangle(10, 135, 110, 237, 25, 25);
	context.endRender();
}
