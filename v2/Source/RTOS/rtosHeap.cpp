#include "RTOS/rtosHeap.h"

#include "FreeRTOS.h"


uint32_t rtos::Heap::_allocateCount = 0;
uint32_t rtos::Heap::_deallocateCount = 0;


/// ----------------------------------------------------------------------
/// \brief    Obte un bloc de memoria del heap.
/// \param    size: El tamany del bloc en bytes.
/// \return   L'adressa al bloc de memoria.
///
void * rtos::Heap::allocate(
	uint32_t size) {

	void *ptr = pvPortMalloc(size);
	if (ptr)
		_allocateCount++;

	return ptr;
}


/// ----------------------------------------------------------------------
/// \brief    Allivera unb loc de memoria del heap.
/// \param    ptr: Adressa del bloc de memoria a alliverar.
///
void rtos::Heap::deallocate(
	void *ptr) {

	if (ptr) {
		_deallocateCount++;
		vPortFree(ptr);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Obte el nombre de bytes del heap.
/// ºreturn   El valor.
///
uint32_t rtos::Heap::getSize() {

	return configTOTAL_HEAP_SIZE;
}

/// ----------------------------------------------------------------------
/// \brief    Obte el nombre de bytes disponibles en el heap
/// \return   El valor.
///
uint32_t rtos::Heap::getAvailableSize() {

	return xPortGetFreeHeapSize();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el nombre de bytes utilitzats en el heap
/// \return   El valor.
///
uint32_t rtos::Heap::getAllocatedSize() {

	return configTOTAL_HEAP_SIZE - xPortGetFreeHeapSize();
}
