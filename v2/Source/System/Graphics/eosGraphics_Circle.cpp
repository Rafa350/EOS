#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


// TODO: Utilitzar acces directe al driver, igual que el·lipse


/// ----------------------------------------------------------------------
/// \brief Dibuixa un cercle buit.
/// \param x: Coordinada X del centre.
/// \param y: Coordinada Y del centre.
/// \param r: Radi del cercle.
///
void Graphics::drawCircle(
    int x,
    int y,
    int r) const {

    int xx = r;
    int yy = 0;
    int d = 1 - xx;

    while (yy <= xx) {
        drawPoint(x + xx, y + yy);
        drawPoint(x - xx, y + yy);
        drawPoint(x - xx, y - yy);
        drawPoint(x + xx, y - yy);
        drawPoint(x + yy, y + xx);
        drawPoint(x - yy, y + xx);
        drawPoint(x - yy, y - xx);
        drawPoint(x + yy, y - xx);
        yy++;
        if (d <= 0)
            d += 2 * yy + 1;
        else {
            xx--;
            d += 2 * (yy - xx) + 1;
        }
    }
}



/// ----------------------------------------------------------------------
/// \brief Dibuixa un cercle omplert.
/// \param cx: Coordinada X del centre.
/// \param cy: Coordinada Y del centre.
/// \param r: Radi del cercle.
///
void Graphics::fillCircle(
    int cx,
    int cy,
    int r) const {

    int x = r;
    int y = 0;
    int d = 1 - x;

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