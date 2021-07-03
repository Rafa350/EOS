#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosThickness.h"
#include "System/Graphics/eosRect.h"
#include "System/Graphics/eosSize.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor per defecte.
///
Thickness::Thickness():
	_left(0),
	_top(0),
	_right(0),
	_bottom(0) {
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param thickness: Amplada.
///
Thickness::Thickness(
	int thickness):

	_left(thickness),
	_top(thickness),
	_right(thickness),
	_bottom(thickness) {

	eosAssert(thickness >= 0);
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param hThickness: Amplada dels perfils horitzontals.
/// \param vThickness: Amplada dels perfils verticals.
///
Thickness::Thickness(
	int horizontal,
	int vertical):

	_left(horizontal),
	_top(vertical),
	_right(horizontal),
	_bottom(vertical) {

	eosAssert(horizontal >= 0);
	eosAssert(vertical >= 0);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    left: Amplada del perfil esquerra
/// \param    top: Amplada del perfil superior.
/// \param    right: Amplada del perfil dret.
/// \param    bottom: Amplada del perfil inferior.
///
Thickness::Thickness(
	int left,
	int top,
	int right,
	int bottom):

	_left(left),
	_top(top),
	_right(right),
	_bottom(bottom) {

	eosAssert(left >= 0);
	eosAssert(top >= 0);
	eosAssert(right >= 0);
	eosAssert(bottom >= 0);
}


/// ----------------------------------------------------------------------
/// \brief Constructor copia.
/// \param t: L'objecte a copiar.
///
Thickness::Thickness(
	const Thickness &t):

	_left(t._left),
	_top(t._top),
	_right(t._right),
	_bottom(t._bottom) {

}


bool Thickness::operator==(
	const Thickness &other) const {

	return
		_left == other._left &&
		_top == other._top &&
		_right == other._right &&
		_bottom == other._bottom;
}


Rect Thickness::inflate(
	const Rect &rect) const {

	return rect.inflated(_left, _top, _right, _bottom);
}


Size Thickness::inflate(
	const Size &size) const {

	return size.inflated(_left, _top, _right, _bottom);
}


Rect Thickness::deflate(
	const Rect &rect) const {

	return rect.inflated(-_left, -_top, -_right, -_bottom);
}


Size Thickness::deflate(
	const Size &size) const {

	return size.inflated(-_left, -_top, -_right, -_bottom);
}

