#include "eos.h"
#include "HAL\halI2C.h"

#include "sys/attribs.h"


extern "C" void __ISR(_I2C_1_VECTOR, IPL2SOFT) isrI2C1Wrapper(void);
extern "C" void __ISR(_I2C_2_VECTOR, IPL2SOFT) isrI2C2Wrapper(void);


/// ----------------------------------------------------------------------
/// \brief Procesa el vector _I2C_1_VECTOR
///
extern "C" void isrI2C1Handler(void) {

    extern I2CData i2cData;

    halI2CInterruptHandler(&i2cData);
}


/// ----------------------------------------------------------------------
/// \brief Procesa el vector _I2C_2_VECTOR
///
extern "C" void isrI2C2Handler(void) {

}
