#ifndef __HAL_GPIO_H
#define	__HAL_GPIO_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <stdint.h>
    
void halGPIOPinSetModeOutput(uint8_t pin);
void halGPIOPinSetModeInput(uint8_t pin);
bool halGPIOPinGetState(uint8_t pin);
void halGPIOPinSetState(uint8_t pin, bool state);
void halGPIOPinToggleState(uint8_t pin);

#ifdef	__cplusplus
}
#endif

#endif	

