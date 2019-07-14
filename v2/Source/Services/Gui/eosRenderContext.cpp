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

	// Selecciona el rectangle de retall
	//
	graphics->setClip(getClip(visual));

	// Aplica una translacio per situar l'origen de coordinades, al origen
	// del widged
	//
	Transformation t;
	t.translate(getPosition(visual));
	graphics->setTransformation(t);

	return graphics;
}


/// ----------------------------------------------------------------------
/// \brief Finalitza el renderitzat.
///
void RenderContext::endRender() {

}


/// ----------------------------------------------------------------------
/// \brief La posicio d'un element visual.
/// \param visual: L'element visual.
/// \return La posicio.
///
Point RenderContext::getPosition(
	Visual *visual) const {

	eosAssert(visual != nullptr);

	Point p;
	for (Visual *v = visual; v != nullptr; v = v->getParent())
		p = p.offset(v->getPosition());

	return p;
}


/// ----------------------------------------------------------------------
/// \brief Obte el rectangle de retall d'un element visual.
/// \param visual: L'element visual.
/// \return El rectangle de retall.
///
Rect RenderContext::getClip(
	Visual *visual) const {

	eosAssert(visual != nullptr);

	Rect clip(0, 0, INT32_MAX, INT32_MAX);
	for (Visual *v = visual; v != nullptr; v = v->getParent()) {
		Rect r(getPosition(v), v->getSize());
		clip = clip.intersect(r);
	}

	return clip;
}
