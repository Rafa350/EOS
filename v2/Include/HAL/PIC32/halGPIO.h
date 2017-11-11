#ifndef __PIC32_halGPIO__
#define	__PIC32_halGPIO__


#include <xc.h>
#include <stdint.h>


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct {                  // Parametres d'inicialitzacio per pins
	uint8_t port;                 // -Identificador del port
	uint8_t pin;                  // -Identificador del pin
	uint32_t options;             // -Opcions
	uint8_t alt;                  // -Funcio alternativa
} GPIOInitializePinInfo;

typedef struct {                  // Parametres d'inicialitzacio d'un port
	uint8_t port;                 // -Identificador del port
	uint16_t mask;                // -Mascara de pins
	uint32_t options;             // -Opcions
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
#define HAL_GPIO_PORT_A      0
#endif
#if defined(PORTB)
#define HAL_GPIO_PORT_B      1
#endif
#if defined(PORTC)
#define HAL_GPIO_PORT_C      2
#endif
#if defined(PORTD)
#define HAL_GPIO_PORT_D      3
#endif
#if defined(PORTE)
#define HAL_GPIO_PORT_E      4
#endif
#if defined(PORTF)
#define HAL_GPIO_PORT_F      5
#endif
#if defined(PORTG)
#define HAL_GPIO_PORT_G      6
#endif
#define HAL_GPIO_PORT_NONE   255


// Identificador dels pins
#define HAL_GPIO_PIN_0       0
#define HAL_GPIO_PIN_1       1
#define HAL_GPIO_PIN_2       2
#define HAL_GPIO_PIN_3       3
#define HAL_GPIO_PIN_4       4
#define HAL_GPIO_PIN_5       5
#define HAL_GPIO_PIN_6       6
#define HAL_GPIO_PIN_7       7
#define HAL_GPIO_PIN_8       8
#define HAL_GPIO_PIN_9       9
#define HAL_GPIO_PIN_10      10
#define HAL_GPIO_PIN_11      11
#define HAL_GPIO_PIN_12      12
#define HAL_GPIO_PIN_13      13
#define HAL_GPIO_PIN_14      14
#define HAL_GPIO_PIN_15      15
#define HAL_GPIO_PIN_NONE    255


// Mascara de posicio dels pins
#define HAL_GPIO_POS_0       ((uint32_t) 1 << HAL_GPIO_PIN_0)
#define HAL_GPIO_POS_1       ((uint32_t) 1 << HAL_GPIO_PIN_1)
#define HAL_GPIO_POS_2       ((uint32_t) 1 << HAL_GPIO_PIN_2)
#define HAL_GPIO_POS_3       ((uint32_t) 1 << HAL_GPIO_PIN_3)
#define HAL_GPIO_POS_4       ((uint32_t) 1 << HAL_GPIO_PIN_4)
#define HAL_GPIO_POS_5       ((uint32_t) 1 << HAL_GPIO_PIN_5)
#define HAL_GPIO_POS_6       ((uint32_t) 1 << HAL_GPIO_PIN_6)
#define HAL_GPIO_POS_7       ((uint32_t) 1 << HAL_GPIO_PIN_7)
#define HAL_GPIO_POS_8       ((uint32_t) 1 << HAL_GPIO_PIN_8)
#define HAL_GPIO_POS_9       ((uint32_t) 1 << HAL_GPIO_PIN_9)
#define HAL_GPIO_POS_10      ((uint32_t) 1 << HAL_GPIO_PIN_10)
#define HAL_GPIO_POS_11      ((uint32_t) 1 << HAL_GPIO_PIN_11)
#define HAL_GPIO_POS_12      ((uint32_t) 1 << HAL_GPIO_PIN_12)
#define HAL_GPIO_POS_13      ((uint32_t) 1 << HAL_GPIO_PIN_13)
#define HAL_GPIO_POS_14      ((uint32_t) 1 << HAL_GPIO_PIN_14)
#define HAL_GPIO_POS_15      ((uint32_t) 1 << HAL_GPIO_PIN_15)


// Tipus de port
#define HAL_GPIO_MODE_OFFSET      0
#define HAL_GPIO_MODE_MASK        0b1111

#define HAL_GPIO_MODE_INPUT       (0 << HAL_GPIO_MODE_OFFSET)   // -Entrada digital
#define HAL_GPIO_MODE_OUTPUT_PP   (1 << HAL_GPIO_MODE_OFFSET)   // -Sortida push-pull
#define HAL_GPIO_MODE_OUTPUT_OD   (2 << HAL_GPIO_MODE_OFFSET)   // -Sortida open-drain
#define HAL_GPIO_MODE_ALT_PP      (3 << HAL_GPIO_MODE_OFFSET)   // -Sortida alternativa push-pull
#define HAL_GPIO_MODE_ALT_OD      (4 << HAL_GPIO_MODE_OFFSET)   // -Sortida alternativa open-drain
#define HAL_GPIO_MODE_ANALOG      (5 << HAL_GPIO_MODE_OFFSET)   // -Entrada/Sortida Analgica


// Velocitat de conmutacio
#define HAL_GPIO_SPEED_OFFSET     4
#define HAL_GPIO_SPEED_MASK       0b11

#define HAL_GPIO_SPEED_LOW        (0 << HAL_GPIO_SPEED_OFFSET)
#define HAL_GPIO_SPEED_MEDIUM	  (1 << HAL_GPIO_SPEED_OFFSET)
#define HAL_GPIO_SPEED_HIGH       (2 << HAL_GPIO_SPEED_OFFSET)
#define HAL_GPIO_SPEED_FAST       (3 << HAL_GPIO_SPEED_OFFSET)

// Resistencies pull-up
#define HAL_GPIO_PULL_OFFSET      6
#define HAL_GPIO_PULL_MASK        0b11

#define HAL_GPIO_PULL_NONE        (0 << HAL_GPIO_PULL_OFFSET)
#define HAL_GPIO_PULL_UP          (1 << HAL_GPIO_PULL_OFFSET)
#define HAL_GPIO_PULL_DOWN        (2 << HAL_GPIO_PULL_OFFSET)

// Valor inicial de la sortida
#define HAL_GPIO_INIT_OFFSET      8
#define HAL_GPIO_INIT_MASK        0b11

#define HAL_GPIO_INIT_CLR         (0 << HAL_GPIO_INIT_OFFSET)
#define HAL_GPIO_INIT_SET         (1 << HAL_GPIO_INIT_OFFSET)


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


void halGPIOInitializePins(const GPIOInitializePinInfo *info, uint8_t count);
void halGPIOInitializePin(const GPIOInitializePinInfo *info);

void halGPIOInitializePorts(const GPIOInitializePortInfo *info, uint8_t count);
void halGPIOInitializePort(const GPIOInitializePortInfo *info);

void halGPIOInitialize(uint8_t port, uint8_t pin, uint32_t options, uint8_t alt);


#ifdef	__cplusplus
}
#endif


#endif // __PIC32_halGPIO__
