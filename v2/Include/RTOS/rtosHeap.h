#pragma once
#ifndef __rtosHeap__
#define __rtosHeap__


#include "eos.h"


namespace rtos {

	class Heap final {
		private:
			static uint32_t _allocateCount;
			static uint32_t _deallocateCount;

		public:
			static void *allocate(uint32_t size);
			static void deallocate(void *ptr);

			static void * getStoragePtr();
			static uint32_t getStorageSize();
			static uint32_t getAllocatedSize();
			static uint32_t getAvailableSize();

			inline static uint32_t getAllocateCount() {
				return _allocateCount;
			}

			inline static uint32_t getDeallocateCount() {
				return _deallocateCount;
			}
	};
}


#endif // __rtosHeap__
