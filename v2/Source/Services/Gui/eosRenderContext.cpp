#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/eosVisual.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosTransformation.h"


using namespace eos;


///-----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
/// \param graphics: L'objecte 'Graphics' per dibuixar.
//
RenderContext::RenderContext(
	Graphics *graphics):

	graphics(graphics) {

	eosAssert(graphics != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief Inicia el renderitzat.
/// \param visual: El visual a renderitzar.
/// \return L'objecte 'Graphics' per dibuixar.
///
Graphics *RenderContext::beginRender(
	Visual *visual) {

	eosAssert(visual != nullptr);
	eosAssert(graphics != nullptr);

	int x, y;
	visual->getAbsolutePosition(x, y);

	Transformation t;
	t.translate(x, y);
	graphics->setTransformation(t);

	graphics->setClip(0, 0, visual->getWidth() - 1, visual->getHeight() - 1);

	return graphics;
}


/// ----------------------------------------------------------------------
/// \brief Finalitza el renderitzat.
///
void RenderContext::endRender() {

	graphics->resetClip();
	graphics->resetTransformation();
}
