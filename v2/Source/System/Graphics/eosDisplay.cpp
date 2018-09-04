#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/Graphics/eosDisplay.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosBitmap.h"
#include "Controllers/Display/eosDisplayDriver.h"

#include <stdint.h>


using namespace eos;


extern const unsigned char *fontConsolas14pt;

#define INSIDE     0x0000u
#define LEFT       0x0001u
#define RIGHT      0x0002u
#define BOTTOM     0x0004u
#define TOP        0x0008u


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param driver: Driver del display
///
Display::Display(
    IDisplayDriver *driver) :

    driver(driver),
	clipX1(0),
	clipY1(0),
	clipX2(driver->getWidth() - 1),
	clipY2(driver->getHeight() - 1),
    color(COLOR_Black),
    font(nullptr),
    hAlign(HorizontalTextAlign::left),
    vAlign(VerticalTextAlign::bottom),
    cursorX(0),
    cursorY(0),
    ttyState(0) {

    setFont(new Font(fontConsolas14pt));
}


/// ---------------------------------------------------------------------
/// \brief Destructor.
///
Display::~Display() {

}


/// ----------------------------------------------------------------------
/// \brief Selecciona el color per dibuixar.
/// \param color: El color a seleccionar.
///
void Display::setColor(
    const Color &color) {

    this->color = color;
}


/// ----------------------------------------------------------------------
/// \brief Selecciona l'aliniacio del texte.
/// \param hAlign: Aliniacio horitzontal.
/// \param vAlign: Aliniacio vertical.
///
void Display::setTextAlign(
    HorizontalTextAlign hAlign,
    VerticalTextAlign vAlign) {

    this->hAlign = hAlign;
    this->vAlign = vAlign;
}


/// ----------------------------------------------------------------------
/// \brief Selecciona el font per dibuixar caracters i cadenes de texte.
/// \param font: El font a seleccionar.
/// \return L'anterior font seleccionat.
///
void Display::setFont(
    Font *font) {

    this->font = font;
}


/// ---------------------------------------------------------------------
/// \brief Canvia l'orientacio del display
/// \param orientation: L'orientacio a seleccionar.
/// \remarks Al canviar l'orientacio, es reseteja l'area de retall.
///
void Display::setOrientation(
	DisplayOrientation orientation) {

	driver->setOrientation(orientation);
	resetClip();
}


/// ----------------------------------------------------------------------
/// \bried Selecciona la regio de retall.
/// \param x1: Coordinada X esquerra.
/// \param y1: Coodinada Y superior.
/// \param x2: Coordinada X dreta.
/// \param y2: Coordinada Y inferior.
///
void Display::setClip(
    int x1,
    int y1,
    int x2,
    int y2) {

    if (x1 > x2)
        Math::swap(x1, x2);
    if (y1 > y2)
        Math::swap(y1, y2);

    int screenWidth = driver->getWidth();
    int screenHeight = driver->getHeight();

    clipX1 = x1 < 0 ? 0 : x1;
    clipY1 = y1 < 0 ? 0 : y1;
    clipX2 = x2 >= screenWidth ? screenWidth - 1 : x2;
    clipY2 = y2 >= screenHeight ? screenHeight - 1 : y2;
}


/// ----------------------------------------------------------------------
/// \brief Reseteja la regio de retall.
///
void Display::resetClip() {

	clipX1 = 0;
	clipY1 = 0;
	clipX2 = driver->getWidth() - 1;
	clipY2 = driver->getHeight() - 1;
}


/// ----------------------------------------------------------------------
/// \brief Borrat de la pantalla al color especificat.
/// \param color: El color per realitzar el borrat.
///
void Display::clear(
    const Color &color) {

    driver->clear(color);
    cursorX = 0;
    cursorY = 0;
}


/// ----------------------------------------------------------------------
/// \brief Refresca la pantalla.
///
void Display::refresh() {

}


/// ----------------------------------------------------------------------
/// \brief Mou el cursor a posicio indicada.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
///
void Display::moveTo(
    int x,
    int y) {

    cursorX = x;
    cursorY = y;
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia desde la posicio del cursor a la posicio
///        indicada.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
///
void Display::lineTo(
    int x,
    int y) {

    drawLine(cursorX, cursorY, x, y);
    cursorX = x;
    cursorY = y;
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un pixel.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
///
void Display::drawPoint(
    int x,
    int y) {

    if (clipPoint(x, y))
        driver->setPixel(x, y, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia.
/// \param x1: Coordinada x del origen.
/// \param y1: Coordinada y del origen.
/// \param x2: Coordinada x del final.
/// \param y2: Coordinada y del final.
///
void Display::drawLine(
    int x1,
    int y1,
    int x2,
    int y2) {

    // Calcula les deltas
    //
    int dx = x2 - x1;
    int dy = y2 - y1;

    // Es una linea horitzontal
    //
    if (dx == 0) {
        if (clipVLine(x1, y1, y2))
            driver->setVPixels(x1, dy > 0 ? y1 : y2, (dy > 0 ? y2 - y1 : y1 - y2) + 1, color);
    }

    // Es una linia vertical
    //
    else if (dy == 0) {
        if (clipHLine(x1, x2, y1))
            driver->setHPixels(dx > 0 ? x1 : x2, y1, (dx > 0 ? x2 - x1 : x1 - x2) + 1, color);
    }

    // No es ni horitzontal ni vertical
    //
    else {
        if (clipLine(x1, y1, x2, y2)) {

            int stepx, stepy;
            int p, incE, incNE;

            if (dy < 0) {
                dy = -dy;
                stepy = -1;
            }
            else
                stepy = 1;

            if (dx < 0)  {
                dx = -dx;
                stepx = -1;
            }
            else
                stepx = 1;

            driver->setPixel(x1, y1, color);

            if (dx > dy) {
                p = dy + dy - dx;
                incE = dy << 1;
                incNE = (dy - dx) << 1;
                while (x1 != x2) {
                    x1 += stepx;
                    if (p < 0)
                        p += incE;
                    else {
                        y1 += stepy;
                        p += incNE;
                    }
                    driver->setPixel(x1, y1, color);
                }
            }
            else {
                p = dx + dx - dy;
                incE = dx << 1;
                incNE = (dx - dy) << 1;
                while (y1 != y2) {
                    y1 += stepy;
                    if (p < 0)
                        p += incE;
                    else {
                        x1 += stepx;
                        p += incNE;
                    }
                    driver->setPixel(x1, y1, color);
                }
            }
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un rectangle buit.
/// \param x1: Coordinada x del origen.
/// \param y1: Coordinada y del origen.
/// \param x2: Coordinada x del final.
/// \param y2: Coordinada y del final.
///
void Display::drawRectangle(
    int x1,
    int y1,
    int x2,
    int y2) {

    drawLine(x1, y1, x2, y1);
    drawLine(x1, y2, x2, y2);
    drawLine(x1, y1, x1, y2);
    drawLine(x2, y1, x2, y2);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un triangle buit.
/// \param x1: Coordinada x del primer punt
/// \param y1: Coordinada y del primer punt
/// \param x2: Coordinada x del segon punt.
/// \param y2: Coordinada y del segon punt.
/// \param x3: Coordinada x del tercer punt.
/// \param y3: Coordinada y del tercer punt.
///
void Display::drawTriangle(
    int x1,
    int y1,
    int x2,
    int y2,
    int x3,
    int y3) {

    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un cercle buit.
/// \param x: Coordinada X del centre.
/// \param y: Coordinada Y del centre.
/// \param r: Radi del cercle.
///
void Display::drawCircle(
    int x,
    int y,
    int r) {

    int xx = r;
    int yy = 0;
    int d = 1 - xx;

    while (yy <= xx) {
        drawPoint(x + xx, y + yy);
        drawPoint(x - xx, y + yy);
        drawPoint(x - xx, y - yy);
        drawPoint(x + xx, y - yy);
        drawPoint(x + yy, y + xx);
        drawPoint(x - yy, y + xx);
        drawPoint(x - yy, y - xx);
        drawPoint(x + yy, y - xx);
        yy++;
        if (d <= 0)
            d += 2 * yy + 1;
        else {
            xx--;
            d += 2 * (yy - xx) + 1;
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un rectangle omplert.
/// \param x1: Coordinada X inicial.
/// \param y1: Coordinada Y inicial
/// \param x2: Coordinada X final.
/// \param y2: Coordinada Y final.
///
void Display::fillRectangle(
    int x1,
    int y1,
    int x2,
    int y2) {

    if (clipArea(x1, y1, x2, y2)) {

        if (x1 > x2)
            Math::swap(x1, x2);
        if (y1 > y2)
            Math::swap(y1, y2);

        driver->setPixels(x1, y1, x2 - x1 + 1, y2 - y1 + 1, color);
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un cercle omplert.
/// \param cx: Coordinada X del centre.
/// \param cy: Coordinada Y del centre.
/// \param r: Radi del cercle.
///
void Display::fillCircle(
    int cx,
    int cy,
    int r) {

    int x = r;
    int y = 0;
    int d = 1 - x;

    while (y <= x) {

        drawLine(cx - x, cy - y, cx + x, cy - y);
        drawLine(cx - x, cy + y, cx + x, cy + y);
        drawLine(cx - y, cy - x, cx + y, cy - x);
        drawLine(cx - y, cy + x, cx + y, cy + x);

        y++;
        if (d <= 0)
            d += 2 * y + 1;
        else {
            x--;
            d += 2 * (y - x) + 1;
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un bitmap complert.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param bitmap: El bitmap
///
void Display::drawBitmap(
    int x,
    int y,
    const Bitmap *bitmap) {

	int x1 = x;
	int y1 = y;
	int x2 = x + bitmap->getWidth() - 1;
	int y2 = y + bitmap->getHeight() - 1;

	if (clipArea(x1, y1, x2, y2)) {

		if (x1 > x2)
            Math::swap(x1, x2);
        if (y1 > y2)
            Math::swap(y1, y2);

        int w = x2 - x1 + 1;
        int h = y2 - y1 + 1;

        driver->writePixels(
			x1, y1,
			w, h,
			bitmap->getPixels(),
			bitmap->getFormat(),
			x1 - x, y1 - y,
			bitmap->getWidth());
	}
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un caracter amb el font i el color actual.
/// \param x: La coordinada X.
/// \param y: La coordinada Y.
/// \param c: El caracter a dibuixar.
///
int Display::drawChar(
    int x,
    int y,
    char c) {

    FontInfo fi;
    font->getFontInfo(fi);
    if ((c >= fi.firstChar) && (c <= fi.lastChar)) {
        CharInfo ci;
        font->getCharInfo(c, ci);
        if (ci.bitmap != nullptr) {
            int cw = (ci.width + 7) / 8;
            x += ci.left;
            y -= ci.top;
            for (int cy = 0; cy < ci.height; cy++) {
                int d = cy * cw;
                for (int cx = 0; cx < ci.width; cx++)
                    if (ci.bitmap[d + (cx / 8)] & (((uint8_t)0x80) >> (cx % 8)))
                        drawPoint(x + cx, y + cy);
                }
        }

        return ci.advance;
    }

    else
        return 0;
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un text amb el font i el color actual.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param s: El text a dibuixar.
/// \param offset: El primer caracter del text
/// \param length: Numero de caracters a dibuixar. -1 si dibuixa fins al final
///                del text.
/// \return L'amplada de la cadena dibuixada en pixels.
///
int Display::drawText(
    int x,
    int y,
    const char *s,
    int offset,
    int length) {

    if (hAlign != HorizontalTextAlign::left) {
        int textWidth = getTextWidth(s, offset, length);
        if (hAlign == HorizontalTextAlign::right)
            x -= textWidth;
        else
            x -= textWidth / 2;
    }

    int sx = x;

    for (int i = offset, j = length; j && s[i]; i++, j--)
        x += drawChar(x, y, s[i]);

    return x - sx;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'amplada d'una cadena de texte.
/// \param s: La cadena de texte.
/// \param offset: El primer caracter del text.
/// \param length: Numero de caracters a mesurar. -1 si es la longitut
///                total del text.
/// \return L'amplada de la cadena en pixels.
///
int Display::getTextWidth(
    const char *s,
    int offset,
    int length) {

    int w = 0;
    for (int i = offset, j = length; j && s[i]; i++, j--)
        w += font->getCharAdvance(s[i]);

    return w;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'alçada d'una cadena de texte.
/// \param s: La cadena de texte.
/// \return L'alçada de la cadena.
///
int Display::getTextHeight(
    const char *s) {

    return font->getFontHeight();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un caracter en emulacio TTY.
/// \param c: El caracter a escriure.
///
void Display::putTTY(
    char c) {

	// TODO: Utilitzar clip
    int screenWidth = driver->getWidth();
    int screenHeight = driver->getHeight();

    switch (ttyState) {
        case 0:
            switch (c) {
                case (char)0xFF:
                    ttyState = 1;
                    break;

                case (char)0xFE:
                    clear(COLOR_Black);
                    break;

                case (char)0xFD:
                    home();
                    cursorX = 0;
                    cursorY = 0;
                    break;

                case '\r':
                    cursorX = 0;
                    break;

                case '\n':
                    cursorX = 0;
                    cursorY += font->getFontHeight();
                    if (cursorY >= screenHeight)
                        cursorY = 0;
                    break;

                default: {
                    CharInfo ci;
                    font->getCharInfo(c, ci);
                    if ((cursorX + ci.advance) >= screenWidth) {
                        cursorX = 0;
                        cursorY += font->getFontHeight();
                        if (cursorY >= screenWidth) {

                            // TODO: fer scroll de pantalla linia a linia
                            return;
                        }
                    }
                    cursorX += drawChar(cursorX, cursorY, c);
                    break;
                }
            }
            break;

        case 1:
            break;

        case 2:
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief Escriu una text en emulacio TTY.
/// \param s: El text a escriure.
/// \param offset: El primer caracter a escriure.
/// \param length: Numero de caracters a escriure. -1 si es tot el text.
///
void Display::putTTY(
    const char *s,
    int offset,
    int length) {

    for (int i = offset, j = length; j && s[i]; i++, j--)
       putTTY(s[i]);
}


/// ----------------------------------------------------------------------
/// \brief Retalla un area.
///
bool Display::clipArea(
    int &x1,
    int &y1,
    int &x2,
    int &y2) {

	unsigned code1 = calcOutCode(x1, y1);
	unsigned code2 = calcOutCode(x2, y2);

	if (!(code1 | code2))
		return true;

	else if (code1 & code2)
		return false;

	else {

		if (x1 < clipX1)
			x1 = clipX1;
		else if (x1 > clipX2)
			x1 = clipX2;

		if (y1 < clipY1)
			y1 = clipY1;
		else if (y1 > clipY2)
			y1 = clipY2;

		if (x2 > clipX2)
			x2 = clipX2;
		else if (x2 < clipX1)
			x2 = clipX1;

		if (y2 > clipY2)
			y2 = clipY2;
		else if (y2 < clipY1)
			y2 = clipY1;

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief Retalla un punt.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \return True si es visible.
///
bool Display::clipPoint(
    int x,
    int y) {

    return (x >= clipX1) && (x <= clipX2) && (y >= clipY1) && (y <= clipY2);
}


/// ----------------------------------------------------------------------
/// \brief Retalla una linia horitzontal.
/// \param x1: Coordinada x inicial.
/// \param x2: Coordinada x final.
/// \paeam y: Coordinada y.
/// \return True si es visible
///
bool Display::clipHLine(
    int &x1,
    int &x2,
    int &y) {

	unsigned code1 = calcOutCode(x1, y);
	unsigned code2 = calcOutCode(x2, y);

	if (!(code1 | code2))
		return true;

	else if (code1 & code2)
		return false;

	else {

		if (x1 < clipX1)
			x1 = clipX1;
		else if (x1 > clipX2)
			x1 = clipX2;

		if (x2 > clipX2)
			x2 = clipX2;
		else if (x2 < clipX1)
			x2 = clipX1;

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief Retalla una linia vertical.
/// \param x: Coordinada x.
/// \param y1: Coordinada y inicial.
/// \paeam y2: Coordinada y final.
/// \return True si es visible.
///
bool Display::clipVLine(
    int &x,
    int &y1,
    int &y2) {

	unsigned code1 = calcOutCode(x, y1);
	unsigned code2 = calcOutCode(x, y2);

	if (!(code1 | code2))
		return true;

	else if (code1 & code2)
		return false;

	else {

		if (y1 < clipY1)
			y1 = clipY1;
		else if (y1 > clipY2)
			y1 = clipY2;

		if (y2 > clipY2)
			y2 = clipY2;
		else if (y2 < clipY1)
			y2 = clipY1;

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief Retalla una linia arbitraria.
/// \param x1: Coordinada X inicial.
/// \param y1: Coordinada Y inicial.
/// \param x2: Coordinada X final.
/// \param y2: Coordinada Y final.
/// \return True si es visible.
///
bool Display::clipLine(
    int &x1,
    int &y1,
    int &x2,
    int &y2) {

	unsigned code1 = calcOutCode(x1, y1);
	unsigned code2 = calcOutCode(x2, y2);

	while (true) {

		if (!(code1 | code2))
			return true;

		else if (code1 & code2)
			return false;

		else {
			int x = 0;
			int y = 0;
			unsigned code = (code1 != 0) ? code1 : code2;

			// Calcula les interseccions
			// x = x1 + (1 / slope) * (y - y1)
			// y = y1 + slope * (x - x1)
			//
			if ((code & TOP) != 0) {
				x = x1 + (x2 - x1) * (clipY2 - y1) / (y2 - y1);
				y = clipY2;
			}

			else if ((code & BOTTOM) != 0) {
				x = x1 + (x2 - x1) * (clipY1 - y1) / (y2 - y1);
				y = clipY1;
			}

			else if ((code & RIGHT) != 0) {
				y = y1 + (y2 - y1) * (clipX2 - x1) / (x2 - x1);
				x = clipX2;
			}

			else if ((code & LEFT) != 0) {
				y = y1 + (y2 - y1) * (clipX1 - x1) / (x2 - x1);
				x = clipX1;
			}

			// NOTE:if you follow this algorithm exactly(at least for c#), then you will fall into an infinite loop
			// in case a line crosses more than two segments. to avoid that problem, leave out the last else
			// if(outcodeOut & LEFT) and just make it else *)

			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if (code == code1) {
				x1 = x;
				y1 = y;
				code1 = calcOutCode(x1, y2);
			}
			else {
				x2 = x;
				y2 = y;
				code2 = calcOutCode(x2, y2);
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief Calcula el 'outcode' per l'algorisme de retall.
/// \param x: Coordinada X del punt.
/// \param y: Coordinada Y del punt.
/// \return El 'outcode' calculat.
///
unsigned Display::calcOutCode(
    int x,
    int y) {

    unsigned code = INSIDE;

    if (x < clipX1)
        code |= LEFT;
    else if (x > clipX2)
        code |= RIGHT;
    if (y < clipY1)
        code |= BOTTOM;
    else if (y > clipY2)
        code |= TOP;

    return code;
}
