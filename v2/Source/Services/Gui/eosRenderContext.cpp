#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/eosVisual.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosRect.h"
#include "System/Graphics/eosSize.h"
#include "System/Graphics/eosTransformation.h"


using namespace eos;


///-----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
/// \param graphics: L'objecte 'Graphics' per dibuixar.
//
RenderContext::RenderContext(
	Graphics &graphics):

	graphics(graphics) {
}


/// ----------------------------------------------------------------------
/// \brief Inicia el renderitzat.
/// \param pVisual: El visual a renderitzar.
/// \return L'objecte 'Graphics' per dibuixar.
///
Graphics &RenderContext::beginRender(
	Visual *pVisual) {

	eosAssert(pVisual != nullptr);

	// Selecciona el rectangle de retall
	//
	graphics.setClip(getClip(pVisual));

	// Aplica una translacio per situar l'origen de coordinades, al origen
	// del widged
	//
	Transformation t;
	t.translate(pVisual->getAbsolutePosition());
	graphics.setTransformation(t);

	return graphics;
}


/// ----------------------------------------------------------------------
/// \brief Finalitza el renderitzat.
///
void RenderContext::endRender() {

}


/// ----------------------------------------------------------------------
/// \brief Obte el rectangle de retall d'un element visual.
/// \param visual: L'element visual.
/// \return El rectangle de retall.
///
Rect RenderContext::getClip(
	Visual *pVisual) const {

	eosAssert(pVisual != nullptr);

	Rect clip(0, 0, INT32_MAX, INT32_MAX);
	for (Visual *v = pVisual; v != nullptr; v = v->getParent()) {
		Rect r(v->getAbsolutePosition(), v->getSize());
		clip = clip.intersect(r);
	}

	return clip;
}
