module;


#include "eos.h"


export module Eos.System.Graphics.Console;


import Eos.System.Graphics.Canvas;
import Eos.System.Graphics.Color;
import Eos.System.Graphics.ColorDefinitions;
import Eos.System.Graphics.Font;


export namespace eos {

	class Console {
		private:
			Graphics* _graphics;
			int _x;
			int _y;
			int _width;
			int _height;
			Color _bkColor;
			Color _fgColor;
			int _cx;
			int _cy;
			int _state;

		public:
			Console(Graphics* graphics, int x, int y, int width, int height);
			void clear();
			void home();
			void moveTo(int x, int y);
			void put(char ch);
			void put(const char *s, int offset, int length);

			inline int getX() const { return _x; }
			inline int getY() const { return _y; }
	};
}



/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param graphics: Objecte 'Graphics' per dibuixar.
///
eos::Console::Console(
	Graphics *graphics,
	int x,
	int y,
	int width,
	int height) :

	_graphics(graphics),
	_x(x),
	_y(y),
	_width(width),
	_height(height),
	_bkColor(Colors::black),
	_fgColor(Colors::yellow),
	_cx(0),
	_cy(0),
	_state(0) {
}


/// ---------------------------------------------------------------------
/// \brief Borra la pantalla
///
void eos::Console::clear() {

	_graphics->clear(_bkColor);
	home();
}

/// ----------------------------------------------------------------------
/// \brief Mou el cursor a l'origen.
///
void eos::Console::home() {

	_cx = 0;
	_cy = 0;
}


/// ----------------------------------------------------------------------
/// \brief Mou el cursor a la posicio indicada.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
///
void eos::Console::moveTo(
	int x,
	int y) {

	_cx = x;
	_cy = y;
}


/// ----------------------------------------------------------------------
/// \brief Escriu un caracter en emulacio TTY.
/// \param c: El caracter a escriure.
///
void eos::Console::put(
    char c) {

	Font font;

    switch (_state) {
        case 0:
            switch (c) {
                case (char)0xFF:
                    _state = 1;
                    break;

                case (char)0xFE:
                    _graphics->clear(_bkColor);
                    break;

                case (char)0xFD:
                	_cx = 0;
                	_cy = 0;
                    break;

                case '\r':
                    _cx = 0;
                    break;

                case '\n':
                    _cx = 0;
                    _cy += font.getFontHeight();
                    if (_cy >= _height)
                        _cy = 0;
                    break;

                default: {
                    CharInfo ci;
                    font.getCharInfo(c, ci);
                    if ((_cx + ci.advance) >= _width) {
                        _cx = 0;
                        _cy += font.getFontHeight();
                        if (_cy >= _height) {

                            // TODO: fer scroll de pantalla linia a linia
                            return;
                        }
                    }
                    //_cx += _graphics->drawChar(_x + _cx, _y + _cy, _fgColor, c);
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
void eos::Console::put(
    const char *s,
    int offset,
    int length) {

    for (int i = offset, j = length; j && s[i]; i++, j--)
       put(s[i]);
}
