#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "System/Graphics/eosBitmap.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un bitmap.
/// \param    position: Posicio del bitmap.
/// \param    bitmap: El bitmap.
///
void Graphics::paintBitmap(
	const Point &position,
	const Bitmap &bitmap) const {

	//bitmap.draw(this, position);

	drawBitmap(position.getX(), position.getY(), bitmap);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un bitmap complert.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \param    bitmap: El bitmap
///
void Graphics::drawBitmap(
    int16_t x,
    int16_t y,
    const Bitmap &bitmap) const {

	int16_t x1 = x;
	int16_t y1 = y;
	int16_t x2 = x + bitmap.getWidth() - 1;
	int16_t y2 = y + bitmap.getHeight() - 1;

	if (clipRectangle(x1, y1, x2, y2)) {

        int16_t w = x2 - x1 + 1;
        int16_t h = y2 - y1 + 1;

        if ((w > 0) && (h > 0)) {
        	_driver->setPixels(
        		x1, y1,
				w, h,
        		bitmap.getPixels(),
				bitmap.getFormat(),
				bitmap.getWidth());
        }
	}
}
