#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un rectangle amb les cantonades arrodonides.
/// \param    x1: Coordinada x del primer punt.
/// \param    y1: Coordinada y del primer punt.
/// \param    x2: Coordinada x del segon punt.
/// \param    y2: Coordinada y del segon punt.
/// \param    rx: Radi x de les cantonades.
/// \param    ry: Radi y de les cantonades.
///
void Graphics::drawRoundedRectangle(
	int x1,
	int y1,
	int x2,
	int y2,
	int rx,
	int ry) const {

	// Transforma a coordinades fisiques
	//
	state.ct.apply(x1, y1);
	state.ct.apply(x2, y2);

	// Normalitza les coordinades
	//
	if (x1 > x2)
		Math::swap(x1, x2);
	if (y1 > y2)
		Math::swap(y1, y2);

	// Obte el centre
	//
	int cx = (x1 + x2) / 2;
	int cy = (y1 + y2) / 2;

	// Precalcula els factors constants
	//
	int aa = 2 * rx * rx;
	int bb = 2 * ry * ry;
	int sx = (x2 - x1 - rx - rx) / 2;
	int sy = (y2 - y1 - ry - ry) / 2;

	int x, y, error;
	int changeX, changeY;
	int stoppingX, stoppingY;

	// Genera el primer grup de punts
	//
	x = rx;
	y = 0;
	changeX = ry * ry * (1 - (rx * 2));
	changeY = rx * rx;
	error = 0;
	stoppingX = bb * rx;
	stoppingY = 0;

	while (stoppingX >= stoppingY) {

		int xx, yy;

		xx = cx + x + sx;
		yy = cy + y + sy;
		if (clipPoint(xx, yy))
			driver->setPixel(xx, yy, color);

	    xx = cx - x - sx;
	    yy = cy + y + sy;
		if (clipPoint(xx, yy))
			driver->setPixel(xx, yy, color);

		xx = cx - x - sx;
		yy = cy - y - sy;
		if (clipPoint(xx, yy))
			driver->setPixel(xx, yy, color);

		xx = cx + x + sx;
		yy = cy - y - sy;
		if (clipPoint(xx, yy))
			driver->setPixel(xx, yy, color);

		y += 1;
		stoppingY += aa;
		error += changeY;
		changeY += aa;
	    if ((2 * error + changeX) > 0 ) {
	    	x -= 1;
	    	stoppingX -= bb;
	    	error += changeX;
	    	changeX += bb;
	    }
	}

	// Genera el segon grup de punts
	//
	x = 0;
	y = ry;
	changeX = ry * ry;
	changeY = rx * rx * (1 - (2 * ry));
	error = 0;
	stoppingX = 0;
	stoppingY = aa * ry;

	while (stoppingX <= stoppingY) {

		int xx, yy;

		xx = cx + x + sx;
		yy = cy + y + sy;
		if (clipPoint(xx, yy))
			driver->setPixel(xx, yy, color);

	    xx = cx - x - sx;
	    yy = cy + y + sy;
		if (clipPoint(xx, yy))
			driver->setPixel(xx, yy, color);

		xx = cx - x - sx;
		yy = cy - y - sy;
		if (clipPoint(xx, yy))
			driver->setPixel(xx, yy, color);

		xx = cx + x + sx;
		yy = cy - y - sy;
		if (clipPoint(xx, yy))
			driver->setPixel(xx, yy, color);

		x += 1;
		stoppingX += bb;
		error += changeX;
		changeX += bb;
		if ((2 * error + changeY) > 0) {
			y -= 1;
			stoppingY -= aa;
			error += changeY;
			changeY += aa;
		}
	}

	// Genera les linies d'unio dels quadrants
	//
	int xx1, yy1, xx2, yy2;

	xx1 = x1 + rx + 1;
	xx2 = x2 - rx - 1;
	if (clipHLine(xx1, xx2, y1))
		driver->setHPixels(xx1, y1, xx2 - xx1 + 1, color);

	xx1 = x1 + rx + 1;
	xx2 = x2 - rx - 1;
	if (clipHLine(xx1, xx2, y2))
		driver->setHPixels(xx1, y2, xx2 - xx1 + 1, color);

	yy1 = y1 + ry + 1;
	yy2 = y2 - ry - 1;
	if (clipVLine(x1, yy1, yy2))
		driver->setVPixels(x1, yy1, yy2 - yy1 + 1, color);

	yy1 = y1 + ry + 1;
	yy2 = y2 - ry - 1;
	if (clipVLine(x2, yy1, yy2))
		driver->setVPixels(x2, yy1, yy2 - yy1 + 1, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un rectangle ple, amb les cantonades arrodonides.
/// \param    x1: Coordinada x del primer punt.
/// \param    y1: Coordinada y del primer punt.
/// \param    x2: Coordinada x del segon punt.
/// \param    y2: Coordinada y del segon punt.
/// \param    rx: Radi x de les cantonades.
/// \param    ry: Radi y de les cantonades.
///
void Graphics::fillRoundedRectangle(
	int x1,
	int y1,
	int x2,
	int y2,
	int rx,
	int ry) const {

	// Transforma a coordinades fisiques
	//
	state.ct.apply(x1, y1);
	state.ct.apply(x2, y2);

	// Normalitza les coordinades
	//
	if (x1 > x2)
		Math::swap(x1, x2);
	if (y1 > y2)
		Math::swap(y1, y2);

	// Obte el centre
	//
	int cx = (x1 + x2) / 2;
	int cy = (y1 + y2) / 2;

	// Precalcula els factors constants
	//
	int aa = 2 * rx * rx;
	int bb = 2 * ry * ry;
	int sx = (x2 - x1 - rx - rx) / 2;
	int sy = (y2 - y1 - ry - ry) / 2;

	int x, y, error;
	int changeX, changeY;
	int stoppingX, stoppingY;

	// Genera el primer grup de linies
	//
	x = rx;
	y = 0;
	changeX = ry * ry * (1 - (rx * 2));
	changeY = rx * rx;
	error = 0;
	stoppingX = bb * rx;
	stoppingY = 0;

	while (stoppingX >= stoppingY) {

		int xx1, xx2, yy;

		xx1 = cx - x - sx;
	    xx2 = cx + x + sx;
		yy = cy + y + sy;
		if (clipHLine(xx1, xx2, yy))
			driver->setPixels(xx1, yy, xx2 - xx1 + 1, 1, color);

		xx1 = cx - x - sx;
		xx2 = cx + x + sx;
		yy = cy - y - sy;
		if (clipHLine(xx1, xx2, yy))
			driver->setPixels(xx1, yy, xx2 - xx1 + 1, 1, color);

		y += 1;
		stoppingY += aa;
		error += changeY;
		changeY += aa;
	    if ((2 * error + changeX) > 0 ) {
	    	x -= 1;
	    	stoppingX -= bb;
	    	error += changeX;
	    	changeX += bb;
	    }
	}

	// Genera el segon grup de linies
	//
	x = 0;
	y = ry;
	changeX = ry * ry;
	changeY = rx * rx * (1 - (2 * ry));
	error = 0;
	stoppingX = 0;
	stoppingY = aa * ry;

	while (stoppingX <= stoppingY) {

		int xx1, xx2, yy;

		xx1 = cx - x - sx;
	    xx2 = cx + x + sx;
		yy = cy + y + sy;
		if (clipHLine(xx1, xx2, yy))
			driver->setPixels(xx1, yy, xx2 - xx1 + 1, 1, color);

		xx1 = cx - x - sx;
		xx2 = cx + x + sx;
		yy = cy - y - sy;
		if (clipHLine(xx1, xx2, yy))
			driver->setPixels(xx1, yy, xx2 - xx1 + 1, 1, color);

		x += 1;
		stoppingX += bb;
		error += changeX;
		changeX += bb;
		if ((2 * error + changeY) > 0) {
			y -= 1;
			stoppingY -= aa;
			error += changeY;
			changeY += aa;
		}
	}
}
