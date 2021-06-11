#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosPen.h"
#include "System/Graphics/eosPoint.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un linia.
/// \param    pen: El pen per dibuixar.
/// \param    p1: Punt inicial.
/// \param    p2: Punt final.
///
void Graphics::drawLine(
	const Pen& pen,
	const Point& p1,
	const Point& p2) {

	Color oldColor = _color;
	_color = pen.getColor();

	drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());

	_color = oldColor;
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia amb l'algorisme de Bresenham
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
			_driver->setVPixels(x1, y1, y2 - y1 + 1, _color);
		}

		// Es una linia horitzontal
		//
		else if (y1 == y2) {
			if (x1 > x2)
				Math::swap(x1, x2);
			_driver->setHPixels(x1, y1, x2 - x1 + 1, _color);
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

            _driver->setPixel(x1, y1, _color);

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
                    _driver->setPixel(x1, y1, _color);
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
                    _driver->setPixel(x1, y1, _color);
                }
            }

            // Es una linia diagonal
            //
            else {
                while (y1 != y2) {
                    y1 += stepY;
                    x1 += stepX;
                    _driver->setPixel(x1, y1, _color);
                }
            }
        }
    }
}


/// ----------------------------------------------------------------------
/// Dibuixa una linia amb l'algoritme de Xiaolin Wu.
///
#if 0
void drawLineWu(int x1, int y1, int x2, int y2) {

	unsigned IntensityShift, ErrorAdj, ErrorAcc;
	unsigned ErrorAccTemp, Weighting, WeightingComplementMask;
	unsigned DeltaX, DeltaY, Temp, XDir;

	/* Make sure the line runs top to bottom */
	if (Y0 > Y1) {
	      Temp = Y0; Y0 = Y1; Y1 = Temp;
	      Temp = X0; X0 = X1; X1 = Temp;
	}

	/* Draw the initial pixel, which is always exactly intersected by
	   the line and so needs no weighting */
	DrawPixel(pDC,X0, Y0, BaseColor);

	if ((DeltaX = X1 - X0) >= 0) {
	   XDir = 1;
	}
	else {
	   XDir = -1;
	   DeltaX = -DeltaX; /* make DeltaX positive */
	}

	/* Special-case horizontal, vertical, and diagonal lines, which
	   require no weighting because they go right through the center of
	   every pixel */
	if ((DeltaY = Y1 - Y0) == 0) {
	      /* Horizontal line */
	    return;
	}
	if (DeltaX == 0) {
		/* Vertical line */
	      return;
	   }
	   if (DeltaX == DeltaY) {
	      /* Diagonal line */
	      return;
	   }
	   /* Line is not horizontal, diagonal, or vertical */
	   ErrorAcc = 0;  /* initialize the line error accumulator to 0 */
	   /* # of bits by which to shift ErrorAcc to get intensity level */
	   IntensityShift = 16 - IntensityBits;
	   /* Mask used to flip all bits in an intensity weighting, producing the
	      result (1 - intensity weighting) */
	   WeightingComplementMask = NumLevels - 1;
	   /* Is this an X-major or Y-major line? */
	   if (DeltaY > DeltaX) {
	      /* Y-major line; calculate 16-bit fixed-point fractional part of a
	         pixel that X advances each time Y advances 1 pixel, truncating the
	         result so that we won't overrun the endpoint along the X axis */
	      ErrorAdj = ((unsigned long) DeltaX << 16) / (unsigned long) DeltaY;
	      /* Draw all pixels other than the first and last */
	      while (--DeltaY) {
	         ErrorAccTemp = ErrorAcc;   /* remember current accumulated error */
	         ErrorAcc += ErrorAdj;      /* calculate error for next pixel */
	         if (ErrorAcc <= ErrorAccTemp) {
	            /* The error accumulator turned over, so advance the X coord */
	            X0 += XDir;
	         }
	         Y0++; /* Y-major, so always advance Y */
	         /* The IntensityBits most significant bits of ErrorAcc give us the
	            intensity weighting for this pixel, and the complement of the
	            weighting for the paired pixel */
	         Weighting = ErrorAcc >> IntensityShift;
	         DrawPixel(pDC,X0, Y0, BaseColor + Weighting);
	         DrawPixel(pDC,X0 + XDir, Y0,
	               BaseColor + (Weighting ^ WeightingComplementMask));
	      }
	      /* Draw the final pixel, which is
	         always exactly intersected by the line
	         and so needs no weighting */
	      DrawPixel(pDC,X1, Y1, BaseColor);
	      return;
	   }
	   /* It's an X-major line; calculate 16-bit fixed-point fractional part of a
	      pixel that Y advances each time X advances 1 pixel, truncating the
	      result to avoid overrunning the endpoint along the X axis */
	   ErrorAdj = ((unsigned long) DeltaY << 16) / (unsigned long) DeltaX;
	   /* Draw all pixels other than the first and last */
	   while (--DeltaX) {
	      ErrorAccTemp = ErrorAcc;   /* remember current accumulated error */
	      ErrorAcc += ErrorAdj;      /* calculate error for next pixel */
	      if (ErrorAcc <= ErrorAccTemp) {
	         /* The error accumulator turned over, so advance the Y coord */
	         Y0++;
	      }
	      X0 += XDir; /* X-major, so always advance X */
	      /* The IntensityBits most significant bits of ErrorAcc give us the
	         intensity weighting for this pixel, and the complement of the
	         weighting for the paired pixel */
	      Weighting = ErrorAcc >> IntensityShift;
	      DrawPixel(pDC,X0, Y0, BaseColor + Weighting);
	      DrawPixel(pDC,X0, Y0 + 1,
	            BaseColor + (Weighting ^ WeightingComplementMask));
	   }
	   /* Draw the final pixel, which is always exactly intersected by the line
	      and so needs no weighting */
	   DrawPixel(pDC,X1, Y1, BaseColor);
}
#endif

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

		_driver->setHPixels(x1, y, x2 - x1 + 1, _color);
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

		_driver->setVPixels(x, y1, y2 - y1 + 1, _color);
	}
}

