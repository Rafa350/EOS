#pragma once
#ifndef __eosBits__
#define __eosBits__


namespace eos {

	namespace bits {

		template <typename T_>
		inline void setM(T_ &data, T_ mask) {
			data |= mask;
		}

		template <typename T_>
		inline void setM(volatile T_ &data, T_ mask) {
			data |= mask;
		}

		template <typename T_>
		inline void clrM(volatile T_ &data, T_ mask) {
			data &= ~mask;
		}

		template <typename T_>
		inline void clrM(T_ &data, T_ mask) {
			data &= ~mask;
		}

		template <typename T_>
		inline void wrtM(volatile T_ &data, T_ clrMask, T_ setMask) {
			auto tmp = data;
			tmp &= ~clrMask;
			tmp |= setMask;
			data = tmp;
		}

		template <typename T_>
		inline void wrtM(T_ &data, T_ clrMask, T_ setMask) {
			auto tmp = data;
			tmp &= ~clrMask;
			tmp |= setMask;
			data = tmp;
		}

		template <typename T_>
		inline void setP(volatile T_ &data, uint8_t bit) {
			data |= 1 << bit;
		}

		template <typename T_>
		inline void setP(T_ &data, uint8_t bit) {
			data |= 1 << bit;
		}

		template <typename T_>
		inline void clrP(volatile T_ &data, uint8_t bit) {
			data &= ~(1 << bit);
		}

		template <typename T_>
		inline void clrP(T_ &data, uint8_t bit) {
			data &= ~(1 << bit);
		}

		template <typename T_>
		inline bool isSetP(volatile T_ &data, uint8_t bit) {
			return (data & (1 << bit)) != 0;
		}

		template <typename T_>
		inline bool isSetP(T_ &data, uint8_t bit) {
			return (data & (1 << bit)) != 0;
		}

		template <typename T_>
		inline bool isSetM(volatile T_ &data, T_ mask) {
			return (data & mask) != 0;
		}

		template <typename T_>
		inline bool isSetM(T_ &data, T_ mask) {
			return (data & mask) != 0;
		}

		template <typename T_>
		inline bool isClrBitP(volatile T_ &data, uint8_t bit) {
			return (data & (1 << bit)) == 0;
		}

		template <typename T_>
		inline bool isClrBitP(T_ &data, uint8_t bit) {
			return (data & (1 << bit)) == 0;
		}

		template <typename T_>
		inline bool isClrBitM(volatile T_ &data, T_ mask) {
			return (data & mask) == 0;
		}

		template <typename T_>
		inline bool isClrBitM(T_ &data, T_ mask) {
			return (data & mask) == 0;
		}
	}
}


#endif // __eosBits__
