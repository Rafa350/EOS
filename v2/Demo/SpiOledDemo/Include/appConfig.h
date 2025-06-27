#pragma once
#ifndef __appConfig__
#define __appConfig__


#include "HTL/htlGPIO.h"
#include "HTL/htlINT.h"
#include "HTL/htlUART.h"
#include "HTL/htlSPI.h"


namespace app {

    namespace hw {

    	// Comunicacio serie
    	//
#ifdef EXIST_SIO
        using DevUART                       = SIO_UART_Device;
        using PinTX                         = SIO_TX_Pin;
        using PinRX                         = SIO_RX_Pin;

        constexpr auto devUART              = DevUART::pInst;
        constexpr auto devUART_VectorID     = SIO_UART_IrqVector;
#endif

        // Control del DISPLAY SSD1603-SPI
        //
#ifdef EXIST_DISPLAY
        using DevSPI                        = ARDUINO_SPI_Device;
        using PinCS                         = DISPLAY_CS_Pin;
        using PinDC                         = DISPLAY_DC_Pin;
        using PinRST                        = DISPLAY_RST_Pin;

        constexpr auto pinCS                = PinCS::pInst;
        constexpr auto pinDC                = PinDC::pInst;
        constexpr auto pinRST               = PinRST::pInst;

        constexpr auto devSPI               = DevSPI::pInst;
        constexpr auto devSPI_ClkPolarity   = htl::spi::ClkPolarity::low;
        constexpr auto devSPI_ClkPhase      = htl::spi::ClkPhase::edge1;
        constexpr auto devSPI_WordSize      = htl::spi::WordSize::ws8;
        constexpr auto devSPI_FirstBit      = htl::spi::FirstBit::msb;
        constexpr auto devSPI_ClockDivider  = htl::spi::ClockDivider::div8;
#endif
    }
}


#endif // __appConfig__
