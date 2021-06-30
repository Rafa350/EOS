#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosPoolAllocator.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosPen.h"


using namespace eos;


/// \brief Estructura que representa les dades internes del Pen
//
class Pen::Impl: public PoolAllocatable<Pen::Impl, eosGraphics_MaxPens> {
	public:
		Color color;
		int thickness;
		PenStyle style;
};


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Pen::Pen() :
	_pImpl(allocate()) {

	_pImpl->style = PenStyle::Solid;
	_pImpl->color = COLOR_Black;
	_pImpl->thickness = 1;
}

/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    color: El color de linia.
///
Pen::Pen(
	Color color):

	_pImpl(allocate()) {

	_pImpl->style = PenStyle::Solid;
	_pImpl->color = color;
	_pImpl->thickness = 1;
}

/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    color: El color de linia.
/// \param    thickness: Amplada de linia.
/// \param    style: Estil.
///
Pen::Pen(
	Color color,
	int thickness,
	PenStyle style) :

	_pImpl(allocate()) {

	_pImpl->style = style;
	_pImpl->color = color;
	_pImpl->thickness = thickness;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    color: El color de linia.
/// \param    thickness: Amplada de linia.
/// \param    style: Estil.
///
Pen::Pen(
	const Brush &brush,
	int thickness,
	PenStyle style) :

	_pImpl(allocate()) {

	_pImpl->style = style;
	_pImpl->color = brush.getColor();
	_pImpl->thickness = thickness;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de copia.
/// \param    pen: L'objecte a copiar.
///
Pen::Pen(
	const Pen &pen) :

	_pImpl(pen._pImpl) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor
///
Pen::~Pen() {

}


/// ----------------------------------------------------------------------
/// \brief    Operador d'asignacio.
/// \param    pen L'objecte a asignar.
/// \return   El propi objecte.
///
Pen& Pen::operator = (
	const Pen &pen) {

	_pImpl = pen._pImpl;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operator ==
/// \param    pen: L'operand.
/// \return   True si son iguals.
///
bool Pen::operator == (
	const Pen &pen) const {

	// Compara l'adresa de les dades internes per verificar
	// si son iguals.
	//
	return &(*_pImpl) == &(*pen._pImpl);
}


/// ----------------------------------------------------------------------
/// \brief    Operator !=
/// \param    pen: L'operand.
/// \return   True si son diferents.
///
bool Pen::operator != (
	const Pen &pen) const {

	// Compara l'adresa de les dades internes per verificar
	// si son diferents.
	//
	return &(*_pImpl) != &(*pen._pImpl);
}


/// ----------------------------------------------------------------------
/// \brief    Crea l'estructura interna de dades.
/// \return   El resultat.
///
Pen::PImpl Pen::allocate() {

	return PImpl(new Impl);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el color.
/// \return   El valor obtingut.
///
Color Pen::getColor() const {

	return _pImpl->color;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'amplada de linia.
/// \return   El valor obtingut.
///
int Pen::getThickness() const {

	return _pImpl->thickness;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estil.
/// \return   El valor obtingut.
///
PenStyle Pen::getStyle() const {

	return _pImpl->style;
}
