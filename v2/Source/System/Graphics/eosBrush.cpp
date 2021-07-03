#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosPoolAllocator.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosBrush.h"


using namespace eos;


class Brush::Impl: public PoolAllocatable<Brush::Impl, eosGraphics_MaxBrushes> {
	public:
		BrushStyle style;
		Color color;
};


/// ----------------------------------------------------------------------
/// \brief    Contructor.
///
Brush::Brush():
	_pImpl(allocate()) {

	_pImpl->style = BrushStyle::null;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    style: L'estil.
/// \param    color: El color.
///
Brush::Brush(
	BrushStyle style,
	Color color):

	_pImpl(allocate()) {

	eosAssert(style == BrushStyle::solid);

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

	Brush::Impl *b1 = &(*_pImpl);
	Brush::Impl *b2 = &(*brush._pImpl);

	return
		(b1->style == b2->style) &&
		(b1->color == b2->color);
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
/// \remarks  Nomes es valid per BrushStyle::solid
///
Color Brush::getColor() const {

	return _pImpl->color;
}


/// ----------------------------------------------------------------------
/// \brief    Indica si es nul.
/// \return   True si es nul, false en cas contrari.
///
bool Brush::isNull() const {

	return _pImpl->style == BrushStyle::null;
}

