#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosPushButton.h"
#include "System/Core/eosString.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
///
PushButton::PushButton():
	state(PushButtonState::normal) {

}


/// ----------------------------------------------------------------------
/// \brief Canvia l'estat del boto.
/// \param state: El nou estat.
///
void PushButton::setState(
	PushButtonState state) {

	if (this->state != state) {
		this->state = state;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant cal Renderitzar el visual.
/// \param context: El context de renderitzat.
///
void PushButton::onRender(
	RenderContext &context) {

	const int radius = 5;
	Rect rect = getRect();

	Graphics &g = context.beginRender(this);

	switch (state) {
		case PushButtonState::normal:
			g.setColor(Color::fromRGB888(0x3A3A3A));
			g.fillRoundedRectangle(rect, radius, radius);
			g.setColor(COLOR_LightSeaGreen);
			g.drawRoundedRectangle(rect, rarius, radius);
			break;

		case PushButtonState::pushed:
			g.setColor(COLOR_DarkSlateGray);
			g.fillRoundedRectangle(rect, radius, radius);
			g.setColor(COLOR_LightSeaGreen);
			g.drawRoundedRectangle(rect, radius, radius);
			break;

		default:
			break;
	}

	context.endRender();
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant es prem el boto.
///
void PushButton::onPress() {

	setState(PushButtonState::pushed);

	ButtonBase::onPress();
}


/// ----------------------------------------------------------------------
/// \brief Es crida quanrt es deixa anar el boto.
///
void PushButton::onRelease() {

	setState(PushButtonState::normal);

	ButtonBase::onRelease();
}
