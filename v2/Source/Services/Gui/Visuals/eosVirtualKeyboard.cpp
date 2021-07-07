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
/// \brief    Priocesa els events dels botons.
/// \param    args: Arguments del event.
///
void VirtualKeyboard::buttonEventHandler(
	const ButtonBase::EventArgs &args) {

	if (_eventCallback != nullptr) {

		if (args.event == ButtonBase::EventType::click) {

			EventArgs vkArgs = {
					.keyboard = this,
					.keyCode = KeyCode(args.button->getId())
			};
			_eventCallback->execute(vkArgs);
		}
	}
}
