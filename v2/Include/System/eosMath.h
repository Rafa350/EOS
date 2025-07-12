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
}


#endif // __eosMath__
