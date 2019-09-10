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

	// Dibuixa el fons del boto
	//
	g.setColor(Color::fromRGB888(0x3A3A3A));
	g.fillRoundedRectangle(getRect(), r, r);

	// Dibuixa el fons del indicador
	//
	if (state == CheckButtonState::checkedPressed ||
		state == CheckButtonState::uncheckedPressed) {
		g.setColor(COLOR_DarkSlateGray);
		g.fillRoundedRectangle(Point(5, 5), Size(20, 20), r, r);
	}

	// Dibuixa el indicador
	//
	if (state ==  CheckButtonState::unchecked ||
		state == CheckButtonState::uncheckedPressed) {
		g.setColor(COLOR_LightSeaGreen);
		g.drawRoundedRectangle(Point(5, 5), Size(20, 20), r, r);
	}
	else if (state == CheckButtonState::checked ||
		     state == CheckButtonState::checkedPressed) {
		g.setColor(COLOR_LightSeaGreen);
		g.drawRoundedRectangle(Point(5, 5), Size(20, 20), r, r);
		g.fillRoundedRectangle(Point(10, 10), Size(10, 10), r/2, r/2);
	}

	context.endRender();
}


void CheckButton::onClick() {

	switch (state) {
		case CheckButtonState::unchecked:
		case CheckButtonState::uncheckedPressed:
			setState(CheckButtonState::checked);
			break;

		case CheckButtonState::checked:
		case CheckButtonState::checkedPressed:
			setState(CheckButtonState::unchecked);
			break;

		default:
			break;
	}
}


void CheckButton::onPress() {

	setState(state == CheckButtonState::checked ? CheckButtonState::checkedPressed : CheckButtonState::uncheckedPressed);
}


void CheckButton::onRelease() {

	setState(state == CheckButtonState::checkedPressed ? CheckButtonState::checked : CheckButtonState::unchecked);
}

