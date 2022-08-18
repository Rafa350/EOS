#ifndef __eosStdHeapAllocator__
#define __eosStdHeapAllocator__


#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
   	namespace System {
       	namespace Collections {
#endif

       		/// \brief Standard allocator for standard containers in heap.
			///
			template <typename T>
			class StdHeapAllocator {
				public:
					typedef T value_type;

				public:
					StdHeapAllocator () = default;

					template <class U>
					constexpr StdHeapAllocator(const StdHeapAllocator <U>&) {
					}

					T* allocate(size_t n) {
						return static_cast<T*>(alloc(n * sizeof(T)));
					}

					void deallocate(T* p, size_t n) {
						free(p);
					}

				private:
					void* alloc(int size) {
						void *p = osalHeapAlloc(NULL, size);
						eosAssert(p != nullptr);
						return p;
					}

					void free(void *p) {
						osalHeapFree(NULL, p);
					}
			};

			template <typename T, typename U>
			bool operator == (const StdHeapAllocator <T>&, const StdHeapAllocator <U>&) {
				return true;
			}

			template <typename T, typename U>
			bool operator != (const StdHeapAllocator <T>&, const StdHeapAllocator <U>&) {
				return false;
			}

#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}

#endif // __eosStdHeapAllocator__
