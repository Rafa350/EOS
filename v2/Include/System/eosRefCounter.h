#pragma once
#ifndef __eosRefCounter__
#define __eosRefCounter__


// EOS includes
//
#include "eos.h"
#include "Core/eosPoolAllocator.h"


#ifndef eos_MaxRefCounters
#define eos_MaxRefCounters 200
#endif


namespace eos {

	class RefCounter: public PoolAllocatable<RefCounter, eos_MaxRefCounters> {
		private:
			int _count;

		public:
			inline RefCounter(int count):
				_count(count) {
			}

			RefCounter(const RefCounter&) = delete;

			RefCounter& operator = (const RefCounter&) = delete;

			inline void inc() {
				_count++;
			}

			inline void dec() {
				_count--;
			}

			inline operator int() const {
				return _count;
			}

			inline operator bool() const {
				return _count != 0;
			}
	};

}


#endif // __eosRefCounter__
