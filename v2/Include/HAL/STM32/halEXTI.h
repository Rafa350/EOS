#ifndef __STM32_halEXTI__
#define __STM32_halEXTI__


#include "eos.h"
#include "hal/STM32/halGPIO.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint32_t EXTIOptions;
typedef uint8_t EXTILine;

typedef void (*EXTICallbackFunction)(EXTILine line, void *pParam);

typedef struct {
	uint32_t irqPriority;
	uint32_t irqSubPriority;
	EXTICallbackFunction function;
	void *pParam;
} EXTIInitializeInfo;

typedef struct {
    GPIOPort port;
    GPIOPin pin;
    EXTIOptions options;
    EXTICallbackFunction function;
    void *pParam;
} EXTIInitializePinInfo;


// Linies configurables asignades a PINs GPIO
#define HAL_EXTI_LINE_0           ((EXTILine) 0)      // Px0
#define HAL_EXTI_LINE_1           ((EXTILine) 1)      // Px1
#define HAL_EXTI_LINE_2           ((EXTILine) 2)      // Px2
#define HAL_EXTI_LINE_3           ((EXTILine) 3)      // Px3
#define HAL_EXTI_LINE_4           ((EXTILine) 4)      // Px4
#define HAL_EXTI_LINE_5           ((EXTILine) 5)      // Px5
#define HAL_EXTI_LINE_6           ((EXTILine) 6)      // Px6
#define HAL_EXTI_LINE_7           ((EXTILine) 7)      // Px7
#define HAL_EXTI_LINE_8           ((EXTILine) 8)      // Px8
#define HAL_EXTI_LINE_9           ((EXTILine) 9)      // Px9
#define HAL_EXTI_LINE_10          ((EXTILine) 10)     // Px10
#define HAL_EXTI_LINE_11          ((EXTILine) 11)     // Px11
#define HAL_EXTI_LINE_12          ((EXTILine) 12)     // Px12
#define HAL_EXTI_LINE_13          ((EXTILine) 13)     // Px13
#define HAL_EXTI_LINE_14          ((EXTILine) 14)     // Px14
#define HAL_EXTI_LINE_15          ((EXTILine) 15)     // Px15

// Linies fixes asignades a moduls interns
#define HAL_EXTI_LINE_16          ((EXTILine) 16)     // PVD output
#define HAL_EXTI_LINE_17          ((EXTILine) 17)     // RTC alarm event
#define HAL_EXTI_LINE_18          ((EXTILine) 18)     // USB OTG FS
#define HAL_EXTI_LINE_19          ((EXTILine) 19)     // Ethernet wakeup
#define HAL_EXTI_LINE_20          ((EXTILine) 20)     // USB OTG HS
#define HAL_EXTI_LINE_21          ((EXTILine) 21)     // RTC tamper and timestamp events
#define HAL_EXTI_LINE_22          ((EXTILine) 22)     // RTC wakeup event
#define HAL_EXTI_LINE_23          ((EXTILine) 23)     // LPTIM1 asynchronous event
#define HAL_EXTI_LINE_24          ((EXTILine) 24)     // MDIO slave asynchronous interrupt


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


void halEXTIInitialize(const EXTIInitializeInfo *pInfo);
void halEXTIInitializePins(const EXTIInitializePinInfo *pInfo, unsigned count);
void halEXTIEnableLine(EXTILine line);
void halEXTIDisableLine(EXTILine line);
void halEXTISetCallbackFunction(EXTILine line, EXTICallbackFunction function, void *pParam);


#ifdef __cplusplus
}
#endif


#endif // __STM32_halEXTI__
