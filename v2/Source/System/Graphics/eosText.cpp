#include "eos.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosBrush.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosText.h"


using namespace eos;


static constexpr Color defaultBackground = Colors::transparent;
static constexpr Color defaultForeground = Colors::black;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte amb els valors per defecte.
///
Text::Text():

	_text(""),
	_font(Font()),
	_background(Brush(BrushStyle::solid, defaultBackground)),
	_foreground(Brush(BrushStyle::solid, defaultForeground)),
	_align(TextAlign::center),
	_width(0),
	_height(0) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    font: El font.
/// \param    align: L'aliniacio del text.
///
Text::Text(
	const Font &font,
	TextAlign align):

	_text(""),
	_font(font),
	_background(Brush(BrushStyle::solid, defaultBackground)),
	_foreground(Brush(BrushStyle::solid, defaultForeground)),
	_align(align),
	_width(0),
	_height(0) {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    font: El font.
/// \param    align: L'aliniacio del text.
/// \param    text: El text.
///
Text::Text(
	const Font& font,
	TextAlign align,
	const char *text):

	_text(text),
	_font(font),
	_background(Brush(BrushStyle::solid, defaultBackground)),
	_foreground(Brush(BrushStyle::solid, defaultForeground)),
	_align(align) {

	recalcBounds();
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el text a formatejar.
/// \param    text: El text.
///
void Text::setText(
	const char *text) {

	if (_text != text) {
		_text = text;
		recalcBounds();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'aliniacio.
/// \param    align: L'aliniacio.
///
void Text::setAlign(
	TextAlign align) {

	if (_align != align) {
		_align = align;
		recalcBounds();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la brotxa per pinter el fons
/// \param    brush: La brotxa.
///
void Text::setBackground(
	const Brush &brush) {

	_background = brush;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la brotxa per pinter els caracters
/// \param    brush: La brotxa.
///
void Text::setForeground(
	const Brush &brush) {

	_foreground = brush;
}


/// ----------------------------------------------------------------------
/// \brief    Recalcula el tamany de l'envolvent.
///
void Text::recalcBounds() {

	const char* p = _text;
	int i = strlen(p);

	_width = 0;
	_height = 0;

	while(i > 1) {
		_width += _font.getCharAdvance(*p++);
		i--;
	}

	if (i > 0) {
		CharInfo ci;
		_font.getCharInfo(*p, ci);
		_width += ci.left + ci.width;

		_height = _font.getFontHeight();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa el text.
/// \param    graphics: L'objecte grafics on dibuixar.
/// \param    position: La Posicio.
///
void Text::draw(
	const Graphics *graphics,
	const Point &position) const {

	const char* p = _text;
	int l = strlen(p);

	if (l > 0) {

		Color bkColor = _background.getColor();
		Color fgColor = _foreground.getColor();

		int x = position.getX();
		int y = position.getY();

		graphics->drawRectangle(x, y, x + _width - 1, y + _height - 1, bkColor);

		y += _font.getFontAscent();
		while (l > 0) {

			drawChar(graphics, x, y, fgColor, *p);

			x += _font.getCharAdvance(*p);

			l--;
			p++;
		}
	}
}


void Text::drawChar(
	const Graphics *graphics,
	int x,
	int y,
	Color color,
	char ch) const {

	FontInfo fi;
    _font.getFontInfo(fi);

    if ((ch >= fi.firstChar) && (ch <= fi.lastChar)) {

    	CharInfo ci;
        _font.getCharInfo(ch, ci);

        if (ci.bitmap != nullptr) {
            int cw = (ci.width + 7) / 8;
            x += ci.left;
            y -= ci.top;
            for (int cy = 0; cy < ci.height; cy++) {
                int d = cy * cw;
                for (int cx = 0; cx < ci.width; cx++)
                    if (ci.bitmap[d + (cx / 8)] & (((uint8_t)0x80) >> (cx % 8)))
                        graphics->drawPoint(x + cx, y + cy, color);
            }
        }
    }
}

