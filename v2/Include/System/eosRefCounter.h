#ifndef __eosRefCounter__
#define __eosRefCounter__


#include "eos.h"
#include "Core/eosPoolAllocator.h"


namespace eos {

	class RefCounter {
		private:
			unsigned _count;
			static MemoryPoolAllocator _allocator;

		public:
			inline RefCounter(int count): _count(count) {}
			RefCounter(const RefCounter&) = delete;

			inline void inc() { _count++; }
			inline void dec() { _count--; }

			inline operator unsigned() const { return _count; }
			inline operator bool() const { return _count != 0; }

			RefCounter& operator = (const RefCounter&) = delete;

			void* operator new(unsigned size);
			void operator delete(void* p);
	};

}


#endif // __eosRefCounter__
