export module htl.bits;

namespace htl {

	export template<typename T_>
	inline void setBits(volatile T_ &var, unsigned bits) {
		var |= (T_) bits;
	}

	export template<typename T_>
	inline void setBits(T_ &var, unsigned bits) {
		var |= (T_) bits;
	}

	export template<typename T_>
	inline void clearBits(volatile T_ &var, unsigned bits) {
		var &= ~((T_) bits);
	}

	export template<typename T_>
	inline void clearBits(T_ &var, unsigned bits) {
		var &= ~((T_) bits);
	}

	export template<typename T_>
	inline bool checkSetBits(volatile T_ &var, unsigned bits) {
		return (var & bits) == bits;
	}

	export template<typename T_>
	inline bool checkSetBits(T_ &var, unsigned bits) {
		return (var & bits) == bits;
	}

	export template<typename T_>
	inline bool checkClearBits(volatile T_ &var, unsigned bits) {
		return (var & bits) == 0;
	}

	export template<typename T_>
	inline bool checkClearBits(T_ &var, unsigned bits) {
		return (var & bits) == 0;
	}

}
