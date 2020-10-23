#ifndef __PIC32_halINT__
#define __PIC32_halINT__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


// Prioritats de les interrupcions
#define HAL_INT_PRIORITY_0             0
#define HAL_INT_PRIORITY_1             1
#define HAL_INT_PRIORITY_2             2
#define HAL_INT_PRIORITY_3             3
#define HAL_INT_PRIORITY_4             4
#define HAL_INT_PRIORITY_5             5
#define HAL_INT_PRIORITY_6             6
#define HAL_INT_PRIORITY_7             7

// Subprioritats de les interrupcions
#define HAL_INT_SUBPRIORITY_0          0
#define HAL_INT_SUBPRIORITY_1          1
#define HAL_INT_SUBPRIORITY_2          2
#define HAL_INT_SUBPRIORITY_3          3

// Fonts d'interrupcio
#define HAL_INT_SOURCE_CN             _CHANGE_NOTICE_IRQ
#define HAL_INT_SOURCE_I2C1_BUS       _I2C1_BUS_IRQ
#define HAL_INT_SOURCE_I2C1_SLAVE     _I2C1_SLAVE_IRQ
#define HAL_INT_SOURCE_I2C1_MASTER    _I2C1_MASTER_IRQ
#define HAL_INT_SOURCE_I2C2_BUS       _I2C2_BUS_IRQ
#define HAL_INT_SOURCE_I2C2_SLAVE     _I2C2_SLAVE_IRQ
#define HAL_INT_SOURCE_I2C2_MASTER    _I2C2_MASTER_IRQ
#define HAL_INT_SOURCE_TMR1           _TIMER_1_IRQ
#define HAL_INT_SOURCE_TMR2           _TIMER_2_IRQ
#define HAL_INT_SOURCE_TMR3           _TIMER_3_IRQ
#define HAL_INT_SOURCE_TMR4           _TIMER_4_IRQ
#define HAL_INT_SOURCE_TMR5           _TIMER_5_IRQ

// Vectors d'interrrupcio
#define HAL_INT_VECTOR_I2C1           _I2C_1_VECTOR
#define HAL_INT_VECTOR_I2C2           _I2C_2_VECTOR
#define HAL_INT_VECTOR_TMR1           _TIMER_1_VECTOR
#define HAL_INT_VECTOR_TMR2           _TIMER_2_VECTOR
#define HAL_INT_VECTOR_TMR3           _TIMER_3_VECTOR
#define HAL_INT_VECTOR_TMR4           _TIMER_4_VECTOR
#define HAL_INT_VECTOR_TMR5           _TIMER_5_VECTOR
#define HAL_INT_VECTOR_UART1          _UART_1_VECTOR
#define HAL_INT_VECTOR_UART2          _UART_2_VECTOR


#define __halINTEnableInterrupts()    __builtin_enable_interrupts()
#define __halINTDisableInterrupts()   (bool)(__builtin_disable_interrupts() & 0x01)

void halINTEnableInterrupts();
bool halINTDisableInterrupts();
void halINTRestoreInterrupts(bool state);


void halINTSetInterruptVectorPriority(uint32_t vector, uint32_t priority, uint32_t subPriority);
#define halINTEnableInterruptVector(vector)

void halINTEnableInterruptSource(uint32_t source);
bool halINTDisableInterruptSource(uint32_t source);
void halINTRestoreInterruptSource(uint32_t source, bool state);

bool halINTGetInterruptSourceFlag(uint32_t source);
void halINTClearInterruptSourceFlag(uint32_t source);


#ifdef	__cplusplus
}
#endif


#endif // __PIC32_halINT__

