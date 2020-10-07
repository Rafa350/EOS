#ifndef __STM32_halUART__
#define __STM32_halUART__


#include "eos.h"


// Identificador de la UART
#ifdef USART1
#define HAL_UART_CHANNEL_1        0
#endif
#ifdef USART2
#define HAL_UART_CHANNEL_2        1
#endif
#ifdef USART3
#define HAL_UART_CHANNEL_3        2
#endif
#ifdef UART4
#define HAL_UART_CHANNEL_4        3
#endif
#ifdef UART5
#define HAL_UART_CHANNEL_5        4
#endif
#ifdef USART6
#define HAL_UART_CHANNEL_6        5
#endif
#ifdef UART7
#define HAL_UART_CHANNEL_7        6
#endif
#ifdef UART8
#define HAL_UART_CHANNEL_8        7
#endif
#define HAL_UART_CHANNEL_NONE     0xFFFFFFFF

// Opcions: Rellotge
#define HAL_UART_CLOCK_pos        0
#define HAL_UART_CLOCK_bits       0b111
#define HAL_UART_CLOCK_mask       (HAL_UART_CLOCK_bits << HAL_UART_CLOCK_pos)

#define HAL_UART_CLOCK_PCLK1      (0 << HAL_UART_CLOCK_pos)
#define HAL_UART_CLOCK_PCLK2      (1 << HAL_UART_CLOCK_pos)
#define HAL_UART_CLOCK_HSI        (2 << HAL_UART_CLOCK_pos)
#define HAL_UART_CLOCK_SYSCLK     (3 << HAL_UART_CLOCK_pos)
#define HAL_UART_CLOCK_LSE        (4 << HAL_UART_CLOCK_pos)
#define HAL_UART_CLOCK_DEFAULT    HAL_UART_CLOCK_PCLK1

// Identificadors dels events
#define HAL_UART_EVENT_CTS        0x01
#define HAL_UART_EVENT_LDB        0x20
#define HAL_UART_EVENT_TXE        0x40
#define HAL_UART_EVENT_TC         0x80
#define HAL_UART_EVENT_RXNE       0x10
#define HAL_UART_EVENT_IDLE       0x20
#define HAL_UART_EVENT_PE         0x40
#define HAL_UART_EVENT_ERR        0x80
#define HAL_UART_EVENT_ALL        0xFF


typedef uint32_t UARTChannel;
typedef uint32_t UARTOptions;
typedef USART_TypeDef UARTRegisters;
typedef struct __UARTData* UARTHandler;
typedef void (*UARTInterruptFunction)(UARTHandler handler, void* params);

struct __UARTData {
    UARTRegisters* regs;
    UARTInterruptFunction isrFunction;
    void* isrParams;
};
typedef struct __UARTData UARTData;

typedef struct {
    UARTChannel channel;
    UARTOptions options;
    uint32_t baudRate;
} UARTInitializeInfo;


UARTHandler halUARTInitialize(UARTData* data, const UARTInitializeInfo *info);

void halUARTSetInterruptFunction(UARTHandler handler, UARTInterruptFunction function, void* params);
void halUARTInterruptHandler(UARTHandler handler);

void halUARTEnableInterrupts(UARTHandler handler, uint32_t events);
uint32_t halUARTDisableInterrupts(UARTHandler handler, uint32_t events);

bool halUARTGetInterruptFlag(UARTHandler handler, uint32_t event);
void halUARTClearInterruptFlags(UARTHandler handler, uint32_t events);


#endif // __STM32_halUART__
