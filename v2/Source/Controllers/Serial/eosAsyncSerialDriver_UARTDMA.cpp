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
/// \param    data: El buffer de dades.
/// \param    dataLength: Nombre de bytes en el buffer de dades..
/// \return   True si tot es correcte.
///
bool AsyncSerialDriver_UARTDMA::transmitImpl(
	const uint8_t *data,
	int dataLength) {

    eosAssert(data != nullptr);
    eosAssert(dataLength > 0);

    if (_devDMAtx == nullptr)
        return AsyncSerialDriver_UART::transmitImpl(data, dataLength);

    else {

        if (isBusy())
            return false;

        else {
            notifyTxStart();

            // TODO DMA_IRQ
            _devUART->transmitDMA(_devDMAtx, data,  dataLength);

            // En aquest moment es genera una interrupcio txEmpty
            // i comença la transmissio controlada per interrupcions.

            return true;
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades de forma asincrona.
/// \param    data: El buffer de dades.
/// \param    dataSize: El tamany en bytes del buffer de dades.
/// \return   True si tot es correcte.
///
bool AsyncSerialDriver_UARTDMA::receiveImpl(
	uint8_t *data,
	int dataSize) {

    eosAssert(data != nullptr);
    eosAssert(dataSize > 0);

    if (_devDMArx == nullptr)
        return AsyncSerialDriver_UART::receiveImpl(data, dataSize);

    else {

        if (isBusy())
		return false;

        else {
            notifyRxStart();

            _devUART->receive_IRQ(data, dataSize);

            // En aquest moment, es generen interrupcions
            // cada cop que hi han dades disposibles en la UART.

            return true;
        }
    }
}
