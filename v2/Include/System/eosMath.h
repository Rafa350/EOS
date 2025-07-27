#pragma once
#ifndef __eosMath__
#define __eosMath__


namespace eos {

	template <typename T>
	inline T min(T a, T b) {
		return a < b ? a : b;
	}

	template <typename T>
	inline T max(T a, T b) {
		return a > b ? a : b;
	}

	inline uint8_t loByte(uint16_t b) {
		return (uint8_t) b;
	}

	inline uint8_t hiByte(uint16_t b) {
		return (uint8_t) (b >> 8);
	}
}


#endif // __eosMath__
