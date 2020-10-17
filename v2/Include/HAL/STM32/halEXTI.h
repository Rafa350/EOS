#ifndef __STM32_halEXTI__
#define __STM32_halEXTI__


#include "eos.h"
#include "hal/STM32/halGPIO.h"


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


// Mode de treball
#define HAL_EXTI_MODE_pos         0
#define HAL_EXTI_MODE_bits        0b11
#define HAL_EXTI_MODE_mask        (HAL_EXTI_MODE_bits << HAL_EXTI_MODE_pos)

#define HAL_EXTI_MODE_NONE        (0 << HAL_EXTI_MODE_pos)
#define HAL_EXTI_MODE_INT         (1 << HAL_EXTI_MODE_pos)
#define HAL_EXTI_MODE_EVENT       (2 << HAL_EXTI_MODE_pos)

// Disparador
#define HAL_EXTI_TRIGGER_pos      2
#define HAL_EXTI_TRIGGER_bits     0b11
#define HAL_EXTI_TRIGGER_mask     (HAL_EXTI_TRIGGER_bits << HAL_EXTI_TRIGGER_pos)

#define HAL_EXTI_TRIGGER_NONE     (0 << HAL_EXTI_TRIGGER_pos)
#define HAL_EXTI_TRIGGER_RISING   (1 << HAL_EXTI_TRIGGER_pos)
#define HAL_EXTI_TRIGGER_FALLING  (2 << HAL_EXTI_TRIGGER_pos)
#define HAL_EXTI_TRIGGER_CHANGING (3 << HAL_EXTI_TRIGGER_pos)


typedef uint32_t EXTIOptions;
typedef uint32_t EXTILine;

typedef void (*EXTIInterruptFunction)(EXTILine line, void *params);

typedef struct {
	uint32_t irqPriority;
	uint32_t irqSubPriority;
	EXTIInterruptFunction function;
	void *params;
} EXTIInitializeInfo;

typedef struct {
    GPIOPort port;
    GPIOPin pin;
    EXTIOptions options;
    EXTIInterruptFunction function;
    void *params;
} EXTIInitializePinInfo;


void halEXTIInitialize(const EXTIInitializeInfo *info);
void halEXTIInitializePins(const EXTIInitializePinInfo *info, int count);

void halEXTIEnableLine(EXTILine line);
void halEXTIDisableLine(EXTILine line);

void halEXTISetInterruptFunction(EXTILine line, EXTIInterruptFunction function, void *params);
void halEXTIEnableInterrupt(EXTILine line);
void halEXTIDisableInterrupt(EXTILine line);

#ifdef __cplusplus
}
#endif


#endif // __STM32_halEXTI__
