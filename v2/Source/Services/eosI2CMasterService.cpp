#include "eos.h"
#include "HTL/htlI2C.h"
#include "Services/eosI2CMasterService.h"


using namespace eos;
using namespace htl::i2c;


/// ----------------------------------------------------------------------
/// \brief    Constructor l'objecte.
///
I2CMasterService::I2CMasterService(
	DevI2C *devI2C):

	_devI2C {devI2C},
	_transactionQueue {_transactionQueueSize},
	_notifyEvent {*this, &I2CMasterService::notifyEventHandler} {

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
bool I2CMasterService::onTask() {

	_devI2C->setNotifyEvent(_notifyEvent);

	uint8_t buffer[5];
	buffer[0] = 0x50;
	buffer[1] = 0x51;
	buffer[2] = 0x52;
	buffer[3] = 0x53;
	buffer[4] = 0x54;

	Transaction tr = {
		.addr = 0x52,
		.txBuffer = buffer,
		.txLength = sizeof(buffer),
		.rxBuffer = nullptr,
		.rxBufferSize = 0,
		.rxLength = 0
	};
	_transactionQueue.push(tr, unsigned(-1));


	while (!stopSignal()) {

		Transaction transaction;
		while (!stopSignal() && _transactionQueue.pop(transaction, 1000)) {

			_devI2C->transmit_IRQ(
				transaction.addr,
				transaction.txBuffer,
				transaction.txLength);

			_finishedTransaction.wait(unsigned(-1));
		}

	}

	_devI2C->disableNotifyEvent();

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les notificacions del dispositiu.
/// \param    args: Els parametres de la notificacio.
///
void I2CMasterService::notifyEventHandler(
	htl::i2c::NotifyEventArgs &args) {

	switch (args.id) {
		case htl::i2c::NotifyID::txCompleted:
			if (args.irq)
				_finishedTransaction.releaseISR();
			else
				_finishedTransaction.release();
			break;
	}
}
