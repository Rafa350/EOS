#pragma once
#ifndef __PIC32_htlINT__
#define __PIC32_htlINT__


// EOS includes
//
#include "HTL/htl.h"


namespace htl {

    enum class INTPriority {
        _0,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7
    };

    enum class INTSubPriority {
        _0,
        _1,
        _2,
        _3
    };

    enum class INTVector {
        i2c1 = _I2C_1_VECTOR,
        i2c2 = _I2C_2_VECTOR,
        spi1 = _SPI_1_VECTOR,
        spi2 = _SPI_2_VECTOR,
        #ifdef _SPI3
        spi3 = _SPI_3_VECTOR,
        #endif
        #ifdef _SPI4
        spi4 = _SPI_4_VECTOR,
        #endif
        tmr1 = _TIMER_1_VECTOR,
        tmr2 = _TIMER_2_VECTOR,
        tmr3 = _TIMER_3_VECTOR,
        tmr4 = _TIMER_4_VECTOR,
        tmr5 = _TIMER_5_VECTOR,
        uart1 = _UART_1_VECTOR,
        uart2 = _UART_2_VECTOR,
        #ifdef _UART3
            uart3 = _UART_3_VECTOR,
        #endif
        #ifdef _UART4
            uart4 = _UART_4_VECTOR,
        #endif
        #ifdef _UART5
            uart5 = _UART_5_VECTOR,
        #endif
        #ifdef _UART6
            uart6 = _UART_6_VECTOR,
        #endif
    };

    template <int dummy_>
    class INT_x {
        public:

            /// \brief Activa les interrupcions.
            ///
            inline static void enableInterrupts() {
                __builtin_enable_interrupts();
            }

            /// \brief  Desactiva les interrupcions.
            /// \return True si previament les interrupcions estaven activades.
            ///
            inline static bool disableInterrupts() {
                return (__builtin_disable_interrupts() & 0x01) != 0;
            }

            /// \brief Restaura les interrupcions.
            /// \param state: True si cal activar les interrupcions.
            ///
            inline static void restoreInterrupts(
                bool state) {

                if (state)
                    enableInterrupts();
            }

            /// \brief Asigna la prioritat al vector.
            /// \param vector: El vector.
            /// \param priority: La prioritat.
            /// \param subPriority: La subprioritat.
            ///
            static void setInterruptVectorPriority(
                INTVector vector,
                INTPriority priority,
                INTSubPriority subPriority) {

                uint32_t mask;
                uint32_t position;

                volatile uint32_t* IPCx = (volatile uint32_t*)(&IPC0 + ((0x10 * (uint32_t(vector) >> 2)) >> 2));

                mask = 0x07 << ((uint32_t(vector) & 0x03) * 8 + 2);
                position = (uint32_t(vector) & 0x03) * 8 + 2;
                *IPCx &= ~mask;
                *IPCx |= (uint32_t(priority) << position) & mask;

                mask = 0x03 << ((uint32_t(vector) & 0x03) * 8);
                position = (uint32_t(vector) & 0x03) * 8;
                *IPCx &= ~mask;
                *IPCx |= (uint32_t(subPriority) << position) & mask;
            }


            static void enableInterruptVector(INTVector vector) {

            }
    };

    using INT_1 = INT_x<1>;
}


#endif
