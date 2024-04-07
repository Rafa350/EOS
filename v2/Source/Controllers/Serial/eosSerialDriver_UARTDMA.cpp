#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosSerialDriver_UARTDMA.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devUART: El dispositiu uart a utilitzar.
///
SerialDriver_UARTDMA::SerialDriver_UARTDMA(
	DevUART *devUART,
	DevDMA *devDMAtx,
	DevDMA *devDMArx):

	SerialDriver_UART(devUART),
	_devDMAtx {devDMAtx},
	_devDMArx {devDMArx} {
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades de forma asincrona.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: Nombre de bytes en el buffer de dades..
///
void SerialDriver_UARTDMA::onTransmit(
	const uint8_t *buffer,
	unsigned bufferSize) {

    //notifyTxStart();
    _devUART->transmit_DMA(_devDMAtx, buffer, bufferSize);
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades de forma asincrona.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany en bytes del buffer de dades.
///
void SerialDriver_UARTDMA::onReceive(
	uint8_t *buffer,
	unsigned bufferSize) {

    //notifyRxStart();
    _devUART->receive_IRQ(buffer, bufferSize);
}
