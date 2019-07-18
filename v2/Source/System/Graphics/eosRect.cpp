#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosRect.h"
#include "System/eosMath.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte. Crea un rectangle buit
///
Rect::Rect():
	x(0),
	y(0),
	width(0),
	height(0) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \param    width: Amplada.
/// \param    height: Alçada.
///
Rect::Rect(
	int x,
	int y,
	int width,
	int height):

	x(x),
	y(y),
	width(width),
	height(height) {

	eosAssert(width >= 0);
	eosAssert(height >= 0);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    p: Posicio.
/// \param    s: Tamany.
///
Rect::Rect(
	const Point &p,
	const Size &s):

	x(p.getX()),
	y(p.getY()),
	width(s.getWidth()),
	height(s.getHeight()) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    p1: Primer punt.
/// \param    p2: Segon punt.
/// \remarks  El rectangle creat, SEMPRE estata normalitzat, independentment
///           dels punt inicials
///
Rect::Rect(
	const Point &p1,
	const Point &p2):

	x(Math::min(p1.getX(), p2.getX())),
	y(Math::min(p1.getY(), p2.getY())),
	width(Math::abs(p2.getX() - p1.getX() + 1)),
	height(Math::abs(p2.getY() - p1.getY() + 1)) {

	eosAssert(width >= 0);
	eosAssert(height >= 0);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia.
/// \param    r: L'objecte a copiar.
///
Rect::Rect(
	const Rect &r):

	x(r.x),
	y(r.y),
	width(r.width),
	height(r.height) {
}


/// ----------------------------------------------------------------------
/// \brief    Obte un rectangle que es la interseccio d'aquest amb un altre.
/// \param    r: Rectangle per realitzar la interseccio.
/// \return   El resultat de la interseccio.
/// \remarks  El resultat SEMPRE sera un rectangle normalitzat.
///
Rect Rect::intersect(
	const Rect &r) const {

	int x1 = Math::max(x, r.x);
	int y1 = Math::max(y, r.y);
	int x2 = Math::min(getMaxX(), r.getMaxX());
	int y2 = Math::min(getMaxY(), r.getMaxY());

	if (x1 > x2)
		Math::swap(x1, x2);
	if (y1 > y2)
		Math::swap(y1, y2);

	if ((x2 < x1) || (y2 < y1))
		return Rect(x1, y1, 0, 0); // Rectangle buit
	else
		return Rect(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
}


bool Rect::contains(
	int x,
	int y) const {

	return
		(x >= getMinX()) && (y >= getMinY()) &&
		(x <= getMaxX()) && (y <= getMaxY());
}


/// ----------------------------------------------------------------------
/// \brief    Indica si es rectangle es buit.
/// \return   True si es buit.
///
bool Rect::isEmpty() const {

	return (width == 0) && (height == 0);
}

