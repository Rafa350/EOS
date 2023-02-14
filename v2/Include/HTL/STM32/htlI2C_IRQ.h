#pragma once
#ifndef __STM32_htlI2C_IRQ__
#define __STM32_htlI2C_IRQ__


// EOS includes
//
#include "HTL/htl.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifdef HTL_I2C1_EXIST
	void I2C_1_InterruptHandler();
#endif
#ifdef HTL_I2C2_EXIST
	void I2C_2_InterruptHandler();
#endif
#ifdef HTL_I2C3_EXIST
	void I2C_3_InterruptHandler();
#endif
#ifdef HTL_I2C4_EXIST
	void I2C_4_InterruptHandler();
#endif
	
#ifdef __cplusplus
}
#endif


#endif // __STM32_htlI2C_IRQ__
