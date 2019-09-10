#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosGuiMessageQueue.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosCheckButton.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
///
CheckButton::CheckButton():
	state(CheckButtonState::unchecked) {

}


/// ----------------------------------------------------------------------
/// \brief Canvia l'estat del boto.
/// \param newState: El nou estat.
///
void CheckButton::setState(
	CheckButtonState newState) {

	if (state != newState) {
		state = newState;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant cal Renderitzar el visual.
/// \param context: El context de renderitzat.
///
void CheckButton::onRender(
	RenderContext &context) {

	const int r = 5;

	Graphics &g = context.beginRender(this);

	g.setColor(Color::fromRGB888(0x3A3A3A));
	g.fillRoundedRectangle(getRect(), r, r);

	switch (state) {
		case CheckButtonState::unchecked:
			g.setColor(COLOR_DarkSlateGray);
			g.fillRoundedRectangle(Point(5, 5), Size(20, 20), r, r);
			g.setColor(COLOR_LightSeaGreen);
			g.drawRoundedRectangle(Point(5, 5), Size(20, 20), r, r);
			break;

		case CheckButtonState::checked:
			break;

		default:
			break;
	}

	context.endRender();
}
