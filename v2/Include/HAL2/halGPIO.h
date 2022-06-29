#ifndef __hal2GPIO__
#define	__hal2GPIO__


// HAL includes
//
#include "HAL2/hal.h"


#define HAL_GPIO_PORT_A      hal::GPIO::Port::portA
#define HAL_GPIO_PORT_B      hal::GPIO::Port::portB
#define HAL_GPIO_PORT_C      hal::GPIO::Port::portC
#define HAL_GPIO_PORT_D      hal::GPIO::Port::portD
#define HAL_GPIO_PORT_E      hal::GPIO::Port::portE
#define HAL_GPIO_PORT_F      hal::GPIO::Port::portF
#define HAL_GPIO_PORT_G      hal::GPIO::Port::portG
#define HAL_GPIO_PORT_H      hal::GPIO::Port::portH
#define HAL_GPIO_PORT_I      hal::GPIO::Port::portI
#define HAL_GPIO_PORT_J      hal::GPIO::Port::portJ
#define HAL_GPIO_PORT_K      hal::GPIO::Port::portK

#define HAL_GPIO_PIN_0       hal::GPIO::Pin::pin0
#define HAL_GPIO_PIN_1       hal::GPIO::Pin::pin1
#define HAL_GPIO_PIN_2       hal::GPIO::Pin::pin2
#define HAL_GPIO_PIN_3       hal::GPIO::Pin::pin3
#define HAL_GPIO_PIN_4       hal::GPIO::Pin::pin4
#define HAL_GPIO_PIN_5       hal::GPIO::Pin::pin5
#define HAL_GPIO_PIN_6       hal::GPIO::Pin::pin6
#define HAL_GPIO_PIN_7       hal::GPIO::Pin::pin7
#define HAL_GPIO_PIN_8       hal::GPIO::Pin::pin8
#define HAL_GPIO_PIN_9       hal::GPIO::Pin::pin9
#define HAL_GPIO_PIN_10      hal::GPIO::Pin::pin10
#define HAL_GPIO_PIN_11      hal::GPIO::Pin::pin11
#define HAL_GPIO_PIN_12      hal::GPIO::Pin::pin12
#define HAL_GPIO_PIN_13      hal::GPIO::Pin::pin13
#define HAL_GPIO_PIN_14      hal::GPIO::Pin::pin14
#define HAL_GPIO_PIN_15      hal::GPIO::Pin::pin15


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL2/PIC32/halGPIO.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL2/STM32/halGPIO.h"

#elif defined(EOS_MSP432)
    #include "HAL2/MSP432/halGPIO.h"

#endif


#endif // __hal2GPIO__

