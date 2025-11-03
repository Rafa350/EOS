#pragma once


#include "HTL/htl.h"

#include <type_traits>


namespace htl::bits {

	template<typename T_>
	inline void set(volatile T_ &var, T_ mask) {
		static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
		var |= mask;
	}

	template<typename T_>
	inline void set(T_ &var, T_ mask) {
		static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
		var |= mask;
	}

	template<typename T_>
	inline void clear(volatile T_ &var, T_ mask) {
		static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
		var &= ~mask;
	}

	template<typename T_>
	inline void clear(T_ &var, T_ mask) {
		static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
		var &= ~mask;
	}

	template<typename T_>
	inline void toggle(volatile T_ &var, T_ mask) {
		static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
		var ^= mask;
	}

	template<typename T_>
	inline void toggle(T_ &var, T_ mask) {
		static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
		var ^= mask;
	}

	template<typename T_>
	inline void modify(volatile T_ &var, T_ clearMask, T_ setMask) {
		static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
		T_ v = var;
		v &= ~clearMask;
		v |= setMask;
		var = v;
	}

	template<typename T_>
	inline void modify(T_ &var, T_ clearMask, T_ setMask) {
		static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
		var &= ~clearMask;
		var |= setMask;
	}

	template<typename T_>
	inline bool isSet(volatile T_ &var, T_ b) {
		static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
		return (var & b) == b;
	}

	template<typename T_>
	inline bool isSet(T_ &var, T_ b) {
		static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
		return (var & b) == b;
	}

	template<typename T_>
	inline bool isAnySet(T_ &var, T_ b) {
		static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
		return (var & b) != 0;
	}

	template<typename T_>
	inline bool isClear(volatile T_ &var, T_ b) {
		static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
		return (var & b) == 0;
	}

	template<typename T_>
	inline bool isClear(T_ &var, T_ b) {
		static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
		return (var & b) == 0;
	}

	template<typename T_>
	inline bool isAnyClear(T_ &var, T_ b) {
		static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
		return (var & b) != b;
	}

	template<typename T_>
	inline void setPos(volatile T_ &var, unsigned pos) {
		static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
		set(var, (T_)(1 << pos));
	}

	template<typename T_>
	inline void setPos(T_ &var, unsigned pos) {
		set(var, (T_)(1 << pos));
	}

	template<typename T_>
	inline void clearPos(volatile T_ &var, unsigned pos) {
		clear(var, (T_)(1 << pos));
	}

	template<typename T_>
	inline void clearPos(T_ &var, unsigned pos) {
		clear(var, (T_)(1 << pos));
	}

	template<typename T_>
	inline void togglePos(volatile T_ &var, unsigned pos) {
		toggle(var, (T_)(1 << pos));
	}

	template<typename T_>
	inline void togglePos(T_ &var, unsigned pos) {
		toggle(var, (T_)(1 << pos));
	}
}
