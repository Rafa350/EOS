#ifndef __STM32_halRNG__
#define __STM32_halRNG__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


void halRNGInitialize();
unsigned halRNGGetRandomNumber();


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halRNG__


