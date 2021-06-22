#ifndef __eosStackAllocator__
#define	__eosStackAllocator__


#include "eos.h"


namespace eos {

    class MemoryStackAllocator {
        private:
            uint8_t *_memory;
            unsigned _memorySize;

        public:
            StackPoolAllocator(unsigned memorySize);
            ~StackPoolAllocator();

            void* allocate();
            void deallocate(void* p);
    };


    template <class T>
    class StackAllocator {

    	private:
    		StackAllocator _allocator;

    	public:

    		StackAllocator(unsigned memorySize):
            	_allocator(memorySize) {
            }

    		inline T *allocate() {
            	return static_cast<T*>(_allocator.allocate(sizeof(T)));
            }

    		inline void deallocate(T* p) {
            	_allocator.deallocate(p);
            }
    };
}


#endif // __eosStackAllocator__


