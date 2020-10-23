#ifndef __PIC32_halCN__
#define	__PIC32_halCN__


#include "eos.h"
#include "HAL/PIC32/halGPIO.h"


#ifdef	__cplusplus
extern "C" {
#endif


// Identificador de les linies
#define HAL_CN_LINE_0             0
#define HAL_CN_LINE_1             1
#define HAL_CN_LINE_2             2
#define HAL_CN_LINE_3             3
#define HAL_CN_LINE_4             4
#define HAL_CN_LINE_5             5
#define HAL_CN_LINE_6             6
#define HAL_CN_LINE_7             7
#define HAL_CN_LINE_8             8
#define HAL_CN_LINE_9             9
#define HAL_CN_LINE_10            10
#define HAL_CN_LINE_11            11
#define HAL_CN_LINE_12            12
#define HAL_CN_LINE_13            13
#define HAL_CN_LINE_14            14
#define HAL_CN_LINE_15            15
#define HAL_CN_LINE_16            16
#define HAL_CN_LINE_17            17
#define HAL_CN_LINE_18            18
#define HAL_CN_LINE_19            19
#define HAL_CN_LINE_20            20
#define HAL_CN_LINE_21            21
#define HAL_CN_LINE_NONE          0xFFFFFFFFF

#define HAL_CN_LINE_COUNT         22


// Identificador del port de cada linia
//
#if defined(__32MX460F512L__)
#define HAL_CN_LINE_0_PORT        HAL_GPIO_PORT_C
#define HAL_CN_LINE_1_PORT        HAL_GPIO_PORT_C
#define HAL_CN_LINE_2_PORT        HAL_GPIO_PORT_B
#define HAL_CN_LINE_3_PORT        HAL_GPIO_PORT_B
#define HAL_CN_LINE_4_PORT        HAL_GPIO_PORT_B
#define HAL_CN_LINE_5_PORT        HAL_GPIO_PORT_B
#define HAL_CN_LINE_6_PORT        HAL_GPIO_PORT_B
#define HAL_CN_LINE_7_PORT        HAL_GPIO_PORT_A
#define HAL_CN_LINE_8_PORT        HAL_GPIO_PORT_G
#define HAL_CN_LINE_9_PORT        HAL_GPIO_PORT_G
#define HAL_CN_LINE_10_PORT       HAL_GPIO_PORT_G
#define HAL_CN_LINE_11_PORT       HAL_GPIO_PORT_G
#define HAL_CN_LINE_12_PORT       HAL_GPIO_PORT_B
#define HAL_CN_LINE_13_PORT       HAL_GPIO_PORT_D
#define HAL_CN_LINE_14_PORT       HAL_GPIO_PORT_D
#define HAL_CN_LINE_15_PORT       HAL_GPIO_PORT_D
#define HAL_CN_LINE_16_PORT       HAL_GPIO_PORT_D
#define HAL_CN_LINE_17_PORT       HAL_GPIO_PORT_F
#define HAL_CN_LINE_18_PORT       HAL_GPIO_PORT_F
#define HAL_CN_LINE_19_PORT       HAL_GPIO_PORT_D
#define HAL_CN_LINE_20_PORT       HAL_GPIO_PORT_D
#define HAL_CN_LINE_21_PORT       HAL_GPIO_PORT_D
#endif


// Identificador del pin de cada linia
//
#if defined(__32MX460F512L__)
#define HAL_CN_LINE_0_PIN         HAL_GPIO_PIN_14
#define HAL_CN_LINE_1_PIN         HAL_GPIO_PIN_13
#define HAL_CN_LINE_2_PIN         HAL_GPIO_PIN_0
#define HAL_CN_LINE_3_PIN         HAL_GPIO_PIN_1
#define HAL_CN_LINE_4_PIN         HAL_GPIO_PIN_2
#define HAL_CN_LINE_5_PIN         HAL_GPIO_PIN_3
#define HAL_CN_LINE_6_PIN         HAL_GPIO_PIN_4
#define HAL_CN_LINE_7_PIN         HAL_GPIO_PIN_5
#define HAL_CN_LINE_8_PIN         HAL_GPIO_PIN_6
#define HAL_CN_LINE_9_PIN         HAL_GPIO_PIN_7
#define HAL_CN_LINE_10_PIN        HAL_GPIO_PIN_8
#define HAL_CN_LINE_11_PIN        HAL_GPIO_PIN_9
#define HAL_CN_LINE_12_PIN        HAL_GPIO_PIN_15
#define HAL_CN_LINE_13_PIN        HAL_GPIO_PIN_4
#define HAL_CN_LINE_14_PIN        HAL_GPIO_PIN_5
#define HAL_CN_LINE_15_PIN        HAL_GPIO_PIN_6
#define HAL_CN_LINE_16_PIN        HAL_GPIO_PIN_7
#define HAL_CN_LINE_17_PIN        HAL_GPIO_PIN_4
#define HAL_CN_LINE_18_PIN        HAL_GPIO_PIN_5
#define HAL_CN_LINE_19_PIN        HAL_GPIO_PIN_13
#define HAL_CN_LINE_20_PIN        HAL_GPIO_PIN_14
#define HAL_CN_LINE_21_PIN        HAL_GPIO_PIN_5
#endif


// Disparador
#define HAL_CN_TRIGGER_POS        0
#define HAL_CN_TRIGGER_BITS       0b11
#define HAL_CN_TRIGGER_MASK       (HAL_CN_TRIGGER_BITS << HAL_CN_TRIGGER_POS)

#define HAL_CN_TRIGGER_NONE       (0 << HAL_CN_TRIGGER_POS)
#define HAL_CN_TRIGGER_RISING     (1 << HAL_CN_TRIGGER_POS)
#define HAL_CN_TRIGGER_FALLING    (2 << HAL_CN_TRIGGER_POS)
#define HAL_CN_TRIGGER_CHANGING   (3 << HAL_CN_TRIGGER_POS)

// Pull up
#define HAL_CN_PULL_POS           2
#define HAL_CN_PULL_BITS          0b1
#define HAL_CN_PULL_MASK          (HAL_CN_PULL_BITS << HAL_CN_PULL_POS)

#define HAL_CN_PULL_NONE          (0 << HAL_CN_PULL_POS)
#define HAL_CN_PULL_UP            (1 << HAL_CN_PULL_POS)

// Activar
#define HAL_CN_ENABLE_POS         3
#define HAL_CN_ENABLE_BITS        0b1
#define HAL_CN_ENABLE_MASK        (HAL_CN_ENABLE_BITS << HAL_CN_ENABLE_POS)

#define HAL_CN_ENABLE_NO          (0 << HAL_CN_ENABLE_POS)
#define HAL_CN_ENABLE_YES         (1 << HAL_CN_ENABLE_POS)

// Events
#define HAL_CN_EVENT_TRIGGER      0x1
#define HAL_CN_EVENT_ALL          0x1


typedef uint32_t CNLine;
typedef uint32_t CNOptions;

typedef void (*CNInterruptFunction)(CNLine line, void* params, uint32_t event);

typedef struct {
    CNLine line;
    CNOptions options;
} CNInitializeLineInfo;


void halCNInitializeLine(CNLine line, CNOptions options);
void halCNInitializeLines(const CNInitializeLineInfo* info, uint32_t count);

void halCNEnableLine(CNLine line);
void halCNDisableLine(CNLine line);

void halCNSetInterruptFunction(CNLine line, CNInterruptFunction function, void* params);
void halCNInterruptHandler();

void halCNEnableInterrupts();
uint32_t halCNDisableInterrupts();

bool halCNGetInterruptFlag();
void halCNClearInterruptFlags();

#define __halCNGetInterruptSourceFlag()      IFS1bits.CNIF
#define __halCNClearInterruptSourceFlag()    IFS1bits.CNIF = 0


#ifdef	__cplusplus
}
#endif


#endif // __PIC32_halCN__

