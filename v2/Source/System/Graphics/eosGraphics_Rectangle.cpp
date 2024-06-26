#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosPen.h"
#include "System/Graphics/eosBrush.h"
#include "System/Graphics/eosGraphics.h"

#include <cmath>


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un rectangle.
/// \param    pen: El pen.
/// \param    brush: El brush.
/// \param    rect: El rectangle.
///
void Graphics::paintRectangle(
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
			fillRectangle(x1, y1, x2, y2, color);
		}

		if (penVisible) {
			Color color = pen.getColor();
			int16_t thickness = pen.getThickness();
			if (thickness < std::min(std::abs(x2 - x1), std::abs(y2 - y1)) / 2) {
				if (thickness > 1) {
					fillRectangle(x1, y1, x2, y1 + thickness, color);
					fillRectangle(x1, y2 - thickness, x2, y2, color);
					fillRectangle(x1, y1 + thickness, x1 + thickness, y2 - thickness, color);
					fillRectangle(x2 - thickness, y1 + thickness, x2, y2 - thickness, color);
				}
				else
					drawRectangle(x1, y1, x2, y2, color);
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un rectangle buit.
/// \param    x1: Coordinada x del primer punt.
/// \param    y1: Coordinada y del primer punt.
/// \param    x2: Coordinada x del segon punt.
/// \param    y2: Coordinada y del segon punt.
/// \param    color: Color.
///
void Graphics::drawRectangle(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
	Color color) const {

    // Transforma a coordinades fisiques.
	//
	transform(x1, y1);
	transform(x2, y2);

	// Normalitza les coordinades.
	//
    if (x1 > x2)
        std::swap(x1, x2);
    if (y1 > y2)
        std::swap(y1, y2);

    int16_t xx1, xx2, yy1, yy2;

    xx1 = x1;
    xx2 = x2;
    yy1 = y1;
    if (clipHLine(xx1, xx2, yy1))
    	_driver->setHPixels(xx1, yy1, xx2 - xx1 + 1, color);

    xx1 = x1;
    xx2 = x2;
    yy1 = y2;
    if (clipHLine(xx1, xx2, yy1))
    	_driver->setHPixels(xx1, yy1, xx2 - xx1 + 1, color);

    xx1 = x1;
    yy1 = y1;
    yy2 = y2;
    if (clipVLine(xx1, yy1, yy2))
    	_driver->setVPixels(xx1, yy1, yy2 - yy1 + 1, color);

    xx1 = x2;
    yy1 = y1;
    yy2 = y2;
    if (clipVLine(xx1, yy1, yy2))
    	_driver->setVPixels(xx1, yy1, yy2 - yy1 + 1, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un rectangle omplert.
/// \param    x1: Coordinada X del primer punt.
/// \param    y1: Coordinada Y del primer punt.
/// \param    x2: Coordinada X del segon punt.
/// \param    y2: Coordinada Y del segon punt.
/// \param    color: Color.
///
void Graphics::fillRectangle(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
	Color color) const {

    // Transforma a coordinades fisiques.
	//
	transform(x1, y1);
	transform(x2, y2);

	// Normalitza les coordinades.
	//
    if (x1 > x2)
        std::swap(x1, x2);
    if (y1 > y2)
        std::swap(y1, y2);

    // Dibuixa el rectangle si es visible
    //
    if (clipRectangle(x1, y1, x2, y2))
         _driver->setPixels(x1, y1, x2 - x1 + 1, y2 - y1 + 1, color);
}
