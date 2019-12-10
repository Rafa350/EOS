#ifndef __PIC32_halGPIO__
#define	__PIC32_halGPIO__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t GPIOPort;
typedef uint8_t GPIOPin;
typedef uint16_t GPIOMask;
typedef uint32_t GPIOOptions;
typedef uint8_t GPIOAlt;

typedef struct {                  // Parametres d'inicialitzacio per pins
	GPIOPort port;                // -Identificador del port
	GPIOPin pin;                  // -Identificador del pin
	GPIOOptions options;          // -Opcions
	GPIOAlt alt;                  // -Funcio alternativa
} GPIOInitializePinInfo;

typedef struct {                  // Parametres d'inicialitzacio d'un port
	GPIOPort port;                // -Identificador del port
	GPIOMask mask;                // -Mascara de pins
	GPIOOptions options;          // -Opcions
	GPIOAlt alt;                  // -Funcio alternativa
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

extern const GPIOPortRegs gpioPortRegs[];


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
#define HAL_GPIO_POS_LO      ((GPIOMask) 0x00FF)
#define HAL_GPIO_POS_HI      ((GPIOMask) 0xFF00)
#define HAL_GPIO_POS_ALL     ((GPIOMask) 0xFFFF)


// Tipus de port
#define HAL_GPIO_MODE_pos         0u
#define HAL_GPIO_MODE_bits        0b111u
#define HAL_GPIO_MODE_mask        (HAL_GPIO_MODE_bits << HAL_GPIO_MODE_pos)

#define HAL_GPIO_MODE_INPUT       (0u << HAL_GPIO_MODE_pos) // -Entrada digital
#define HAL_GPIO_MODE_OUTPUT_PP   (1u << HAL_GPIO_MODE_pos) // -Sortida push-pull
#define HAL_GPIO_MODE_OUTPUT_OD   (2u << HAL_GPIO_MODE_pos) // -Sortida open-drain
#define HAL_GPIO_MODE_ALT_PP      (3u << HAL_GPIO_MODE_pos) // -Sortida alternativa push-pull
#define HAL_GPIO_MODE_ALT_OD      (4u << HAL_GPIO_MODE_pos) // -Sortida alternativa open-drain
#define HAL_GPIO_MODE_ANALOG      (5u << HAL_GPIO_MODE_pos) // -Entrada/Sortida Analgica

// Velocitat de conmutacio
#define HAL_GPIO_SPEED_pos        3u
#define HAL_GPIO_SPEED_bits       0b11u
#define HAL_GPIO_SPEED_mask       (HAL_GPIO_SPEED_bits << HAL_GPIO_SPEED_pos)

#define HAL_GPIO_SPEED_LOW        (0u << HAL_GPIO_SPEED_pos)
#define HAL_GPIO_SPEED_MEDIUM	  (1u << HAL_GPIO_SPEED_pos)
#define HAL_GPIO_SPEED_HIGH       (2u << HAL_GPIO_SPEED_pos)
#define HAL_GPIO_SPEED_FAST       (3u << HAL_GPIO_SPEED_pos)

// Resistencies pull-up
#define HAL_GPIO_PULL_pos         5u
#define HAL_GPIO_PULL_bits        0b11u
#define HAL_GPIO_PULL_mask        (HAL_GPIO_PULL_bits << HAL_GPIO_PULL_pos)

#define HAL_GPIO_PULL_NONE        (0u << HAL_GPIO_PULL_pos)
#define HAL_GPIO_PULL_UP          (1u << HAL_GPIO_PULL_pos)
#define HAL_GPIO_PULL_DOWN        (2u << HAL_GPIO_PULL_pos)

// Valor inicial de la sortida
#define HAL_GPIO_INIT_pos         7u
#define HAL_GPIO_INIT_bits        0b11u
#define HAL_GPIO_INIT_mask        (HAL_GPIO_INIT_bits << HAL_GPIO_INIT_pos)

#define HAL_GPIO_INIT_NOCHANGE    (0u << HAL_GPIO_INIT_pos)
#define HAL_GPIO_INIT_CLR         (1u << HAL_GPIO_INIT_pos)
#define HAL_GPIO_INIT_SET         (2u << HAL_GPIO_INIT_pos)

// Funcio alternativa
#define HAL_GPIO_AF_NONE          ((GPIOAlt) 0)


// Canvi d'entrada a sortida i viceversa
//
#define halGPIOModePinInput(portId, pin) \
    *gpioPortRegs[portId].trisSET = 1u << (pin)

#define halGPIOModePinOutput(portId, pin) \
    *gpioPortRegs[portId].trisCLR = 1u << (pin)

#define halGPIOModePortInput(portId, mask) \
    *gpioPortRegs[portId].trisSET = (mask)

#define halGPIOModePortOutput(portId, mask) \
    *gpioPortRegs[portId].trisCLR = (mask)

// Canvi del estat del pin
//
#define halGPIOSetPin(portId, pin) \
    *gpioPortRegs[portId].latSET = 1u << (pin)

#define halGPIOClearPin(portId, pin) \
    *gpioPortRegs[portId].latCLR = 1u << (pin)

#define halGPIOTogglePin(portId, pin) \
    *gpioPortRegs[portId].latINV = 1u << (pin)

// Lectura i escriptura del pin
//
#define halGPIOReadPin(portId, pin) \
    (*gpioPortRegs[portId].port & (1u << (pin))) != 0

#define halGPIOWritePin(portId, pin, data) \
    if (1) { \
        if (data) \
            *gpioPortRegs[portId].latSET = 1u << (pin); \
        else \
            *gpioPortRegs[portId].latCLR = 1u << (pin); \
    }

// Lectura i escriptura del port
//
#define halGPIOWritePort(portId, data) \
    *gpioPortRegs[portId].lat = (data)

#define halGPIOReadPort(portId) \
    *gpioPortRegs[portId].port


void halGPIOInitializePins(const GPIOInitializePinInfo *info, unsigned count);
void halGPIOInitializePin(GPIOPort port, GPIOPin pin, GPIOOptions options, GPIOAlt alt);

void halGPIOInitializePorts(const GPIOInitializePortInfo *info, unsigned count);
void halGPIOInitializePort(GPIOPort port, GPIOMask mask, GPIOOptions options, GPIOAlt alt);


#ifdef	__cplusplus
}
#endif


#endif // __PIC32_halGPIO__
