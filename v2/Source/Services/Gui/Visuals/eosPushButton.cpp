#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosGuiMessageQueue.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosButtons.h"
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
/// \param newState: El nou estat.
///
void PushButton::setState(
	PushButtonState newState) {

	if (state != newState) {
		state = newState;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant cal Renderitzar el visual.
/// \param context: El context de renderitzat.
///
void PushButton::onRender(
	RenderContext &context) {

	Graphics &g = context.beginRender(this);

	const Size &s = getSize();
	Color c1(COLOR_Red);
	Color c2(COLOR_Green);

	g.setColor(state == PushButtonState::normal ? c1 : c2);
	g.fillRectangle(getRect());

	g.setColor(state == PushButtonState::normal ? c2 : c1);
	g.setTextAlign(HorizontalTextAlign::center, VerticalTextAlign::middle);
	g.drawText(s.getWidth() / 2, s.getHeight() / 2, "Boton", 0, -1);

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
