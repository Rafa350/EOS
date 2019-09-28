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
/// \brief    Retorna un objecte engrandit.
/// \param    dw: Increment del tamany en amplada.
/// \param    dw: increment de tamany en alçada.
/// \return   El nou objecte.
/// \remarks  El increment tant en amplada com en alçada pot ser negatiu.
///
Size Size::inflate(
	int dw,
	int dh) const {

	return Size(
		Math::max(0, width + dw),
		Math::max(0, height + dh));
}


/// ----------------------------------------------------------------------
/// \brief    Retorna un objecte inflat.
/// \param    t: Marges.
///
Size Size::inflate(
	const Thickness &t) const {

	return Size(
		width + t.getLeft() + t.getRight(),
		height + t.getTop() + t.getBottom());
}


/// ----------------------------------------------------------------------
/// \brief    Retorna un objecte desinflat.
/// \param    t: Marges.
///
Size Size::deflate(
	const Thickness &t) const {

	return Size(
		Math::max(0, width - t.getLeft() - t.getRight()),
		Math::max(0, height - t.getTop() - t.getBottom()));
}


/// ----------------------------------------------------------------------
/// \brief    Limita un tamany amb un altre.
/// \param    s: El tamany per limitar.
///
Size Size::constrain(
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
