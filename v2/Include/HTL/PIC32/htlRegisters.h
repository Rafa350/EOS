#pragma once
#ifndef __PIC32_htlRegisters__
#define __PIC32_htlRegisters__


#include "eos.h"


namespace htl {

    template <typename type_, volatile type_ *reg_, unsigned pos_>
    struct FLAG_STD {
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

    template <typename type_, volatile type_ *reg_, unsigned pos_>
    struct FLAG_CSI {
        constexpr static volatile type_ *addr = &reg_[0];
        constexpr static volatile type_ *addrCLR = &reg_[1];
        constexpr static volatile type_ *addrSET = &reg_[2];
        constexpr static volatile type_ *addrINV = &reg_[3];
        constexpr static unsigned pos = pos_;
        constexpr static type_ mask = (type_)1 << pos_;

        inline static void clr() {
            *addrCLR = mask;
        }

        inline static void set() {
            *addrSET = mask;
        }

        inline static void inv() {
            *addrINV = mask;
        }

        inline static bool value() {
            return (*addr & mask) != 0;
        }
    };
}



#endif // __PIC32_htlRegisters__
