#ifndef __STM32_halEXTI__
#define __STM32_halEXTI__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


#include "hal/STM32/halGPIO.h"


typedef uint32_t EXTIOptions;
typedef uint8_t EXTILine;

typedef struct {
    GPIOPort port;
    GPIOPin pin;
    EXTILine line;                // El parametre es irrellevant. Les interrupcions son fixes en STM32
    EXTIOptions options;
} EXTIInitializePinInfo;


#define HAL_EXTI_LINE_0           ((EXTILine) 0)
#define HAL_EXTI_LINE_1           ((EXTILine) 1)
#define HAL_EXTI_LINE_2           ((EXTILine) 2)
#define HAL_EXTI_LINE_3           ((EXTILine) 3)
#define HAL_EXTI_LINE_4           ((EXTILine) 4)
#define HAL_EXTI_LINE_5           ((EXTILine) 5)
#define HAL_EXTI_LINE_6           ((EXTILine) 6)
#define HAL_EXTI_LINE_7           ((EXTILine) 7)
#define HAL_EXTI_LINE_8           ((EXTILine) 8)
#define HAL_EXTI_LINE_9           ((EXTILine) 9)
#define HAL_EXTI_LINE_10          ((EXTILine) 10)
#define HAL_EXTI_LINE_11          ((EXTILine) 11)
#define HAL_EXTI_LINE_12          ((EXTILine) 12)
#define HAL_EXTI_LINE_13          ((EXTILine) 13)
#define HAL_EXTI_LINE_14          ((EXTILine) 14)
#define HAL_EXTI_LINE_15          ((EXTILine) 15)


// Mode de treball
#define HAL_EXTI_MODE_POS         0u
#define HAL_EXTI_MODE_BITS        0b11u
#define HAL_EXTI_MODE_MASK        (HAL_EXTI_MODE_BITS << HAL_EXTI_MODE_POS)

#define HAL_EXTI_MODE_NONE        (0b00 << HAL_EXTI_MODE_POS)
#define HAL_EXTI_MODE_INT         (0b01 << HAL_EXTI_MODE_POS)
#define HAL_EXTI_MODE_EVENT       (0b10 << HAL_EXTI_MODE_POS)

// Disparador
#define HAL_EXTI_TRIGGER_POS      2u
#define HAL_EXTI_TRIGGER_BITS     0b11u
#define HAL_EXTI_TRIGGER_MASK     (HAL_EXTI_TRIGGER_BITS << HAL_EXTI_TRIGGER_POS)

#define HAL_EXTI_TRIGGER_NONE     (0b00u << HAL_EXTI_TRIGGER_POS)
#define HAL_EXTI_TRIGGER_RISING   (0b01u << HAL_EXTI_TRIGGER_POS)
#define HAL_EXTI_TRIGGER_FALLING  (0b10u << HAL_EXTI_TRIGGER_POS)
#define HAL_EXTI_TRIGGER_CHANGING (0b11u << HAL_EXTI_TRIGGER_POS)


typedef void (*EXTICallbackFunction)(EXTILine line, void *pParam);

void halEXTIInitializePins(const EXTIInitializePinInfo *pInfo, unsigned count);
void halEXTISetCallbackFunction(EXTILine line, EXTICallbackFunction function, void *pParam);


#ifdef __cplusplus
}
#endif


#endif // __STM32_halEXTI__
