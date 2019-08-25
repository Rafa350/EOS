#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosBorder.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
///
Border::Border():
	backgroundColor(COLOR_Transparent),
	borderColor(),
	borderThickness(1),
	borderRadius(0),
	pContent(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief Assigna el contingut.
/// \param pVisual: El contingut.
///
void Border::setContent(
	Visual *pVisual) {

	if (pContent != pVisual) {

		if (pContent != nullptr)
			removeVisual(pContent);

		pContent = pVisual;

		if (pContent != nullptr)
			addVisual(pContent);

		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el color del perfil.
/// \param color: El color.
///
void Border::setBorderColor(
	const Color &color) {

	if (borderColor != color) {
		borderColor = color;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna l'amplada del perfil.
/// \param thickness: Amplada del perfil.
///
void Border::setBorderThickness(
	int thickness) {

	if (borderThickness != thickness) {
		borderThickness = thickness;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el radi de curvatura del perfil.
/// \param radius: Radi de curvatura.
///
void Border::setBorderRadius(
	int radius) {

	if (borderRadius != radius) {
		borderRadius = radius;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el color del fons.
/// \param color: El color.
///
void Border::setBackgroundColor(
	const Color &color) {

	if (backgroundColor != color) {
		backgroundColor = color;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Renderitza la imatge..
/// \param context: El context de representacio.
///
void Border::onRender(
	RenderContext &context) {

	Graphics &g = context.beginRender(this);

	Rect r(getRect());

	g.setColor(backgroundColor);
	g.fillRectangle(r);

	g.setColor(borderColor);
	g.drawRectangle(r);

	context.endRender();
}
