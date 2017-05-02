#ifndef __EOS_HAL_PIC32_GPIO_H
#define	__EOS_HAL_PIC32_GPIO_H


#include <xc.h>
#include <stdint.h>


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct {
	uint32_t volatile *trisSET;
	uint32_t volatile *trisCLR;
	uint32_t volatile *odcSET;
	uint32_t volatile *odcCLR;
	uint32_t volatile *latSET;
	uint32_t volatile *latCLR;
	uint32_t volatile *latINV;
	uint32_t volatile *lat;
	uint32_t volatile *port;
} GPIOPortRegs;

typedef uint8_t GPIOPort;
typedef uint8_t GPIOPin;
typedef uint8_t GPIOOptions;


extern GPIOPortRegs gpioPortRegs[];


#if defined(PORTA)
#define HAL_GPIO_PORT_A      0
#endif
#if defined(PORTB)
#define HAL_GPIO_PORT_B      1
#endif
#if defined(PORTC)
#define HAL_GPIO_PORT_C      2
#endif
#if defined(PORTD)
#define HAL_GPIO_PORT_D      3
#endif
#if defined(PORTE)
#define HAL_GPIO_PORT_E      4
#endif
#if defined(PORTF)
#define HAL_GPIO_PORT_F      5
#endif
#if defined(PORTG)
#define HAL_GPIO_PORT_G      6
#endif
#define HAL_GPIO_PORT_NONE   255

#define HAL_GPIO_PIN_0       0
#define HAL_GPIO_PIN_1       1
#define HAL_GPIO_PIN_2       2
#define HAL_GPIO_PIN_3       3
#define HAL_GPIO_PIN_4       4
#define HAL_GPIO_PIN_5       5
#define HAL_GPIO_PIN_6       6
#define HAL_GPIO_PIN_7       7
#define HAL_GPIO_PIN_8       8
#define HAL_GPIO_PIN_9       9
#define HAL_GPIO_PIN_10      10
#define HAL_GPIO_PIN_11      11
#define HAL_GPIO_PIN_12      12
#define HAL_GPIO_PIN_13      13
#define HAL_GPIO_PIN_14      14
#define HAL_GPIO_PIN_15      15
#define HAL_GPIO_PIN_NONE    255

#define HAL_GPIO_DIRECTION_MASK        0b00000001
#define HAL_GPIO_DIRECTION_INPUT       0b00000000
#define HAL_GPIO_DIRECTION_OUTPUT      0b00000001

#define HAL_GPIO_OPENDRAIN_MASK        0b00000010
#define HAL_GPIO_OPENDRAIN_DISABLED    0b00000000
#define HAL_GPIO_OPENDRAIN_ENABLED     0b00000010


#define halGPIOInitializePinInput(port, pin) \
    *gpioPortRegs[port].trisSET = 1 << (pin) 

#define halGPIOInitializePinOutput(port, pin) \
    *gpioPortRegs[port].trisCLR = 1 << (pin)

#define halGPIOSetPin(port, pin) \
    *gpioPortRegs[port].latSET = 1 << (pin)

#define halGPIOClearPin(port, pin) \
    *gpioPortRegs[port].latCLR = 1 << (pin)

#define halGPIOTogglePin(port, pin) \
    *gpioPortRegs[port].latINV = 1 << (pin)

#define halGPIOReadPin(portId, pin) \
    (*gpioPortRegs[portId].port & (1 << (pin))) != 0

#define halGPIOWritePin(port, pin, data) \
    if (data) \
        *gpioPortRegs[port].latSET = 1 << (pin); \
    else \
        *gpioPortRegs[port].latCLR = 1 << (pin)

#define halGPIOInitializePortInput(port, mask) \
    *gpioPortRegs[port].trisSET = mask

#define halGPIOInitializePortOutput(port, mask) \
    *gpioPortRegs[port].trisCLR = mask

#define halGPIOWritePort(port, data) \
    *gpioPortRegs[port].lat = data

#define halGPIOReadPort(port) \
    *gpioPortRegs[port].lat


void halGPIOInitializePin(GPIOPort port, GPIOPin pin, GPIOOptions options);
void halGPIOInitializePort(GPIOPort port, GPIOOptions options, uint16_t mask);


#ifdef	__cplusplus
}
#endif


#endif

