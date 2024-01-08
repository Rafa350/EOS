#pragma once
#ifndef __appConfig__
#define __appConfig__


#include "HTL/htlUART.h"
#include "HTL/htlGPIO.h"


namespace app {

    namespace hw {

        using DevUART = htl::uart::UARTDevice1;
        using PinTX = htl::gpio::PinA9;
        using PinRX = htl::gpio::PinB7;

        constexpr auto devUART = DevUART::pInst;
    }
}


#endif // __appConfig__
