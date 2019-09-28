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


/// ----------------------------------------------------------------------
/// \brief Converteix un punt a coordinades de pantalla.
/// \param    pVisual: El visual.
/// \param    p: El punt en coordinades relatives al visual.
/// \return   El punt en coordinades absolutes de pantalla.
///
static Point PointToScreen(
	Visual *pVisual,
	const Point& p) {

	int x = 0;
	int y = 0;

	while (pVisual != nullptr) {
		const Rect& bounds = pVisual->getBounds();
		x += bounds.getX();
		y += bounds.getY();

		pVisual = pVisual->getParent();
	}

	return Point(x, y);
}


/// ----------------------------------------------------------------------
/// \brief Converteix un rectangle a coordinades de pantalla.
/// \param    pVisual: El visual.
/// \param    p: El rectangle en coordinades relatives al visual.
/// \return   El rectangle en coordinades absolutes de pantalla.
///
static Rect PointToScreen(
	Visual *pVisual,
	const Rect& r) {

	return Rect(PointToScreen(pVisual, r.getPosition()), r.getSize());
}


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
	t.translate(PointToScreen(pVisual, pVisual->getBounds().getPosition()));
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
	/*for (Visual *v = pVisual; v != nullptr; v = v->getParent()) {
		Rect r(v->getAbsolutePosition(), v->getSize());
		clip = clip.intersect(r);
	}*/

	return clip;
}
