#include "HTL/htl.h"
#include "HTL/STM32/htlI2C.h"
#include "HTL/STM32/htlI2C_IRQ.h"


using namespace htl;


#ifdef HTL_I2C1_EXIST
void I2CSlave_1_InterruptHandler() {

	I2CSlave_1::interruptHandler();
}
#endif


#ifdef HTL_I2C2_EXIST
void I2CSlave_2_InterruptHandler() {

	I2CSlave_2::interruptHandler();
}
#endif


#ifdef HTL_I2C3_EXIST
void I2CSlave_3_InterruptHandler() {

	I2CSlave_3::interruptHandler();
}
#endif


#ifdef HTL_I2C4_EXIST
void I2CSlave_4_InterruptHandler() {

	I2CSlave_4::interruptHandler();
}
#endif

