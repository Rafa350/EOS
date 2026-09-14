module;


#include "eos.h"

#include "FreeRTOS.h"


export module Eos.System.Core.HeapAllocator;


export namespace eos {

    class HeapAllocator {
        private:
            static uint32_t _allocateCount;
            static uint32_t _deallocateCount;

        public:
            static void * allocate(size_t size);
            static bool deallocate(void *ptr);

			inline static uint32_t getAllocateCount() {
				return _allocateCount;
			}

			inline static uint32_t getDeallocateCount() {
				return _deallocateCount;
			}

            static void *getStoragePtr();
            static size_t getStorageSize();
            static size_t getAvailableSize();
            static size_t getAllocatedSize();
    };

    uint32_t HeapAllocator::_allocateCount = 0;
    uint32_t HeapAllocator::_deallocateCount = 0;
}


//uint8_t ucHeap[configTOTAL_HEAP_SIZE];


/// ---------------------------------------------------------------------------
/// \brief    Obte un bloc de memoria
/// \param    size: Tamany del bloc de momoria.
/// \return   Punter al bloc de memoria. nullptr en cas d'error.
///
void* eos::HeapAllocator::allocate(
    size_t size) {

	void *ptr = pvPortMalloc(size);
	if (ptr != nullptr)
		_allocateCount++;

    return ptr;
}


/// ---------------------------------------------------------------------------
/// \brief    Allibera un bloc de memoria.
/// \param    p: Punter al bloc de memoria.
///
bool eos::HeapAllocator::deallocate(
    void *ptr) {

	if (ptr != nullptr) {
		_deallocateCount++;
		vPortFree(ptr);
	}

    return true;
}


/// ---------------------------------------------------------------------------
/// \brief    Obte l'adressa del magatzem
/// \return   L'adressa.
///
void * eos::HeapAllocator::getStoragePtr() {

	return nullptr; // ucHeap;
}


/// ---------------------------------------------------------------------------
/// \brief    Obte el nombre de bytes del magetzem.
/// ºreturn   El valor.
///
size_t eos::HeapAllocator::getStorageSize() {

	return configTOTAL_HEAP_SIZE;
}


/// ---------------------------------------------------------------------------
/// \brief    Obte el nombre de bytes disponibles en el heap
/// \return   El valor.
///
size_t eos::HeapAllocator::getAvailableSize() {

	return xPortGetFreeHeapSize();
}


/// ---------------------------------------------------------------------------
/// \brief    Obte el nombre de bytes utilitzats en el heap
/// \return   El valor.
///
size_t eos::HeapAllocator::getAllocatedSize() {

	return configTOTAL_HEAP_SIZE - xPortGetFreeHeapSize();
}
