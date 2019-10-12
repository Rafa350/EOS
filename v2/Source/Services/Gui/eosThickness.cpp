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
	left(0),
	top(0),
	right(0),
	bottom(0) {
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param thickness: Amplada.
///
Thickness::Thickness(
	int thickness):

	left(thickness),
	top(thickness),
	right(thickness),
	bottom(thickness) {

	eosAssert(thickness >= 0);
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param hThickness: Amplada en horitzontal.
/// \param vThickness: Amplada en vertical.
///
Thickness::Thickness(
	int hThickness,
	int vThickness):

	left(hThickness),
	top(vThickness),
	right(hThickness),
	bottom(vThickness) {

	eosAssert(hThickness >= 0);
	eosAssert(vThickness >= 0);
}


Thickness::Thickness(
	int left,
	int top,
	int right,
	int bottom):

	left(left),
	top(top),
	right(right),
	bottom(bottom) {

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

	left(t.left),
	top(t.top),
	right(t.right),
	bottom(t.bottom) {

}


bool Thickness::operator==(
	const Thickness &other) const {

	return
		left == other.left &&
		top == other.top &&
		right == other.right &&
		bottom == other.bottom;
}


Rect Thickness::inflate(
	const Rect &rect) {

	return rect.inflated(left, top, right, bottom);
}


Size Thickness::inflate(
	const Size &size) {

	return size.inflated(left, top, right, bottom);
}


Rect Thickness::deflate(
	const Rect &rect) {

	return rect.inflated(-left, -top, -right, -bottom);
}


Size Thickness::deflate(
	const Size &size) {

	return size.inflated(-left, -top, -right, -bottom);
}

