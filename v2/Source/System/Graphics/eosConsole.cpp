#include "eos.h"
#include "System/Graphics/eosConsole.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param graphics: Objecte 'Graphics' per dibuixar.
/// \param columns: Numero de columnes.
/// \param rows: Numero de fil·leres.
///
Console::Console(
	Graphics *graphics,
	int x,
	int y,
	int width,
	int height) :

	graphics(graphics),
	x(x),
	y(y),
	width(width),
	height(height),
	cx(0),
	cy(0),
	state(0) {
}


/// ---------------------------------------------------------------------
/// \brief Borra la pantalla
///
void Console::clear() {

	graphics->clear(COLOR_Black);
	home();
}

/// ----------------------------------------------------------------------
/// \brief Mou el cursor a l'origen.
///
void Console::home() {

	cx = 0;
	cy = 0;
}


/// ----------------------------------------------------------------------
/// \brief Mou el cursor a la posicio indicada.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
///
void Console::moveTo(
	int x,
	int y) {

	cx = x;
	cy = y;
}


/// ----------------------------------------------------------------------
/// \brief Escriu un caracter en emulacio TTY.
/// \param c: El caracter a escriure.
///
void Console::put(
    char c) {

    Font *font = graphics->getFont();

    switch (state) {
        case 0:
            switch (c) {
                case (char)0xFF:
                    state = 1;
                    break;

                case (char)0xFE:
                    graphics->clear(COLOR_Black);
                    break;

                case (char)0xFD:
                	x = 0;
                	y = 0;
                    break;

                case '\r':
                    x = 0;
                    break;

                case '\n':
                    cx = 0;
                    cy += font->getFontHeight();
                    if (cy >= height)
                        cy = 0;
                    break;

                default: {
                    CharInfo ci;
                    font->getCharInfo(c, ci);
                    if ((cx + ci.advance) >= width) {
                        cx = 0;
                        cy += font->getFontHeight();
                        if (y >= height) {

                            // TODO: fer scroll de pantalla linia a linia
                            return;
                        }
                    }
                    cx += graphics->drawChar(x + cx, y + cy, c);
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
