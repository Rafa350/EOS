#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosImage.h"
#include "System/Graphics/eosBitmap.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


Image::Image() :
	pBitmap(nullptr) {

}


void Image::setBitmap(
	Bitmap *newBitmap) {

	if (pBitmap != newBitmap){
		pBitmap = newBitmap;
		invalidate();
	}
}


void Image::onRender(
	RenderContext &context) {

}
