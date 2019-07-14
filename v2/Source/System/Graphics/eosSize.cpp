#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosSize.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte. Crea un objecte buit.
///
Size::Size():

	width(0),
	height(0) {
}


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
/// \param width: L'amplada.
/// \param height: L'alçada.
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
/// \brief Constructor copia.
/// \param s: L'objecte a copiar.
///
Size::Size(
	const Size &s):

	width(s.width),
	height(s.height) {
}


/// ----------------------------------------------------------------------
/// \brief Retorna un objecte engrandit.
/// \param dw: Increment del tamany en amplada.
/// \param dw: increment de tamany en alçada.
/// \return El nou objecte.
///
Size Size::inflate(
	int dw,
	int dh) const {

	eosAssert(width + dw >= 0);
	eosAssert(height + dh >= 0);

	return Size(width + dw, height + dh);
}


/// ----------------------------------------------------------------------
/// \brief Comprova si el tamany es zero.
/// \return True si es zero.
///
bool Size::isEmpty() const {

	return (width == 0) && (height == 0);
}


/// ----------------------------------------------------------------------
/// \brief Operador ==
/// \param s: Objecte a comparar.
/// \return True si son iguals.
///
bool Size::operator==(
	const Size &s) const {

	return (width == s.width) && (height == s.height);
}


/// ----------------------------------------------------------------------
/// \brief Operador !=
/// \param s: Objecte a comparar.
/// \return True si son diferents.
///
bool Size::operator!=(
	const Size &s) const {

	return (width != s.width) || (height != s.height);
}
