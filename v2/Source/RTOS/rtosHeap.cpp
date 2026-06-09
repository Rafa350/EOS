#include "eos.h"
#include "RTOS/rtosHeap.h"

#include "FreeRTOS.h"


#define RTOS_HEAP_USE_SAFEMODE 0


uint32_t rtos::Heap::_allocateCount = 0;
uint32_t rtos::Heap::_deallocateCount = 0;

uint8_t ucHeap[configTOTAL_HEAP_SIZE];


#if RTOS_HEAP_USE_SAFEMODE == 1
constexpr uint32_t headGuard = 0x0F1E2D3C;
constexpr uint32_t tailGuard = 0x5B5A6978;

struct Head {
	uint32_t guard;
	uint32_t size;
};

struct Tail {
	uint32_t guard;
};
#endif


/// ----------------------------------------------------------------------
/// \brief    Obte un bloc de memoria del heap.
/// \param    size: El tamany del bloc en bytes.
/// \return   L'adressa al bloc de memoria.
///
void * rtos::Heap::allocate(
	uint32_t size) {


#if RTOS_HEAP_USE_SAFEMODE == 1

	void *ptr = pvPortMalloc(sizeof(Head) + size + sizeof(Tail));

	Head *head = (Head*) ptr;
	head->guard = headGuard;
	head->size = size;

	Tail *tail = (Tail*) ((uint8_t*)ptr + sizeof(Head) + size);
	tail->guard = tailGuard;

	return (void*) ((uint8_t*)ptr + sizeof(Head));

#else

	void *ptr = pvPortMalloc(size);
	if (ptr)
		_allocateCount++;

	return ptr;

#endif
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
/// \brief    Obte l'adressa del magatzem
/// \return   L'adressa.
///
void * rtos::Heap::getStoragePtr() {

	return ucHeap;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el nombre de bytes del magetzem.
/// ºreturn   El valor.
///
uint32_t rtos::Heap::getStorageSize() {

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
