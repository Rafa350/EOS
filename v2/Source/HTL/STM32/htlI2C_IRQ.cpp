#include "HTL/htl.h"
#include "HTL/STM32/htlI2C.h"
#include "HTL/STM32/htlI2C_IRQ.h"


using namespace htl::i2c;


#ifdef HTL_I2C1_EXIST
void I2CSlave_1_InterruptHandler() {

	I2CSlaveDevice1::getHandler()->interruptService();
}
#endif


#ifdef HTL_I2C2_EXIST
void I2CSlave_2_InterruptHandler() {

	I2CSlaveDevice2::getHandler()->interruptService();
}
#endif


#ifdef HTL_I2C3_EXIST
void I2CSlave_3_InterruptHandler() {

	I2CSlaveDevice3::getHandler()->interruptHandler();
}
#endif


#ifdef HTL_I2C4_EXIST
void I2CSlave_4_InterruptHandler() {

	I2CSlaveDevice4::getHandler()->interruptHandler();
}
#endif

