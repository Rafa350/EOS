#pragma once


#include "eos.h"


namespace rtos {

	class Heap final {
		private:
			static uint32_t _allocateCount;
			static uint32_t _deallocateCount;

		public:
			static void *allocate(uint32_t size);
			static void deallocate(void *ptr);

			static uint32_t getSize();
			static uint32_t getAllocatedSize();
			static uint32_t getAvailableSize();

			static uint32_t getAllocateCount() {
				return _allocateCount;
			}

			static uint32_t getDeallocateCount() {
				return _deallocateCount;
			}
	};
}
