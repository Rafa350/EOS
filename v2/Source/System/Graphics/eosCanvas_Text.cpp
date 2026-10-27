module;

#include <string.h>


module Eos.System.Graphics.Canvas;

import Eos.Math;
import Eos.System.Graphics.Color;
import Eos.System.Graphics.ColorDefinitions;
import Eos.Types;


using namespace eos;


static constexpr Color defaultBackground = Colors::transparent;
static constexpr Color defaultForeground = Colors::black;


/// ---------------------------------------------------------------------------
/// @brief    Constructor del objecte amb els valors per defecte.
///
Text::Text():

	_text {nullptr},
	_textLength {0},
	_font {Font()},
	//_background(defaultBackground)),
	_foreground {Brush(defaultForeground)},
	_horizontalAlign {HorizontalAlign::center},
	_verticalAlign {VerticalAlign::middle},
	_width {0},
	_height {0} {
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor del objecte.
/// @param    font: El font.
/// @param    align: L'aliniacio del text.
///
Text::Text(
	const Font &font,
	HorizontalAlign align):

	_text {nullptr},
	_textLength {0},
	_font {font},
	//_background(Brush(defaultBackground)),
	_foreground {Brush(defaultForeground)},
	_horizontalAlign {align},
	_verticalAlign {VerticalAlign::middle},
	_width {0},
	_height {0} {

}


/// ---------------------------------------------------------------------------
/// @brief    Constructor del objecte.
/// @param    font: El font.
/// @param    align: L'aliniacio del text.
/// @param    text: El text.
///
Text::Text(
	const Font &font,
	HorizontalAlign align,
	const char *text,
	UInt32 textLength):

	_text {text},
	_textLength {(textLength == Math::maxU32) ? strlen(text) : textLength},
	_font {font},
	//_background {Brush(defaultBackground)},
	_foreground {Brush(defaultForeground)},
	_horizontalAlign {align},
	_verticalAlign {VerticalAlign::middle} {

	recalcBounds();
}


/// ---------------------------------------------------------------------------
/// @brief    Asigna el text a formatejar.
/// @param    text: El text.
/// @param    textLength: La longitut del text.
///
void Text::setText(
	const char *text,
	UInt32 textLength) {

	if (_text != text) {
		_text = text;
		_textLength = (textLength == eos::Math::maxU32) ? strlen(text) : textLength;
		recalcBounds();
	}
}


/// ----------------------------------------------------------------------
/// @brief    Asigna el text a formatejar.
/// @param    text: El text.
///
void Text::setText(
	const char *text) {

	setText(text, Math::maxU32);
}


/// ----------------------------------------------------------------------
/// @brief    Asigna el font.
/// @param    font: El font.
///
void Text::setFont(
	const Font &font) {

	if (_font != font) {
		_font = font;
		recalcBounds();
	}
}


/// ----------------------------------------------------------------------
/// @brief    Asigna l'aliniacio.
/// @param    align: L'aliniacio.
///
void Text::setHorizontalAlign(
	HorizontalAlign align) {

	_horizontalAlign = align;
}


/// ----------------------------------------------------------------------
/// @brief    Asigna l'aliniacio vertical.
/// @param    align: L'aliniacio.
///
void Text::setVerticalAlign(
	VerticalAlign align) {

	_verticalAlign = align;
}

/// ----------------------------------------------------------------------
/// @brief    Asigna la brotxa per pinter el fons
/// @param    brush: La brotxa.
///
void Text::setBackground(
	const Brush &brush) {

	_background = brush;
}


/// ----------------------------------------------------------------------
/// @brief    Asigna la brotxa per pinter els caracters
/// @param    brush: La brotxa.
///
void Text::setForeground(
	const Brush &brush) {

	_foreground = brush;
}


/// ----------------------------------------------------------------------
/// @brief    Recalcula el tamany de l'envolvent.
///
void Text::recalcBounds() {

	_width = 0;
	_height = 0;

	const char *p = _text;
	if (p != nullptr) {
		auto i = _textLength;
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
}


/// ----------------------------------------------------------------------
/// @brief    Dibuixa el text.
/// @param    graphics: L'objecte grafics on dibuixar.
/// @param    position: La Posicio.
///
void Text::draw(
	const Graphics *graphics,
	const Point &position) const {

	const char* p = _text;
	auto l = _textLength;

	if (l > 0) {

		Int16 x = position.getX();
		Int16 y = position.getY();

		if (!_background.isNull()) {
			Color bkColor = _background.getColor();
			graphics->drawRectangle(x, y, x + _width - 1, y + _height - 1, bkColor);
		}

		Color fgColor = _foreground.getColor();
		y += _font.getFontAscent();
		while (l > 0) {

			drawChar(graphics, x, y, fgColor, *p);

			x += _font.getCharAdvance(*p);

			l--;
			p++;
		}
	}
}


/// ----------------------------------------------------------------------
/// @brief    Dibuixa el text.
/// @param    graphics: L'objecte grafic on dibuixar.
/// @param    box: La caixa on dibuixar.
///
void Text::draw(
	const Graphics *graphics,
	const Rect &box) const {

	Int16 x;
	Int16 y;

	switch (_horizontalAlign) {
		default:
		case HorizontalAlign::left:
			x = box.getX();
			break;

		case HorizontalAlign::center:
			x = box.getX() + ((box.getWidth() - _width) / 2);
			break;

		case HorizontalAlign::right:
			x = box.getX() + box.getWidth() - _width;
			break;
	}

	y = box.getY() + ((box.getHeight() - _height) / 2);

	draw(graphics, Point(x, y));
}



void Text::drawChar(
	const Graphics *graphics,
	Int16 x,
	Int16 y,
	Color color,
	char ch) const {

	FontInfo fi;
    _font.getFontInfo(fi);

    if ((ch >= fi.firstChar) && (ch <= fi.lastChar)) {

    	CharInfo ci;
        _font.getCharInfo(ch, ci);

        if (ci.bitmap != nullptr) {
            Int16 cw = (ci.width + 7) / 8;
            x += ci.left;
            y -= ci.top;
            for (Int16 cy = 0; cy < ci.height; cy++) {
                Int16 d = cy * cw;
                for (Int16 cx = 0; cx < ci.width; cx++)
                    if (ci.bitmap[d + (cx / 8)] & (((UInt8)0x80) >> (cx % 8)))
                        graphics->drawPoint(x + cx, y + cy, color);
            }
        }
    }
}
