#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosSize.h"

#include <cmath>


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte. Crea un objecte de tamany zero.
///
Size::Size():

	_width(0),
	_height(0) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    width: L'amplada.
/// \param    height: L'alçada.
///
Size::Size(
	int16_t width,
	int16_t height):

	_width(width),
	_height(height) {

	eosAssert(width >= 0);
	eosAssert(height >= 0);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copy.
/// \param    s: L'objecte a copiar.
///
Size::Size(
	const Size &s):

	_width(s._width),
	_height(s._height) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor move.
/// \param    s: L'objecte a copiar.
///
Size::Size(
	const Size &&s):

	_width(s._width),
	_height(s._height) {
}


/// ----------------------------------------------------------------------
/// \brief    Retorna un objecte inflat.
/// \param    h: Inflat en horitzontal.
/// \param    v: Inflat en vertical
/// \return   El nou objecte.
/// \remarks  El increment tant en amplada com en alçada pot ser negatiu.
///
Size Size::inflated(
	int16_t h,
	int16_t v) const {

	return Size(
		std::max(0, _width + h),
		std::max(0, _height + v));
}


/// ----------------------------------------------------------------------
/// \brief    Retorna un objecte inflat.
/// \param    left: Inflat per l'esquerra.
/// \param    top: Inflat per dalt.
/// \param    right: Inflat per la dreta.
/// \param    bottom: Inflat per avall.
///
Size Size::inflated(
	int16_t left,
	int16_t top,
	int16_t right,
	int16_t bottom) const {

	return Size(
		std::max(0, _width + left + right),
		std::max(0, _height + top + bottom));
}


/// ----------------------------------------------------------------------
/// \brief    Retorna un tamany limitat.
/// \param    s: El tamany limit.
///
Size Size::constrained(
	const Size &s) const {

	return Size(
		std::min(_width, s._width),
		std::min(_height, s._height));
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el tamany es zero.
/// \return   True si es zero.
///
bool Size::isEmpty() const {

	return (_width == 0) && (_height == 0);
}


/// ----------------------------------------------------------------------
/// \brief    Operador =
/// \param    s: L'objecte a asignar.
/// \return   Referencia al propi objecte.
///
Size& Size::operator = (
	const Size &s) {

	_width = s._width;
	_height = s._height;

	return *this;
}

/// ----------------------------------------------------------------------
/// \brief    Operador ==
/// \param    s: Objecte a comparar.
/// \return   True si son iguals.
///
bool Size::operator == (
	const Size &s) const {

	return (_width == s._width) && (_height == s._height);
}
