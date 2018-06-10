#ifndef __PIC32_halGPIO__
#define	__PIC32_halGPIO__


#include <xc.h>
#include <stdint.h>


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t GPIOPort;
typedef uint8_t GPIOPin;
typedef uint16_t GPIOMask;
typedef uint32_t GPIOOptions;

typedef struct {                  // Parametres d'inicialitzacio per pins
	GPIOPort port;                // -Identificador del port
	GPIOPin pin;                  // -Identificador del pin
	GPIOOptions options;          // -Opcions
	uint8_t alt;                  // -Funcio alternativa
} GPIOInitializePinInfo;

typedef struct {                  // Parametres d'inicialitzacio d'un port
	GPIOPort port;                // -Identificador del port
	GPIOMask mask;                // -Mascara de pins
	GPIOOptions options;          // -Opcions
	uint8_t alt;                  // -Funcio alternativa
} GPIOInitializePortInfo;

typedef struct {                  // Registres de hardware
	uint32_t volatile *trisSET;   // -Registre TRIS
	uint32_t volatile *trisCLR;
	uint32_t volatile *odcSET;    // -Registre ODC
	uint32_t volatile *odcCLR;
	uint32_t volatile *latSET;    // -Registre LAT
	uint32_t volatile *latCLR;
	uint32_t volatile *latINV;
	uint32_t volatile *lat;
	uint32_t volatile *port;      // -Registre PORT
} GPIOPortRegs;

extern GPIOPortRegs gpioPortRegs[];


// Identificador dels ports
#if defined(PORTA)
#define HAL_GPIO_PORT_A      ((GPIOPort) 0)
#endif
#if defined(PORTB)
#define HAL_GPIO_PORT_B      ((GPIOPort) 1)
#endif
#if defined(PORTC)
#define HAL_GPIO_PORT_C      ((GPIOPort) 2)
#endif
#if defined(PORTD)
#define HAL_GPIO_PORT_D      ((GPIOPort) 3)
#endif
#if defined(PORTE)
#define HAL_GPIO_PORT_E      ((GPIOPort) 4)
#endif
#if defined(PORTF)
#define HAL_GPIO_PORT_F      ((GPIOPort) 5)
#endif
#if defined(PORTG)
#define HAL_GPIO_PORT_G      ((GPIOPort) 6)
#endif
#define HAL_GPIO_PORT_NONE   ((GPIOPort) 255)


// Identificador dels pins
#define HAL_GPIO_PIN_0       ((GPIOPin) 0)
#define HAL_GPIO_PIN_1       ((GPIOPin) 1)
#define HAL_GPIO_PIN_2       ((GPIOPin) 2)
#define HAL_GPIO_PIN_3       ((GPIOPin) 3)
#define HAL_GPIO_PIN_4       ((GPIOPin) 4)
#define HAL_GPIO_PIN_5       ((GPIOPin) 5)
#define HAL_GPIO_PIN_6       ((GPIOPin) 6)
#define HAL_GPIO_PIN_7       ((GPIOPin) 7)
#define HAL_GPIO_PIN_8       ((GPIOPin) 8)
#define HAL_GPIO_PIN_9       ((GPIOPin) 9)
#define HAL_GPIO_PIN_10      ((GPIOPin) 10)
#define HAL_GPIO_PIN_11      ((GPIOPin) 11)
#define HAL_GPIO_PIN_12      ((GPIOPin) 12)
#define HAL_GPIO_PIN_13      ((GPIOPin) 13)
#define HAL_GPIO_PIN_14      ((GPIOPin) 14)
#define HAL_GPIO_PIN_15      ((GPIOPin) 15)
#define HAL_GPIO_PIN_NONE    ((GPIOPin) 255)


// Mascara de posicio dels pins
#define HAL_GPIO_POS_0       ((GPIOMask) 1 << HAL_GPIO_PIN_0)
#define HAL_GPIO_POS_1       ((GPIOMask) 1 << HAL_GPIO_PIN_1)
#define HAL_GPIO_POS_2       ((GPIOMask) 1 << HAL_GPIO_PIN_2)
#define HAL_GPIO_POS_3       ((GPIOMask) 1 << HAL_GPIO_PIN_3)
#define HAL_GPIO_POS_4       ((GPIOMask) 1 << HAL_GPIO_PIN_4)
#define HAL_GPIO_POS_5       ((GPIOMask) 1 << HAL_GPIO_PIN_5)
#define HAL_GPIO_POS_6       ((GPIOMask) 1 << HAL_GPIO_PIN_6)
#define HAL_GPIO_POS_7       ((GPIOMask) 1 << HAL_GPIO_PIN_7)
#define HAL_GPIO_POS_8       ((GPIOMask) 1 << HAL_GPIO_PIN_8)
#define HAL_GPIO_POS_9       ((GPIOMask) 1 << HAL_GPIO_PIN_9)
#define HAL_GPIO_POS_10      ((GPIOMask) 1 << HAL_GPIO_PIN_10)
#define HAL_GPIO_POS_11      ((GPIOMask) 1 << HAL_GPIO_PIN_11)
#define HAL_GPIO_POS_12      ((GPIOMask) 1 << HAL_GPIO_PIN_12)
#define HAL_GPIO_POS_13      ((GPIOMask) 1 << HAL_GPIO_PIN_13)
#define HAL_GPIO_POS_14      ((GPIOMask) 1 << HAL_GPIO_PIN_14)
#define HAL_GPIO_POS_15      ((GPIOMask) 1 << HAL_GPIO_PIN_15)


// Tipus de port
#define HAL_GPIO_MODE_OFFSET      0
#define HAL_GPIO_MODE_BITS        0b1111
#define HAL_GPIO_MODE_MASK        (HAL_GPIO_MODE_BITS << HAL_GPIO_MODE_OFFSET)

#define HAL_GPIO_MODE_INPUT       (0 << HAL_GPIO_MODE_OFFSET)   // -Entrada digital
#define HAL_GPIO_MODE_OUTPUT_PP   (1 << HAL_GPIO_MODE_OFFSET)   // -Sortida push-pull
#define HAL_GPIO_MODE_OUTPUT_OD   (2 << HAL_GPIO_MODE_OFFSET)   // -Sortida open-drain
#define HAL_GPIO_MODE_ALT_PP      (3 << HAL_GPIO_MODE_OFFSET)   // -Sortida alternativa push-pull
#define HAL_GPIO_MODE_ALT_OD      (4 << HAL_GPIO_MODE_OFFSET)   // -Sortida alternativa open-drain
#define HAL_GPIO_MODE_ANALOG      (5 << HAL_GPIO_MODE_OFFSET)   // -Entrada/Sortida Analgica


// Velocitat de conmutacio
#define HAL_GPIO_SPEED_OFFSET     4
#define HAL_GPIO_SPEED_BITS       0b11
#define HAL_GPIO_SPEED_MASK       (HAL_GPIO_SPEED_BITS << HAL_GPIO_SPEED_OFFSET)

#define HAL_GPIO_SPEED_LOW        (0 << HAL_GPIO_SPEED_OFFSET)
#define HAL_GPIO_SPEED_MEDIUM	  (1 << HAL_GPIO_SPEED_OFFSET)
#define HAL_GPIO_SPEED_HIGH       (2 << HAL_GPIO_SPEED_OFFSET)
#define HAL_GPIO_SPEED_FAST       (3 << HAL_GPIO_SPEED_OFFSET)

// Resistencies pull-up
#define HAL_GPIO_PULL_OFFSET      6
#define HAL_GPIO_PULL_BITS        0b11
#define HAL_GPIO_PULL_MASK        (HAL_GPIO_PULL_BITS << HAL_GPIO_PULL_OFFSET)

#define HAL_GPIO_PULL_NONE        (0 << HAL_GPIO_PULL_OFFSET)
#define HAL_GPIO_PULL_UP          (1 << HAL_GPIO_PULL_OFFSET)
#define HAL_GPIO_PULL_DOWN        (2 << HAL_GPIO_PULL_OFFSET)

// Valor inicial de la sortida
#define HAL_GPIO_INIT_OFFSET      8
#define HAL_GPIO_INIT_BITS        0b11
#define HAL_GPIO_INIT_MASK        (HAL_GPIO_INIT_BITS << HAL_GPIO_INIT_OFFSET)

#define HAL_GPIO_INIT_CLR         (0 << HAL_GPIO_INIT_OFFSET)
#define HAL_GPIO_INIT_SET         (1 << HAL_GPIO_INIT_OFFSET)

// Funcio alternativa 
#define HAL_GPIO_AF_NONE          0


#define halGPIOInitializePinInput(port, pin) \
    *gpioPortRegs[port].trisSET = 1 << (pin) 

#define halGPIOInitializePinOutput(port, pin) \
    *gpioPortRegs[port].trisCLR = 1 << (pin)

#define halGPIOSetPin(port, pin) \
    *gpioPortRegs[port].latSET = 1 << (pin)

#define halGPIOClearPin(port, pin) \
    *gpioPortRegs[port].latCLR = 1 << (pin)

#define halGPIOTogglePin(port, pin) \
    *gpioPortRegs[port].latINV = 1 << (pin)

#define halGPIOReadPin(portId, pin) \
    (*gpioPortRegs[portId].port & (1 << (pin))) != 0

#define halGPIOWritePin(port, pin, data) \
    if (data) \
        *gpioPortRegs[port].latSET = 1 << (pin); \
    else \
        *gpioPortRegs[port].latCLR = 1 << (pin)

#define halGPIOWritePort(port, data) \
    *gpioPortRegs[port].lat = data

#define halGPIOReadPort(port) \
    *gpioPortRegs[port].lat


void halGPIOInitializePins(const GPIOInitializePinInfo *info, unsigned count);
void halGPIOInitializePin(const GPIOInitializePinInfo *info);

void halGPIOInitializePorts(const GPIOInitializePortInfo *info, unsigned count);
void halGPIOInitializePort(const GPIOInitializePortInfo *info);

void halGPIOInitialize(GPIOPort port, GPIOPin pin, uint32_t options, uint8_t alt);


#ifdef	__cplusplus
}
#endif


#endif // __PIC32_halGPIO__
