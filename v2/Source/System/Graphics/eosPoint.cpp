#include "eos.h"
#include "System/Graphics/eosPoint.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
Point::Point():

	_x(0),
	_y(0) {
}


/// -----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
///
Point::Point(
	int x,
	int y):

	_x(x),
	_y(y) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia.
/// \param    p: El objecte a copiar.
///
Point::Point(
	const Point &p):

	_x(p._x),
	_y(p._y) {
}


/// ----------------------------------------------------------------------
/// \brief    Obte un punt despla�at.
/// \param    dx: Increment X.
/// \param    dy: Increment Y.
/// \return   El punt despla�at.
///
Point Point::translated(
	int dx,
	int dy) const {

	return Point(_x + dx, _y + dy);
}


/// ----------------------------------------------------------------------
/// \brief    Obte un punt despla�at.
/// \param    d: Increment.
/// \return   El punt despla�at.
///
Point Point::translated(
	const Point &d) const {

	return Point(_x + d._x, _y + d._y);
}


/// ----------------------------------------------------------------------
/// \brief    Operador ==
/// \param    p: Objecte a comparar.
/// \return   True si son iguals.
///
bool Point::operator==(
	const Point &p) const {

	return (_x == p._x) && (_y == p._y);
}


/// ----------------------------------------------------------------------
/// \brief    Operador !=
/// \param    p: Objecte a comparar.
/// \return   True si son diferents.
///
bool Point::operator!=(
	const Point &p) const {

	return (_x != p._x) || (_y != p._y);
}
