#include "HTL/htl.h"
#include "HTL/STM32/htlI2C.h"
#include "HTL/STM32/htlI2C_IRQ.h"


using namespace htl::i2c;


#ifdef HTL_I2C1_EXIST
void I2CSlaveDevice1_InterruptHandler() {

	I2CSlaveDevice1::interruptHandler();
}
#endif


#ifdef HTL_I2C2_EXIST
void I2CSlaveDevice2_InterruptHandler() {

	I2CSlaveDevice2::interruptHandler();
}
#endif


#ifdef HTL_I2C3_EXIST
void I2CSlaveDevice3_InterruptHandler() {

	I2CSlaveDevice3::interruptHandler();
}
#endif


#ifdef HTL_I2C4_EXIST
void I2CSlaveDevice4_InterruptHandler() {

	I2CSlaveDevice4::interruptHandler();
}
#endif

