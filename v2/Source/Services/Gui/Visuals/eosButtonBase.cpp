#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosButtonBase.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
ButtonBase::ButtonBase():
	pressed(false) {

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
#ifdef OPT_GUI_TouchPad
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
#ifdef OPT_GUI_TouchPad
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
#ifdef OPT_GUI_TouchPad
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

	if (clickCallback != nullptr)
		clickCallback->execute(this);
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
