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
Panel::Panel() {

}


/// ----------------------------------------------------------------------
/// \brief    Assigna la brotxa de fons.
/// \param    value: La brotxa.
///
void Panel::setBackground(
	const Brush &value) {

	if (_background != value) {
		_background = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Renderitza el visual.
/// \param    context: El context de renderitzat.
//
void Panel::onRender(
	RenderContext *context) {

	if (!_background.isNull()) {

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
		g.paintRectangle(Pen(), _background, Rect(0, 0, width, height));

		// Finalitza el renderitzat.
		//
		context->endRender();
	}
}
