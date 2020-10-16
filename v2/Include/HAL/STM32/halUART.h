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

#define HAL_UART_CLOCK_PCLK       (0 << HAL_UART_CLOCK_pos)
#define HAL_UART_CLOCK_HSI        (1 << HAL_UART_CLOCK_pos)
#define HAL_UART_CLOCK_SYSCLK     (2 << HAL_UART_CLOCK_pos)
#define HAL_UART_CLOCK_LSE        (3 << HAL_UART_CLOCK_pos)
#define HAL_UART_CLOCK_AUTO		  (4 << HAL_UART_CLOCK_pos)

// Opcions: Baud rate
#define HAL_UART_BAUD_pos         3
#define HAL_UART_BAUD_bits        0b1111
#define HAL_UART_BAUD_mask        (HAL_UART_BAUD_bits << HAL_UART_BAUD_pos)

#define HAL_UART_BAUD_RATE        (0 << HAL_UART_BAUD_pos)
#define HAL_UART_BAUD_DIV         (1 << HAL_UART_BAUD_pos)
#define HAL_UART_BAUD_AUTO        (2 << HAL_UART_BAUD_pos)
#define HAL_UART_BAUD_1200        (3 << HAL_UART_BAUD_pos)
#define HAL_UART_BAUD_2400        (4 << HAL_UART_BAUD_pos)
#define HAL_UART_BAUD_4800        (5 << HAL_UART_BAUD_pos)
#define HAL_UART_BAUD_9600        (6 << HAL_UART_BAUD_pos)
#define HAL_UART_BAUD_19200       (7 << HAL_UART_BAUD_pos)
#define HAL_UART_BAUD_38400       (8 << HAL_UART_BAUD_pos)
#define HAL_UART_BAUD_57600       (9 << HAL_UART_BAUD_pos)
#define HAL_UART_BAUD_115200      (10 << HAL_UART_BAUD_pos)

// Opcions: Oversampling
#define HAL_UART_OVERSAMPLING_pos      7
#define HAL_UART_OVERSAMPLING_bits     0b1
#define HAL_UART_OVERSAMPLING_mask     (HAL_UART_OVERSAMPLING_bits << HAL_UART_OVERSAMPLING_pos)

#define HAL_UART_OVERSAMPLING_8        (0 << HAL_UART_OVERSAMPLING_pos)
#define HAL_UART_OVERSAMPLING_16       (1 << HAL_UART_OVERSAMPLING_pos)

// Opcions: Data length
#define HAL_UART_LEN_pos          8
#define HAL_UART_LEN_bits         0b11
#define HAL_UART_LEN_mask         (HAL_UART_LEN_bits << HAL_UART_LEN_pos)

#define HAL_UART_LEN_7			  (0 << HAL_UART_LEN_pos)
#define HAL_UART_LEN_8			  (1 << HAL_UART_LEN_pos)
#define HAL_UART_LEN_9			  (2 << HAL_UART_LEN_pos)

// Opcions: Stop bits
#define HAL_UART_STOP_pos         10
#define HAL_UART_STOP_bits        0b11
#define HAL_UART_STOP_mask        (HAL_UART_STOP_bits << HAL_UART_STOP_pos)

#define HAL_UART_STOP_05		  (0 << HAL_UART_STOP_pos)
#define HAL_UART_STOP_10          (1 << HAL_UART_STOP_pos)
#define HAL_UART_STOP_15		  (2 << HAL_UART_STOP_pos)
#define HAL_UART_STOP_20		  (3 << HAL_UART_STOP_pos)

// Opcions: Paritat
#define HAL_UART_PARITY_pos       12
#define HAL_UART_PARITY_bits      0b11
#define HAL_UART_PARITY_mask      (HAL_UART_PARITY_bits << HAL_UART_PARITY_pos)

#define HAL_UART_PARITY_NONE      (0 << HAL_UART_PARITY_pos)
#define HAL_UART_PARITY_EVEN      (1 << HAL_UART_PARITY_pos)
#define HAL_UART_PARITY_ODD       (2 << HAL_UART_PARITY_pos)

// Opcions: HwControl
#define HAL_UART_HWCTRL__pos      14
#define HAL_UART_HWCTRL_bits      0b11
#define HAL_UART_HWCTRL_mask      (HAL_UART_HWCTRL_bits << HAL_UART_CTRL_pos)

#define HAL_UART_HWCTRL_NONE	  (0 << HAL_UART_HWCTRL_pos)
#define HAL_UART_HWCTRL_CTS       (1 << HAL_UART_HWCTRL_pos)
#define HAL_UART_HWCTRL_RTS		  (2 << HAL_UART_HWCTRL_pos)
#define HAL_UART_HWCTRL_CTS_RTS	  (3 << HAL_UART_HWCTRL_pos)


// Identificadors dels events
#define HAL_UART_EVENT_CTS        0x01      // CTS interrupt
#define HAL_UART_EVENT_LBD        0x20      // Break detection
#define HAL_UART_EVENT_TXE        0x40      // Transmit register empty
#define HAL_UART_EVENT_TC         0x80      // Transmission complete
#define HAL_UART_EVENT_RXNE       0x10      // Receiver data register no empty
#define HAL_UART_EVENT_IDLE       0x20      // Idle line detected
#define HAL_UART_EVENT_PE         0x40      // Parity error
#define HAL_UART_EVENT_ERR        0x80      //
#define HAL_UART_EVENT_ALL        0xFF      // Totes combinades


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint32_t UARTChannel;
typedef uint32_t UARTOptions;
typedef struct __UARTData* UARTHandler;
typedef void (*UARTInterruptFunction)(UARTHandler handler, void* params);

struct __UARTData {
    USART_TypeDef* device;
    UARTInterruptFunction isrFunction;
    void* isrParams;
};
typedef struct __UARTData UARTData;

typedef struct {
    UARTChannel channel;
    UARTOptions options;
    uint32_t baud;
} UARTInitializeInfo;


UARTHandler halUARTInitialize(UARTData* data, const UARTInitializeInfo *info);
void halUARTDeinitialize(UARTHandler handler);

uint32_t halUARTSend(UARTHandler handler, const void* data, uint32_t length);

void halUARTSetInterruptFunction(UARTHandler handler, UARTInterruptFunction function, void* params);
void halUARTInterruptHandler(UARTHandler handler);

void halUARTEnableInterrupts(UARTHandler handler, uint32_t events);
uint32_t halUARTDisableInterrupts(UARTHandler handler, uint32_t events);

bool halUARTGetInterruptFlag(UARTHandler handler, uint32_t event);
void halUARTClearInterruptFlags(UARTHandler handler, uint32_t events);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halUART__
