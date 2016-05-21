#include "Controllers/Display/eosDisplay.hpp"
#include "Controllers/Display/eosFont.hpp"


using namespace eos;


extern const unsigned char *fontArial10pt;
extern const unsigned char *fontArial12pt;
extern const unsigned char *fontArial24pt;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param driver: Driver del display
///
Display::Display(
    IDisplayDriver *_driver):
    driver(_driver),
    color(0),
    xCursor(0),
    yCursor(0),
    ttyState(0),
    font(new Font(fontArial24pt)) {
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
    Color _color) {
    
    color = _color;
}


/// ----------------------------------------------------------------------
/// \brief Selecciona el font per dibuixar caracters i cadenes de texte.
/// \param font: El font a seleccionar.
///
void Display::setFont(
    Font *_font) {
    
    font = _font;
    font->getFontInfo(fontInfo);
}


/// ----------------------------------------------------------------------
/// \brief Borrat de la pantalla al color especificat.
/// \param color: El color per realitzar el borrat.
///
void Display::clear(
    Color color) {

    driver->clear(color);
    xCursor = 0;
    yCursor = 0;
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
    
    xCursor = x;
    yCursor = y;
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
    
    drawLine(xCursor, yCursor, x, y);
    xCursor = x;
    yCursor = y;
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
   
    int stepx, stepy;
    int dx, dy, p, incE, incNE;
    
    if (x1 == x2)
        driver->setVPixels(x1, y1, y2 - y1, color);
	
    else if (y1 == y2)
        driver->setHPixels(x1, y1, x2 - x1, color);
	
    else {
		
        dx = x2 - x1;
        dy = y2 - y1;
 
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


/// ----------------------------------------------------------------------
/// \brief Dibuixa un rectangle buit.
/// \param x1: Coordinada x deo origen.
/// \param y1: Coordinada y del origen.
/// \param x2: Coordinada x del final.
/// \param y2: Coordinada y del final.
///
void Display::drawRectangle(
    int x1, 
    int y1, 
    int x2, 
    int y2) {
    
    driver->setHPixels(x1, y1, x2 - x1, color);
    driver->setHPixels(x1, y2, x2 - x1, color);
    driver->setVPixels(x1, y1, y2 - y1, color);
    driver->setVPixels(x2, y1, y2 - y1, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un cercle buit.
/// \param cx: Coordinada X del centre.
/// \param cy: Coordinada Y del centre.
/// \param r: Radi del cercle.
///
void Display::drawCircle(
    int cx, 
    int cy, 
    int r) {

    int x = r;
    int y = 0;
    int d = 1 - x;  

    while (y <= x) {
        driver->setPixel(cx + x, cy + y, color);
        driver->setPixel(cx - x, cy + y, color);
        driver->setPixel(cx - x, cy - y, color);
        driver->setPixel(cx + x, cy - y, color);
        driver->setPixel(cx + y, cy + x, color);
        driver->setPixel(cx - y, cy + x, color);
        driver->setPixel(cx - y, cy - x, color);
        driver->setPixel(cx + y, cy - x, color);
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
void Display::fillRectangle(
    int x1, 
    int y1, 
    int x2, 
    int y2) {

    if (x1 > x2) {
        int v = x1;
        x1 = x2;
        x2 = v;
    }

    while (x1 <= x2)
        driver->setVPixels(x1++, y1, y2 - y1, color);
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
        driver->setVPixels(cx + x, cy - y, y + y + 1, color);
        driver->setVPixels(cx - x, cy - y, y + y + 1, color);
        driver->setVPixels(cx + y, cy - x, x + x + 1, color);
        driver->setVPixels(cx - y, cy - x, x + x + 1, color);
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
/// \brief Dibuixa un bitmap.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
///
void Display::drawBitmap1BPP(
    int x, 
    int y, 
    const uint8_t *bitmap, 
    int sx, 
    int sy, 
    Color color) {
    
    
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

    int cx, cy, cw, d;
    FontInfo fi;
    CharInfo ci;

    font->getFontInfo(fi);
    if ((c >= fi.firstChar) && (c <= fi.lastChar)) {
        font->getCharInfo(c, ci);
        if (ci.bitmap != nullptr) {
            cw = (ci.width + 7) >> 3;
            x += ci.left;
            y -= ci.top;
            for (cy = 0; cy < ci.height; cy++) {
                d = cy * cw;
                for (cx = 0; cx < ci.width; cx++)
                    if (ci.bitmap[d + (cx >> 3)] & (0x80 >> (cx & 7)))
                        driver->setPixel(x + cx, y + cy, color);
                }
        }

        return ci.advance;
    }

    else
        return 0;
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una cadena de texte amb el font i el color actual.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param s: La cadena a dibuixar.
/// \param offset: El primer caracter a dibuixar
/// \param length: Numero de caracters a dibuixar
///
int Display::drawString(
    int x, 
    int y, 
    const char *s,
    int offset,
    int length) {
    
    char c;
    int sx = x;
    while ((c = *s++) != '\0')
        x += drawChar(x, y, c);

    return x - sx;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'amplada d'una cadena de texte.
/// \param s: La cadena de texte.
/// \return L'amplada de la cadena en pixels.
///
int Display::getTextWidth(
    const char *s) {
    
    char c;
    CharInfo ci;

    int w = 0;
    while ((c = *s++) != '\0') {
        font->getCharInfo(c, ci);
        w += ci.advance;
    }

    return w;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'alçada d'una cadena de texte.
/// \param s: La cadena de texte.
/// \return L'alçada de la cadena.
///
int Display::getTextHeight(
    const char *s) {
    
    return fontInfo.height;
}


/// ----------------------------------------------------------------------
/// \brief Escriu un caracter en emulacio TTY.
/// \param c: El caracter a escriure.
///
void Display::putTTY(
    char c) {

    switch (ttyState) {
        case 0:
            switch (c) {
                case (char)0xFF:
                    ttyState = 1;
                    break;

                case (char)0xFE:
                    clear(0);
                    break;
            
                case (char)0xFD:
                    home();
                    xCursor = 0;
                    yCursor = 0;
                    break;

                case '\r':
                    xCursor = 0;
                    break;

                case '\n':
                    xCursor = 0;
                    yCursor += fontInfo.height;
                    if (yCursor >= driver->getYSize())
                        yCursor = 0;
                    break;
            
                default: {
                    CharInfo ci;
                    font->getCharInfo(c, ci);
                    if ((xCursor + ci.advance) >= driver->getXSize()) {
                        xCursor = 0;
                        yCursor += fontInfo.height;
                        if (yCursor >= driver->getXSize()) {

                            // TODO: fer scroll de pantalla linia a linia
                            return;
                        }
                    }
                    xCursor += drawChar(xCursor, yCursor, c);
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
/// \brief Escriu una cadena de texte en emulacio TTY.
/// \param s: La cadena a escriure.
///
void Display::putTTY(
    const char *s) {
    
    char c;
    while ((c = *s++) != '\0')
        putTTY(c);
}


/// ----------------------------------------------------------------------
/// \brief Escriu una cadena de texte en emulacio TTY.
/// \param s: La cadena a escriure.
/// \param length: Numero de caracters a escriure com a maxim.
///
void Display::putTTY(
    const char *s,
    int length) {
    
    char c;
    while (((c = *s++) != '\0') && (length-- > 0))
        putTTY(c);
}
