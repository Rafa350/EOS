export module App.Hardware;

import Eos.Hardware.GPIO;
import Eos.Hardware.SPI;
import Eos.Hardware.LTDC;


using namespace eos::hardware::gpio;
using namespace eos::hardware::spi;
using namespace eos::hardware::ltdc;


export namespace app {

    using PinLED = PinG13;

    constexpr auto pinLED = PinLED::pInst;


    using DeviceSPI = SPIDevice5;
    using PinCS = PinC2;
    using PinRS = PinD13;
    using PinSCK = PinF7;
    using PinMOSI = PinF9;

    constexpr auto devSPI = DeviceSPI::pInst;
    constexpr auto pinCS = PinCS::pInst;
    constexpr auto pinRS = PinRS::pInst;


    using DeviceLTDC = LTDCDevice;
    using DeviceLTDCLayer = LTDCLayerDevice1;
    using PinTE = PinD11;
    using PinHSYNC = PinC6;
    using PinVSYNC = PinA4;
    using PinDE = PinF10;
    using PinPC = PinG7;
    using PinR2 = PinC10;
    using PinR3 = PinB0;
    using PinR4 = PinA11;
    using PinR5 = PinA12;
    using PinR6 = PinB1;
    using PinR7 = PinG6;
    using PinG2 = PinA6;
    using PinG3 = PinG10;
    using PinG4 = PinB10;
    using PinG5 = PinB11;
    using PinG6 = PinC7;
    using PinG7 = PinD3;
    using PinB2 = PinD6;
    using PinB3 = PinG11;
    using PinB4 = PinG12;
    using PinB5 = PinA3;
    using PinB6 = PinB8;
    using PinB7 = PinB9;

    constexpr auto devLTDC = DeviceLTDC::pInst;
    constexpr auto devLTDCLayer = DeviceLTDCLayer::pInst;

    constexpr auto pinDEPolarity = LTDCDevice::PinPolarity::activeLow;
    constexpr auto pinPCPolarity = LTDCDevice::PinPolarity::activeLow;
    constexpr auto pinHSYNCPolarity = LTDCDevice::PinPolarity::activeLow;
    constexpr auto pinVSYNCPolarity = LTDCDevice::PinPolarity::activeLow;

}
