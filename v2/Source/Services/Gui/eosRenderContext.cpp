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
static Point getPosition(
	Visual *pVisual) {

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
/// \brief    Obte el rectangle de retall d'un visual.
/// \param    pVisual: El visual.
/// \return   El rectangle de retall.
///
static Rect getClip(
	Visual *pVisual) {

	Rect clip(0, 0, INT32_MAX, INT32_MAX);
	while (pVisual != nullptr) {
		Rect bounds(pVisual->getBounds());
		clip = clip.intersect(bounds.getSize());
		clip = clip.offset(bounds.getPosition());
		pVisual = pVisual->getParent();
	}

	return clip;
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
	t.translate(getPosition(pVisual));
	graphics.setTransformation(t);

	return graphics;
}


/// ----------------------------------------------------------------------
/// \brief Finalitza el renderitzat.
///
void RenderContext::endRender() {

}
