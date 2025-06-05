#pragma once


#include "HTL/htl.h"


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
