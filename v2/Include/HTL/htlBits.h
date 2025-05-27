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

namespace htl::bits {

	template<typename T_>
	void set(volatile T_ &var, T_ s) {
		var |= s;
	}

	template<typename T_>
	inline void set(T_ &var, T_ s) {
		var |= s;
	}

	template<typename T_>
	inline void clear(volatile T_ &var, T_ c) {
		var &= ~c;
	}

	template<typename T_>
	inline void clear(T_ &var, T_ c) {
		var &= ~c;
	}

	template<typename T_>
	inline void modify(volatile T_ &var, T_ c, T_ s) {
		auto v = var;
		v &= ~c;
		v |= s;
		var = v;
	}

	template<typename T_>
	inline void modify(T_ &var, T_ c, T_ s) {
		var &= ~c;
		var |= s;
	}

	template<typename T_>
	inline bool isSet(volatile T_ &var, T_ b) {
		return (var & b) == b;
	}

	template<typename T_>
	inline bool isSet(T_ &var, T_ b) {
		return (var & b) == b;
	}

	template<typename T_>
	inline bool isAnySet(T_ &var, T_ b) {
		return (var & b) != 0;
	}

	template<typename T_>
	inline bool isClear(volatile T_ &var, T_ b) {
		return (var & b) == 0;
	}

	template<typename T_>
	inline bool isClear(T_ &var, T_ b) {
		return (var & b) == 0;
	}

	template<typename T_>
	inline bool isAnyClear(T_ &var, T_ b) {
		return (var & b) != b;
	}
}
