#pragma once


#include "HTL/htl.h"


namespace htl {

	template<typename T_>
	void setBits(volatile T_ &var, unsigned bits) {
		var |= (T_) bits;
	}

	template<typename T_>
	inline void setBits(T_ &var, unsigned bits) {
		var |= (T_) bits;
	}

	template<typename T_>
	inline void clearBits(volatile T_ &var, unsigned bits) {
		var &= ~((T_) bits);
	}

	template<typename T_>
	inline void clearBits(T_ &var, unsigned bits) {
		var &= ~((T_) bits);
	}

	template<typename T_>
	inline bool checkSetBits(volatile T_ &var, unsigned bits) {
		return (var & bits) == bits;
	}

	template<typename T_>
	inline bool checkSetBits(T_ &var, unsigned bits) {
		return (var & bits) == bits;
	}

	template<typename T_>
	inline bool checkClearBits(volatile T_ &var, unsigned bits) {
		return (var & bits) == 0;
	}

	template<typename T_>
	inline bool checkClearBits(T_ &var, unsigned bits) {
		return (var & bits) == 0;
	}

}
