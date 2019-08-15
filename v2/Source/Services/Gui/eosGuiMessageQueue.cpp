#include "eos.h"
#include "Services/Gui/eosGuiMessageQueue.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
///
GuiMessageQueue::GuiMessageQueue():

	queue(OPT_GUI_MessageQueueSize) {

}


/// ----------------------------------------------------------------------
/// \brief Envia un missatge.
/// \param msg: El missatge a enviar.
///
void GuiMessageQueue::send(
	const Message &msg) {

	queue.put(msg, 0);
}


/// ----------------------------------------------------------------------
/// \brief Espera la recepcio dun missatge.
/// \param msg: El missatge rebut.
/// \return Tue si tot es correcte.
///
bool GuiMessageQueue::receive(
	Message &msg) {

	return queue.get(msg, OPT_GUI_MessageQueueBlockTime);
}
