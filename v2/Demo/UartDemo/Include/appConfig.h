#pragma once
#ifndef __appConfig__
#define __appConfig__


#include "HTL/htlGPIO.h"
#include "HTL/htlINT.h"
#include "HTL/htlUART.h"


namespace app {

    namespace hw {

        using DevUART = SIO_UART_Device;
        using PinTX = SIO_TX_Pin;
        using PinRX = SIO_RX_Pin;

        constexpr auto devUART = DevUART::pInst;
        constexpr auto devUART_VectorID = SIO_UART_IrqVector;
    }
}


#endif // __appConfig__
