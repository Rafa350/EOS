#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosCheckButton.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


// TODO: Millorar la maquina d'estats del boto per evitar release
// abans que push.


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
	CheckButtonState state) {

	if (this->state != state) {
		this->state = state;
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
	if (isPressed()) {
		g.setColor(COLOR_DarkSlateGray);
		g.fillRoundedRectangle(Point(5, 5), Size(20, 20), r, r);
	}

	// Dibuixa el indicador
	//
	if (state ==  CheckButtonState::unchecked) {
		g.setColor(COLOR_LightSeaGreen);
		g.drawRoundedRectangle(Point(5, 5), Size(20, 20), r, r);
	}
	else if (state == CheckButtonState::checked) {
		g.setColor(COLOR_LightSeaGreen);
		g.drawRoundedRectangle(Point(5, 5), Size(20, 20), r, r);
		g.fillRoundedRectangle(Point(10, 10), Size(10, 10), r/2, r/2);
	}

	context.endRender();
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant es fal click en el boto.
///
void CheckButton::onClick() {

	switch (state) {
		case CheckButtonState::unchecked:
			setState(CheckButtonState::checked);
			break;

		case CheckButtonState::checked:
			setState(CheckButtonState::unchecked);
			break;

		default:
			break;
	}

	ButtonBase::onClick();
}

