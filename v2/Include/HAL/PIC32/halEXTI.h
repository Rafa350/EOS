#ifndef __PIC32_halEXTI__
#define	__PIC32_halEXTI__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t EXTILine;
typedef uint32_t EXTIOptions;

typedef void (*EXTICallbackFunction)(EXTILine line, void *pParam);

typedef struct {
    EXTILine line;
    EXTIOptions options;
} EXTIInitializePinInfo;



// Identificador de les linies
#define HAL_EXTI_LINE_0           ((EXTILine) 0)
#define HAL_EXTI_LINE_1           ((EXTILine) 1)
#define HAL_EXTI_LINE_2           ((EXTILine) 2)
#define HAL_EXTI_LINE_3           ((EXTILine) 3)
#define HAL_EXTI_LINE_4           ((EXTILine) 4)

// Identificador de les linies alternatiu (Depenent de la CPU)
#define HAL_EXTI_LINE_PA0         HAL_EXTI_LINE_0
    

// Mode de treball
#define HAL_EXTI_MODE_POS         0u
#define HAL_EXTI_MODE_BITS        0b11u
#define HAL_EXTI_MODE_MASK        (HAL_EXTI_MODE_BITS << HAL_EXTI_MODE_POS)

#define HAL_EXTI_MODE_NONE        (0b00u << HAL_EXTI_MODE_POS)
#define HAL_EXTI_MODE_INT         (0b01u << HAL_EXTI_MODE_POS)
#define HAL_EXTI_MODE_EVENT       (0b10u << HAL_EXTI_MODE_POS)

// Disparador
#define HAL_EXTI_TRIGGER_POS      2u
#define HAL_EXTI_TRIGGER_BITS     0b11u
#define HAL_EXTI_TRIGGER_MASK     (HAL_EXTI_TRIGGER_BITS << HAL_EXTI_TRIGGER_POS)

#define HAL_EXTI_TRIGGER_NONE     (0b00u << HAL_EXTI_TRIGGER_POS)
#define HAL_EXTI_TRIGGER_RISING   (0b01u << HAL_EXTI_TRIGGER_POS)
#define HAL_EXTI_TRIGGER_FALLING  (0b10u << HAL_EXTI_TRIGGER_POS)
#define HAL_EXTI_TRIGGER_CHANGING (0b11u << HAL_EXTI_TRIGGER_POS)

// Pull up/down
#define HAL_EXTI_PUPD_POS         4u
#define HAL_EXTI_PUPD_BITS        0b11u
#define HAL_EXTI_PUPD_MASK        (HAL_EXTI_PUPD_BITS << HAL_EXTI_PUPD_POS)

#define HAL_EXTI_PUPD_NONE        (0b00u << HAL_EXTI_PUPD_POS)
#define HAL_EXTI_PUPD_UP          (0b01u << HAL_EXTI_PUPD_POS)
#define HAL_EXTI_PUPD_DOWN        (0b10u << HAL_EXTI_PUPD_POS)

       
void halEXTIInitializePins(const EXTIInitializePinInfo *pInfo, unsigned count);
void halEXTISetCallbackFunction(EXTILine line, EXTICallbackFunction function, void *pParam);



#ifdef	__cplusplus
}
#endif


#endif // __PIC32_halEXTI__

