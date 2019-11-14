#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosPushButton.h"
#include "System/eosString.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
PushButton::PushButton():
	state(State::normal) {
}


/// ----------------------------------------------------------------------
/// \brief    Canvia l'estat del boto.
/// \param    value: El nou estat.
///
void PushButton::setState(
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
void PushButton::onRender(
	RenderContext *context) {

	// Inicia el renderitzat.
	//
	Graphics &g = context->beginRender(this);

	// Obte les mides de l'area de dibuix
	//
	const int radius = 5;
	const Size &s = getBounds().getSize();
	int x2 = s.getWidth() - 1;
	int y2 = s.getHeight() - 1;

	// Dibuixa el boto
	//
	switch (state) {
		case State::normal:
			g.setColor(COLOR_Teal);
			g.fillRoundedRectangle(0, 0, x2, y2, radius, radius);
			g.setColor(COLOR_LightSeaGreen);
			g.drawRoundedRectangle(0, 0, x2, y2, radius, radius);
			break;

		case State::pushed:
			g.setColor(COLOR_CadetBlue);
			g.fillRoundedRectangle(0, 0, x2, y2, radius, radius);
			g.setColor(COLOR_LightCyan);
			g.drawRoundedRectangle(0, 0, x2, y2, radius, radius);
			break;

		default:
			break;
	}

	// Finalitza el renderitzat.
	//
	context->endRender();
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant es prem el boto.
///
void PushButton::onPress() {

	setState(State::pushed);

	ButtonBase::onPress();
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quanrt es deixa anar el boto.
///
void PushButton::onRelease() {

	setState(State::normal);

	ButtonBase::onRelease();
}
