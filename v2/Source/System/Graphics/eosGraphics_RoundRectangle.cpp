#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un rectangle amb cantonades arrodonides.
/// \param    pen: El pen.
/// \param    brush: El brush.
/// \param    rect: El rectangle.
/// \param    rx: Radi x.
/// \param    ry: Radi y.
///
void Graphics::paintRoundedRectangle(
	const Pen &pen,
	const Brush &brush,
	const Rect &box,
	int rx,
	int ry) const {

	bool penVisible = !pen.isNull();
	bool brushVisible = !brush.isNull();

	if (penVisible || brushVisible) {

		int x1 = box.getMinX();
		int y1 = box.getMinY();
		int x2 = box.getMaxX();
		int y2 = box.getMaxY();

		if (brushVisible) {
			Color color = brush.getColor();
			fillRoundedRectangle(x1, y1, x2, y2, rx, ry, color);
		}

		if (penVisible) {
			Color color = pen.getColor();
			drawRoundedRectangle(x1, y1, x2, y2, rx, ry, color);
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un rectangle amb les cantonades arrodonides.
/// \param    x1: Coordinada x del primer punt.
/// \param    y1: Coordinada y del primer punt.
/// \param    x2: Coordinada x del segon punt.
/// \param    y2: Coordinada y del segon punt.
/// \param    rx: Radi x de les cantonades.
/// \param    ry: Radi y de les cantonades.
/// \param    color: Color.
///
void Graphics::drawRoundedRectangle(
	int x1,
	int y1,
	int x2,
	int y2,
	int rx,
	int ry,
	Color color) const {

	if ((rx == 0) || (ry == 0))
		drawRectangle(x1, y1, x2, y2, color);

	else {

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

		// Precalcula els factors constants
		//
		int aa = 2 * rx * rx;
		int bb = 2 * ry * ry;
		int xc1 = x1 + rx;
		int xc2 = x2 - rx;
		int yc1 = y1 + ry;
		int yc2 = y2 - ry;

		int x, y, error;
		int changeX, changeY;
		int stoppingX, stoppingY;
		int xx1, xx2, yy1, yy2;

		// Dibuixa el primer grup de punts
		//
		x = rx;
		y = 0;
		changeX = ry * ry * (1 - (rx * 2));
		changeY = rx * rx;
		error = 0;
		stoppingX = bb * rx;
		stoppingY = 0;

		while (stoppingX >= stoppingY) {

			xx1 = xc1 - x;
			yy1 = yc1 - y;
			if (clipPoint(xx1, yy1))
				_driver->setPixel(xx1, yy1, color);

			xx1 = xc2 + x;
			yy1 = yc1 - y;
			if (clipPoint(xx1, yy1))
				_driver->setPixel(xx1, yy1, color);

			xx1 = xc1 - x;
			yy1 = yc2 + y;
			if (clipPoint(xx1, yy1))
				_driver->setPixel(xx1, yy1, color);

			xx1 = xc2 + x;
			yy1 = yc2 + y;
			if (clipPoint(xx1, yy1))
				_driver->setPixel(xx1, yy1, color);

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

		// Dibuixa el segon grup de punts
		//
		x = 0;
		y = ry;
		changeX = ry * ry;
		changeY = rx * rx * (1 - (2 * ry));
		error = 0;
		stoppingX = 0;
		stoppingY = aa * ry;

		while (stoppingX <= stoppingY) {

			xx1 = xc1 - x;
			yy1 = yc1 - y;
			if (clipPoint(xx1, yy1))
				_driver->setPixel(xx1, yy1, color);

			xx1 = xc2 + x;
			yy1 = yc1 - y;
			if (clipPoint(xx1, yy1))
				_driver->setPixel(xx1, yy1, color);

			xx1 = xc1 - x;
			yy1 = yc2 + y;
			if (clipPoint(xx1, yy1))
				_driver->setPixel(xx1, yy1, color);

			xx1 = xc2 + x;
			yy1 = yc2 + y;
			if (clipPoint(xx1, yy1))
				_driver->setPixel(xx1, yy1, color);

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

		// Dibuixa les linies d'unio dels quadrants
		//
		xx1 = x1;
		yy1 = yc1 + 1;
		yy2 = yc2 - 1;
		if (clipVLine(xx1, yy1, yy2))
			_driver->setVPixels(xx1, yy1, yy2 - yy1 + 1, color);

		xx1 = x2;
		yy1 = yc1 + 1;
		yy2 = yc2 - 1;
		if (clipVLine(xx1, yy1, yy2))
			_driver->setVPixels(xx1, yy1, yy2 - yy1 + 1, color);

		xx1 = xc1 + 1;
		xx2 = xc2 - 1;
		yy1 = y1;
		if (clipHLine(xx1, xx2, yy1))
			_driver->setHPixels(xx1, yy1, xx2 - xx1 + 1, color);

		xx1 = xc1 + 1;
		xx2 = xc2 - 1;
		yy1 = y2;
		if (clipHLine(xx1, xx2, yy1))
			_driver->setHPixels(xx1, yy1, xx2 - xx1 + 1, color);
	}
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
	int ry,
	Color color) const {

	if ((rx == 0) || (ry == 0))
		fillRectangle(x1, y1, x2, y2, color);

	else {

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

		// Precalcula els factors constants
		//
		int aa = 2 * rx * rx;
		int bb = 2 * ry * ry;
		int xc1 = x1 + rx;
		int xc2 = x2 - rx;
		int yc1 = y1 + ry;
		int yc2 = y2 - ry;

		int x, y, error;
		int changeX, changeY;
		int stoppingX, stoppingY;
		int xx1, yy1, xx2, yy2;

		// Dibuixa el primer grup de linies
		//
		x = rx;
		y = 0;
		changeX = ry * ry * (1 - (rx * 2));
		changeY = rx * rx;
		error = 0;
		stoppingX = bb * rx;
		stoppingY = 0;

		while (stoppingX >= stoppingY) {

			xx1 = xc1 - x;
			xx2 = xc2 + x;
			yy1 = yc1 - y;
			if (clipHLine(xx1, xx2, yy1))
				_driver->setPixels(xx1, yy1, xx2 - xx1 + 1, 1, color);

			xx1 = xc1 - x;
			xx2 = xc2 + x;
			yy1 = yc2 + y;
			if (clipHLine(xx1, xx2, yy1))
				_driver->setPixels(xx1, yy1, xx2 - xx1 + 1, 1, color);

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

		// Dibuixa el segon grup de linies
		//
		x = 0;
		y = ry;
		changeX = ry * ry;
		changeY = rx * rx * (1 - (2 * ry));
		error = 0;
		stoppingX = 0;
		stoppingY = aa * ry;

		while (stoppingX <= stoppingY) {

			xx1 = xc1 - x;
			xx2 = xc2 + x;
			yy1 = yc1 - y;
			if (clipHLine(xx1, xx2, yy1))
				_driver->setPixels(xx1, yy1, xx2 - xx1 + 1, 1, color);

			xx1 = xc1 - x;
			xx2 = xc2 + x;
			yy1 = yc2 + y;
			if (clipHLine(xx1, xx2, yy1))
				_driver->setPixels(xx1, yy1, xx2 - xx1 + 1, 1, color);

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

		// Dibuixa el rectangle central
		//
		xx1 = x1;
		yy1 = yc1 + 1;
		xx2 = x2;
		yy2 = yc2 - 1;
		if (clipRectangle(xx1, yy1, xx2, yy2))
			_driver->setPixels(xx1, yy1, xx2 - xx1 + 1, yy2 - yy1 + 1, color);
	}
}
