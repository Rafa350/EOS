#ifndef __PIC32_halUART__
#define __PIC32_halUART__


#include "eos.h"


#ifdef _UART1
#define HAL_UART_CHANNEL_1        0
#endif
#ifdef _UART2
#define HAL_UART_CHANNEL_2        1
#endif
#ifdef _UART3
#define HAL_UART_CHANNEL_3        2
#endif
#ifdef _UART4
#define HAL_UART_CHANNEL_4        3
#endif
#ifdef _UART5
#define HAL_UART_CHANNEL_5        4
#endif
#ifdef _UART6
#define HAL_UART_CHANNEL_6        5
#endif
#define HAL_UART_CHANNEL_NONE     0xFFFFFFFF


typedef uint32_t UARTChannel;
typedef uint32_t UARTOptions;
typedef struct __UARTData* UARTHandler;

typedef struct __attribute__((packed , aligned(4))) {
    __U1MODEbits_t UxMODE;
    volatile uint32_t UxMODECLR;
    volatile uint32_t UxMODESET;
    volatile uint32_t UxMODEINV;
    __U1STAbits_t UxSTA;
    volatile uint32_t UxSTACLR;
    volatile uint32_t UxSTASET;
    volatile uint32_t UxSTAINV;
    volatile uint32_t UxTXREG;
    volatile uint32_t unused1[3];
    volatile uint32_t UxRXREG;
    volatile uint32_t unused2[3];
    volatile uint32_t UxBRG;
} UARTRegisters;

struct __UARTData {
    UARTRegisters regs;
};
typedef struct __UARTData UARTData;

typedef struct {
    UARTChannel channel;
    UARTOptions options;
    int baudRate;
} UARTInitializeInfo;


UARTHandler halUARTInitialize(UARTData* data, const UARTInitializeInfo *info);

void halUARTInterruptHandler(UARTHandler handler);


#endif // __PIC32_halUART__