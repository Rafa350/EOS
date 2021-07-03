#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosBorder.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
Border::Border():
	_background(Brush(BrushStyle::solid, COLOR_Red)),
	_borderBrush(Brush(BrushStyle::solid, COLOR_Black)),
	_borderThickness(1),
	_radius(0) {

}


/// ----------------------------------------------------------------------
///
Size Border::measureOverride(
	const Size &availableSize) const {

	Size size = Decorator::measureOverride(availableSize);
	return _borderThickness.inflate(size);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la brotxa del perfil.
/// \param    value: La brotxa
///
void Border::setBorderBrush(
	const Brush &value) {

	if (_borderBrush != value) {
		_borderBrush = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'amplada del perfil.
/// \param    value: Amplada del perfil.
///
void Border::setBorderThickness(
	int value) {

	if (_borderThickness != value) {
		_borderThickness = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el radi de curvatura del perfil.
/// \param    value: Radi de curvatura.
///
void Border::setRadius(
	int value) {

	if (_radius != value) {
		_radius = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la brotxa del fons.
/// \param    value: La brotxa.
///
void Border::setBackground(
	const Brush &value) {

	if (_background != value) {
		_background = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Renderitza la imatge..
/// \param    context: El context de representacio.
///
void Border::onRender(
	RenderContext *context) {

	Graphics &g = context->beginRender(this);

	const Size &s = getBounds().getSize();
	Pen pen(PenStyle::solid, _borderBrush.getColor(), _borderThickness.getLeft());
	g.paintRectangle(pen, _background, Rect(0, 0, s.getWidth(), s.getHeight()));

	context->endRender();
}
