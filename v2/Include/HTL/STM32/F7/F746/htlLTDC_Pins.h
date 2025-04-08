#pragma once
#ifndef __136CEA02A3A54C2C9C6C2D860BAA0ADB__
#define __136CEA02A3A54C2C9C6C2D860BAA0ADB__


#if !defined(EOS_PLATFORM_STM32F746)
    #error 'Unsupported platform'
#endif


namespace htl::ltdc::internal {

    #if defined(HTL_LTDC_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::de, htl::gpio::PortID::portF, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::de, htl::gpio::PortID::portE, htl::gpio::PinID::pin13> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::de, htl::gpio::PortID::portK, htl::gpio::PinID::pin7> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::pc, htl::gpio::PortID::portE, htl::gpio::PinID::pin14> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::pc, htl::gpio::PortID::portG, htl::gpio::PinID::pin7> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::pc, htl::gpio::PortID::portI, htl::gpio::PinID::pin14> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::hsync, htl::gpio::PortID::portC, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::hsync, htl::gpio::PortID::portI, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::hsync, htl::gpio::PortID::portI, htl::gpio::PinID::pin12> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::vsync, htl::gpio::PortID::portA, htl::gpio::PinID::pin4> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::vsync, htl::gpio::PortID::portI, htl::gpio::PinID::pin9> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::vsync, htl::gpio::PortID::portI, htl::gpio::PinID::pin13> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r0, htl::gpio::PortID::portI, htl::gpio::PinID::pin15> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r0, htl::gpio::PortID::portH, htl::gpio::PinID::pin2> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r1, htl::gpio::PortID::portJ, htl::gpio::PinID::pin0> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r1, htl::gpio::PortID::portA, htl::gpio::PinID::pin2> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r1, htl::gpio::PortID::portH, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r2, htl::gpio::PortID::portA, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r2, htl::gpio::PortID::portC, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r2, htl::gpio::PortID::portH, htl::gpio::PinID::pin8> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r2, htl::gpio::PortID::portJ, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r3, htl::gpio::PortID::portH, htl::gpio::PinID::pin9> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r3, htl::gpio::PortID::portB, htl::gpio::PinID::pin0> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r3, htl::gpio::PortID::portJ, htl::gpio::PinID::pin2> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r4, htl::gpio::PortID::portA, htl::gpio::PinID::pin5> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r4, htl::gpio::PortID::portA, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r4, htl::gpio::PortID::portH, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r4, htl::gpio::PortID::portJ, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r5, htl::gpio::PortID::portH, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r5, htl::gpio::PortID::portA, htl::gpio::PinID::pin12> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r5, htl::gpio::PortID::portJ, htl::gpio::PinID::pin4> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r6, htl::gpio::PortID::portA, htl::gpio::PinID::pin8> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r6, htl::gpio::PortID::portB, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_9;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r6, htl::gpio::PortID::portH, htl::gpio::PinID::pin12> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r6, htl::gpio::PortID::portJ, htl::gpio::PinID::pin5> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r7, htl::gpio::PortID::portE, htl::gpio::PinID::pin15> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r7, htl::gpio::PortID::portG, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::r7, htl::gpio::PortID::portJ, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b0, htl::gpio::PortID::portE, htl::gpio::PinID::pin4> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b0, htl::gpio::PortID::portJ, htl::gpio::PinID::pin12> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b1, htl::gpio::PortID::portG, htl::gpio::PinID::pin12> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b1, htl::gpio::PortID::portJ, htl::gpio::PinID::pin13> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b2, htl::gpio::PortID::portD, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b2, htl::gpio::PortID::portG, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b2, htl::gpio::PortID::portJ, htl::gpio::PinID::pin14> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b3, htl::gpio::PortID::portG, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b3, htl::gpio::PortID::portD, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b3, htl::gpio::PortID::portJ, htl::gpio::PinID::pin15> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b4, htl::gpio::PortID::portE, htl::gpio::PinID::pin12> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b4, htl::gpio::PortID::portG, htl::gpio::PinID::pin12> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_9;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b4, htl::gpio::PortID::portI, htl::gpio::PinID::pin4> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b4, htl::gpio::PortID::portK, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b5, htl::gpio::PortID::portI, htl::gpio::PinID::pin5> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b5, htl::gpio::PortID::portA, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b5, htl::gpio::PortID::portK, htl::gpio::PinID::pin4> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b6, htl::gpio::PortID::portB, htl::gpio::PinID::pin8> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b6, htl::gpio::PortID::portI, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b6, htl::gpio::PortID::portK, htl::gpio::PinID::pin5> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b7, htl::gpio::PortID::portI, htl::gpio::PinID::pin7> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b7, htl::gpio::PortID::portB, htl::gpio::PinID::pin9> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::b7, htl::gpio::PortID::portK, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g0, htl::gpio::PortID::portE, htl::gpio::PinID::pin5> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g0, htl::gpio::PortID::portJ, htl::gpio::PinID::pin7> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g1, htl::gpio::PortID::portE, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g1, htl::gpio::PortID::portJ, htl::gpio::PinID::pin8> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g2, htl::gpio::PortID::portA, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g2, htl::gpio::PortID::portJ, htl::gpio::PinID::pin9> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g2, htl::gpio::PortID::portH, htl::gpio::PinID::pin13> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g3, htl::gpio::PortID::portH, htl::gpio::PinID::pin14> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g3, htl::gpio::PortID::portE, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g3, htl::gpio::PortID::portG, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_9;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g3, htl::gpio::PortID::portJ, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g4, htl::gpio::PortID::portB, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g4, htl::gpio::PortID::portH, htl::gpio::PinID::pin15> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g4, htl::gpio::PortID::portJ, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g5, htl::gpio::PortID::portI, htl::gpio::PinID::pin0> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g5, htl::gpio::PortID::portB, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g5, htl::gpio::PortID::portK, htl::gpio::PinID::pin0> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g6, htl::gpio::PortID::portC, htl::gpio::PinID::pin7> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g6, htl::gpio::PortID::portI, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g6, htl::gpio::PortID::portK, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g7, htl::gpio::PortID::portI, htl::gpio::PinID::pin2> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g7, htl::gpio::PortID::portD, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    template<>
    struct PinFunctionInfo<DeviceID::ltdc, PinFunction::g7, htl::gpio::PortID::portK, htl::gpio::PinID::pin2> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_14;
    };
    #endif

}


#endif

