#pragma once
#ifndef __STM32F030_htlINT_Vectors__
#define __STM32F030_htlINT_Vectors__


// HAL includes
//
#include "HTL/STM32/htl.h"


// Platform check
//
#if !defined(EOS_PLATFORM_STM32F030)
	#error "Valid for STM32F030 platform only"
#endif


namespace htl {

	namespace irq {

	enum class VectorID {
			tmr14,
		};

	}

}


#endif // __STM32F030_htlINT_Vectors__

