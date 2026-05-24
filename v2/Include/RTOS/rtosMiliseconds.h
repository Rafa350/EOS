#pragma once


#include "eos.h"


namespace rtos {

	class Ticks;

	class Miliseconds final {
		private:
			uint32_t const _value;

		public:
			explicit inline Miliseconds(uint32_t value):
				_value {value} {
			}

			Ticks asTicks() const;

			inline operator uint32_t() const {
				return _value;
			}
	};
}
