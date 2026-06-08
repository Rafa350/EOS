#pragma once


#include "eos.h"

#include <atomic>

namespace rtos {

	template <typename T_>
	class Atomic final {
		private:
			volatile T_ _value;

		public:
			inline Atomic(T_ value):
				_value {value} {
			}

			inline T_ load() const {
				return _value;
			}

			inline void store(T_ value) {
				_value = value;
			}

			inline Atomic& operator = (T_ value) {
				store(value);
				return *this;
			}

			inline operator T_() {
				return load();
			}
	};

	using AtomicBool = Atomic<bool>;
}
