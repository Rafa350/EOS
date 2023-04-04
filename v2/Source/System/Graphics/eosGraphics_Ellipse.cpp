#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una el·lipse.
/// \param    pen: El pen.
/// \param    brush: El brush.
/// \param    rect: El rectangle que conte l'el·lipse.
///
void Graphics::paintEllipse(
	const Pen &pen,
	const Brush &brush,
	const Rect &box) const {

	bool penVisible = !pen.isNull();
	bool brushVisible = !brush.isNull();

	if (penVisible || brushVisible) {

		int16_t x1 = box.getMinX();
		int16_t y1 = box.getMinY();
		int16_t x2 = box.getMaxX();
		int16_t y2 = box.getMaxY();

		if (brushVisible) {
			Color color = brush.getColor();
			fillEllipse(x1, y1, x2, y2, color);
		}

		if (penVisible) {
			Color color = pen.getColor();
			drawEllipse(x1, y1, x2, y2, color);
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una el·lipse buida inscrita en un rectangle.
/// \param    x1: Coordinada X del primer punt.
/// \param    y1: Coordinada Y del primer punt.
/// \param    x2: Coordinada X del segon punt.
/// \param    y2: Coordinada Y del segon punt.
/// \param    color: Color.
///
void Graphics::drawEllipse(
	int16_t x1,
	int16_t y1,
	int16_t x2,
	int16_t y2,
	Color color) const {

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

	// Cas que nomes sigui un punt
	//
	if ((x1 == x2) && (y1 == y2))
		_driver->setPixel(x1, y1, color);

	else {

		// Obte el centre i els radis
		//
		int16_t cx = (x1 + x2) / 2;
		int16_t cy = (y1 + y2) / 2;
		int16_t rx = (x2 - x1) / 2;
		int16_t ry = (y2 - y1) / 2;

		// Precalcula els factors constants
		//
		int16_t aa = 2 * rx * rx;
		int16_t bb = 2 * ry * ry;

		int16_t x, y;
		int32_t error, changeX, changeY;
		int32_t stoppingX, stoppingY;

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

			int16_t xx, yy;

			xx = cx + x;
			yy = cy + y;
			if (clipPoint(xx, yy))
				_driver->setPixel(xx, yy, color);

			xx = cx - x;
			yy = cy + y;
			if (clipPoint(xx, yy))
				_driver->setPixel(xx, yy, color);

			xx = cx - x;
			yy = cy - y;
			if (clipPoint(xx, yy))
				_driver->setPixel(xx, yy, color);

			xx = cx + x;
			yy = cy - y;
			if (clipPoint(xx, yy))
				_driver->setPixel(xx, yy, color);

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

			int16_t xx, yy;

			xx = cx + x;
			yy = cy + y;
			if (clipPoint(xx, yy))
				_driver->setPixel(xx, yy, color);

			xx = cx - x;
			yy = cy + y;
			if (clipPoint(xx, yy))
				_driver->setPixel(xx, yy, color);

			xx = cx - x;
			yy = cy - y;
			if (clipPoint(xx, yy))
				_driver->setPixel(xx, yy, color);

			xx = cx + x;
			yy = cy - y;
			if (clipPoint(xx, yy))
				_driver->setPixel(xx, yy, color);

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
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una el·lipse plena inscrita en un rectangle.
/// \param    x1: Coordinada X del primer punt.
/// \param    y1: Coordinada Y del primer punt.
/// \param    x2: Coordinada X del segon punt.
/// \param    y2: Coordinada Y del segon punt.
/// \param    color: Color
///
void Graphics::fillEllipse(
	int16_t x1,
	int16_t y1,
	int16_t x2,
	int16_t y2,
	Color color) const {

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

	// Cas que nomes sigui un punt
	//
	if ((x1 == x2) && (y1 == y2))
		_driver->setPixel(x1, y1, color);

	else {

		// Obte el centre i els radis
		//
		int16_t cx = (x1 + x2) / 2;
		int16_t cy = (y1 + y2) / 2;
		int16_t rx = (x2 - x1) / 2;
		int16_t ry = (y2 - y1) / 2;

		// Precalcula els factors constants
		//
		int16_t aa = 2 * rx * rx;
		int16_t bb = 2 * ry * ry;

		int16_t x, y;
		int32_t error, changeX, changeY;
		int32_t stoppingX, stoppingY;

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

			int16_t xx1, xx2, yy;

			xx1 = cx - x;
			xx2 = cx + x;
			yy = cy + y;
			if (clipHLine(xx1, xx2, yy))
				_driver->setPixels(xx1, yy, xx2 - xx1 + 1, 1, color);

			xx1 = cx - x;
			xx2 = cx + x;
			yy = cy - y;
			if (clipHLine(xx1, xx2, yy))
				_driver->setPixels(xx1, yy, xx2 - xx1 + 1, 1, color);

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

			int16_t xx1, xx2, yy;

			xx1 = cx - x;
			xx2 = cx + x;
			yy = cy + y;
			if (clipHLine(xx1, xx2, yy))
				_driver->setPixels(xx1, yy, xx2 - xx1 + 1, 1, color);

			xx1 = cx - x;
			xx2 = cx + x;
			yy = cy - y;
			if (clipHLine(xx1, xx2, yy))
				_driver->setPixels(xx1, yy, xx2 - xx1 + 1, 1, color);

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
}

