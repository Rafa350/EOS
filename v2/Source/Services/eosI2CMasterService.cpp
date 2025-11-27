#include "eos.h"
#include "HTL/htlI2C.h"
#include "Services/eosI2CMasterService.h"


using namespace eos;
using namespace htl::i2c;


/// ----------------------------------------------------------------------
/// \brief    Constructor l'objecte.
///
I2CMasterService::I2CMasterService(
	htl::i2c::I2CMasterDevice *devI2C):

	_devI2C {devI2C},
	_devI2CNotificationEvent {*this, &I2CMasterService::devI2CNotificationEventHandler},
	_transactionQueue {_transactionQueueSize} {

}


/// -----------------------------------------------------------------------
/// \brief    Inicia una transaccio sense resposta.
/// \param    addr: L'adresa I2C
/// \param    txBuffer: Buffer de dades per transmetrte.
/// \param    txLength: Nombre de bytes a transmetre.
/// \param    event: L'event de final de transaccio.
/// \param    blockTime: Tamns maxim de bloqueig
///
bool I2CMasterService::startTransaction(
	I2CAddr addr,
	const uint8_t *txBuffer,
	unsigned txLength,
	ITransactionEvent &event,
	unsigned blockTime) {

	return startTransaction(addr, txBuffer, txLength, nullptr, 0, event, blockTime);
}


/// -----------------------------------------------------------------------
/// \brief    Inicia una transaccio
/// \param    addr: L'adresa I2C
/// \param    txBuffer: Buffer de dades per transmetrte.
/// \param    txLength: Nombre de bytes a transmetre.
/// \param    rxBuffer: Bupper per les dades de recepcio.
/// \params   rxBufferSize: Tamany en bytes del buffer de recepcio.
/// \param    event: L'event de final de transaccio.
/// \param    blockTime: Tamns maxim de bloqueig
///
bool I2CMasterService::startTransaction(
	I2CAddr addr,
	const uint8_t *txBuffer,
	unsigned txLength,
	uint8_t *rxBuffer,
	unsigned rxBufferSize,
	ITransactionEvent &event,
	unsigned blockTime) {

	// Prepara les dades de la transaccio
	//
	Transaction transaction = {
		.addr = addr,
		.txBuffer = txBuffer,
		.txLength = txLength,
		.rxBuffer = rxBuffer,
		.rxBufferSize = rxBufferSize,
		.rxLength = 0,
		.event = &event
	};

	// Afegeix la transaccio a la cua
	//
	return _transactionQueue.push(transaction, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servei.
///
void I2CMasterService::onExecute() {

	_devI2C->setNotificationEvent(_devI2CNotificationEvent);

	uint8_t txBufBer[5];
	txBufBer[0] = 0x50;
	txBufBer[1] = 0x51;
	txBufBer[2] = 0x52;
	txBufBer[3] = 0x53;
	txBufBer[4] = 0x54;

	uint8_t rxBuffer[3];

	Transaction tr = {
		.addr = 0x52,
		.txBuffer = txBufBer,
		.txLength = sizeof(txBufBer),
		.rxBuffer = rxBuffer,
		.rxBufferSize = sizeof(rxBuffer),
		.rxLength = 0,
		.event = nullptr
	};
	_transactionQueue.push(tr, unsigned(-1));

	while (!stopSignal()) {

		Transaction transaction;
		while (!stopSignal() && _transactionQueue.pop(transaction, 1000)) {

			_txFinishedLength = 0;
			_rxFinishedLength = 0;

			_devI2C->transmit_IRQ(
				transaction.addr,
				transaction.txBuffer,
				transaction.txLength);

			_txFinished.wait(unsigned(-1));

			if ((transaction.rxBuffer != nullptr) && (transaction.rxBufferSize != 0)) {

				_devI2C->receive_IRQ(
					transaction.addr,
					transaction.rxBuffer,
					transaction.rxBufferSize);

				_rxFinished.wait(unsigned(-1));
			}

			if (transaction.event != nullptr) {
				TransactionEventArgs args = {
					.txData = (uint8_t*) transaction.txBuffer,
					.txDataLength = _txFinishedLength,
					.rxData = transaction.rxBuffer,
					.rxDataLength = _rxFinishedLength
				};
				transaction.event->execute(this, args);
			}
		}

	}

	_devI2C->disableNotificationEvent();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les notificacions del dispositiu.
/// \param    args: Els parametres de la notificacio.
///
void I2CMasterService::devI2CNotificationEventHandler(
	htl::i2c::I2CMasterDevice * const sender,
	htl::i2c::NotificationEventArgs * const args) {

	switch (args->id) {
		case htl::i2c::NotificationID::txCompleted:
			if (args->irq)
				_txFinished.releaseISR();
			else
				_txFinished.release();
			_txFinishedLength = args->txCompleted.length;
			break;

		case htl::i2c::NotificationID::rxCompleted:
			if (args->irq)
				_rxFinished.releaseISR();
			else
				_rxFinished.release();
			_rxFinishedLength = args->rxCompleted.length;
			break;

		default:
			break;
	}
}
