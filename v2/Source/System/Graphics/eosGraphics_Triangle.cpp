#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un triangle buit.
/// \param    x1: Coordinada x del primer punt
/// \param    y1: Coordinada y del primer punt
/// \param    x2: Coordinada x del segon punt.
/// \param    y2: Coordinada y del segon punt.
/// \param    x3: Coordinada x del tercer punt.
/// \param    y3: Coordinada y del tercer punt.
/// \param    color: Color.
///
void Graphics::drawTriangle(
    int x1,
    int y1,
    int x2,
    int y2,
    int x3,
    int y3,
	Color color) const {

	// Dibuixa el triangle com tres linies independents
	//
	drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x3, y3, color);
    drawLine(x3, y3, x1, y1, color);
}
