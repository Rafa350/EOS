module;


#include "eos.h"

#include "FreeRTOS.h"


export module Eos.System.Core.HeapAllocator;


import Eos.Types;
import Eos.Math;


export namespace eos {

    class HeapAllocator: private StaticClass<HeapAllocator> {
        private:
            static uint32_t _allocateCount;
            static uint32_t _deallocateCount;
#ifdef EOS_DEBUG
            static size_t _minSize;
            static size_t _maxSize;
            static uint32_t _count8Bytes;
            static uint32_t _count16Bytes;
            static uint32_t _count32Bytes;
            static uint32_t _count48Bytes;
            static uint32_t _count64Bytes;
#endif

        public:
            [[nodiscard]] static void * allocate(size_t size);
            static bool deallocate(void *ptr);

			static uint32_t getAllocateCount() {
				return _allocateCount;
			}

			static uint32_t getDeallocateCount() {
				return _deallocateCount;
			}

            static void *getStoragePtr();
            static size_t getStorageSize();
            static size_t getAvailableSize();
            static size_t getAllocatedSize();
    };

    uint32_t HeapAllocator::_allocateCount = 0;
    uint32_t HeapAllocator::_deallocateCount = 0;
#ifdef EOS_DEBUG
    size_t HeapAllocator::_minSize = Math::maxU32;
    size_t HeapAllocator::_maxSize = Math::minU32;
    uint32_t HeapAllocator::_count8Bytes = 0;
    uint32_t HeapAllocator::_count16Bytes = 0;
    uint32_t HeapAllocator::_count32Bytes = 0;
    uint32_t HeapAllocator::_count48Bytes = 0;
    uint32_t HeapAllocator::_count64Bytes = 0;
#endif
}


#if (configAPPLICATION_ALLOCATED_HEAP == 1)
extern "C" {
    export uint8_t ucHeap[configTOTAL_HEAP_SIZE];
}
#endif


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

#ifdef EOS_DEBUG
	_minSize = eos::Math::min(_minSize, size);
	_maxSize = eos::Math::max(_maxSize, size);

    if (size <= 8)
        _count8Bytes++;
    else if (size <= 16)
        _count16Bytes++;
    else if (size <= 32)
        _count32Bytes++;
    else if (size <= 48)
        _count48Bytes++;
    else if (size <= 64)
        _count64Bytes++;
#endif

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

	return ucHeap;
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
