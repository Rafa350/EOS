#ifndef __eosStackAllocator__
#define	__eosStackAllocator__


#include "eos.h"


namespace eos {

    class MemoryStackAllocator {
        private:
            uint8_t *_storage;
            unsigned _size;

        public:
            MemoryStackAllocator(unsigned size);
            ~MemoryStackAllocator();

            void* allocate(unsigned size);
            void deallocate(void* p);

            inline void* getAddr() const { return _storage; }
            inline unsigned getSize() const { return _size; }
    };


    template <typename T, unsigned SIZE>
    class StackAllocator {

    	private:
    		StackAllocator _allocator;

    	public:

    		StackAllocator():
            	_allocator(SIZE) {
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


