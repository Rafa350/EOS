#pragma once

#include "eos.h"
#include "eosAssert.h"
#include "RTOS/rtosHeap.h"


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
					inline void* alloc(uint32_t size) const {
						return rtos::Heap::allocate(size);
					}

					inline void free(void *ptr) const {
						rtos::Heap::deallocate(ptr);
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
