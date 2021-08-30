#include "eos.h"
#include "Services/Gui/eosMsgQueue.h"
#include "Services/Gui/Visuals/eosCommandButton.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
CommandButton::CommandButton():
	_id(-1),
	_param(nullptr),
	_target(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant es fa click. Genera una comanda.
///
void CommandButton::onClick(
	const ButtonEventArgs& args) {

	if (_id != -1) {
		Message msg;
		msg.msgId = MsgId::command;
		msg.target = (_target == nullptr) ? getParent() : _target;
		msg.command.id = _id;
		msg.command.param = _param;
		send(msg);
	}

	PushButton::onClick(args);
}
