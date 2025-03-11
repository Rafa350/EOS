export module htl.bits;


export namespace htl {

	template<typename T_>
	void setBits(volatile T_ &var, unsigned bits);

	template<typename T_>
	void setBits(T_ &var, unsigned bits);

	template<typename T_>
	void clearBits(volatile T_ &var, unsigned bits);

	template<typename T_>
	void clearBits(T_ &var, unsigned bits);

	template<typename T_>
	bool checkSetBits(volatile T_ &var, unsigned bits);

	template<typename T_>
	bool checkSetBits(T_ &var, unsigned bits);

	template<typename T_>
	bool checkClearBits(volatile T_ &var, unsigned bits);

	template<typename T_>
	bool checkClearBits(T_ &var, unsigned bits);

}


template<typename T_>
void htl::setBits(volatile T_ &var, unsigned bits) {
	var |= (T_) bits;
}


template<typename T_>
inline void htl::setBits(T_ &var, unsigned bits) {
	var |= (T_) bits;
}

template<typename T_>
inline void htl::clearBits(volatile T_ &var, unsigned bits) {
	var &= ~((T_) bits);
}


template<typename T_>
inline void htl::clearBits(T_ &var, unsigned bits) {
	var &= ~((T_) bits);
}


template<typename T_>
inline bool htl::checkSetBits(volatile T_ &var, unsigned bits) {
	return (var & bits) == bits;
}

template<typename T_>
inline bool htl::checkSetBits(T_ &var, unsigned bits) {
	return (var & bits) == bits;
}


template<typename T_>
inline bool htl::checkClearBits(volatile T_ &var, unsigned bits) {
	return (var & bits) == 0;
}


template<typename T_>
inline bool htl::checkClearBits(T_ &var, unsigned bits) {
	return (var & bits) == 0;
}
