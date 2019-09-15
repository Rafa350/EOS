#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosThickness.h"


using namespace eos;


Thickness::Thickness(
	int thickness):

	left(thickness),
	top(thickness),
	right(thickness),
	bottom(thickness) {

	eosAssert(left >= 0);
	eosAssert(top >= 0);
	eosAssert(right >= 0);
	eosAssert(bottom >= 0);
}


Thickness::Thickness(
	int hThickness,
	int vThickness):

	left(hThickness),
	top(vThickness),
	right(hThickness),
	bottom(vThickness) {

	eosAssert(left >= 0);
	eosAssert(top >= 0);
	eosAssert(right >= 0);
	eosAssert(bottom >= 0);
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
