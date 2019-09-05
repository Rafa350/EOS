#ifndef __PIC32_halCN__
#define	__PIC32_halCN__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t CNLine;
typedef uint32_t CNOptions;

typedef struct {
    CNLine line;
    CNOptions options;
} CNInitializeLineInfo;

typedef void (*CNCallbackFunction)(CNLine line, void *pParam);


// Identificador de les linies
#define HAL_CN_LINE_0             ((CNLine) 0)
#define HAL_CN_LINE_1             ((CNLine) 1)
#define HAL_CN_LINE_2             ((CNLine) 2)
#define HAL_CN_LINE_3             ((CNLine) 3)
#define HAL_CN_LINE_4             ((CNLine) 4)
#define HAL_CN_LINE_5             ((CNLine) 5)
#define HAL_CN_LINE_6             ((CNLine) 6)
#define HAL_CN_LINE_7             ((CNLine) 7)
#define HAL_CN_LINE_8             ((CNLine) 8)
#define HAL_CN_LINE_9             ((CNLine) 9)
#define HAL_CN_LINE_10            ((CNLine) 10)
#define HAL_CN_LINE_11            ((CNLine) 11)
#define HAL_CN_LINE_12            ((CNLine) 12)
#define HAL_CN_LINE_13            ((CNLine) 13)
#define HAL_CN_LINE_14            ((CNLine) 14)
#define HAL_CN_LINE_15            ((CNLine) 15)
#define HAL_CN_LINE_16            ((CNLine) 16)
#define HAL_CN_LINE_17            ((CNLine) 17)
#define HAL_CN_LINE_18            ((CNLine) 18)
#define HAL_CN_LINE_19            ((CNLine) 19)
#define HAL_CN_LINE_20            ((CNLine) 20)
#define HAL_CN_LINE_21            ((CNLine) 21)

#define HAL_CN_LINE_COUNT         22
  

// Disparador
#define HAL_CN_TRIGGER_POS        0u
#define HAL_CN_TRIGGER_BITS       0b11u
#define HAL_CN_TRIGGER_MASK       (HAL_CN_TRIGGER_BITS << HAL_CN_TRIGGER_POS)

#define HAL_CN_TRIGGER_NONE       (0u << HAL_CN_TRIGGER_POS)
#define HAL_CN_TRIGGER_RISING     (1u << HAL_CN_TRIGGER_POS)
#define HAL_CN_TRIGGER_FALLING    (2u << HAL_CN_TRIGGER_POS)
#define HAL_CN_TRIGGER_CHANGING   (3u << HAL_CN_TRIGGER_POS)

// Pull up/down
#define HAL_CN_PULL_POS           2u
#define HAL_CN_PULL_BITS          0b1u
#define HAL_CN_PULL_MASK          (HAL_CN_PULL_BITS << HAL_CN_PULL_POS)

#define HAL_CN_PULL_NONE          (0u << HAL_CN_PULL_POS)
#define HAL_CN_PULL_UP            (1u << HAL_CN_PULL_POS)

// Activar
#define HAL_CN_ENABLE_POS         3u
#define HAL_CN_ENABLE_BITS        0b1u
#define HAL_CN_ENABLE_MASK        (HAL_CN_ENABLE_BITS << HAL_CN_ENABLE_POS)

#define HAL_CN_ENABLE_NO          (0u << HAL_CN_ENABLE_POS)
#define HAL_CN_ENABLE_YES         (1u << HAL_CN_ENABLE_POS)

       
void halCNInitializeLines(const CNInitializeLineInfo *pInfo, unsigned count);
void halCNEnableLine(CNLine line);
void halCNDisableLine(CNLine line);
void halCNSetCallbackFunction(CNLine line, CNCallbackFunction function, void *pParam);



#ifdef	__cplusplus
}
#endif


#endif // __PIC32_halCN__

