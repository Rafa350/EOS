#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosPoolAllocator.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosPen.h"


using namespace eos;


class Pen::Impl {
	private:
		static MemoryPoolAllocator _allocator;

	public:
		Color color;
		int thickness;

	public:
    	void* operator new(unsigned size);
    	void operator delete(void*p);
};


MemoryPoolAllocator Pen::Impl::_allocator(sizeof(Pen::Impl), eosGraphics_MaxPens);


/// ----------------------------------------------------------------------
/// \brief    Operador new
/// \param    size: Tamany del bloc.
/// \return   El bloc.
///
void* Pen::Impl::operator new(
	unsigned size) {

	eosAssert(size == sizeof(Pen::Impl));

	void* p = Pen::Impl::_allocator.allocate();
	eosAssert(p != 0);

	return p;
}


/// ----------------------------------------------------------------------
/// \brief    Operador delete.
/// \param    p: El bloc.
///
void Pen::Impl::operator delete(
	void* p) {

	eosAssert(p != nullptr);

	Pen::Impl::_allocator.deallocate(p);
}


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
/// \brief    Descruttor
///
Pen::~Pen() {

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
