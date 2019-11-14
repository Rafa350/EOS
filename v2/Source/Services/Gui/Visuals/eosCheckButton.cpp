#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosCheckButton.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
CheckButton::CheckButton():
	state(State::unchecked) {

}


/// ----------------------------------------------------------------------
/// \brief    Canvia l'estat del boto.
/// \param    value: El nou estat.
///
void CheckButton::setState(
	State value) {

	if (state != value) {
		state = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant cal Renderitzar el visual.
/// \param    context: El context de renderitzat.
///
void CheckButton::onRender(
	RenderContext *context) {

	// Inicia el renderitzat.
	//
	Graphics &g = context->beginRender(this);

	// Obte les mides de l'area de dibuix
	///
	const int radius = 5;
	const Size &s = getBounds().getSize();
	int x2 = s.getWidth() - 1;
	int y2 = s.getHeight() - 1;

	// Dibuixa el fons del boto
	//
	g.setColor(Color::fromRGB888(0x3A3A3A));
	g.fillRoundedRectangle(0, 0, x2, y2, radius, radius);

	// Dibuixa el fons del indicador
	//
	if (isPressed()) {
		g.setColor(COLOR_DarkSlateGray);
		g.fillRoundedRectangle(Point(5, 5), Size(20, 20), radius, radius);
	}

	// Dibuixa el indicador
	//
	if (state ==  State::unchecked) {
		g.setColor(COLOR_LightSeaGreen);
		g.drawRoundedRectangle(Point(5, 5), Size(20, 20), radius, radius);
	}
	else if (state == State::checked) {
		g.setColor(COLOR_LightSeaGreen);
		g.drawRoundedRectangle(Point(5, 5), Size(20, 20), radius, radius);
		g.fillRoundedRectangle(Point(10, 10), Size(10, 10), radius / 2, radius / 2);
	}

	// Finalitza el renderitzat.
	///
	context->endRender();
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant es fal click en el boto.
///
void CheckButton::onClick() {

	switch (state) {
		case State::unchecked:
			setState(State::checked);
			break;

		case State::checked:
			setState(State::unchecked);
			break;

		default:
			break;
	}

	ButtonBase::onClick();
}

