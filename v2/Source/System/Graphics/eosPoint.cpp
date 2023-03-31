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
	int16_t x,
	int16_t y):

	_x(x),
	_y(y) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copy.
/// \param    p: El objecte a copiar.
///
Point::Point(
	const Point &p):

	_x(p._x),
	_y(p._y) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor move.
/// \param    p: L'objecte a moure.
///
Point::Point(
	const Point&& p) :

	_x(p._x),
	_y(p._y) {

}


/// ----------------------------------------------------------------------
/// \brief    Desplaça el punt.
/// \param    dx: Desplaçament x.
/// \param    dy: Desplaçament y.
/// \return   Referencia al propi objecte.
///
Point& Point::translate(
	int16_t dx,
	int16_t dy) {

	_x += dx;
	_y += dy;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Desplaça el punt.
/// \param    p: El vector de desplaçament.
/// \return   Referencia al propi objecte.
///
Point& Point::translate(
	const Point & p) {

	_x += p._x;
	_y += p._y;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Obte un punt despla�at.
/// \param    dx: Increment X.
/// \param    dy: Increment Y.
/// \return   El punt despla�at.
///
Point Point::translated(
	int16_t dx,
	int16_t dy) const {

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
/// \brief    Operador =
/// \param    p: L'objecte a asignar.
/// \return   Referencioa al propi objecte.
///
Point& Point::operator = (
	const Point &p) {

	_x = p._x;
	_y = p._y;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador ==
/// \param    p: Objecte a comparar.
/// \return   True si son iguals.
///
bool Point::operator == (
	const Point &p) const {

	return (_x == p._x) && (_y == p._y);
}
