#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/eosVisual.h"
#include "Services/Gui/eosVisualUtils.h"
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
	graphics.setClip(VisualUtils::getClip(pVisual));

	// Aplica una translacio per situar l'origen de coordinades, al origen
	// del widged
	//
	Transformation t;
	t.translate(VisualUtils::getPosition(pVisual));
	graphics.setTransformation(t);

	return graphics;
}


/// ----------------------------------------------------------------------
/// \brief Finalitza el renderitzat.
///
void RenderContext::endRender() {

}
