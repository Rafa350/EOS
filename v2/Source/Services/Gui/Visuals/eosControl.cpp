#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosControl.h"
#include "System/Graphics/eosColorDefinitions.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Control::Control():
	_foreground(Brush(BrushStyle::solid, COLOR_Black)),
	_background(Brush(BrushStyle::solid, COLOR_White)),
	_borderBrush(Brush(BrushStyle::solid, COLOR_Black)),
	_borderThickness(1) {

}


/// ---------------------------------------------------------------------
/// \brief    Inicialitza el control.
///
void Control::initializeControl() {

}


/// ----------------------------------------------------------------------
/// \brief    Calcula les measures del panell i dels seus fills
/// \param    availableSize: Tamany maxim disponible.
/// \return   El tamany desitjat.
///
Size Control::measureOverride(
	const Size& availableSize) const {

	Size size = Visual::measureOverride(availableSize);
	return _borderThickness.inflate(size);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la brotxa del perfil.
/// \param    value: La brotxa
///
void Control::setBorderBrush(
	const Brush& value) {

	if (_borderBrush != value) {
		_borderBrush = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'amplada del perfil.
/// \param    value: Amplada del perfil.
///
void Control::setBorderThickness(
	int value) {

	if (_borderThickness != value) {
		_borderThickness = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la brotxa de primer pla.
/// \param    value: La brotxa.
///
void Control::setForeground(
	const Brush& value) {

	if (_foreground != value) {
		_foreground = value;
		invalidate();
	}
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
