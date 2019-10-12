#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/Graphics/eosSize.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte. Crea un objecte de tamany zero.
///
Size::Size():

	width(0),
	height(0) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    width: L'amplada.
/// \param    height: L'alçada.
///
Size::Size(
	int width,
	int height):

	width(width),
	height(height) {

	eosAssert(width >= 0);
	eosAssert(height >= 0);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia.
/// \param    s: L'objecte a copiar.
///
Size::Size(
	const Size &s):

	width(s.width),
	height(s.height) {
}


/// ----------------------------------------------------------------------
/// \brief    Retorna un objecte inflat.
/// \param    h: Inflat en horitzontal.
/// \param    v: Inflat en vertical
/// \return   El nou objecte.
/// \remarks  El increment tant en amplada com en alçada pot ser negatiu.
///
Size Size::inflated(
	int h,
	int v) const {

	return Size(
		Math::max(0, width + h),
		Math::max(0, height + v));
}


/// ----------------------------------------------------------------------
/// \brief    Retorna un objecte inflat.
/// \param    left: Inflat per l'esquerra.
/// \param    top: Inflat per dalt.
/// \param    right: Inflat per la dreta.
/// \param    bottom: Inflat per avall.
///
Size Size::inflated(
	int left,
	int top,
	int right,
	int bottom) const {

	return Size(
		Math::max(0, width + left + right),
		Math::max(0, height + top + bottom));
}


/// ----------------------------------------------------------------------
/// \brief    Retorna un tamany limitat.
/// \param    s: El tamany limit.
///
Size Size::constrained(
	const Size &s) const {

	return Size(
		Math::min(width, s.width),
		Math::min(height, s.height));
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el tamany es zero.
/// \return   True si es zero.
///
bool Size::isEmpty() const {

	return (width == 0) && (height == 0);
}


/// ----------------------------------------------------------------------
/// \brief    Operador ==
/// \param    s: Objecte a comparar.
/// \return   True si son iguals.
///
bool Size::operator==(
	const Size &s) const {

	return (width == s.width) && (height == s.height);
}


/// ----------------------------------------------------------------------
/// \brief    Operador !=
/// \param    s: Objecte a comparar.
/// \return   True si son diferents.
///
bool Size::operator!=(
	const Size &s) const {

	return (width != s.width) || (height != s.height);
}
