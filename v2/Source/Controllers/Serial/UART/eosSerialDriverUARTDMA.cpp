module;


#include "eos.h"
#include "HTL/htlDMA.h"


export module Eos.Controllers.Serial.UARTDMA;


export import Eos.Controllers.Serial.UART;


import Eos.Types;


export namespace eos {

	class SerialDriver_UARTDMA: public SerialDriver_UART {
		public:
			using DMADevice = htl::dma::DMADevice;

	    private:
	        DMADevice * const _devDMAtx;
	        DMADevice * const _devDMArx;

	    private:
            bool onTransmit(const UInt8 *buffer, UInt32 length) override;
            bool onReceive(UInt8 *buffer, UInt32 bufferSize) override;

	    public:
            SerialDriver_UARTDMA(UARTDevice *devUART, DMADevice *devDMAtx, DMADevice *devDMArx);
	};
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devUART: El dispositiu uart a utilitzar.
///
eos::SerialDriver_UARTDMA::SerialDriver_UARTDMA(
	UARTDevice *devUART,
	DMADevice *devDMAtx,
	DMADevice *devDMArx):

	SerialDriver_UART {devUART},
	_devDMAtx {devDMAtx},
	_devDMArx {devDMArx} {
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades de forma asincrona.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: Nombre de bytes en el buffer de dades..
///
bool eos::SerialDriver_UARTDMA::onTransmit(
	const UInt8 *buffer,
	UInt32 bufferSize) {

    return _devUART->transmit_DMA(_devDMAtx, buffer, bufferSize).isSuccess();
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades de forma asincrona.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany en bytes del buffer de dades.
///
bool eos::SerialDriver_UARTDMA::onReceive(
	UInt8 *buffer,
	UInt32 bufferSize) {

    return _devUART->receive_IRQ(buffer, bufferSize).isSuccess();
}
