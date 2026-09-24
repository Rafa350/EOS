module;


#include "eos.h"
#include "HTL/htlDMA.h"
#include "HTL/htlUART.h"


export module Eos.Controllers.Serial.UARTDMA;


export import Eos.Controllers.Serial.UART;


export namespace eos {

	class SerialDriver_UARTDMA: public SerialDriver_UART {
		public:
			using DMADevice = htl::dma::DMADevice;

	    private:
	        DMADevice * const _devDMAtx;
	        DMADevice * const _devDMArx;

	    private:
            bool onTransmit(const uint8_t *buffer, size_t length) override;
            bool onReceive(uint8_t *buffer, size_t bufferSize) override;

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
	const uint8_t *buffer,
	size_t bufferSize) {

    return _devUART->transmit_DMA(_devDMAtx, buffer, bufferSize).isSuccess();
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades de forma asincrona.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany en bytes del buffer de dades.
///
bool eos::SerialDriver_UARTDMA::onReceive(
	uint8_t *buffer,
	size_t bufferSize) {

    return _devUART->receive_IRQ(buffer, bufferSize).isSuccess();
}
