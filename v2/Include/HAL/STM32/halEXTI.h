#ifndef __STM32_halEXTI__
#define __STM32_halEXTI__


#include "HAL/hal.h"
#include "HAL/STM32/halGPIO.h"


#ifdef	__cplusplus
extern "C" {
#endif


// Linies configurables asignades a PINs GPIO
#define HAL_EXTI_LINE_0           0    // Px0
#define HAL_EXTI_LINE_1           1    // Px1
#define HAL_EXTI_LINE_2           2    // Px2
#define HAL_EXTI_LINE_3           3    // Px3
#define HAL_EXTI_LINE_4           4    // Px4
#define HAL_EXTI_LINE_5           5    // Px5
#define HAL_EXTI_LINE_6           6    // Px6
#define HAL_EXTI_LINE_7           7    // Px7
#define HAL_EXTI_LINE_8           8    // Px8
#define HAL_EXTI_LINE_9           9    // Px9
#define HAL_EXTI_LINE_10          10   // Px10
#define HAL_EXTI_LINE_11          11   // Px11
#define HAL_EXTI_LINE_12          12   // Px12
#define HAL_EXTI_LINE_13          13   // Px13
#define HAL_EXTI_LINE_14          14   // Px14
#define HAL_EXTI_LINE_15          15   // Px15

// Linies fixes asignades a moduls interns
#define HAL_EXTI_LINE_16          16   // PVD output
#define HAL_EXTI_LINE_17          17   // RTC alarm event
#define HAL_EXTI_LINE_18          18   // USB OTG FS
#define HAL_EXTI_LINE_19          19   // Ethernet wakeup
#define HAL_EXTI_LINE_20          20   // USB OTG HS
#define HAL_EXTI_LINE_21          21   // RTC tamper and timestamp events
#define HAL_EXTI_LINE_22          22   // RTC wakeup event
#define HAL_EXTI_LINE_23          23   // LPTIM1 asynchronous event
#define HAL_EXTI_LINE_24          24   // MDIO slave asynchronous interrupt


// Opcions: Mode de treball INT/EVENT
#define HAL_EXTI_MODE_pos         0
#define HAL_EXTI_MODE_bits        0b11
#define HAL_EXTI_MODE_mask        (HAL_EXTI_MODE_bits << HAL_EXTI_MODE_pos)

#define HAL_EXTI_MODE_NONE        (0 << HAL_EXTI_MODE_pos)
#define HAL_EXTI_MODE_INT         (1 << HAL_EXTI_MODE_pos)
#define HAL_EXTI_MODE_EVENT       (2 << HAL_EXTI_MODE_pos)

// Opcions: Flanc a detectar
#define HAL_EXTI_TRIGGER_pos      2
#define HAL_EXTI_TRIGGER_bits     0b11
#define HAL_EXTI_TRIGGER_mask     (HAL_EXTI_TRIGGER_bits << HAL_EXTI_TRIGGER_pos)

#define HAL_EXTI_TRIGGER_NONE     (0 << HAL_EXTI_TRIGGER_pos)
#define HAL_EXTI_TRIGGER_RISING   (1 << HAL_EXTI_TRIGGER_pos)
#define HAL_EXTI_TRIGGER_FALLING  (2 << HAL_EXTI_TRIGGER_pos)
#define HAL_EXTI_TRIGGER_CHANGING (3 << HAL_EXTI_TRIGGER_pos)

// Opcions: Port a capturar
#define HAL_EXTI_PORT_pos         4
#define HAL_EXTI_PORT_bits        0b1111
#define HAL_EXTI_PORT_mask        (HAL_EXTI_PORT_bits << HAL_EXTI_PORT_pos)

#define HAL_EXTI_PORT_A           (0 << HAL_EXTI_PORT_pos)
#define HAL_EXTI_PORT_B           (1 << HAL_EXTI_PORT_pos)
#define HAL_EXTI_PORT_C           (2 << HAL_EXTI_PORT_pos)
#define HAL_EXTI_PORT_D           (3 << HAL_EXTI_PORT_pos)
#define HAL_EXTI_PORT_E           (4 << HAL_EXTI_PORT_pos)
#define HAL_EXTI_PORT_F           (5 << HAL_EXTI_PORT_pos)
#define HAL_EXTI_PORT_G           (6 << HAL_EXTI_PORT_pos)
#define HAL_EXTI_PORT_H           (7 << HAL_EXTI_PORT_pos)
#define HAL_EXTI_PORT_I           (8 << HAL_EXTI_PORT_pos)
#define HAL_EXTI_PORT_J           (9 << HAL_EXTI_PORT_pos)
#define HAL_EXTI_PORT_K           (10 << HAL_EXTI_PORT_pos)


typedef uint32_t EXTILine;
typedef uint32_t EXTIOptions;

typedef void (*EXTIInterruptFunction)(EXTILine line, void *params);

typedef struct {
    EXTILine line;
    EXTIOptions options;
    EXTIInterruptFunction isrFunction;
    void *isrParams;
} EXTIPinSettings;


void halEXTIInitializePins(const EXTIPinSettings *settings, uint32_t count);

void halEXTISetInterruptFunction(EXTILine line, EXTIInterruptFunction function, void *params);
void halEXTIEnableInterrupt(EXTILine line);
bool halEXTIDisableInterrupt(EXTILine line);

#ifdef __cplusplus
}
#endif


#endif // __STM32_halEXTI__
