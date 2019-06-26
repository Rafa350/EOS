#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/eosVisual.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


///-----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
/// \param[in] graphics: L'objecte 'Graphics' per dibuixar.
//
RenderContext::RenderContext(
	Graphics *graphics):

	graphics(graphics),
	offsetX(0),
	offsetY(0) {

	eosAssert(graphics != nullptr);

}


/// ----------------------------------------------------------------------
/// \brief Inicia el renderitzat.
/// \param[in] visual: El visual a renderitzar.
///
void RenderContext::beginRender(
	Visual *visual) {

	eosAssert(visual != nullptr);
	eosAssert(graphics != nullptr);

	visual->getAbsolutePosition(offsetX, offsetY);

	graphics->setClip(
		offsetX,
		offsetY,
		offsetX + visual->getWidth() - 1,
		offsetY + visual->getHeight() - 1);
}


/// ----------------------------------------------------------------------
/// \brief Finalitza el renderitzat.
///
void RenderContext::endRender() {

	offsetX = 0;
	offsetY = 0;

	graphics->resetClip();
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un rectangle ple.
/// \param[in] x: Coordinada X de la posicio.
/// \param[in] y: Coordinada Y de la posicio.
/// \param[in] width: Amplada.
/// \param[in] height: Alçada.
/// \param[in] color: Color.
///
void RenderContext::fillRectangle(
	int x,
	int y,
	int width,
	int height,
	const Color &color) {

	graphics->setColor(color);
	graphics->fillRectangle(
		offsetX + x,
		offsetY + y,
		offsetX + x + width - 1,
		offsetY + y + height - 1);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un rectangle ple.
/// \param[in] x: Coordinada X de la posicio.
/// \param[in] y: Coordinada Y de la posicio.
/// \param[in] width: Amplada.
/// \param[in] height: Alçada.
/// \param[in] color: Color.
///
void RenderContext::drawRectangle(
	int x,
	int y,
	int width,
	int height,
	const Color &color) {

	graphics->setColor(color);
	graphics->drawRectangle(
		offsetX + x,
		offsetY + y,
		offsetX + x + width - 1,
		offsetY + y + height - 1);
}

