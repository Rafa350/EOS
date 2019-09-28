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

		// Inicia el renderitzat.
		//
		Graphics &g = context.beginRender(this);

		// Obte les mides de l'area de dibuix.
		//
		const Size &s = getBounds().getSize();
		int width = s.getWidth();
		int height = s.getHeight();

		// Dibuixa el fons.
		//
		g.setColor(color);
		g.fillRectangle(0, 0, width, height);

		// Finalitza el renderitzat.
		//
		context.endRender();
	}
}
