#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosButtonBase.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
ButtonBase::ButtonBase():
	pressed(false),
	clickMode(ClickMode::atRelease),
	eventCallback(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Genera una pulsacio del boto.
///
void ButtonBase::click() {

	onClick();
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant es presiona el touchpad.
/// \param    position: Posicio del toc.
///
#if eosGuiService_TouchPadEnabled
void ButtonBase::onTouchPadPress(
	const Point &position) {

	onPress();

	pressed = true;

	Visual::onTouchPadPress(position);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Es crida quant es deixa de presionar el pad.
///
#if eosGuiService_TouchPadEnabled
void ButtonBase::onTouchPadRelease() {

	onRelease();

	if (pressed)
		onClick();

	pressed = false;

	Visual::onTouchPadRelease();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Es crida quant el pad ja no actua en el visual.
///
#if eosGuiService_TouchPadEnabled
void ButtonBase::onTouchPadLeave() {

	onRelease();

	pressed = false;

	Visual::onTouchPadLeave();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Es crida quant es prem el boto i es deixa anar.
///
void ButtonBase::onClick() {

	if (eventCallback != nullptr) {
		EventArgs args = {
			.button = this,
			.event = EventType::click
		};
		eventCallback->execute(args);
	}
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant es prem el boto.
///
void ButtonBase::onPress() {

	if (eventCallback != nullptr) {
		EventArgs args = {
			.button = this,
			.event = EventType::press
		};
		eventCallback->execute(args);
	}
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant es deixa anar el boto.
///
void ButtonBase::onRelease() {

	if (eventCallback != nullptr) {
		EventArgs args = {
			.button = this,
			.event = EventType::release
		};
		eventCallback->execute(args);
	}
}
