#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosImage.h"
#include "System/Graphics/eosBitmap.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor de la imatge.
///
Image::Image() :
	pBitmap(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief Asigna un bitmap a la imatge.
/// \param newBitmap: El nou bitmap.
///
void Image::setBitmap(
	Bitmap *newBitmap) {

	if (pBitmap != newBitmap){
		pBitmap = newBitmap;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Renderitza la imatge.
/// \param context: El context de renderitzat.
///
void Image::onRender(
	RenderContext &context) {

	Graphics &g = context.beginRender(this);

	g.drawBitmap(
		getPosition(),
		pBitmap);

	context.endRender();
}
