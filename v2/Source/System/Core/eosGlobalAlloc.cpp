#include "eos.h"
#include "RTOS/rtosHeap.h"


/// ----------------------------------------------------------------------
/// \brief    Operador new global.
/// \param    size: Tamany en bytes de la memoria a reservar.
///
void* operator new(
    size_t size) {

    return rtos::Heap::allocate(size);
}


/// ----------------------------------------------------------------------
/// \brief    Operador delete global.
/// \param    ptr: Punter al bloc de memoria a alliberar.
///
void operator delete(
    void *ptr) {

    rtos::Heap::deallocate(ptr);
}


void operator delete(
	void *ptr,
	size_t size) {

}
