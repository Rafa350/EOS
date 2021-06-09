#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosPen.h"


using namespace eos;


struct Pen::Impl {
	Color color;
	int thickness;
};


/// ----------------------------------------------------------------------
/// \brief    Constructor. Crea el objecte amb els valors per defecte.
///
Pen::Pen():
	_pImpl(allocate()) {

	_pImpl->color = COLOR_Black;
	_pImpl->thickness = 1;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    color: El color de linia.
/// \param    thickness: Emplada de linia.
///
Pen::Pen(
	const Color& color,
	int thickness) :

	_pImpl(allocate()) {

	_pImpl->color = color;
	_pImpl->thickness = thickness;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de copia.
/// \param    pen: L'objecte a copiar.
///
Pen::Pen(
	const Pen& pen) :

	_pImpl(pen._pImpl) {
}


/// ----------------------------------------------------------------------
/// \brief    Operador d'asignacio.
/// \param    L'objecte a asignar.
/// \return   El propi objecte.
///
Pen& Pen::operator = (
	const Pen& pen) {

	_pImpl = pen._pImpl;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Crea l'estructura interna de dades.
/// \return   El resultat.
///
Pen::PImpl Pen::allocate() {

	return std::shared_ptr<Impl>(new Impl);
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
