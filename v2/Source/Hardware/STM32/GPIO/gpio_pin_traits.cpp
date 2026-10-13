module;


#include "hardware.h"


export module Eos.Hardware.GPIO.__PIN_TRAITS;


import Eos.Hardware.GPIO.__TYPES;


namespace eos::hardware::gpio::internal {

    namespace hidden {

        template <PinID pinId_>
        struct Traits {
        };

        template <>
        struct Traits<PinID::pin0> {
            static constexpr PinMask mask {1 << 0};
            static constexpr PinBit bit {0};
        };

        template <>
        struct Traits<PinID::pin1> {
            static constexpr PinMask mask {1 << 1};
            static constexpr PinBit bit {1};
        };

        template <>
        struct Traits<PinID::pin2> {
            static constexpr PinMask mask {1 << 2};
            static constexpr PinBit bit {2};
        };

        template <>
        struct Traits<PinID::pin3> {
            static constexpr PinMask mask {1 << 3};
            static constexpr PinBit bit {3};
        };

        template <>
        struct Traits<PinID::pin4> {
            static constexpr PinMask mask {1 << 4};
            static constexpr PinBit bit {4};
        };

        template <>
        struct Traits<PinID::pin5> {
            static constexpr PinMask mask {1 << 5};
            static constexpr PinBit bit {5};
        };

        template <>
        struct Traits<PinID::pin6> {
            static constexpr PinMask mask {1 << 6};
            static constexpr PinBit bit {6};
        };

        template <>
        struct Traits<PinID::pin7> {
            static constexpr PinMask mask {1 << 7};
            static constexpr PinBit bit {7};
        };

        template <>
        struct Traits<PinID::pin8> {
            static constexpr PinMask mask {1 << 8};
            static constexpr PinBit bit {8};
        };

        template <>
        struct Traits<PinID::pin9> {
            static constexpr PinMask mask {1 << 9};
            static constexpr PinBit bit {9};
        };

        template <>
        struct Traits<PinID::pin10> {
            static constexpr PinMask mask {1 << 10};
            static constexpr PinBit bit {10};
        };

        template <>
        struct Traits<PinID::pin11> {
            static constexpr PinMask mask {1 << 11};
            static constexpr PinBit bit {11};
        };

        template <>
        struct Traits<PinID::pin12> {
            static constexpr PinMask mask {1 << 12};
            static constexpr PinBit bit {12};
        };

        template <>
        struct Traits<PinID::pin13> {
            static constexpr PinMask mask {1 << 13};
            static constexpr PinBit bit {13};
        };

        template <>
        struct Traits<PinID::pin14> {
            static constexpr PinMask mask {1 << 14};
            static constexpr PinBit bit {14};
        };

        template <>
        struct Traits<PinID::pin15> {
            static constexpr PinMask mask {1 << 15};
            static constexpr PinBit bit {15};
        };
    }

    export template<PinID pinId_> using PinTraits = hidden::Traits<pinId_>;
}
