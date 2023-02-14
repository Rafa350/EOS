#include "HTL/htl.h"
#include "HTL/STM32/htlI2C.h"
#include "HTL/STM32/htlI2C_IRQ.h"


using namespace htl;


#ifdef HTL_I2C1_EXIST
void I2C_1_InterruptHandler() {

	I2C_1::interruptHandler();
}
#endif


#ifdef HTL_I2C2_EXIST
void I2C_2_InterruptHandler() {

	I2C_2::interruptHandler();
}
#endif


#ifdef HTL_I2C3_EXIST
void I2C_3_InterruptHandler() {

	I2C_3::interruptHandler();
}
#endif


#ifdef HTL_I2C4_EXIST
void I2C_4_InterruptHandler() {

	I2C_4::interruptHandler();
}
#endif

