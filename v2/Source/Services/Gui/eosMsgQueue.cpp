#include "eos.h"
#include "Services/Gui/eosMsgQueue.h"


using namespace eos;


MsgQueue *MsgQueue::_instance = nullptr;


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
///
MsgQueue::MsgQueue():

	_queue(eosGuiService_MessageQueueSize) {
}


/// ----------------------------------------------------------------------
/// \brief    Obte una instancia unica del objecte.
/// \return   La instancio del objecte.
///
MsgQueue* MsgQueue::getInstance() {

	if (_instance == nullptr)
		_instance = new MsgQueue();
	return _instance;
}


/// ----------------------------------------------------------------------
/// \brief    Envia un missatge.
/// \param    msg: El missatge a enviar.
///
void MsgQueue::send(
	const Message& msg) {

	_queue.push(msg, 0);
}


/// ----------------------------------------------------------------------
/// \brief    Espera la recepcio dun missatge.
/// \param    msg: El missatge rebut.
/// \return   True si tot es correcte.
///
bool MsgQueue::receive(
	Message& msg) {

	return _queue.pop(msg, eosGuiService_MessageQueueBlockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si la cua es buida.
/// \return   True si es buida, false en cas contrari.
///
bool MsgQueue::isEmpty() const {

	return false;
}
