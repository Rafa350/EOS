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
	_clickEventCallback(nullptr),
	_pressEventCallback(nullptr),
	_releaseEventCallback(nullptr) {
}


/// ----------------------------------------------------------------------
/// \brief    Genera una pulsacio del boto.
///
void ButtonBase::click() {

	onClick(ButtonEventArgs(this, getId()));
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el modus de click.
/// \param    clickMode: El modus.
///
void ButtonBase::setClickMode(
	ClickMode value) {

	_clickMode = value;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el event 'TouchpadPress'.
/// \param    args: Parametres del event.
///
#if eosGuiService_TouchpadEnabled
void ButtonBase::onTouchpadPress(
	const TouchpadPressEventArgs& args) {

	Visual::onTouchpadPress(args);

	onPress(ButtonEventArgs(this, getId()));

	if (_clickMode == ClickMode::atPress)
		onClick(ButtonEventArgs(this, getId()));

	_pressed = true;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el event 'TouchpadRelease'.
/// \param    args: Parametres del event.
///
#if eosGuiService_TouchpadEnabled
void ButtonBase::onTouchpadRelease(
	const TouchpadReleaseEventArgs& args) {

	onRelease(ButtonEventArgs(this, getId()));

	if (_pressed && (_clickMode == ClickMode::atRelease))
		onClick(ButtonEventArgs(this, getId()));

	_pressed = false;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el event 'TouchpadLeave'
/// \param    args: Parametres del event.
///
#if eosGuiService_TouchpadEnabled
void ButtonBase::onTouchpadLeave(
	const TouchpadLeaveEventArgs& args) {

	onRelease(ButtonEventArgs(this, getId()));

	_pressed = false;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Es crida quant es prem el boto i es deixa anar.
/// \param    args: Parametres del event.
///
void ButtonBase::onClick(
	const ButtonEventArgs& args) {

	if (_clickEventCallback != nullptr)
		_clickEventCallback->execute(args);
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant es prem el boto.
/// \param    args: Parametres del event.
///
void ButtonBase::onPress(
	const ButtonEventArgs& args) {

	if (_pressEventCallback != nullptr)
		_pressEventCallback->execute(args);
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant es deixa anar el boto.
/// \param    args: Parametres del event.
///
void ButtonBase::onRelease(
	const ButtonEventArgs& args) {

	if (_releaseEventCallback != nullptr)
		_releaseEventCallback->execute(args);
}
