#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosButtonBase.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
ButtonBase::ButtonBase():
	_pressed(false),
	_clickMode(ClickMode::atRelease),
	_eventCallback(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Genera una pulsacio del boto.
///
void ButtonBase::click() {

	onClick();
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el modus de click.
/// \param    clickMode: El modus.
///
void ButtonBase::setClickMode(ClickMode value) {

	_clickMode = value;
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant es presiona el touchpad.
/// \param    position: Posicio del toc.
///
#if eosGuiService_TouchPadEnabled
void ButtonBase::onTouchPadPress(
	const Point& position) {

	onPress();

	if (_clickMode == ClickMode::atPress)
		onClick();

	_pressed = true;

	Visual::onTouchPadPress(position);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Es crida quant es deixa de presionar el pad.
///
#if eosGuiService_TouchPadEnabled
void ButtonBase::onTouchPadRelease() {

	onRelease();

	if (_pressed && (_clickMode == ClickMode::atRelease))
		onClick();

	_pressed = false;

	Visual::onTouchPadRelease();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Es crida quant el pad ja no actua en el visual.
///
#if eosGuiService_TouchPadEnabled
void ButtonBase::onTouchPadLeave() {

	onRelease();

	_pressed = false;

	Visual::onTouchPadLeave();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Es crida quant es prem el boto i es deixa anar.
///
void ButtonBase::onClick() {

	if (_eventCallback != nullptr) {
		EventArgs args = {
			.button = this,
			.event = EventType::click,
			.id = getId()
		};
		_eventCallback->execute(args);
	}
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant es prem el boto.
///
void ButtonBase::onPress() {

	if (_eventCallback != nullptr) {
		EventArgs args = {
			.button = this,
			.event = EventType::press
		};
		_eventCallback->execute(args);
	}
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant es deixa anar el boto.
///
void ButtonBase::onRelease() {

	if (_eventCallback != nullptr) {
		EventArgs args = {
			.button = this,
			.event = EventType::release
		};
		_eventCallback->execute(args);
	}
}
