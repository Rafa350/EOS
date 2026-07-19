#pragma once
#ifndef __eosMath__
#define __eosMath__


#include <cstdint>
#include <cmath>


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

			template <typename T>
			inline static T abs(T v) {
				return std::abs(v);
			}

			static constexpr uint32_t maxU32 = 0xFFFFFFFF;
			static constexpr uint32_t maxU16 = 0xFFFF;
			static constexpr uint32_t maxU8  = 0xFF;
			static constexpr uint32_t minU32 = 0x00000000;
			static constexpr uint32_t minU16 = 0x0000;
			static constexpr uint32_t minU8  = 0x00;
	};
}


#endif // __eosMath__
