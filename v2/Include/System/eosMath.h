#pragma once
#ifndef __eosMath__
#define __eosMath__


namespace eos {

	class Math final {
		public:
			template <typename T>
			inline static T min(T a, T b) {
				return a < b ? a : b;
			}

			template <typename T>
			inline static T max(T a, T b) {
				return a > b ? a : b;
			}

			inline static uint8_t loByte(uint16_t b) {
				return (uint8_t) b;
			}

			inline static uint8_t hiByte(uint16_t b) {
				return (uint8_t) (b >> 8);
			}

			template <typename T>
			inline static void swap(T &a, T &b) {
				auto x{a};
				a = b;
				b = x;
			}
	};
}


#endif // __eosMath__
