#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un rectangle buit.
/// \param    x1: Coordinada x del primer punt.
/// \param    y1: Coordinada y del primer punt.
/// \param    x2: Coordinada x del segon punt.
/// \param    y2: Coordinada y del segon punt.
///
void Graphics::drawRectangle(
    int x1,
    int y1,
    int x2,
    int y2) const {

	// Dibuixa el perfil com quatre linies independents
	//
   	drawHLine(x1, x2, y1);
   	drawHLine(x1, x2, y2);
   	drawVLine(x1, y1, y2);
   	drawVLine(x2, y1, y2);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un rectangle buit.
/// \param    x1: Coordinada x del primer punt.
/// \param    y1: Coordinada y del primer punt.
/// \param    x2: Coordinada x del segon punt.
/// \param    y2: Coordinada y del segon punt.
/// \param    thickness: Amplada de linia.
///
void Graphics::drawRectangle(
	int x1,
	int y1,
	int x2,
	int y2,
	int thickness) const {

}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un rectangle omplert.
/// \param    x1: Coordinada X del primer punt.
/// \param    y1: Coordinada Y del primer punt.
/// \param    x2: Coordinada X del segon punt.
/// \param    y2: Coordinada Y del segon punt.
///
void Graphics::fillRectangle(
    int x1,
    int y1,
    int x2,
    int y2) const {

    // Transforma a coordinades fisiques.
	//
	transform(x1, y1);
	transform(x2, y2);

	// Normalitza les coordinades.
	//
    if (x1 > x2)
        Math::swap(x1, x2);
    if (y1 > y2)
        Math::swap(y1, y2);

    // Dibuixa el rectangle si es visible
    //
    if (clipRectangle(x1, y1, x2, y2))
         driver->setPixels(x1, y1, x2 - x1 + 1, y2 - y1 + 1, color);
}
