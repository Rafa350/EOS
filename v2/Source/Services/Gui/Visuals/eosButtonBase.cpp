#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosGuiMessageQueue.h"
#include "Services/Gui/Visuals/eosButtonBase.h"


using namespace eos;


/// ---------------------------------------------------------------------
/// \brief Genera una pulsacio del boto.
///
void ButtonBase::click() {

	onClick();
}


/// ----------------------------------------------------------------------
/// \brief procesa el missatge 'touchPadEvent'.
/// \param msg: El missatge a procesar.
///
void ButtonBase::onTouchPadEvent(
	const Message &msg) {

	switch(msg.touchPad.event) {
		case MsgTouchPadEvent::press:
			onPress();
			onClick();
			break;

		case MsgTouchPadEvent::release:
			onRelease();
			break;

		default:
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Es crida quantt es prem el boto.
///
void ButtonBase::onClick() {

}


/// ----------------------------------------------------------------------
/// \brief Es crida quant es prem el boto.
///
void ButtonBase::onPress() {

}


/// ----------------------------------------------------------------------
/// \brief Es crida quant es deixa anar el boto.
///
void ButtonBase::onRelease() {

}
