#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosControl.h"
#include "System/Graphics/eosColorDefinitions.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Control::Control():
	_background(Brush(BrushStyle::solid, Colors::white)) {

}


/// ---------------------------------------------------------------------
/// \brief    Inicialitza el control.
///
void Control::initializeControl() {

}


/// ----------------------------------------------------------------------
/// \brief    Asigna la brotxa del fons.
/// \param    value: La brotxa.
///
void Control::setBackground(
	const Brush& value) {

	if (_background != value) {
		_background = value;
		invalidate();
	}
}
