#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosAsyncSerialDriver_UARTDMA.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devUART: El dispositiu uart a utilitzar.
///
AsyncSerialDriver_UARTDMA::AsyncSerialDriver_UARTDMA(
	DevUART *devUART,
	DevDMA *devDMAtx,
	DevDMA *devDMArx):

	AsyncSerialDriver_UART(devUART),
	_devDMAtx {devDMAtx},
	_devDMArx {devDMArx} {
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades de forma asincrona.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: Nombre de bytes en el buffer de dades..
/// \return   True si tot es correcte.
///
bool AsyncSerialDriver_UARTDMA::transmitImpl(
	const uint8_t *buffer,
	unsigned bufferSize) {

    eosAssert(buffer != nullptr);
    eosAssert(bufferSize > 0);

    if (_devDMAtx == nullptr)
        return AsyncSerialDriver_UART::transmitImpl(buffer, bufferSize);

    else {

        if (isBusy())
            return false;

        else {
            notifyTxStart();

            // TODO DMA_IRQ
            _devUART->transmit_DMA(_devDMAtx, buffer, bufferSize);

            // En aquest moment es genera una comença la transmissio,
            // fins la interrupcio TX_COMPLETE

            return true;
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades de forma asincrona.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany en bytes del buffer de dades.
/// \return   True si tot es correcte.
///
bool AsyncSerialDriver_UARTDMA::receiveImpl(
	uint8_t *buffer,
	unsigned bufferSize) {

    eosAssert(buffer != nullptr);
    eosAssert(bufferSize > 0);

    if (_devDMArx == nullptr)
        return AsyncSerialDriver_UART::receiveImpl(buffer, bufferSize);

    else {

        if (isBusy())
		return false;

        else {
            notifyRxStart();

            _devUART->receive_IRQ(buffer, bufferSize);

            // En aquest moment, es generen interrupcions
            // cada cop que hi han dades disposibles en la UART.

            return true;
        }
    }
}
