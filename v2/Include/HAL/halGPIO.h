#ifndef __EOS_HAL_GPIO_H
#define	__EOS_HAL_GPIO_H


#include "eos.h"

#if defined( EOS_PIC32MX) || defined(EOS_PIC32MZ)
#include "xc.h"
#include "peripheral/ports/plib_ports.h"
#endif

#include <stdint.h>


#ifdef	__cplusplus
extern "C" {
#endif
    

#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
    
#ifdef PORTA
#define GPIO_PORT_A     PORT_CHANNEL_A
#endif    
    
#ifdef PORTB
#define GPIO_PORT_B     PORT_CHANNEL_B
#endif

#ifdef PORTC
#define GPIO_PORT_C     PORT_CHANNEL_C
#endif

#ifdef PORTD
#define GPIO_PORT_D     PORT_CHANNEL_D
#endif

#ifdef PORTE
#define GPIO_PORT_E     PORT_CHANNEL_E
#endif

#ifdef PORTF
#define GPIO_PORT_F     PORT_CHANNEL_F
#endif
    
#ifdef PORTG
#define GPIO_PORT_G     PORT_CHANNEL_G
#endif
    
#define GPIO_PIN_0      PORTS_BIT_POS_0
#define GPIO_PIN_1      PORTS_BIT_POS_1
#define GPIO_PIN_2      PORTS_BIT_POS_2
#define GPIO_PIN_3      PORTS_BIT_POS_3
#define GPIO_PIN_4      PORTS_BIT_POS_4
#define GPIO_PIN_5      PORTS_BIT_POS_5
#define GPIO_PIN_6      PORTS_BIT_POS_6
#define GPIO_PIN_7      PORTS_BIT_POS_7
#define GPIO_PIN_8      PORTS_BIT_POS_8
#define GPIO_PIN_9      PORTS_BIT_POS_9
#define GPIO_PIN_10     PORTS_BIT_POS_10
#define GPIO_PIN_11     PORTS_BIT_POS_11
#define GPIO_PIN_12     PORTS_BIT_POS_12
#define GPIO_PIN_13     PORTS_BIT_POS_13
#define GPIO_PIN_14     PORTS_BIT_POS_14
#define GPIO_PIN_15     PORTS_BIT_POS_15
    
#define GPIO_DIRECTION_INPUT      0
#define GPIO_DIRECTION_OUTPUT     1
    

typedef PORTS_CHANNEL GPIOPort;
typedef PORTS_BIT_POS GPIOPin;
typedef uint8_t GPIODirection;


#endif

    
#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)

#define halGPIOSetPin(port, pin) PLIB_PORTS_PinSet(PORTS_ID_0, port, pin)
#define halGPIOClearPin(port, pin) PLIB_PORTS_PinClear(PORTS_ID_0, port, pin)
#define halGPIOTogglePin(port, pin) PLIB_PORTS_PinToggle(PORTS_ID_0, port, pin)
#define halGPIOReadPin(port, pin) PLIB_PORTS_PinGet(PORTS_ID_0, port, pin)  
#define halGPIOWritePin(port, pin, data) PLIB_PORTS_PinWrite(PORTS_ID_0, port, pin, data);
    
#define halGPIOSetPort(port, mask) PLIB_PORTS_Set(PORTS_ID_0, port, mask, mask)
#define halGPIOClearPort(port, mask) PLIB_PORTS_Clear(PORTS_ID_0, port, mask)
#define halGPIOTogglePort(port, mask) PLIB_PORTS_Toggle(PORTS_ID_0, port, mask)
#define halGPIOWritePort(port, data) PLIB_PORTS_Write(PORTS_ID_0, port, data)
#define halGPIOReadPort(port) PLIB_PORTS_Read(PORTS_ID_0, port)    

#endif


void halGPIOInitializePin(GPIOPort port, GPIOPin pin, GPIODirection direction);
void halGPIOInitializePort(GPIOPort port, GPIODirection direction, uint16_t mask);


#ifdef	__cplusplus
}
#endif


#endif	

