#pragma once
#ifndef __htl__
#define __htl__


#include "eos.h"
#include "System/eosCallbacks.h"


#if defined(EOS_PLATFORM_PIC32MX) || \
    defined(EOS_PLATFORM_PIC32MZ)
    #include "HTL/PIC32/htl.h"

#elif defined(EOS_PLATFORM_STM32G0) || \
	defined(EOS_PLATFORM_STM32F0) || \
	defined(EOS_PLATFORM_STM32F1) || \
	defined(EOS_PLATFORM_STM32F4) || \
	defined(EOS_PLATFORM_STM32F7)
	#include "HTL/STM32/htl.h"

#else
	#error "Unknown platform"

#endif


namespace htl {

	void initialize();
	void deinitialize();

	uint32_t getTick();
	void waitTicks(uint32_t ticks);
/*
	template <typename T_>
	inline void setBitM(T_ &data, T_ mask) {
		data |= mask;
	}

	template <typename T_>
	inline void setBitM(volatile T_ &data, T_ mask) {
		data |= mask;
	}

	template <typename T_>
	inline void clrBitM(volatile T_ &data, T_ mask) {
		data &= ~mask;
	}

	template <typename T_>
	inline void clrBitM(T_ &data, T_ mask) {
		data &= ~mask;
	}

	template <typename T_>
	inline void wrtRegM(volatile T_ &data, T_ clrMask, T_ setMask) {
		auto tmp = data;
		tmp &= ~clrMask;
		tmp |= setMask;
		data = tmp;
	}

	template <typename T_>
	inline void wrtRegM(T_ &data, T_ clrMask, T_ setMask) {
		auto tmp = data;
		tmp &= ~clrMask;
		tmp |= setMask;
		data = tmp;
	}

	template <typename T_>
	inline void setBitP(volatile T_ &data, uint8_t bit) {
		data |= 1 << bit;
	}

	template <typename T_>
	inline void setBitP(T_ &data, uint8_t bit) {
		data |= 1 << bit;
	}

	template <typename T_>
	inline void clrBitP(volatile T_ &data, uint8_t bit) {
		data &= ~(1 << bit);
	}

	template <typename T_>
	inline void clrBitP(T_ &data, uint8_t bit) {
		data &= ~(1 << bit);
	}

	template <typename T_>
	inline bool isSetBitP(volatile T_ &data, uint8_t bit) {
		return (data & (1 << bit)) != 0;
	}

	template <typename T_>
	inline bool isSetBitP(T_ &data, uint8_t bit) {
		return (data & (1 << bit)) != 0;
	}

	template <typename T_>
	inline bool isSetBitM(volatile T_ &data, T_ mask) {
		return (data & mask) != 0;
	}

	template <typename T_>
	inline bool isSetBitM(T_ &data, T_ mask) {
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
	}*/
}


#endif // __htl__
