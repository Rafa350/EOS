#pragma once


#include "eos.h"


namespace htl {

	class Device {
		public:
			Device (const Device &) = delete;
			Device & operator = (const Device &) = delete;

		protected:
			Device () = default;
			virtual ~Device () = default;
	};
}
