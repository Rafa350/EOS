#ifndef __eosStdHeapAllocator__
#define __eosStdHeapAllocator__


#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
   	namespace system {
       	namespace collections {
#endif

       		/// \brief Standard allocator for standard containers in heap.
			///
			template <typename T_>
			class StdHeapAllocator {
				public:
					typedef T_ value_type;

				public:
					StdHeapAllocator () = default;

					template <class U_>
					constexpr StdHeapAllocator(const StdHeapAllocator<U_> &) {
					}

					T_* allocate(size_t n) {
						return static_cast<T_*>(alloc(n * sizeof(T_)));
					}

					void deallocate(T_ *p, size_t n) {
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

			template <typename T_, typename U_>
			bool operator == (const StdHeapAllocator<T_>&, const StdHeapAllocator<U_>&) {
				return true;
			}

			template <typename T_, typename U_>
			bool operator != (const StdHeapAllocator<T_>&, const StdHeapAllocator<U_>&) {
				return false;
			}

#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}

#endif // __eosStdHeapAllocator__
