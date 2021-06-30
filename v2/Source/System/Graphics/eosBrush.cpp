#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosPoolAllocator.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosBrush.h"


using namespace eos;


class Brush::Impl: public PoolAllocatable<Brush::Impl, eosGraphics_MaxBrushes> {
	public:
		Color color;
		BrushStyle style;
};


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    color: El color.
///
Brush::Brush(
	Color color):

	_pImpl(allocate()){

	_pImpl->style = BrushStyle::Solid;
	_pImpl->color = color;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    color: El color.
/// \param    style: L'estil.
///
Brush::Brush(
	Color color,
	BrushStyle style):

	_pImpl(allocate()){

	_pImpl->style = style;
	_pImpl->color = color;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de copia.
/// \param    brush: L'objecte a copiar.
///
Brush::Brush(
	const Brush &brush) :

	_pImpl(brush._pImpl) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
Brush::~Brush() {

}


/// ----------------------------------------------------------------------
/// \brief    Operador d'asignacio.
/// \param    brush: L'objecte a asignar.
/// \return   El propi objecte.
///
Brush& Brush::operator = (
	const Brush &brush) {

	_pImpl = brush._pImpl;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador ==
/// \param    brush: El operand
/// \return   True si son iguals.
///
bool Brush::operator == (
	const Brush &brush) const {

	return &(*_pImpl) == &(*brush._pImpl);
}


/// ----------------------------------------------------------------------
/// \brief    Operador !=
/// \param    brush: El operand
/// \return   True si son diferents.
///
bool Brush::operator != (
	const Brush &brush) const {

	return &(*_pImpl) != &(*brush._pImpl);
}


/// ----------------------------------------------------------------------
/// \brief    Crea l'estructura interna de dades.
/// \param    Punter a l'estructura.
///
Brush::PImpl Brush::allocate() {

	return PImpl(new Impl);
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estil del brush.
/// \return   L'estil.
///
BrushStyle Brush::getStyle() const {

	return _pImpl->style;
}

/// ----------------------------------------------------------------------
/// \brief    Obte el color.
/// \return   El color.
///
Color Brush::getColor() const {

	return _pImpl->color;
}
