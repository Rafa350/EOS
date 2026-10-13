module;


#include "hardware.h"


export module Eos.Hardware.GPIO.__TYPES;


import Eos.Types;
import Eos.Hardware.GPIO.__PLATFORM_TRAITS;


export namespace eos::hardware::gpio {

    using PortID = internal::PlatformTraits::PortID;

	/// Identificador dels pins.
	///
    enum class PinID {
        pin0, pin1, pin2, pin3, pin4, pin5, pin6, pin7,
        pin8, pin9, pin10, pin11, pin12, pin13, pin14, pin15
    };

    /// Bit del pin
    ///
    class PinBit final {
        private:
            UInt8 _value;

        public:
            constexpr explicit PinBit(UInt8 value): _value {value} {}
            constexpr operator UInt8 () const { return _value; }
    };

    /// Mascara de pins
    ///
    class PinMask final {
        private:
            UInt16 _value;

        public:
            constexpr explicit PinMask(UInt16 value) : _value {value} {}
            constexpr explicit PinMask(PinBit bit) : _value {(UInt16)(1 << bit)} {}
            constexpr operator UInt16 () const { return _value; }
    };

    /// Identificador de la funcio alternativa.
    ///
    enum class AlternateFunction {
        _0, _1, _2, _3, _4, _5, _6, _7,
        _8, _9, _10, _11, _12, _13, _14, _15
    };

    /// Opcions de velocitat.
    ///
    enum class Speed {
        low,
        medium,
        high,
        fast
    };

    // Opcio de resistencies pull up/down.
    //
    enum class PullUpDown {
        none,
        up,
        down
    };

    // Opcions del driver de sortida.
    //
    enum class OutputType {
        pushPull,
        openDrain
    };

}
