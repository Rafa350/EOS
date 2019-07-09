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
    color(COLOR_Black),
    font(nullptr),
    hAlign(HorizontalTextAlign::left),
    vAlign(VerticalTextAlign::bottom) {

	resetClip();
	resetTransformation();
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

	// Transforma les coordinades
	//
	state.ct.apply(x1, y1);
	state.ct.apply(x2, y2);

	// Normalitzacio de coordinades
	//
    if (x1 > x2)
        Math::swap(x1, x2);
    if (y1 > y2)
        Math::swap(y1, y2);

    // Asigna la nova area de retall
    //
	state.clipX1 = Math::max(0, x1);
	state.clipY1 = Math::max(0, y1);
	state.clipX2 = Math::min(x2, driver->getWidth() - 1);
	state.clipY2 = Math::min(y2, driver->getHeight() - 1);
}


/// ----------------------------------------------------------------------
/// \brief Elimina l'area de retall.
///
void Graphics::resetClip() {

	state.clipX1 = 0;
	state.clipY1 = 0;
	state.clipX2 = INT32_MAX;
	state.clipY2 = INT32_MAX;
}


/// ----------------------------------------------------------------------
/// \brief Asigna la transformacio.
/// \param t: La transformacio.
/// \param combine: True si cal combinar la transformacio amb l'actual.
///
void Graphics::setTransformation(
	const Transformation &t,
	bool combine) {

	// Asigna la nova transformacio
	//
	state.ct = t;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza la transformacio.
///
void Graphics::resetTransformation() {

	state.ct.identity();
}


/// ----------------------------------------------------------------------
/// \brief Salva l'estat.
///
void Graphics::push() {

	if (!stack.isFull())
		stack.push(state);
}


/// ----------------------------------------------------------------------
/// \brief Recupera l'estat.
///
void Graphics::pop() {

	if (!stack.isEmpty()) {
		state = stack.peek();
		stack.pop();
	}
}


/// ----------------------------------------------------------------------
/// \brief Borrat de la pantalla al color especificat.
/// \param color: El color per realitzar el borrat.
///
void Graphics::clear(
    const Color &color) const {

	int x1 = 0;
	int y1 = 0;
	int x2 = driver->getWidth() - 1;
	int y2 = driver->getHeight() - 1;

    if (clipArea(x1, y1, x2, y2))
        driver->setPixels(x1, y1, x2 - x1 + 1, y2 - y1 + 1, color);
}


/// ----------------------------------------------------------------------
/// \brief Refresca la pantalla.
///
void Graphics::refresh() const {

	driver->refresh();
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un pixel.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
///
void Graphics::drawPoint(
    int x,
    int y) const {

	state.ct.apply(x, y);

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
void Graphics::drawLine(
    int x1,
    int y1,
    int x2,
    int y2) const {

	// Transforma les coordinades
	//
	state.ct.apply(x1, y1);
	state.ct.apply(x2, y2);

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

            else if (dx < dy) {
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

            // Es una linia diagonal
            //
            else {
                while (y1 != y2) {
                    y1 += stepy;
                    x1 += stepx;
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
void Graphics::drawRectangle(
    int x1,
    int y1,
    int x2,
    int y2) const {

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
void Graphics::drawTriangle(
    int x1,
    int y1,
    int x2,
    int y2,
    int x3,
    int y3) const {

	drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un cercle buit.
/// \param cx: Coordinada X del centre.
/// \param cy: Coordinada Y del centre.
/// \param r: Radi del cercle.
///
void Graphics::drawCircle(
    int cx,
    int cy,
    int r) const {

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
/// \param x1: Coordinada X inicial.
/// \param y1: Coordinada Y inicial
/// \param x2: Coordinada X final.
/// \param y2: Coordinada Y final.
///
void Graphics::fillRectangle(
    int x1,
    int y1,
    int x2,
    int y2) const {

	// Transforma les coordinades
	//
	state.ct.apply(x1, y1);
	state.ct.apply(x2, y2);

	// Normalitza els punts.
	//
    if (x1 > x2)
        Math::swap(x1, x2);
    if (y1 > y2)
        Math::swap(y1, y2);

    // Dibuixa el rectangle si es visible
    //
    if (clipArea(x1, y1, x2, y2))
         driver->setPixels(x1, y1, x2 - x1 + 1, y2 - y1 + 1, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un cercle omplert.
/// \param cx: Coordinada X del centre.
/// \param cy: Coordinada Y del centre.
/// \param r: Radi del cercle.
///
void Graphics::fillCircle(
    int cx,
    int cy,
    int r) const {

	state.ct.apply(cx, cy);

	int x = r;
    int y = 0;
    int d = 1 - x;

    while (y <= x) {

    	int x1;
    	int x2;
    	int y1;

    	x1 = cx - x;
    	y1 = cy - y;
    	x2 = cx + x;
    	if (clipHLine(x1, x2, y1))
    		driver->setPixels(x1, y1, x2 - x1 + 1, 1, color);

        x1 = cx - x;
        y1 = cy + y;
    	x2 = cx + x;
    	if (clipHLine(x1, x2, y1))
    		driver->setPixels(x1, y1, x2 - x1 + 1, 1, color);

        x1 = cx - y;
        y1 = cy - x;
    	x2 = cx + y;
    	if (clipHLine(x1, x2, y1))
    		driver->setPixels(x1, y1, x2 - x1 + 1, 1, color);

        x1 = cx - y;
        y1 = cy + x;
    	x2 = cx + y;
    	if (clipHLine(x1, x2, y1))
    		driver->setPixels(x1, y1, x2 - x1 + 1, 1, color);

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
void Graphics::drawBitmap(
    int x,
    int y,
    const Bitmap *bitmap) const {

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
/// \param x: La coordinada X.
/// \param y: La coordinada Y.
/// \param c: El caracter a dibuixar.
///
int Graphics::drawChar(
    int x,
    int y,
    char c) const {

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
int Graphics::drawText(
    int x,
    int y,
    const char *s,
    int offset,
    int length) const {

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
int Graphics::getTextWidth(
    const char *s,
    int offset,
    int length) const {

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
    const char *s) const {

    return font->getFontHeight();
}


/// ----------------------------------------------------------------------
/// \brief Retalla un area.
///
bool Graphics::clipArea(
    int &x1,
    int &y1,
    int &x2,
    int &y2) const {

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

	    if (x1 < state.clipX1)
			x1 = state.clipX1;
		else if (x1 > state.clipX2)
			x1 = state.clipX2;

		if (y1 < state.clipY1)
			y1 = state.clipY1;
		else if (y1 > state.clipY2)
			y1 = state.clipY2;

		if (x2 > state.clipX2)
			x2 = state.clipX2;
		else if (x2 < state.clipX1)
			x2 = state.clipX1;

		if (y2 > state.clipY2)
			y2 = state.clipY2;
		else if (y2 < state.clipY1)
			y2 = state.clipY1;

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief Retalla un punt.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \return True si es visible.
///
bool Graphics::clipPoint(
    int x,
    int y) const {

    return
    	(x >= state.clipX1) && (x <= state.clipX2) &&
    	(y >= state.clipY1) && (y <= state.clipY2);
}


/// ----------------------------------------------------------------------
/// \brief Retalla una linia horitzontal.
/// \param x1: Coordinada X dreta.
/// \param x2: Coordinada X esquerra.
/// \param y: Coordinada Y.
/// \return True si es visible.
///
bool Graphics::clipHLine(
	int &x1,
	int &x2,
	int y) const {

	if ((y >= state.clipY1) && (y <= state.clipY2)) {

		x1 = Math::max(state.clipX1, x1);
		x2 = Math::min(x2, state.clipX2);

		return x1 < x2;
	}
	else
		return false;
}


/// ----------------------------------------------------------------------
/// \brief Retalla una linia arbitraria.
/// \param x1: Coordinada X inicial.
/// \param y1: Coordinada Y inicial.
/// \param x2: Coordinada X final.
/// \param y2: Coordinada Y final.
/// \return True si es visible.
///
#if 0
bool Graphics::clipLine(
    int &x1,
    int &y1,
    int &x2,
    int &y2) const {

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
				x = x1 + (x2 - x1) * (state.clipY2 - y1) / (y2 - y1);
				y = state.clipY2;
			}

			else if ((code & BOTTOM) != 0) {
				x = x1 + (x2 - x1) * (state.clipY1 - y1) / (y2 - y1);
				y = state.clipY1;
			}

			else if ((code & RIGHT) != 0) {
				y = y1 + (y2 - y1) * (state.clipX2 - x1) / (x2 - x1);
				x = state.clipX2;
			}

			else if ((code & LEFT) != 0) {
				y = y1 + (y2 - y1) * (state.clipX1 - x1) / (x2 - x1);
				x = state.clipX1;
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
/// \brief Calcula el 'outcode' d'un punt per l'algorisme de retall.
/// \param x: Coordinada X del punt.
/// \param y: Coordinada Y del punt.
/// \return El 'outcode' calculat.
///
unsigned Graphics::calcOutCode(
	int x,
	int y) const {

	int code = INSIDE;

	if (x < state.clipX1)
        code |= LEFT;
    else if (x > state.clipX2)
        code |= RIGHT;

	if (y < state.clipY1)
        code |= BOTTOM;
    else if (y > state.clipY2)
        code |= TOP;

    return code;
}

#else 


/// ----------------------------------------------------------------------
/// \brief Retalla una linia arbitraria. Amb l'algorisme Liang-Barsky.
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
    int &y2) const {

    bool clipTest(int p, int q, int &t1, int &t2);
    
    if (((x1 < state.clipX1) && (x2 < state.clipX1)) ||
        ((x1 > state.clipX2) && (x2 > state.clipX2)) ||
        ((y1 < state.clipY1) && (y2 < state.clipY1)) ||
        ((y1 > state.clipY2) && (y2 > state.clipY2)))
        return false;
        
    int t1 = 0;
    int t2 = 1 << 10;
    
    int dx = x2 - x1;    
    if (!clipTest(-dx, x1 - state.clipX1, t1, t2))
        return false;    
    if (!clipTest(dx, state.clipX2 - x1, t1, t2))
        return false;
    
    int dy = y2 - y1;
    if (!clipTest(-dy, y1 - state.clipY2, t1, t2))
        return false;
    if (!clipTest(dy, state.clipY1 - y1, t1, t2))
        return false;
    
    if (t2 < (1 << 10)) {
        x2 = x1 + ((t2 * dx) >> 10);
        y2 = y1 + ((t2 * dy) >> 10);
    }
    if (t1 > 0) {
        x1 = x1 + ((t1 * dx) >> 10);
        y1 = y1 + ((t1 * dy) >> 10);
    }
    
    return true;
}

static inline bool clipTest(
    int p,
    int q,
    int &t1,
    int &t2) {

    int r;

    if (p < 0) {
        if (q < 0) {
            r = (q << 10) / p;
            if (r > t2)
                return false;
            else if (r > t1)
                t1 = r;
        }
    }

    else if (p > 0) {
        if (q < p) {
            r = (q << 10) / p;
            if (r < t1)
                return false;
            else if (r < t2)
                t2 = r;
        }
    }

    else
        if (q < 0)
            return false;

    return true;
}


#endif
