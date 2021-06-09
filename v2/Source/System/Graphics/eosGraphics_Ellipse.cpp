#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una el·lipse buida inscrita en un rectangle.
/// \param    x1: Coordinada X del primer punt.
/// \param    y1: Coordinada Y del primer punt.
/// \param    x2: Coordinada X del segon punt.
/// \param    y2: Coordinada Y del segon punt.
/// \param    sx: Espaiat x.
/// \param    sy: Espaiat y.
///
void Graphics::drawEllipse(
	int x1,
	int y1,
	int x2,
	int y2) const {

	// Transforma a coordinades fisiques
	//
	transform(x1, y1);
	transform(x2, y2);

	// Normalitza les coordinades
	//
	if (x1 > x2)
		Math::swap(x1, x2);
	if (y1 > y2)
		Math::swap(y1, y2);

	// Obte el centre i els radis
	//
	int cx = (x1 + x2) / 2;
	int cy = (y1 + y2) / 2;
	int rx = (x2 - x1) / 2;
	int ry = (y2 - y1) / 2;

	// Precalcula els factors constants
	//
	int aa = 2 * rx * rx;
	int bb = 2 * ry * ry;

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

		xx = cx + x;
		yy = cy + y;
		if (clipPoint(xx, yy))
			_driver->setPixel(xx, yy, _color);

	    xx = cx - x;
	    yy = cy + y;
		if (clipPoint(xx, yy))
			_driver->setPixel(xx, yy, _color);

		xx = cx - x;
		yy = cy - y;
		if (clipPoint(xx, yy))
			_driver->setPixel(xx, yy, _color);

		xx = cx + x;
		yy = cy - y;
		if (clipPoint(xx, yy))
			_driver->setPixel(xx, yy, _color);

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

		xx = cx + x;
		yy = cy + y;
		if (clipPoint(xx, yy))
			_driver->setPixel(xx, yy, _color);

	    xx = cx - x;
	    yy = cy + y;
		if (clipPoint(xx, yy))
			_driver->setPixel(xx, yy, _color);

		xx = cx - x;
		yy = cy - y;
		if (clipPoint(xx, yy))
			_driver->setPixel(xx, yy, _color);

		xx = cx + x;
		yy = cy - y;
		if (clipPoint(xx, yy))
			_driver->setPixel(xx, yy, _color);

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


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una el·lipse plena inscrita en un rectangle.
/// \param    x1: Coordinada X del primer punt.
/// \param    y1: Coordinada Y del primer punt.
/// \param    x2: Coordinada X del segon punt.
/// \param    y2: Coordinada Y del segon punt.
///
void Graphics::fillEllipse(
	int x1,
	int y1,
	int x2,
	int y2) const {

	// Transforma a coordinades fisiques
	//
	transform(x1, y1);
	transform(x2, y2);

	// Normalitza les coordinades
	//
	if (x1 > x2)
		Math::swap(x1, x2);
	if (y1 > y2)
		Math::swap(y1, y2);

	// Obte el centre i els radis
	//
	int cx = (x1 + x2) / 2;
	int cy = (y1 + y2) / 2;
	int rx = (x2 - x1) / 2;
	int ry = (y2 - y1) / 2;

	// Precalcula els factors constants
	//
	int aa = 2 * rx * rx;
	int bb = 2 * ry * ry;

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

		int xx1, xx2, yy;

		xx1 = cx - x;
	    xx2 = cx + x;
		yy = cy + y;
		if (clipHLine(xx1, xx2, yy))
			_driver->setPixels(xx1, yy, xx2 - xx1 + 1, 1, _color);

		xx1 = cx - x;
		xx2 = cx + x;
		yy = cy - y;
		if (clipHLine(xx1, xx2, yy))
			_driver->setPixels(xx1, yy, xx2 - xx1 + 1, 1, _color);

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

		int xx1, xx2, yy;

		xx1 = cx - x;
	    xx2 = cx + x;
		yy = cy + y;
		if (clipHLine(xx1, xx2, yy))
			_driver->setPixels(xx1, yy, xx2 - xx1 + 1, 1, _color);

		xx1 = cx - x;
		xx2 = cx + x;
		yy = cy - y;
		if (clipHLine(xx1, xx2, yy))
			_driver->setPixels(xx1, yy, xx2 - xx1 + 1, 1, _color);

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


