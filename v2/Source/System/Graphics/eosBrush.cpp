#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosPoolAllocator.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosBrush.h"


using namespace eos;


class Brush::Impl {
	private:
		static MemoryPoolAllocator _allocator;

	public:
		Color color;
		BrushStyle style;

	public:
    	void* operator new(unsigned size);
    	void operator delete(void*p);
};


MemoryPoolAllocator Brush::Impl::_allocator(sizeof(Brush::Impl), eosGraphics_MaxBrushes);


/// ----------------------------------------------------------------------
/// \brief    Operador new
/// \param    size: Tamany del bloc.
/// \return   El bloc.
///
void* Brush::Impl::operator new(
	unsigned size) {

	eosAssert(size == sizeof(Brush::Impl));

	void* p = Brush::Impl::_allocator.allocate();
	eosAssert(p != 0);

	return p;
}


/// ----------------------------------------------------------------------
/// \brief    Operador delete.
/// \param    p: El bloc.
///
void Brush::Impl::operator delete(
	void* p) {

	eosAssert(p != nullptr);

	Brush::Impl::_allocator.deallocate(p);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    color: Color.
///
Brush::Brush(
	const Color& color):

	_pImpl(allocate()){

	_pImpl->style = BrushStyle::Solid;
	_pImpl->color = color;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de copia.
/// \param    pen: L'objecte a copiar.
///
Brush::Brush(
	const Brush& brush) :

	_pImpl(brush._pImpl) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
Brush::~Brush() {

}


/// ----------------------------------------------------------------------
/// \brief    Crea l'estructura interna de dades.
/// \param    Punter a l'estructura.
///
Brush::PImpl Brush::allocate() {

	return PImpl(new Impl);
}


BrushStyle Brush::getStyle() const {

	return _pImpl->style;
}


Color Brush::getColor() const {

	return _pImpl->color;
}
