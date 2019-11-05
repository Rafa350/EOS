#include "eos.h"
#include "Services/Gui/eosMsgQueue.h"
#include "Services/Gui/Visuals/eosCommandButton.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
CommandButton::CommandButton():
	id(-1),
	param(nullptr),
	target(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant es fa click. Genera una comanda.
///
void CommandButton::onClick() {

	if (id != -1) {
		Message msg;
		msg.msgId = MsgId::commandEvent;
		msg.target = (target == nullptr) ? getParent() : target;
		msg.command.id = id;
		msg.command.param = param;
		send(msg);
	}

	PushButton::onClick();
}
