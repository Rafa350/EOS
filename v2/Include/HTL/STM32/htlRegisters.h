#pragma once
#ifndef __STM32_htlRegisters__
#define __STM32_htlRegisters__


#include "HTL/htl.h"


namespace htl {

    template <typename type_, volatile type_ *reg_, unsigned pos_>
    struct FLAG {
        static constexpr volatile type_ *addr = reg_;
        static constexpr unsigned pos = pos_;
        static constexpr type_ mask = (type_)1 << pos_;

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
