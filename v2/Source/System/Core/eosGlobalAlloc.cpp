import Eos.System.Core.HeapAllocator;


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Operador new global.
/// @param    size: Tamany en bytes de la memoria a reservar.
/// @return   Punter al bloc de memoria o nullptr en cas d'error.
///
void* operator new(
    unsigned size) {

    void *ptr = HeapAllocator::allocate(size);

	return ptr;
}


/// ---------------------------------------------------------------------------
/// @brief    Operador placement new global.
/// @param    size: Tamany en bytes de la memoria a reservar.
/// @param    ptr: Punter a la memoria ya reservada.
/// @return   Punter al bloc de memoria o nullptr en cas d'error.
///
void * operator new (
	unsigned size,
	void *ptr) {

	return ptr;
}


/// ---------------------------------------------------------------------------
/// @brief    Operador delete global.
/// @param    ptr: Punter al bloc de memoria a alliberar.
///
void operator delete(
    void *ptr) {

    HeapAllocator::deallocate(ptr);
}


/// ---------------------------------------------------------------------------
/// @brief    Operador delete global.
/// @param    ptr: El punter a la memoria
/// @param    size: El tamany de la memoria.
///
void operator delete(
	void *ptr,
	unsigned size) {

}


/// ---------------------------------------------------------------------------
/// @brief    Funcio standard malloc
/// @param    size: Tamany en bytes de la memoria a reserver.
/// @return   El punter al bloc de memoria o nullptr en cas d'error.
///
void *malloc(
	unsigned size) {

    return HeapAllocator::allocate(size);
}


/// --------------------------------------------------------------------------
/// @brief    Funcio standard free.
/// @param    ptr: El blñoc de memoria a alliverar.
///
void free(
	void *ptr) {

    HeapAllocator::deallocate(ptr);
}
