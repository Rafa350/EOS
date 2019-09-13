#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosPanel.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
///
Panel::Panel() :
	color(COLOR_Blue) {

}


/// ----------------------------------------------------------------------
/// \brief Assigna el color.
/// \param color: El color.
///
void Panel::setColor(
	const Color &color) {

	if (this->color != color) {
		this->color = color;
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
