#pragma once
#ifndef __eosSerialDriver_UARTDMA__
#define __eosSerialDriver_UARTDMA__


#include "Controllers/Serial/eosSerialDriver_UART.h"
#include "HTL/htlDMA.h"


namespace eos {

	class SerialDriver_UARTDMA: public SerialDriver_UART {
	    private:
	        using DevDMA = htl::dma::DMADevice;

	    private:
	        DevDMA * const _devDMAtx;
	        DevDMA * const _devDMArx;

	    private:
            bool onTransmit(const uint8_t *buffer, unsigned length) override;
            bool onReceive(uint8_t *buffer, unsigned bufferSize) override;

	    public:
            SerialDriver_UARTDMA(DevUART *devUART, DevDMA *devDMAtx, DevDMA *devDMArx);
	};
}


#endif // __eosSerialDriver_UARTDMA__
