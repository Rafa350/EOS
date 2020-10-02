#ifndef __PIC32_halGPIO__
#define	__PIC32_halGPIO__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif

    
// Estructura de registres de cada port    
typedef struct __attribute__((packed , aligned(4))) {
    volatile uint32_t TRISx;
    volatile uint32_t TRISxCLR;
    volatile uint32_t TRISxSET;
    volatile uint32_t TRISxINV;
    volatile uint32_t PORTx;
    volatile uint32_t PORTxCLR;
    volatile uint32_t PORTxSET;
    volatile uint32_t PORTxINV;
    volatile uint32_t LATx;
    volatile uint32_t LATxCLR;
    volatile uint32_t LATxSET;
    volatile uint32_t LATxINV;
    volatile uint32_t ODCx;
    volatile uint32_t ODCxCLR;
    volatile uint32_t ODCxSET;
    volatile uint32_t ODCxINV;
} GPIORegisters;

typedef uint32_t GPIOPort;
typedef uint32_t GPIOPin;
typedef uint32_t GPIOMask;
typedef uint32_t GPIOOptions;
typedef uint32_t GPIOAlt;

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


// Adresses base de cada port
#define HAL_GPIO_ADDR_A           (_PORTA_BASE_ADDRESS - 0x10)
#define HAL_GPIO_ADDR_B           (_PORTB_BASE_ADDRESS - 0x10)
#define HAL_GPIO_ADDR_C           (_PORTC_BASE_ADDRESS - 0x10)
#define HAL_GPIO_ADDR_D           (_PORTD_BASE_ADDRESS - 0x10)
#define HAL_GPIO_ADDR_E           (_PORTE_BASE_ADDRESS - 0x10)
#define HAL_GPIO_ADDR_F           (_PORTF_BASE_ADDRESS - 0x10)
#define HAL_GPIO_ADDR_G           (_PORTG_BASE_ADDRESS - 0x10)

// Identificador dels ports
#if defined(_PORTA)
#define HAL_GPIO_PORT_A           HAL_GPIO_ADDR_A
#endif
#if defined(_PORTB)
#define HAL_GPIO_PORT_B           HAL_GPIO_ADDR_B
#endif
#if defined(_PORTC)
#define HAL_GPIO_PORT_C           HAL_GPIO_ADDR_C
#endif
#if defined(_PORTD)
#define HAL_GPIO_PORT_D           HAL_GPIO_ADDR_D
#endif
#if defined(_PORTE)
#define HAL_GPIO_PORT_E           HAL_GPIO_ADDR_E
#endif
#if defined(_PORTF)
#define HAL_GPIO_PORT_F           HAL_GPIO_ADDR_F
#endif
#if defined(_PORTG)
#define HAL_GPIO_PORT_G           HAL_GPIO_ADDR_G
#endif
#define HAL_GPIO_PORT_NONE        0

// Identificador dels pins
#define HAL_GPIO_PIN_0            0
#define HAL_GPIO_PIN_1            1
#define HAL_GPIO_PIN_2            2
#define HAL_GPIO_PIN_3            3
#define HAL_GPIO_PIN_4            4
#define HAL_GPIO_PIN_5            5
#define HAL_GPIO_PIN_6            6
#define HAL_GPIO_PIN_7            7
#define HAL_GPIO_PIN_8            8
#define HAL_GPIO_PIN_9            9
#define HAL_GPIO_PIN_10           10
#define HAL_GPIO_PIN_11           11
#define HAL_GPIO_PIN_12           12
#define HAL_GPIO_PIN_13           13
#define HAL_GPIO_PIN_14           14
#define HAL_GPIO_PIN_15           15
#define HAL_GPIO_PIN_NONE         255

// Mascara de posicio dels pins
#define HAL_GPIO_POS_0            (1 << HAL_GPIO_PIN_0)
#define HAL_GPIO_POS_1            (1 << HAL_GPIO_PIN_1)
#define HAL_GPIO_POS_2            (1 << HAL_GPIO_PIN_2)
#define HAL_GPIO_POS_3            (1 << HAL_GPIO_PIN_3)
#define HAL_GPIO_POS_4            (1 << HAL_GPIO_PIN_4)
#define HAL_GPIO_POS_5            (1 << HAL_GPIO_PIN_5)
#define HAL_GPIO_POS_6            (1 << HAL_GPIO_PIN_6)
#define HAL_GPIO_POS_7            (1 << HAL_GPIO_PIN_7)
#define HAL_GPIO_POS_8            (1 << HAL_GPIO_PIN_8)
#define HAL_GPIO_POS_9            (1 << HAL_GPIO_PIN_9)
#define HAL_GPIO_POS_10           (1 << HAL_GPIO_PIN_10)
#define HAL_GPIO_POS_11           (1 << HAL_GPIO_PIN_11)
#define HAL_GPIO_POS_12           (1 << HAL_GPIO_PIN_12)
#define HAL_GPIO_POS_13           (1 << HAL_GPIO_PIN_13)
#define HAL_GPIO_POS_14           (1 << HAL_GPIO_PIN_14)
#define HAL_GPIO_POS_15           (1 << HAL_GPIO_PIN_15)
#define HAL_GPIO_POS_LO           0x000000FF
#define HAL_GPIO_POS_HI           0x0000FF00
#define HAL_GPIO_POS_ALL          0x0000FFFF

// Tipus de port
#define HAL_GPIO_MODE_pos         0
#define HAL_GPIO_MODE_bits        0b111
#define HAL_GPIO_MODE_mask        (HAL_GPIO_MODE_bits << HAL_GPIO_MODE_pos)

#define HAL_GPIO_MODE_INPUT       (0 << HAL_GPIO_MODE_pos) // -Entrada digital
#define HAL_GPIO_MODE_OUTPUT_PP   (1 << HAL_GPIO_MODE_pos) // -Sortida push-pull
#define HAL_GPIO_MODE_OUTPUT_OD   (2 << HAL_GPIO_MODE_pos) // -Sortida open-drain
#define HAL_GPIO_MODE_ALT_PP      (3 << HAL_GPIO_MODE_pos) // -Sortida alternativa push-pull
#define HAL_GPIO_MODE_ALT_OD      (4 << HAL_GPIO_MODE_pos) // -Sortida alternativa open-drain
#define HAL_GPIO_MODE_ANALOG      (5 << HAL_GPIO_MODE_pos) // -Entrada/Sortida Analgica

// Velocitat de conmutacio
#define HAL_GPIO_SPEED_pos        3
#define HAL_GPIO_SPEED_bits       0b11
#define HAL_GPIO_SPEED_mask       (HAL_GPIO_SPEED_bits << HAL_GPIO_SPEED_pos)

#define HAL_GPIO_SPEED_LOW        (0 << HAL_GPIO_SPEED_pos)
#define HAL_GPIO_SPEED_MEDIUM	  (1 << HAL_GPIO_SPEED_pos)
#define HAL_GPIO_SPEED_HIGH       (2 << HAL_GPIO_SPEED_pos)
#define HAL_GPIO_SPEED_FAST       (3 << HAL_GPIO_SPEED_pos)

// Resistencies pull-up
#define HAL_GPIO_PULL_pos         5
#define HAL_GPIO_PULL_bits        0b11
#define HAL_GPIO_PULL_mask        (HAL_GPIO_PULL_bits << HAL_GPIO_PULL_pos)

#define HAL_GPIO_PULL_NONE        (0 << HAL_GPIO_PULL_pos)
#define HAL_GPIO_PULL_UP          (1 << HAL_GPIO_PULL_pos)
#define HAL_GPIO_PULL_DOWN        (2 << HAL_GPIO_PULL_pos)

// Valor inicial de la sortida
#define HAL_GPIO_INIT_pos         7
#define HAL_GPIO_INIT_bits        0b11
#define HAL_GPIO_INIT_mask        (HAL_GPIO_INIT_bits << HAL_GPIO_INIT_pos)

#define HAL_GPIO_INIT_NOCHANGE    (0 << HAL_GPIO_INIT_pos)
#define HAL_GPIO_INIT_CLR         (1 << HAL_GPIO_INIT_pos)
#define HAL_GPIO_INIT_SET         (2 << HAL_GPIO_INIT_pos)

// Funcio alternativa
#define HAL_GPIO_AF_NONE          0


// Canvi d'entrada a sortida i viceversa
//
#define halGPIOModePinInput(port, pin) \
    ((GPIORegisters*)port)->TRISxSET = 1 << (pin)

#define halGPIOModePinOutput(port, pin) \
    ((GPIORegisters*)port)->TRISxCLR = 1 << (pin)

#define halGPIOModePortInput(port, mask) \
    ((GPIORegisters*)port)->TRISxSET = (mask)

#define halGPIOModePortOutput(port, mask) \
    ((GPIORegisters*)port)->TRISxCLR = (mask)

// Canvi del estat del pin
//
#define halGPIOSetPin(port, pin) \
    ((GPIORegisters*)port)->LATxSET = 1 << (pin)

#define halGPIOClearPin(port, pin) \
    ((GPIORegisters*)port)->LATxCLR = 1 << (pin)

#define halGPIOTogglePin(port, pin) \
    ((GPIORegisters*)port)->LATxINV = 1 << (pin)

// Lectura i escriptura del pin
//
#define halGPIOReadPin(port, pin) \
    ((((GPIORegisters*)port)->PORTx & (1 << (pin))) != 0)

#define halGPIOWritePin(port, pin, data) \
    if (1) { \
        if (data) \
            ((GPIORegisters*)port)->LATxSET = 1 << (pin); \
        else \
            ((GPIORegisters*)port)->LATxCLR = 1 << (pin); \
    }

// Lectura i escriptura del port
//
#define halGPIOWritePort(port, data) \
    ((GPIORegisters*)port)->LATx = data

#define halGPIOReadPort(port) \
    ((GPIORegisters*)port)->PORTx;


void halGPIOInitializePins(const GPIOInitializePinInfo* info, uint32_t count);
void halGPIOInitializePin(GPIOPort port, GPIOPin pin, GPIOOptions options, GPIOAlt alt);

void halGPIOInitializePorts(const GPIOInitializePortInfo* info, uint32_t count);
void halGPIOInitializePort(GPIOPort port, GPIOMask mask, GPIOOptions options, GPIOAlt alt);


#ifdef	__cplusplus
}
#endif


#endif // __PIC32_halGPIO__
