#ifndef __PIC32_halEXTI__
#define	__PIC32_halEXTI__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t EXTILine;
typedef uint32_t EXTIOptions;

typedef struct {
    EXTILine line;
    EXTIOptions options;
} EXTIInitializeLineInfo;

typedef void (*EXTICallbackFunction)(EXTILine line, void *pParam);


// Identificador de les linies
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

#define HAL_EXTI_MODE_NONE        (0u << HAL_EXTI_MODE_POS)
#define HAL_EXTI_MODE_INT         (1u << HAL_EXTI_MODE_POS)
#define HAL_EXTI_MODE_EVENT       (2u << HAL_EXTI_MODE_POS)

// Disparador
#define HAL_EXTI_TRIGGER_POS      2u
#define HAL_EXTI_TRIGGER_BITS     0b11u
#define HAL_EXTI_TRIGGER_MASK     (HAL_EXTI_TRIGGER_BITS << HAL_EXTI_TRIGGER_POS)

#define HAL_EXTI_TRIGGER_NONE     (0u << HAL_EXTI_TRIGGER_POS)
#define HAL_EXTI_TRIGGER_RISING   (1u << HAL_EXTI_TRIGGER_POS)
#define HAL_EXTI_TRIGGER_FALLING  (2u << HAL_EXTI_TRIGGER_POS)
#define HAL_EXTI_TRIGGER_CHANGING (3u << HAL_EXTI_TRIGGER_POS)

// Pull up/down
#define HAL_EXTI_PULL_POS         4u
#define HAL_EXTI_PULL_BITS        0b1u
#define HAL_EXTI_PULL_MASK        (HAL_EXTI_PULL_BITS << HAL_EXTI_PULL_POS)

#define HAL_EXTI_PULL_NONE        (0u << HAL_EXTI_PULL_POS)
#define HAL_EXTI_PULL_UP          (1u << HAL_EXTI_PULL_POS)

// Activar
#define HAL_EXTI_ENABLE_POS       5u
#define HAL_EXTI_ENABLE_BITS      0b1u
#define HAL_EXTI_ENABLE_MASK      (HAL_EXTI_ENABLE_BITS << HAL_EXTI_ENABLE_POS)

#define HAL_EXTI_ENABLE_NO        (0u << HAL_EXTI_ENABLE_POS)
#define HAL_EXTI_ENABLE_YES       (1u << HAL_EXTI_ENABLE_POS)

       
void halEXTIInitializeLines(const EXTIInitializeLineInfo *pInfo, unsigned count);
void halEXTIDisable();
void halEXTIEnableLine(EXTILine line);
void halEXTIDisableLine(EXTILine line);
void halEXTISetCallbackFunction(EXTILine line, EXTICallbackFunction function, void *pParam);



#ifdef	__cplusplus
}
#endif


#endif // __PIC32_halEXTI__

