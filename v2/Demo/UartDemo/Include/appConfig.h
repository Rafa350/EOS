#pragma once
#ifndef __appConfig__
#define __appConfig__


#include "HTL/htlGPIO.h"
#include "HTL/htlINT.h"
#include "HTL/htlUART.h"


namespace app {

    namespace hw {

        using DevUART = htl::uart::UARTDevice1;
        using PinTX = htl::gpio::PinA9;
        using PinRX = htl::gpio::PinB7;

        constexpr auto devUART = DevUART::pInst;
        constexpr auto devUART_VectorID = htl::irq::VectorID::uart1;
    }
}


#endif // __appConfig__
