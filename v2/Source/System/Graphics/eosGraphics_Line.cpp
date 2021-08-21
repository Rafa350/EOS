#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosPen.h"
#include "System/Graphics/eosPoint.h"
#include <math.h>

using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un linia amb el pen actual.
/// \brief    pen: El pen per dibuixar la linia
/// \param    p1: Punt inicial.
/// \param    p2: Punt final.
///
void Graphics::paintLine(
	const Pen& pen,
	const Point& p1,
	const Point& p2) const {

	if (!pen.isNull()) {

		Color color = pen.getColor();
		int thickness = pen.getThickness();

		if (thickness <= 1)
			drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color);
		else
			drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), thickness, color);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia amb l'algorisme de Bresenham
/// \param    x1 : Coordinada x del primer punt.
/// \param    y1 : Coordinada y del primer punt.
/// \param    x2 : Coordinada x del segon punt.
/// \param    y2 : Coordinada y del segon punt.
/// \param    color: Color.
/// \remarks  La funcio esta molt optimitzada. No cal perdre el temps
///           en millor-la. Potser codi maquina.
///
void Graphics::drawLine(
    int x1,
    int y1,
    int x2,
    int y2,
	Color color) const {

	// Transforma a coordinades fisiques
	//
	transform(x1, y1);
	transform(x2, y2);

    if (clipLine(x1, y1, x2, y2)) {

    	// Es una linea vertical
		//
		if (x1 == x2) {
			if (y1 > y2)
				Math::swap(y1, y2);
			_driver->setVPixels(x1, y1, y2 - y1 + 1, color);
		}

		// Es una linia horitzontal
		//
		else if (y1 == y2) {
			if (x1 > x2)
				Math::swap(x1, x2);
			_driver->setHPixels(x1, y1, x2 - x1 + 1, color);
		}

		// No es ni horitzontal ni vertical
		//
		else {

            int stepX, stepY;
            int p, incE, incNE;

            int deltaX = x2 - x1;
            int deltaY = y2 - y1;

            if (deltaX < 0)  {
                deltaX = -deltaX;
                stepX = -1;
            }
            else
                stepX = 1;

            if (deltaY < 0) {
                deltaY = -deltaY;
                stepY = -1;
            }
            else
                stepY = 1;

            _driver->setPixel(x1, y1, color);

            // Es mes gran el desplaçament X que el Y
            //
            if (deltaX > deltaY) {
                p = deltaY + deltaY - deltaX;
                incE = deltaY << 1;
                incNE = (deltaY - deltaX) << 1;
                while (x1 != x2) {
                    x1 += stepX;
                    if (p < 0)
                        p += incE;
                    else {
                        y1 += stepY;
                        p += incNE;
                    }
                    _driver->setPixel(x1, y1, color);
                }
            }

            // Es mes gran el deslaçament Y que el X
            //
            else if (deltaX < deltaY) {
                p = deltaX + deltaX - deltaY;
                incE = deltaX << 1;
                incNE = (deltaX - deltaY) << 1;
                while (y1 != y2) {
                    y1 += stepY;
                    if (p < 0)
                        p += incE;
                    else {
                        x1 += stepX;
                        p += incNE;
                    }
                    _driver->setPixel(x1, y1, color);
                }
            }

            // Es una linia diagonal
            //
            else {
                while (y1 != y2) {
                    y1 += stepY;
                    x1 += stepX;
                    _driver->setPixel(x1, y1, color);
                }
            }
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia amb l'algorisme de Bresenham modificat
///           per linies amples i anti-aliasing.
/// \param    x1 : Coordinada x del primer punt.
/// \param    y1 : Coordinada y del primer punt.
/// \param    x2 : Coordinada x del segon punt.
/// \param    y2 : Coordinada y del segon punt.
/// \param    thickness: Amplada de linia.
/// \param    color: Color.
/// \remarks  La funcio esta molt optimitzada. No cal perdre el temps
///           en millor-la. Potser codi maquina.
///
void Graphics::drawLine(
	int x0,
	int y0,
	int x1,
	int y1,
	int thickness,
	Color color) const {

	// Transforma a coordinades fisiques
	//
	transform(x0, y0);
	transform(x1, y1);

    if (clipLine(x0, y0, x1, y1)) {

		int e2, x2, y2;

		int dx = Math::abs(x1 - x0);
		int sx = x0 < x1 ? 1 : -1;
		int dy = Math::abs(y1 - y0);
		int sy = y0 < y1 ? 1 : -1;

		int err = dx - dy;
		float wd = thickness;
		float ed = dx + dy == 0 ? 1.0f : (int)sqrt((float)(dx * dx) + (float)(dy * dy));

		// Pixel loop
		//
		wd = (wd + 1) / 2;
		while (true) {

			uint8_t alpha = 255 - (uint8_t)Math::max(0.0f, 255.0f * (Math::abs(err - dx + dy) / ed - wd + 1.0f));

			Color c(makeColor<Color::CI::format>(alpha, color.getR(), color.getG(), color.getB()));
			_driver->setPixel(x0, y0, c);
			e2 = err;
			x2 = x0;

			// Step X
			//
			if (2 * e2 >= -dx) {
				for (e2 += dy, y2 = y0; e2 < ed*wd && (y1 != y2 || dx > dy); e2 += dx) {

					uint8_t alpha = 255 - (uint8_t)Math::max(0.0f, 255.0f * (Math::abs(e2) / ed - wd + 1.0f));

					Color c(makeColor<Color::CI::format>(alpha, color.getR(), color.getG(), color.getB()));
					_driver->setPixel(x0, y2 += sy, c);
				}
				if (x0 == x1)
					break;
				e2 = err;
				err -= dy;
				x0 += sx;
			}

			// Step Y
			//
			if (2 * e2 <= dy) {
				for (e2 = dx-e2; e2 < ed*wd && (x1 != x2 || dx < dy); e2 += dy) {

					uint8_t alpha = 255 - (uint8_t)Math::max(0.0f, 255.0f * (Math::abs(e2) / ed - wd + 1.0f));

					Color c(makeColor<Color::CI::format>(alpha, color.getR(), color.getG(), color.getB()));
					_driver->setPixel(x2 += sx, y0, c);
				}
				if (y0 == y1)
					break;
				err += dx;
				y0 += sy;
			}
		}
    }
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia horitzontal.
/// \param    x1: Coordinada X inicial.
/// \param    x2: Coordinada Y final.
/// \param    y: Coordinada Y.
/// \param    color: Color.
///
void Graphics::drawHLine(
	int x1,
	int x2,
	int y,
	Color color) const {

	// Transforma a coordinades fisiques
	//
	int y2 = y;
	transform(x1, y);
	transform(x2, y2);

	if (clipHLine(x1, x2, y)) {

		if (x1 > x2)
			Math::swap(x1, x2);

		_driver->setHPixels(x1, y, x2 - x1 + 1, color);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia vertical.
/// \param    x: Coordinada X.
/// \param    y1: Coordinada Y inicial.
/// \param    y2: Coordinada Y final.
/// \param    color: Color.
///
void Graphics::drawVLine(
	int x,
	int y1,
	int y2,
	Color color) const {

	// Transforma a coordinades fisiques
	//
	int x2 = x;
	transform(x, y1);
	transform(x2, y2);

	if (clipVLine(x, y1, y2)) {

		if (y1 > y2)
			Math::swap(y1, y2);

		_driver->setVPixels(x, y1, y2 - y1 + 1, color);
	}
}

