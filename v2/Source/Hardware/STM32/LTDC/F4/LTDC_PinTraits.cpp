module;

#include "hardware.h"


export module Eos.Hardware.LTDC._PinTraits;

import Eos.Hardware.GPIO;
import Eos.Hardware.LTDC._Types;
import Eos.Platform;


static_assert(eos::platformCheck("STM32F4xxxx"));


using namespace eos::hardware::gpio;


export namespace eos::hardware::ltdc::internal {

    enum class PinFunction {
        hsync,
        vsync,
        de,
        pc,
        r0, r1, r2, r3, r4, r5, r6, r7,
        g0, g1, g2, g3, g4, g5, g6, g7,
        b0, b1, b2, b3, b4, b5, b6, b7
    };

	template <LTDCDeviceID, PinFunction, PortID, PinID>
	struct PinTraits;

#ifdef LTDC_BASE
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::de, PortID::portF, PinID::pin10> {
        static constexpr auto value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::de, PortID::portE, PinID::pin13> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::de, PortID::portK, PinID::pin7> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::pc, PortID::portE, PinID::pin14> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::pc, PortID::portG, PinID::pin7> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::pc, PortID::portI, PinID::pin14> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::hsync, PortID::portC, PinID::pin6> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::hsync, PortID::portI, PinID::pin10> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::hsync, PortID::portI, PinID::pin12> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::vsync, PortID::portA, PinID::pin4> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::vsync, PortID::portI, PinID::pin9> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::vsync, PortID::portI, PinID::pin13> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r0, PortID::portI, PinID::pin15> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r0, PortID::portH, PinID::pin2> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r1, PortID::portJ, PinID::pin0> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r1, PortID::portA, PinID::pin2> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r1, PortID::portH, PinID::pin3> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r2, PortID::portA, PinID::pin1> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r2, PortID::portC, PinID::pin10> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r2, PortID::portH, PinID::pin8> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r2, PortID::portJ, PinID::pin1> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r3, PortID::portH, PinID::pin9> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r3, PortID::portB, PinID::pin0> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r3, PortID::portJ, PinID::pin2> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r4, PortID::portA, PinID::pin5> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r4, PortID::portA, PinID::pin11> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r4, PortID::portH, PinID::pin10> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r4, PortID::portJ, PinID::pin3> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r5, PortID::portH, PinID::pin11> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r5, PortID::portA, PinID::pin12> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r5, PortID::portJ, PinID::pin4> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r6, PortID::portA, PinID::pin8> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r6, PortID::portB, PinID::pin1> {
        static constexpr AlternateFunction value = AlternateFunction::_9;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r6, PortID::portH, PinID::pin12> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r6, PortID::portJ, PinID::pin5> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r7, PortID::portE, PinID::pin15> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r7, PortID::portG, PinID::pin6> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::r7, PortID::portJ, PinID::pin6> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b0, PortID::portE, PinID::pin4> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b0, PortID::portJ, PinID::pin12> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b1, PortID::portG, PinID::pin12> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b1, PortID::portJ, PinID::pin13> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b2, PortID::portD, PinID::pin6> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b2, PortID::portG, PinID::pin10> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b2, PortID::portJ, PinID::pin14> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b3, PortID::portG, PinID::pin11> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b3, PortID::portD, PinID::pin10> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b3, PortID::portJ, PinID::pin15> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b4, PortID::portE, PinID::pin12> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b4, PortID::portG, PinID::pin12> {
        static constexpr AlternateFunction value = AlternateFunction::_9;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b4, PortID::portI, PinID::pin4> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b4, PortID::portK, PinID::pin3> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b5, PortID::portI, PinID::pin5> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b5, PortID::portA, PinID::pin3> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b5, PortID::portK, PinID::pin4> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b6, PortID::portB, PinID::pin8> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b6, PortID::portI, PinID::pin6> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b6, PortID::portK, PinID::pin5> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b7, PortID::portI, PinID::pin7> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b7, PortID::portB, PinID::pin9> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::b7, PortID::portK, PinID::pin6> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g0, PortID::portE, PinID::pin5> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g0, PortID::portJ, PinID::pin7> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g1, PortID::portE, PinID::pin6> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g1, PortID::portJ, PinID::pin8> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g2, PortID::portA, PinID::pin6> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g2, PortID::portJ, PinID::pin9> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g2, PortID::portH, PinID::pin13> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g3, PortID::portH, PinID::pin14> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g3, PortID::portE, PinID::pin11> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g3, PortID::portG, PinID::pin10> {
        static constexpr AlternateFunction value = AlternateFunction::_9;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g3, PortID::portJ, PinID::pin10> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g4, PortID::portB, PinID::pin10> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g4, PortID::portH, PinID::pin15> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g4, PortID::portJ, PinID::pin11> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g5, PortID::portI, PinID::pin0> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g5, PortID::portB, PinID::pin11> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g5, PortID::portK, PinID::pin0> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g6, PortID::portC, PinID::pin7> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g6, PortID::portI, PinID::pin1> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g6, PortID::portK, PinID::pin1> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g7, PortID::portI, PinID::pin2> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g7, PortID::portD, PinID::pin3> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
    template<>
    struct PinTraits<LTDCDeviceID::ltdc, PinFunction::g7, PortID::portK, PinID::pin2> {
        static constexpr AlternateFunction value = AlternateFunction::_14;
    };
#endif
}
