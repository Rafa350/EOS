/// \file     halUART.h
/// \author   Rafael Serrano (rsr.openware@gmail.com)
/// \brief    Gestio de la UART
/// \addtogroup HAL Hardware Abstraction Layer
/// @{
/// \addtogroup HAL_STM32 STM32 Hardware Abstraction Layer
/// @{
/// \defgroup HAL_STM32_UART UART
/// @{
///
#ifndef __STM32_halUART__
#define __STM32_halUART__


// HAL includes
//
#include "HAL/hal.h"


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
#define HAL_UART_CHANNEL_NONE     ((halUARTChannel) -1)

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

// Opcions: Stop bits
#define HAL_UART_STOP_pos         10
#define HAL_UART_STOP_bits        0b11
#define HAL_UART_STOP_mask        (HAL_UART_STOP_bits << HAL_UART_STOP_pos)

#define HAL_UART_STOP_HALF		  (0 << HAL_UART_STOP_pos)
#define HAL_UART_STOP_1           (1 << HAL_UART_STOP_pos)
#define HAL_UART_STOP_1HALF		  (2 << HAL_UART_STOP_pos)
#define HAL_UART_STOP_2	          (3 << HAL_UART_STOP_pos)

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
#define HAL_UART_EVENT_BREAK      0x02      // Break detected
#define HAL_UART_EVENT_TXEMPTY    0x04      // Transmit data register register empty
#define HAL_UART_EVENT_TXCOMPLETE 0x08      // Transmission complete
#define HAL_UART_EVENT_RXFULL     0x10      // Receiver data register no empty
#define HAL_UART_EVENT_IDLE       0x20      // Idle line detected
#define HAL_UART_EVENT_PARITY     0x40      // Parity error
#define HAL_UART_EVENT_FRAMING    0x80      // Framing error
#define HAL_UART_EVENT_OVERRUN    0x100     // Overrun error
#define HAL_UART_EVENT_NOISE      0x200     // Noise error
#define HAL_UART_EVENT_ERROR      0x380     // Combinat Noise, Framing i Overrun
#define HAL_UART_EVENT_ALL        0x3FF     // Totes combinades


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint32_t halUARTChannel;
typedef uint32_t halUARTOptions;
typedef struct __halUARTData* halUARTHandler;
typedef void (*halUARTInterruptFunction)(halUARTHandler handler, void* params, uint32_t event);

struct __halUARTData {
    USART_TypeDef* device;
    halUARTInterruptFunction isrFunction;
    void* isrParams;
};
typedef struct __halUARTData halUARTData;

typedef struct {
    halUARTChannel channel;
    halUARTOptions options;
    uint32_t baud;
} halUARTSettings;


halUARTHandler halUARTInitialize(halUARTData* data, const halUARTSettings* settings);
void halUARTDeinitialize(halUARTHandler handler);

void halUARTSend(halUARTHandler handler, uint8_t data);
uint8_t halUARTReceive(halUARTHandler handler);

void halUARTSetInterruptFunction(halUARTHandler handler, halUARTInterruptFunction function, void* params);
void halUARTInterruptHandler(halUARTHandler handler);

void halUARTEnableInterrupts(halUARTHandler handler, uint32_t events);
uint32_t halUARTDisableInterrupts(halUARTHandler handler, uint32_t events);

bool halUARTGetInterruptFlag(halUARTHandler handler, uint32_t event);
void halUARTClearInterruptFlags(halUARTHandler handler, uint32_t events);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halUART__

/// @}
/// @}
/// @}
