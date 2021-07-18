#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/eosVisual.h"
#include "Services/Gui/eosVisualUtils.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosTransformation.h"


using namespace eos;


///-----------------------------------------------------------------------
/// \brief    Contructor de l'objecte.
/// \param    graphics: L'objecte 'Graphics' per dibuixar.
//
RenderContext::RenderContext(
	Graphics* graphics):

	_graphics(graphics) {

	eosAssert(graphics != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el renderitzat.
/// \param    visual: El visual a renderitzar.
/// \return   L'objecte 'Graphics' per dibuixar.
///
Graphics& RenderContext::beginRender(
	Visual* visual) {

	eosAssert(visual != nullptr);

	// Selecciona el rectangle de retall
	//
	_graphics->setClip(VisualUtils::getClip(visual));

	// Aplica una translacio per situar l'origen de coordinades, al origen
	// del widged
	//
	Transformation t;
	t.translate(VisualUtils::getPosition(visual));
	_graphics->setTransformation(t);
	//_graphics->push();

	return *_graphics;
}


/// ----------------------------------------------------------------------
/// \brief Finalitza el renderitzat.
///
void RenderContext::endRender() {

	//_graphics->pop();
}
