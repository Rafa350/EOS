#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosVirtualKeyboard.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
VirtualKeyboard::VirtualKeyboard():
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

	switch (args.event) {
		case ButtonBase::EventType::click:
			// Genera un missatge MsgKey
			break;

		default:
			break;
	}
}