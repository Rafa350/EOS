#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosBitmap.h"
#include "Controllers/Display/eosDisplayDriver.h"


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
Graphics::Graphics(
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
Graphics::~Graphics() {

}


/// ----------------------------------------------------------------------
/// \brief Selecciona el color per dibuixar.
/// \param color: El color a seleccionar.
///
void Graphics::setColor(
    const Color &color) {

    this->color = color;
}


/// ----------------------------------------------------------------------
/// \brief Selecciona l'aliniacio del texte.
/// \param hAlign: Aliniacio horitzontal.
/// \param vAlign: Aliniacio vertical.
///
void Graphics::setTextAlign(
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
void Graphics::setFont(
    Font *font) {

    this->font = font;
}


/// ---------------------------------------------------------------------
/// \brief Canvia l'orientacio del display
/// \param orientation: L'orientacio a seleccionar.
/// \remarks Al canviar l'orientacio, es reseteja l'area de retall.
///
void Graphics::setOrientation(
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
void Graphics::setClip(
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
void Graphics::resetClip() {

	clipX1 = 0;
	clipY1 = 0;
	clipX2 = driver->getWidth() - 1;
	clipY2 = driver->getHeight() - 1;
}


/// ----------------------------------------------------------------------
/// \brief Borrat de la pantalla al color especificat.
/// \param color: El color per realitzar el borrat.
///
void Graphics::clear(
    const Color &color) {

	int x1 = 0;
	int y1 = 0;
	int x2 = driver->getWidth() - 1;
	int y2 = driver->getHeight() - 1;

    if (clipArea(x1, y1, x2, y2))
        driver->setPixels(x1, y1, x2 - x1 + 1, y2 - y1 + 1, color);

    cursorX = 0;
    cursorY = 0;
}


/// ----------------------------------------------------------------------
/// \brief Refresca la pantalla.
///
void Graphics::refresh() {

	driver->refresh();
}


/// ----------------------------------------------------------------------
/// \brief Mou el cursor a posicio indicada.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
///
void Graphics::moveTo(
    int x,
    int y) {

    cursorX = x;
    cursorY = y;
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia desde la posicio del cursor a la posicio
///        indicada.
/// \param[in] x: Coordinada X.
/// \param[in] y: Coordinada Y.
///
void Graphics::lineTo(
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
void Graphics::drawPoint(
    int x,
    int y) {

    if (clipPoint(x, y))
        driver->setPixel(x, y, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia.
/// \param[in] x1: Coordinada x del origen.
/// \param[in] y1: Coordinada y del origen.
/// \param[in] x2: Coordinada x del final.
/// \param[in] y2: Coordinada y del final.
///
void Graphics::drawLine(
    int x1,
    int y1,
    int x2,
    int y2) {

    // Es una linea vertical
    //
    if (x1 == x2) {
        if (clipVLine(x1, y1, y2)) {
        	if (y1 > y2)
        		Math::swap(y1, y2);
            driver->setVPixels(x1, y1, y2 - y1 + 1, color);
        }
    }

    // Es una linia horitzontal
    //
    else if (y1 == y2) {
        if (clipHLine(x1, x2, y1)) {
        	if (x1 > x2)
        		Math::swap(x1, x2);
            driver->setHPixels(x1, y1, x2 - x1 + 1, color);
        }
    }

    // No es ni horitzontal ni vertical
    //
    else {
        if (clipLine(x1, y1, x2, y2)) {

            int stepx, stepy;
            int p, incE, incNE;

            int dx = x2 - x1;
            int dy = y2 - y1;

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
/// \brief Dibuixa una linia horitzontal.
/// \param[in] x1: Coordinada X del origen.
/// \param[in] x2: Coordinada X del final.
/// \param[in] y: Coordinada Y
///
void Graphics::drawHLine(int x1, int x2, int y) {

	if (clipHLine(x1, x2, y)) {
		if (x1 > x2)
			Math::swap(x1, x2);
        driver->setHPixels(x1, y, x2 - x1 + 1, color);
	}
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia vertical.
/// \param[in] x: Coordinada X.
/// \param[in] y1: Coordinada Y del origen.
/// \param[in] y2: Coordinada Y del final.
///
void Graphics::drawVLine(int x, int y1, int y2) {

	if (clipVLine(x, y1, y2)) {
		if (y1 > y2)
			Math::swap(y1, y2);
        driver->setVPixels(x, y1, y2 - y1 + 1, color);
	}
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un rectangle buit.
/// \param[in] x1: Coordinada x del origen.
/// \param[in] y1: Coordinada y del origen.
/// \param[in] x2: Coordinada x del final.
/// \param[in] y2: Coordinada y del final.
///
void Graphics::drawRectangle(
    int x1,
    int y1,
    int x2,
    int y2) {

	drawHLine(x1, x2, y1);
	drawHLine(x1, x2, y2);
	drawVLine(x1, y1, y2);
	drawVLine(x2, y1, y2);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un triangle buit.
/// \param[in] x1: Coordinada x del primer punt
/// \param[in] y1: Coordinada y del primer punt
/// \param[in] x2: Coordinada x del segon punt.
/// \param[in] y2: Coordinada y del segon punt.
/// \param[in] x3: Coordinada x del tercer punt.
/// \param[in] y3: Coordinada y del tercer punt.
///
void Graphics::drawTriangle(
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
/// \param[in] cx: Coordinada X del centre.
/// \param[in] cy: Coordinada Y del centre.
/// \param[in] r: Radi del cercle.
///
void Graphics::drawCircle(
    int cx,
    int cy,
    int r) {

	int x = r;
    int y = 0;
    int d = 1 - x;

    while (y <= x) {
        drawPoint(cx + x, cy + y);
        drawPoint(cx - x, cy + y);
        drawPoint(cx - x, cy - y);
        drawPoint(cx + x, cy - y);
        drawPoint(cx + y, cy + x);
        drawPoint(cx - y, cy + x);
        drawPoint(cx - y, cy - x);
        drawPoint(cx + y, cy - x);
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
/// \brief Dibuixa un rectangle omplert.
/// \param[in] x1: Coordinada X inicial.
/// \param[in] y1: Coordinada Y inicial
/// \param[in] x2: Coordinada X final.
/// \param[in] y2: Coordinada Y final.
///
void Graphics::fillRectangle(
    int x1,
    int y1,
    int x2,
    int y2) {

    if (x1 > x2)
        Math::swap(x1, x2);
    if (y1 > y2)
        Math::swap(y1, y2);

    if (clipArea(x1, y1, x2, y2))
         driver->setPixels(x1, y1, x2 - x1 + 1, y2 - y1 + 1, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un cercle omplert.
/// \param[in] cx: Coordinada X del centre.
/// \param[in] cy: Coordinada Y del centre.
/// \param[in] r: Radi del cercle.
///
void Graphics::fillCircle(
    int cx,
    int cy,
    int r) {

	int x = r;
    int y = 0;
    int d = 1 - x;

    while (y <= x) {

        drawHLine(cx - x, cx + x, cy - y);
        drawHLine(cx - x, cx + x, cy + y);
        drawHLine(cx - y, cx + y, cy - x);
        drawHLine(cx - y, cx + y, cy + x);

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
/// \param[in] x: Coordinada X.
/// \param[in] y: Coordinada Y.
/// \param[in] bitmap: El bitmap
///
void Graphics::drawBitmap(
    int x,
    int y,
    const Bitmap *bitmap) {

	int x1 = x;
	int y1 = y;
	int x2 = x + bitmap->getWidth() - 1;
	int y2 = y + bitmap->getHeight() - 1;

	if (clipArea(x1, y1, x2, y2)) {

        int w = x2 - x1 + 1;
        int h = y2 - y1 + 1;

        if ((w > 0) && (h > 0))
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
/// \param[in] x: La coordinada X.
/// \param[in] y: La coordinada Y.
/// \param[in] c: El caracter a dibuixar.
///
int Graphics::drawChar(
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
/// \param[in] x: Coordinada X.
/// \param[in] y: Coordinada Y.
/// \param[in] s: El text a dibuixar.
/// \param[in] offset: El primer caracter del text
/// \param[in] length: Numero de caracters a dibuixar. -1 si dibuixa fins al final
///                del text.
/// \return L'amplada de la cadena dibuixada en pixels.
///
int Graphics::drawText(
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
/// \param[in] s: La cadena de texte.
/// \param[in] offset: El primer caracter del text.
/// \param[in] length: Numero de caracters a mesurar. -1 si es la longitut
///                total del text.
/// \return L'amplada de la cadena en pixels.
///
int Graphics::getTextWidth(
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
/// \param[in] s: La cadena de texte.
/// \return L'alçada de la cadena.
///
int Graphics::getTextHeight(
    const char *s) {

    return font->getFontHeight();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un caracter en emulacio TTY.
/// \param[in] c: El caracter a escriure.
///
void Graphics::putTTY(
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
/// \param[in] s: El text a escriure.
/// \param[in] offset: El primer caracter a escriure.
/// \param[in] length: Numero de caracters a escriure. -1 si es tot el text.
///
void Graphics::putTTY(
    const char *s,
    int offset,
    int length) {

    for (int i = offset, j = length; j && s[i]; i++, j--)
       putTTY(s[i]);
}


/// ----------------------------------------------------------------------
/// \brief Retalla un area.
///
bool Graphics::clipArea(
    int &x1,
    int &y1,
    int &x2,
    int &y2) {

	unsigned code1 = calcOutCode(x1, y1);
	unsigned code2 = calcOutCode(x2, y2);

	// Comprova si es dins
	//
	if (!(code1 | code2))
		return true;

	// Comprova si es fora
	//
	else if (code1 & code2)
		return false;

	// Ni a dins ni a fora
	//
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
/// \param[in] x: Coordinada X.
/// \param[in] y: Coordinada Y.
/// \return True si es visible.
///
bool Graphics::clipPoint(
    int x,
    int y) {

    return (x >= clipX1) && (x <= clipX2) && (y >= clipY1) && (y <= clipY2);
}


/// ----------------------------------------------------------------------
/// \brief Retalla una linia horitzontal.
/// \param x1: Coordinada x inicial.
/// \param x2: Coordinada x final.
/// \param y: Coordinada y.
/// \return True si es visible
///
bool Graphics::clipHLine(
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
bool Graphics::clipVLine(
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
bool Graphics::clipLine(
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
unsigned Graphics::calcOutCode(
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
