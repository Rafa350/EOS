#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosSerialDriver_UARTDMA.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devUART: El dispositiu uart a utilitzar.
///
SerialDriver_UARTDMA::SerialDriver_UARTDMA(
	htl::uart::UARTDevice *devUART,
	htl::dma::DMADevice *devDMAtx,
	htl::dma::DMADevice *devDMArx):

	SerialDriver_UART(devUART),
	_devDMAtx {devDMAtx},
	_devDMArx {devDMArx} {
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades de forma asincrona.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: Nombre de bytes en el buffer de dades..
///
bool SerialDriver_UARTDMA::onTransmit(
	const uint8_t *buffer,
	unsigned bufferSize) {

    return _devUART->transmit_DMA(_devDMAtx, buffer, bufferSize).isSuccess();
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades de forma asincrona.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany en bytes del buffer de dades.
///
bool SerialDriver_UARTDMA::onReceive(
	uint8_t *buffer,
	unsigned bufferSize) {

    return _devUART->receive_IRQ(buffer, bufferSize).isSuccess();
}
