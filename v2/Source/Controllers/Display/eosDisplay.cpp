#include "Controllers/Display/eosDisplay.h"
#include "Controllers/Display/eosFont.h"

#include <stdint.h>


using namespace eos;


extern const unsigned char *fontConsolas14pt;

const uint8_t inside = 0;
const uint8_t left = 1;
const uint8_t right = 2;
const uint8_t bottom = 4;
const uint8_t top = 8;


/// ----------------------------------------------------------------------
/// \brief Intercamvia dues variables A i B.
/// \param a: Variable A.
/// \param b: Variable B.
///
inline void swap(
    int16_t &a, 
    int16_t &b) {
    
    int16_t t = a; 
    a = b; 
    b = t;
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param driver: Driver del display
///
Display::Display(
    IDisplayDriver *driver) :
    
    driver(driver),
    color(COLOR_Black),
    screenWidth(driver->getWidth()),
    screenHeight(driver->getHeight()),
    cursorX(0),
    cursorY(0),
    clipEnabled(false),
    ttyState(0),
    font(nullptr),
    vAlign(VerticalTextAlign::bottom),
    hAlign(HorizontalTextAlign::left) {
    
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
    Color color) {
    
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


/// ----------------------------------------------------------------------
/// \bried Selecciona la regio de retall.
/// \param x1: Coordinada X esquerra.
/// \param y1: Coodinada Y superior.
/// \param x2: Coordinada X dreta.
/// \param y2: Coordinada Y inferior.
///
void Display::setClip(
    int16_t x1, 
    int16_t y1, 
    int16_t x2, 
    int16_t y2) {
    
    if (x1 > x2) 
        swap(x1, x2);
    if (y1 > y2) 
        swap(y1, y2);
    
    clipX1 = x1 < 0 ? 0 : x1;
    clipY1 = y1 < 0 ? 0 : y1;
    clipX2 = x2 >= screenWidth ? screenWidth - 1 : x2;
    clipY2 = y2 >= screenHeight ? screenHeight - 1 : y2;
    
    clipEnabled = true;
}


/// ----------------------------------------------------------------------
/// \brief Reseteja la regio de retall.
///
void Display::resetClip() {
    
    clipEnabled = false;
}


/// ----------------------------------------------------------------------
/// \brief Borrat de la pantalla al color especificat.
/// \param color: El color per realitzar el borrat.
///
void Display::clear(
    Color color) {

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
    int16_t x, 
    int16_t y) {
    
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
    int16_t x,
    int16_t y) {
    
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
    int16_t x, 
    int16_t y) {

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
    int16_t x1, 
    int16_t y1, 
    int16_t x2, 
    int16_t y2) {
   
    // Calcula les deltas
    //
    int16_t dx = x2 - x1;
    int16_t dy = y2 - y1;
    
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
		
            int16_t stepx, stepy;
            int16_t p, incE, incNE;

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
    int16_t x1, 
    int16_t y1, 
    int16_t x2, 
    int16_t y2) {

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
    int16_t x1, 
    int16_t y1, 
    int16_t x2, 
    int16_t y2, 
    int16_t x3, 
    int16_t y3) {

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
void Display::drawCircle(
    int16_t cx, 
    int16_t cy, 
    int16_t r) {

    int16_t x = r;
    int16_t y = 0;
    int16_t d = 1 - x;  

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
void Display::fillRectangle(
    int16_t x1, 
    int16_t y1, 
    int16_t x2, 
    int16_t y2) {

    if (clipArea(x1, y1, x2, y2)) {
        if (x1 > x2) 
            swap(x1, x2);
        if (y1 > y2) 
            swap(y1, y2);
        driver->setPixels(x1, y1, x2 - x1 + 1, y2 -y1 + 1, color);
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un cercle omplert.
/// \param cx: Coordinada X del centre.
/// \param cy: Coordinada Y del centre.
/// \param r: Radi del cercle.
///
void Display::fillCircle(
    int16_t cx, 
    int16_t cy, 
    int16_t r) {

    int16_t x = r;
    int16_t y = 0;
    int16_t d = 1 - x;  

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
/// \brief Dibuixa un bitmap.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param bitmap: El bitmap
/// \param width: Amplada del bitmap.
/// \param height: Alçada del bitmap.
///
void Display::drawBitmap1BPP(
    int16_t x, 
    int16_t y, 
    const uint8_t *bitmap, 
    int16_t width, 
    int16_t height, 
    Color color) {
    
    
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un caracter amb el font i el color actual.
/// \param x: La coordinada X.
/// \param y: La coordinada Y.
/// \param c: El caracter a dibuixar.
///
int16_t Display::drawChar(
    int16_t x, 
    int16_t y, 
    char c) {

    FontInfo fi;
    font->getFontInfo(fi);
    if ((c >= fi.firstChar) && (c <= fi.lastChar)) {
        CharInfo ci;
        font->getCharInfo(c, ci);
        if (ci.bitmap != nullptr) {
            int16_t cw = (ci.width + 7) >> 3;
            x += ci.left;
            y -= ci.top;
            for (int16_t cy = 0; cy < ci.height; cy++) {
                int d = cy * cw;
                for (int16_t cx = 0; cx < ci.width; cx++)
                    if (ci.bitmap[d + (cx >> 3)] & (0x80 >> (cx & 7)))
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
int16_t Display::drawText(
    int16_t x, 
    int16_t y, 
    const char *s,
    int16_t offset,
    int16_t length) {
    
    if (hAlign != HorizontalTextAlign::left) {
        int16_t textWidth = getTextWidth(s, offset, length);
        if (hAlign == HorizontalTextAlign::right)
            x -= textWidth;
        else
            x -= textWidth / 2;
    }
    
    int16_t sx = x;

    for (int16_t i = offset, j = length; j && s[i]; i++, j--)
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
int16_t Display::getTextWidth(
    const char *s,
    int16_t offset,
    int16_t length) {
    
    int16_t w = 0;
    for (int16_t i = offset, j = length; j && s[i]; i++, j--) 
        w += font->getCharAdvance(s[i]);

    return w;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'alçada d'una cadena de texte.
/// \param s: La cadena de texte.
/// \return L'alçada de la cadena.
///
int16_t Display::getTextHeight(
    const char *s) {
    
    return font->getFontHeight();
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
    int16_t offset,
    int16_t length) {
    
    for (int16_t i = offset, j = length; j && s[i]; i++, j--)
       putTTY(s[i]);
}


/// ----------------------------------------------------------------------
/// \brief Retalla un area.
///
bool Display::clipArea(
    int16_t &x1, 
    int16_t &y1, 
    int16_t &x2, 
    int16_t &y2) {
    
    if (clipEnabled) {
    
        uint8_t code1 = calcOutCode(x1, y1);
        uint8_t code2 = calcOutCode(x2, y2);
        
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
    else
        return true;
}


/// ----------------------------------------------------------------------
/// \brief Retalla un punt.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \return True si es visible.
///
bool Display::clipPoint(
    int16_t x, 
    int16_t y) {
    
    if (clipEnabled)
        return (x >= clipX1) && (x <= clipX2) && (y >= clipY1) && (y <= clipY2);
    else
        return true;
}


/// ----------------------------------------------------------------------
/// \brief Retalla una linia horitzontal.
/// \param x1: Coordinada x inicial.
/// \param x2: Coordinada x final.
/// \paeam y: Coordinada y.
/// \return True si es visible
///
bool Display::clipHLine(
    int16_t &x1, 
    int16_t &x2, 
    int16_t &y) {
    
    if (clipEnabled) {
        
        uint8_t code1 = calcOutCode(x1, y);
        uint8_t code2 = calcOutCode(x2, y);
        
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
    else
        return true;
}


/// ----------------------------------------------------------------------
/// \brief Retalla una linia vertical.
/// \param x: Coordinada x.
/// \param y1: Coordinada y inicial.
/// \paeam y2: Coordinada y final.
/// \return True si es visible.
///
bool Display::clipVLine(
    int16_t &x, 
    int16_t &y1, 
    int16_t &y2) {

    if (clipEnabled) {
        
        uint8_t code1 = calcOutCode(x, y1);
        uint8_t code2 = calcOutCode(x, y2);
        
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
    else
        return true;
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
    int16_t &x1,
    int16_t &y1,
    int16_t &x2,
    int16_t &y2) {    
    
    if (clipEnabled) {

        uint8_t code1 = calcOutCode(x1, y1);
        uint8_t code2 = calcOutCode(x2, y2);

        while (true) {

            if (!(code1 | code2))
                return true;

            else if (code1 & code2)
                return false;

            else {
                int x = 0;
                int y = 0;
                uint8_t code = (code1 != 0) ? code1 : code2;

                // Calcula les interseccions
                // x = x1 + (1 / slope) * (y - y1)
                // y = y1 + slope * (x - x1)
                //
                if ((code & top) != 0) {
                    x = x1 + (x2 - x1) * (clipY2 - y1) / (y2 - y1);
                    y = clipY2;
                }

                else if ((code & bottom) != 0) {
                    x = x1 + (x2 - x1) * (clipY1 - y1) / (y2 - y1);
                    y = clipY1;
                }

                else if ((code & right) != 0) {
                    y = y1 + (y2 - y1) * (clipX2 - x1) / (x2 - x1);
                    x = clipX2;
                }

                else if ((code & left) != 0) {
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
    else
        return true;
}


/// ----------------------------------------------------------------------
/// \brief Cancula el 'outcode' per l'algorisme de retall.
/// \param x: Coordinada X del punt.
/// \param y: Coordinada Y del punt.
/// \return El 'outcode' calculat.
///
uint8_t Display::calcOutCode(
    int16_t x, 
    int16_t y) {
    
    uint8_t code = inside;   
    
    if (x < clipX1)
        code |= left;
    else if (x > clipX2)
        code |= right;    
    if (y < clipY1)
        code |= bottom;
    else if (y > clipY2)
        code |= top;
    
    return code;
}
