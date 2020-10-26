#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosVirtualKeyboard.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
VirtualKeyboard::VirtualKeyboard():
	eventCallback(nullptr),
	buttonEventCallback(this, &VirtualKeyboard::buttonEventHandler) {

	VirtualKeyboardTemplate t(this);
	t.applyTemplate();
}


/// ----------------------------------------------------------------------
/// \brief    Priocesa els events dels botons.
/// \param    args: Arguments del event.
///
void VirtualKeyboard::buttonEventHandler(
	const ButtonBase::EventArgs &args) {

	if (eventCallback != nullptr) {

		if (args.event == ButtonBase::EventType::click) {

			EventArgs vkArgs = {
					.keyboard = this,
					.keyCode = KeyCode(args.button->getId())
			};
			eventCallback->execute(vkArgs);
		}
	}
}
