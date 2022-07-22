#pragma once
#ifndef __STM32_htlRegisters__
#define __STM32_htlRegisters__


#include "eos.h"


namespace htl {

    template <typename type_, volatile type_ *reg_, unsigned pos_>
    struct FLAG {
        constexpr static volatile type_ *addr = reg_;
        constexpr static unsigned pos = pos_;
        constexpr static type_ mask = (type_)1 << pos_;

        inline static void clr() {
            *addr &= ~mask;
        }

        inline static void set() {
            *addr |= mask;
        }

        inline static void inv() {
            *addr ^= mask;
        }

        inline static bool value() {
            return (*addr & mask) != 0;
        }
    };
}



#endif // __STM32_htlRegisters__
