#pragma once
#ifndef __appConfig__
#define __appConfig__


#include "HTL/htlGPIO.h"
#include "HTL/htlINT.h"
#include "HTL/htlUART.h"


namespace app {

    namespace hw {

        //using DevUART = SIO_UART_Device;
        //using PinTX = SIO_TX_Pin;
        //using PinRX = SIO_RX_Pin;

        //constexpr auto devUART = DevUART::pInst;
        //constexpr auto devUART_VectorID = SIO_UART_IrqVector;
    }

    namespace configuration {
    	namespace usbd {

    		constexpr uint16_t vendorID = 0x0483;     // Vendor ID
    		constexpr uint16_t productID = 0x5720;    // Product ID
    		constexpr uint16_t languageID = 0x0409;   // Language ID

    		constexpr const char *manufacturerStr = "rsr.openware@gmail.com";
    		constexpr const char *productStr = "EOS USB Device Demo";

    		constexpr uint8_t maxPower = 50;          // Power 50mA

    		namespace cdc {
    			constexpr eos::EpAddr inEpAddr = eos::EpAddr(0x81);    // IN endpoint
    			constexpr eos::EpAddr outEpAddr = eos::EpAddr(0x01);   // OUT endpoint
    			constexpr eos::EpAddr cmdEpAddr = eos::EpAddr(0x82);   // CMD endpoint

    			constexpr unsigned cmdPacketSize = 8;       // CMD packet size
    			constexpr unsigned dataMaxPackedSize = 64;  // DATA FS packet size
    			constexpr unsigned bInterval = 16;          // bInterval
    		}

    		namespace msc {
    			constexpr eos::EpAddr inEpAddr = eos::EpAddr(0x81);    // IN endpoint
    			constexpr eos::EpAddr outEpAddr = eos::EpAddr(0x01);   // OUT endpoint
    		}
    	}
    }
}


#endif // __appConfig__
