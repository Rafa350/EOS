#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia.
/// \param    x1 : Coordinada x del primer punt.
/// \param    y1 : Coordinada y del primer punt.
/// \param    x2 : Coordinada x del segon punt.
/// \param    y2 : Coordinada y del segon punt.
///
void Graphics::drawLine(
    int x1,
    int y1,
    int x2,
    int y2) const {

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
			driver->setVPixels(x1, y1, y2 - y1 + 1, color);
		}

		// Es una linia horitzontal
		//
		else if (y1 == y2) {
			if (x1 > x2)
				Math::swap(x1, x2);
			driver->setHPixels(x1, y1, x2 - x1 + 1, color);
		}

		// No es ni horitzontal ni vertical
		//
		else {

            int stepX, stepY;
            int p, incE, incNE;

            int deltaX = x2 - x1;
            int deltaY = y2 - y1;

            if (deltaY < 0) {
                deltaY = -deltaY;
                stepY = -1;
            }
            else
                stepY = 1;

            if (deltaX < 0)  {
                deltaX = -deltaX;
                stepX = -1;
            }
            else
                stepX = 1;

            driver->setPixel(x1, y1, color);

            // Es mes gran el desplaçament X que el Y
            //
            if (deltaX > deltaY) {
                p = deltaY + deltaY - deltaX;
                incE = deltaY << 1;
                incNE = (deltaY - deltaX) * 2;
                while (x1 != x2) {
                    x1 += stepX;
                    if (p < 0)
                        p += incE;
                    else {
                        y1 += stepY;
                        p += incNE;
                    }
                    driver->setPixel(x1, y1, color);
                }
            }

            // Es mes gran el deslaçament Y que el X
            //
            else if (deltaX < deltaY) {
                p = deltaX + deltaX - deltaY;
                incE = deltaX << 1;
                incNE = (deltaX - deltaY) * 2;
                while (y1 != y2) {
                    y1 += stepY;
                    if (p < 0)
                        p += incE;
                    else {
                        x1 += stepX;
                        p += incNE;
                    }
                    driver->setPixel(x1, y1, color);
                }
            }

            // Es una linia diagonal
            //
            else {
                while (y1 != y2) {
                    y1 += stepY;
                    x1 += stepX;
                    driver->setPixel(x1, y1, color);
                }
            }
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia horitzontal.
/// \param    x1 : Coordinada X inicial.
/// \param    x2 : Coordinada Y final.
/// \param    y  : Coordinada Y.
///
void Graphics::drawHLine(
	int x1,
	int x2,
	int y) const {

	// Transforma a coordinades fisiques
	//
	int y2 = y;
	transform(x1, y);
	transform(x2, y2);

	if (clipHLine(x1, x2, y)) {

		if (x1 > x2)
			Math::swap(x1, x2);

		driver->setHPixels(x1, y, x2 - x1 + 1, color);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia vertical.
/// \param    x  : Coordinada X.
/// \param    y1 : Coordinada Y inicial.
/// \param    y2 : Coordinada Y final.
///
void Graphics::drawVLine(
	int x,
	int y1,
	int y2) const {

	// Transforma a coordinades fisiques
	//
	int x2 = x;
	transform(x, y1);
	transform(x2, y2);

	if (clipVLine(x, y1, y2)) {

		if (y1 > y2)
			Math::swap(y1, y2);

		driver->setVPixels(x, y1, y2 - y1 + 1, color);
	}
}

