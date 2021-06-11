#include "eos.h"
#include "eosAssert.h"
#include "System/eosRefCounter.h"


using namespace eos;


MemoryPoolAllocator RefCounter::_allocator(sizeof(RefCounter), 100);


/// ----------------------------------------------------------------------
/// \brief    operador new
/// \param    size: Tamany del bloc de memoria.
///
void* RefCounter::operator new(
	unsigned size) {

	eosAssert(size == sizeof(RefCounter));

	void* p = RefCounter::_allocator.allocate();
	eosAssert(p != nullptr);

	return p;
}


/// ----------------------------------------------------------------------
/// \brief    Operador delete
/// \param    Bloc de memoria.
///
void RefCounter::operator delete(
	void* p) {

	eosAssert(p != nullptr);

	RefCounter::_allocator.deallocate(p);
}
