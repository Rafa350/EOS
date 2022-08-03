#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosPushButton.h"
#include "System/eosString.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
PushButton::PushButton():
	_state(State::normal) {
}


/// ----------------------------------------------------------------------
/// \brief    Canvia l'estat del boto.
/// \param    value: El nou estat.
///
void PushButton::setState(
	State value) {

	if (_state != value) {
		_state = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant cal Renderitzar el visual.
/// \param    context: El context de renderitzat.
///
void PushButton::onRender(
	RenderContext *context) {

	// Inicia el renderitzat.
	//
	Graphics &g = context->beginRender(this);

	// Obte les mides de l'area de dibuix
	//
	const Size s = getBounds().getSize();
	const Rect r(0, 0, s.getWidth(), s.getHeight());
	const int radius = Math::min(s.getWidth(), s.getHeight()) / 3;

	// Dibuixa el boto
	//
	switch (_state) {
		case State::normal:
			g.paintRoundedRectangle(
				Pen(PenStyle::solid, Colors::lightSeaGreen, 1),
				Brush(BrushStyle::solid, Colors::teal),
				r,
				radius, radius);
			break;

		case State::pushed:
			g.paintRoundedRectangle(
				Pen(PenStyle::solid, Colors::lightCyan, 1),
				Brush(BrushStyle::solid, Colors::cadetBlue),
				r,
				radius, radius);
			break;

		default:
			break;
	}

	// Finalitza el renderitzat.
	//
	context->endRender();
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant es prem el boto.
///
void PushButton::onPress(
	const ButtonEventArgs& args) {

	setState(State::pushed);

	ButtonBase::onPress(args);
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quanrt es deixa anar el boto.
///
void PushButton::onRelease(
	const ButtonEventArgs& args) {

	setState(State::normal);

	ButtonBase::onRelease(args);
}
