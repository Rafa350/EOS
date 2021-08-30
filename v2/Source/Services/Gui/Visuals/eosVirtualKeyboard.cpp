#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosVirtualKeyboard.h"
#include "System/Graphics/eosColorDefinitions.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
VirtualKeyboard::VirtualKeyboard():
	_virtualKeyboardEventCallback(nullptr),
	_buttonClickEventCallback(this, &VirtualKeyboard::buttonClickEventHandler) {

	VirtualKeyboardTemplate t(this);
	t.applyTemplate();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els events dels botons.
/// \param    args: Arguments del event.
///
void VirtualKeyboard::buttonClickEventHandler(
	const ButtonEventArgs& args) {

	// Genera el missatge de teclat, com si fos un teclat real
	//
	Message msg = {
		.msgId = MsgId::keyboardEvent,
		.target = nullptr,
		.keyboard = {
			.event = MsgKeyboardEvent::press,
			.keyCode = KeyCode(args.id),
			.keyFlags = 0
		}
	};
	send(msg);

	// Crida a la funcio callback
	//
	if (_virtualKeyboardEventCallback != nullptr)
		_virtualKeyboardEventCallback->execute(VirtualKeyboardEventArgs(this, KeyCode(args.id)));
}
