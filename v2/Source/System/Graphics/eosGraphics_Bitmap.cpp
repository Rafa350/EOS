#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "System/Graphics/eosBitmap.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un bitmap complert.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \param    bitmap: El bitmap
///
void Graphics::drawBitmap(
    int x,
    int y,
    const Bitmap *pBitmap) const {

	int x1 = x;
	int y1 = y;
	int x2 = x + pBitmap->getWidth() - 1;
	int y2 = y + pBitmap->getHeight() - 1;

	if (clipRectangle(x1, y1, x2, y2)) {

        int w = x2 - x1 + 1;
        int h = y2 - y1 + 1;

        if ((w > 0) && (h > 0))
			driver->writePixels(
				x1, y1,
				w, h,
				pBitmap->getPixels(),
				pBitmap->getFormat(),
				x1 - x, y1 - y,
				x1 - x);
	}
}
