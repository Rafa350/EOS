#ifndef __STM32_halEXTI__
#define __STM32_halEXTI__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t EXTIPort;
typedef uint8_t EXTIPin;
typedef uint32_t EXTIOptions;

typedef struct {
    EXTIPort port;
    EXTIPin pin;
    EXTIOptions options;
} EXTIInitializeInfo;


// Identificado del port
#define HAL_EXTI_PORT_A      ((EXTIPort) 0)
#define HAL_EXTI_PORT_B      ((EXTIPort) 1)
#define HAL_EXTI_PORT_C      ((EXTIPort) 2)
#define HAL_EXTI_PORT_D      ((EXTIPort) 3)
#define HAL_EXTI_PORT_E      ((EXTIPort) 4)
#define HAL_EXTI_PORT_F      ((EXTIPort) 5)
#define HAL_EXTI_PORT_G      ((EXTIPort) 6)
#define HAL_EXTI_PORT_H      ((EXTIPort) 7)
#define HAL_EXTI_PORT_I      ((EXTIPort) 8)
#define HAL_EXTI_PORT_J      ((EXTIPort) 9)
#define HAL_EXTI_PORT_K      ((EXTIPort) 10)

// Identificador del pin
#define HAL_EXTI_PIN_0       ((EXTIPin) 0)
#define HAL_EXTI_PIN_1		 ((EXTIPin) 1)
#define HAL_EXTI_PIN_2	     ((EXTIPin) 2)
#define HAL_EXTI_PIN_3       ((EXTIPin) 3)
#define HAL_EXTI_PIN_4       ((EXTIPin) 4)
#define HAL_EXTI_PIN_5       ((EXTIPin) 5)
#define HAL_EXTI_PIN_6       ((EXTIPin) 6)
#define HAL_EXTI_PIN_7       ((EXTIPin) 7)
#define HAL_EXTI_PIN_8       ((EXTIPin) 8)
#define HAL_EXTI_PIN_9       ((EXTIPin) 9)
#define HAL_EXTI_PIN_10      ((EXTIPin) 10)
#define HAL_EXTI_PIN_11      ((EXTIPin) 11)
#define HAL_EXTI_PIN_12      ((EXTIPin) 12)
#define HAL_EXTI_PIN_13      ((EXTIPin) 13)
#define HAL_EXTI_PIN_14      ((EXTIPin) 14)
#define HAL_EXTI_PIN_15      ((EXTIPin) 15)

// Mode de treball
#define HAL_EXTI_MODE_POS    0u
#define HAL_EXTI_MODE_BITS   0b11u
#define HAL_EXTI_MODE_MASK   (HAL_EXTI_MODE_BITS << HAL_EXTI_MODE_POS)

// Disparador
#define HAL_EXTI_TRIGGER_POS      2u
#define HAL_EXTI_TRIGGER_BITS     0b11u
#define HAL_EXTI_TRIGGER_MASK     (HAL_EXTI_TRIGGER_BITS << HAL_EXTI_TRIGGER_POS)

#define HAL_EXTI_TRIGGER_NONE     (0b00u << HAL_EXTI_TRIGGER_POS)
#define HAL_EXTI_TRIGGER_RISING   (0b01u << HAL_EXTI_TRIGGER_POS)
#define HAL_EXTI_TRIGGER_FALLING  (0b10u << HAL_EXTI_TRIGGER_POS)
#define HAL_EXTI_TRIGGER_CHANGING (0b11u << HAL_EXTI_TRIGGER_POS)


void halEXTIInitialize(const EXTIInitializeInfo *info);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halEXTI__
