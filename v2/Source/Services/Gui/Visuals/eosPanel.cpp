#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosPanel.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
///
Panel::Panel() :
	color(COLOR_Blue) {

}


void Panel::initializePanel() {

}


/// ----------------------------------------------------------------------
/// \brief Assigna el color.
/// \param newColor: El color.
///
void Panel::setColor(
	const Color &newColor) {

	if (color != newColor) {
		color = newColor;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Renderitza el visual.
/// \param context: El context de renderitzat.
//
void Panel::onRender(
	RenderContext &context) {

	if (color.getA() > 0) {
		Graphics &g = context.beginRender(this);
		g.setColor(color);
		g.fillRectangle(getRect());
		context.endRender();
	}
}
