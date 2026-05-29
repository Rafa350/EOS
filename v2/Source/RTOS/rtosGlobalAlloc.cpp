#include "eos.h"
#include "RTOS/rtosHeap.h"


/// ----------------------------------------------------------------------
/// \brief    Operador new global.
/// \param    size: Tamany en bytes de la memoria a reservar.
/// \return   Punter al bloc de memoria o nullptr en cas d'error.
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


/// ----------------------------------------------------------------------
/// \brief    Funcio standard malloc
/// \param    size: Tamany en bytes de la memoria a reserver.
/// \return   El punter al bloc de memoria o nullptr en cas d'error.
///
void *malloc(
	size_t size) {

    return rtos::Heap::allocate(size);
}


/// ---------------------------------------------------------------------
/// \brief    Funcio standard free.
/// \param    ptr: El blñoc de memoria a alliverar.
///
void free(
	void *ptr) {

    rtos::Heap::deallocate(ptr);
}
