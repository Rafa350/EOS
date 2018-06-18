#ifndef __STM32_halUSB__
#define __STM32_halUSB__


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


typedef uint8_t USBPort;

typedef struct {
    USBPort port;
} USBInitializeInfo;


#define HAL_USB_PORT_0            ((USBPort) 0)
#define HAL_USB_PORT_1            ((USBPort) 1)

#define HAL_USB_PORT_FS           HAL_USB_PORT_0
#define HAL_USB_PORT_HS           HAL_USB_PORT_1


bool halUSBInitialize(const USBInitializeInfo *info);


#ifdef __cplusplus
}
#endif


#endif // __STM32_halUSB__
