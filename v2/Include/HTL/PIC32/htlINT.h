#pragma once
#ifndef __PIC32_htlINT__
#define __PIC32_htlINT__


// EOS includes
//
#include "eos.h"


namespace htl {

    enum class INTPriority {
        p0 = 0,
        p1,
        p2,
        p3,
        p4,
        p5,
        p6,
        p7
    };

    enum class INTSubPriority {
        s0 = 0,
        s1,
        s2,
        s3
    };

    enum class INTVector {
        I2C1 = _I2C_1_VECTOR,
        I2C2 = _I2C_2_VECTOR,
        SPI1 = _SPI_1_VECTOR,
        SPI2 = _SPI_2_VECTOR,
        #ifdef _SPI3
        SPI3 = _SPI_3_VECTOR,
        #endif
        #ifdef _SPI4
        SPI4 = _SPI_4_VECTOR,
        #endif
        TMR1 = _TIMER_1_VECTOR,
        TMR2 = _TIMER_2_VECTOR,
        TMR3 = _TIMER_3_VECTOR,
        TMR4 = _TIMER_4_VECTOR,
        TMR5 = _TIMER_5_VECTOR,
        UART1 = _UART_1_VECTOR,
        UART2 = _UART_2_VECTOR,
        #ifdef _UART3
            UART3 = _UART_3_VECTOR,
        #endif
        #ifdef _UART4
            UART4 = _UART_4_VECTOR,
        #endif
        #ifdef _UART5
            UART5 = _UART_5_VECTOR
        #endif
        #ifdef _UART6
            UART6 = _UART_6_VECTOR
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
            inline static void restoreInterrupts(bool state) {
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
    };

    using INT_1 = INT_x<1>;
}


#endif
