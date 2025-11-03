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
	//_background(defaultBackground)),
	_foreground(Brush(defaultForeground)),
	_horizontalAlign(HorizontalAlign::center),
	_verticalAlign {VerticalAlign::middle},
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
	HorizontalAlign align):

	_text {""},
	_font {font},
	//_background(Brush(defaultBackground)),
	_foreground {Brush(defaultForeground)},
	_horizontalAlign {align},
	_verticalAlign {VerticalAlign::middle},
	_width {0},
	_height {0} {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    font: El font.
/// \param    align: L'aliniacio del text.
/// \param    text: El text.
///
Text::Text(
	const Font &font,
	HorizontalAlign align,
	const char *text):

	_text {text},
	_font {font},
	//_background {Brush(defaultBackground)},
	_foreground {Brush(defaultForeground)},
	_horizontalAlign {align},
	_verticalAlign {VerticalAlign::middle} {

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
/// \brief    Asigna el font.
/// \param    font: El font.
///
void Text::setFont(
	const Font &font) {

	if (_font != font) {
		_font = font;
		recalcBounds();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'aliniacio.
/// \param    align: L'aliniacio.
///
void Text::setHorizontalAlign(
	HorizontalAlign align) {

	_horizontalAlign = align;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'aliniacio vertical.
/// \param    align: L'aliniacio.
///
void Text::setVerticalAlign(
	VerticalAlign align) {

	_verticalAlign = align;
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

	_width = 0;
	_height = 0;

	const char *p = _text;
	if (p != nullptr) {
		int i = strlen(p);
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
/// \brief    Dibuixa el text.
/// \param    graphics: L'objecte grafics on dibuixar.
/// \param    position: La Posicio.
///
void Text::draw(
	const Graphics *graphics,
	const Point &position) const {

	const char* p = _text;
	unsigned l = strlen(p);

	if (l > 0) {

		int16_t x = position.getX();
		int16_t y = position.getY();

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
/// \brief    Dibuixa el text.
/// \param    graphics: L'objecte grafics on dibuixar.
/// \param    box: La caixa un dibuixar.
///
void Text::draw(
	const Graphics *graphics,
	const Rect &box) const {

	int16_t x;
	int16_t y;

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

