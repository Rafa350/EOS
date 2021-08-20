#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosPanel.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosBrush.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
Panel::Panel() {
}


/// ----------------------------------------------------------------------
/// \brief    Renderitza el panell.
/// \param    context: El context de renderitzat.
//
void Panel::onRender(
	RenderContext* context) {

	const Brush& bkBrush = getBackground();

	if (!bkBrush.isNull()) {

		// Inicia el renderitzat.
		//
		Graphics& g = context->beginRender(this);

		// Obte les mides de l'area de dibuix.
		//
		const Size& s = getBounds().getSize();
		int width = s.getWidth();
		int height = s.getHeight();

		// Dibuixa el fons.
		//
		g.paintRectangle(Pen(), bkBrush, Rect(0, 0, width, height));

		// Finalitza el renderitzat.
		//
		context->endRender();
	}
}
