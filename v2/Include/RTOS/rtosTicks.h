#pragma once


#include "eos.h"


namespace rtos {

	class Miliseconds;

	class Ticks final {
		private:
			uint32_t const _value;

		public:
			explicit inline Ticks(uint32_t value):
				_value {value} {
			}

			Miliseconds asMiliseconds() const;

			inline operator uint32_t() const {
				return _value;
			}
	};

}

