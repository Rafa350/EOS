#pragma once


namespace htl {

	class Device {
		protected:
			Device () = default;

		public:
			Device (const Device &) = delete;
			Device (const Device &&) = delete;
			Device & operator = (const Device &) = delete;
			Device & operator = (const Device &&) = delete;
			virtual ~Device () = default;
	};
}
