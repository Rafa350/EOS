#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosPanel.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
Panel::Panel() :
	color(COLOR_Blue) {

}


/// ----------------------------------------------------------------------
/// \brief    Assigna el color.
/// \param    value: El color.
///
void Panel::setColor(
	const Color &value) {

	if (color != value) {
		color = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Renderitza el visual.
/// \param    context: El context de renderitzat.
//
void Panel::onRender(
	RenderContext *context) {

	if (!color.isTransparent()) {

		// Inicia el renderitzat.
		//
		Graphics &g = context->beginRender(this);

		// Obte les mides de l'area de dibuix.
		//
		const Size &s = getBounds().getSize();
		int width = s.getWidth();
		int height = s.getHeight();

		// Dibuixa el fons.
		//
		g.fillRectangle(0, 0, width, height, color);

		// Finalitza el renderitzat.
		//
		context->endRender();
	}
}
