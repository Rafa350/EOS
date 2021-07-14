#include "eos.h"
#include "eosAssert.h"
#include "System/eosString.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un caracter amb el font i el color actual.
/// \param    x: La coordinada X.
/// \param    y: La coordinada Y. El origen es a la linia base.
/// \param    color: Color.
/// \param    c: El caracter a dibuixar.
///
int Graphics::drawChar(
    int x,
    int y,
	Color color,
    char c) const {

    FontInfo fi;
    _font.getFontInfo(fi);

    if ((c >= fi.firstChar) && (c <= fi.lastChar)) {

    	CharInfo ci;
        _font.getCharInfo(c, ci);

        if (ci.bitmap != nullptr) {
            int cw = (ci.width + 7) / 8;
            x += ci.left;
            y -= ci.top;
            for (int cy = 0; cy < ci.height; cy++) {
                int d = cy * cw;
                for (int cx = 0; cx < ci.width; cx++)
                    if (ci.bitmap[d + (cx / 8)] & (((uint8_t)0x80) >> (cx % 8)))
                        drawPoint(x + cx, y + cy, color);
            }
        }

        return ci.advance;
    }

    else
        return 0;
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un text amb el font i el color actual.
/// \param    x      : Coordinada X.
/// \param    y      : Coordinada Y.
/// \param    color  : Color.
/// \param    text   : El text a dibuixar.
/// \param    offset : El primer caracter del text
/// \param    length : Numero de caracters a dibuixar. -1 si dibuixa fins al final
///                    del text.
/// \return   L'amplada de la cadena dibuixada en pixels.
///
int Graphics::drawText(
    int x,
    int y,
	Color color,
    const String &text,
    unsigned offset,
    unsigned length) const {

    if (_state.hAlign != HorizontalTextAlign::left) {
        int textWidth = getTextWidth(text, offset, length);
        if (_state.hAlign == HorizontalTextAlign::right)
            x -= textWidth;
        else
            x -= textWidth / 2;
    }

    if (_state.vAlign != VerticalTextAlign::top) {
    	int textHeight = _font.getFontHeight();
    	if (_state.vAlign == VerticalTextAlign::bottom)
    		y += textHeight;
    	else
    		y += textHeight / 2;
    }

    int sx = x;

    for (unsigned i = offset, j = length; j && text[i]; i++, j--)
        x += drawChar(x, y, color, text[i]);

    return x - sx;
}

