#include "eos.h"
#include "System/Graphics/eosPoint.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
///
Point::Point():

	x(0),
	y(0) {
}


/// -----------------------------------------------------------------------
/// \brief Constructor del objecte.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
///
Point::Point(
	int x,
	int y):

	x(x),
	y(y) {
}


/// ----------------------------------------------------------------------
/// \brief Constructor copia.
/// \param p: El objecte a copiar.
///
Point::Point(
	const Point &p):

	x(p.x),
	y(p.y) {
}


/// ----------------------------------------------------------------------
/// \brief Obte un punt desplaçat.
/// \param dx: Increment X.
/// \param dy: Increment Y.
/// \return El punt desplaçat.
///
Point Point::offset(
	int dx,
	int dy) const {

	return Point(x + dx, y + dy);
}


/// ----------------------------------------------------------------------
/// \brief Obte un punt desplaçat.
/// \param d: Increment.
/// \return El punt desplaçat.
///
Point Point::offset(
	const Point &d) const {

	return Point(x + d.x, y + d.y);
}


/// ----------------------------------------------------------------------
/// \brief Operador ==
/// \param p: Objecte a comparar.
/// \return True si son iguals.
///
bool Point::operator==(
	const Point &p) const {

	return (x == p.x) && (y == p.y);
}


/// ----------------------------------------------------------------------
/// \brief Operador !=
/// \param p: Objecte a comparar.
/// \return True si son diferents.
///
bool Point::operator!=(
	const Point &p) const {

	return (x != p.x) || (y != p.y);
}
