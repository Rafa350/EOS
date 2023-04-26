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
	void I2CMasterDevice1_InterruptHandler();
	void I2CSlaveDevice1_InterruptHandler();
#endif
#ifdef HTL_I2C2_EXIST
	void I2CMasterDevice2_InterruptHandler();
	void I2CSlaveDevice2_InterruptHandler();
#endif
#ifdef HTL_I2C3_EXIST
	void I2CMasterDevice3_InterruptHandler();
	void I2CSlaveDevice3_InterruptHandler();
#endif
#ifdef HTL_I2C4_EXIST
	void I2CMasterDevice4_InterruptHandler();
	void I2CSlaveDevice4_InterruptHandler();
#endif
	
#ifdef __cplusplus
}
#endif


#endif // __STM32_htlI2C_IRQ__
