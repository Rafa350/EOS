#ifndef __STM32_halLTDC__
#define __STM32_halLTDC__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


#define HAL_LTDC_LAYER_0     0
#define HAL_LTDC_LAYER_1     1


void halLTDCSetFrameAddress(int layerNum, int frameAddr);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halLTDC__
