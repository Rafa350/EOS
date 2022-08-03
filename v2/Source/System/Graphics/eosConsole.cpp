#include "eos.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosConsole.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param graphics: Objecte 'Graphics' per dibuixar.
///
Console::Console(
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
void Console::clear() {

	_graphics->clear(_bkColor);
	home();
}

/// ----------------------------------------------------------------------
/// \brief Mou el cursor a l'origen.
///
void Console::home() {

	_cx = 0;
	_cy = 0;
}


/// ----------------------------------------------------------------------
/// \brief Mou el cursor a la posicio indicada.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
///
void Console::moveTo(
	int x,
	int y) {

	_cx = x;
	_cy = y;
}


/// ----------------------------------------------------------------------
/// \brief Escriu un caracter en emulacio TTY.
/// \param c: El caracter a escriure.
///
void Console::put(
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
void Console::put(
    const char *s,
    int offset,
    int length) {

    for (int i = offset, j = length; j && s[i]; i++, j--)
       put(s[i]);
}
