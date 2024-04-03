#pragma once
#ifndef __eosSerialDriver_UARTDMA__
#define __eosSerialDriver_UARTDMA__


#include "Controllers/Serial/eosSerialDriver_UART.h"
#include "HTL/htlDMA.h"


namespace eos {

	class AsyncSerialDriver_UARTDMA: public AsyncSerialDriver_UART {
	    private:
	        using DevDMA = htl::dma::DMADevice;

	    private:
	        DevDMA * const _devDMAtx;
	        DevDMA * const _devDMArx;

	    private:
            bool startTxImpl(const uint8_t *buffer, unsigned length) override;
            bool startRxImpl(uint8_t *buffer, unsigned bufferSize) override;

	    public:
            AsyncSerialDriver_UARTDMA(DevUART *devUART, DevDMA *devDMAtx, DevDMA *devDMArx);
	};
}


#endif // __eosSerialDriver_UARTDMA__
