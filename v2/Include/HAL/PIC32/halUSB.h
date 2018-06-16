#ifndef __PIC32_halUSB__
#define __PIC32_halUSB__


// EOS includes
//
#include "eos.h"
#include "hal/hal.h"

// Standard includes
//
#include <stdint.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef uint8_t USBId;


#define HAL_USB_PORT_0            ((USBId) 0)
#define HAL_USB_PORT_1            ((USBId) 1)


#ifdef __cplusplus
}
#endif


#endif // __PIC32_halUSB__
