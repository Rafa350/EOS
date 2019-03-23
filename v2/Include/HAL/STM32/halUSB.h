#ifndef __STM32_halUSB__
#define __STM32_halUSB__


// EOS includes
//
#include "eos.h"

// Standard includes
//
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef uint8_t USBPort;

#define HAL_USB_PORT_0            ((USBPort) 0)
#define HAL_USB_PORT_1            ((USBPort) 1)

#define HAL_USB_PORT_FS           HAL_USB_PORT_0
#define HAL_USB_PORT_HS           HAL_USB_PORT_1


#ifdef __cplusplus
}
#endif


#endif // __STM32_halUSB__
