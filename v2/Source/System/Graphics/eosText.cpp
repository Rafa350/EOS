#include "eos.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosBrush.h"
#include "System/Graphics/eosText.h"


using namespace eos;


Text::Text():

	_text(""),
	_font(Font()),
	_background(Brush(BrushStyle::solid, COLOR_Transparent)),
	_foreground(Brush(BrushStyle::solid, COLOR_Black)),
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
	const Font& font,
	TextAlign align):

	_text(""),
	_font(font),
	_background(Brush(BrushStyle::solid, COLOR_Transparent)),
	_foreground(Brush(BrushStyle::solid, COLOR_Black)),
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
	const String& text):

	_text(text),
	_font(font),
	_background(Brush(BrushStyle::solid, COLOR_Transparent)),
	_foreground(Brush(BrushStyle::solid, COLOR_Black)),
	_align(align) {

	recalcBounds();
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el text a formatejar.
/// \param    text: El text.
///
void Text::setText(
	const String& text) {

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


void Text::setBackground(
	const Brush& brush) {

	_background = brush;
}


void Text::setForeground(
	const Brush& brush) {

	_foreground = brush;
}


/// ----------------------------------------------------------------------
/// \brief    Recalcula el tamany de l'envolvent.
///
void Text::recalcBounds() {

	if (_text.isEmpty()) {
		_width = 0;
		_height = 0;
	}

	else {
		FontInfo fi;
		_font.getFontInfo(fi);

		_height = fi.height;

		_width = 0;
		for (int i = 0, j = _text.getLength(); j; i++, j--) {

			char ch = _text[i];

			if (j == 1) {

				CharInfo ci;
				_font.getCharInfo(ch, ci);

				_width += ci.left + ci.width;
			}
			else
				_width += _font.getCharAdvance(ch);
		}

	}
}


void Text::draw(
	Graphics* graphics,
	const Point& position) {

	FontInfo fi;
	_font.getFontInfo(fi);

	Color color = _foreground.getColor();

	int x = position.getX();
	int y = position.getY() + fi.ascent;

	for (int i = 0, j = _text.getLength(); j; i++, j--) {

		char ch = _text[i];

        drawChar(graphics, x, y, color, ch);

        x += _font.getCharAdvance(ch);
	}

}


void Text::drawChar(
	Graphics* graphics,
	int x,
	int y,
	Color color,
	char ch) {

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

