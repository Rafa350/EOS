#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosVirtualKeyboard.h"
#include "System/Graphics/eosColorDefinitions.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
VirtualKeyboard::VirtualKeyboard():
	_eventCallback(nullptr),
	_buttonEventCallback(this, &VirtualKeyboard::buttonEventHandler) {

	VirtualKeyboardTemplate t(this);
	t.applyTemplate();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els events dels botons.
/// \param    args: Arguments del event.
///
void VirtualKeyboard::buttonEventHandler(
	const ButtonBase::EventArgs& args) {

	if (args.event == ButtonBase::EventType::click) {

		// Genera el missatge de teclat
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
		if (_eventCallback != nullptr) {
			EventArgs vkArgs = {
				.keyboard = this,
				.keyCode = KeyCode(args.button->getId())
			};
			_eventCallback->execute(vkArgs);
		}
	}
}
