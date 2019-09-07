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
/// \param pNewContent: El contingut.
///
void Border::setContent(
	Visual *pNewContent) {

	if (pContent != pNewContent) {

		if (pContent != nullptr)
			removeVisual(pContent);

		pContent = pNewContent;

		if (pContent != nullptr)
			addVisual(pContent);

		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el color del perfil.
/// \param newColor: El color.
///
void Border::setBorderColor(
	const Color &newColor) {

	if (borderColor != newColor) {
		borderColor = newColor;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna l'amplada del perfil.
/// \param newThickness: Amplada del perfil.
///
void Border::setBorderThickness(
	int newThickness) {

	if (borderThickness != newThickness) {
		borderThickness = newThickness;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el radi de curvatura del perfil.
/// \param newRadius: Radi de curvatura.
///
void Border::setBorderRadius(
	int newRadius) {

	if (borderRadius != newRadius) {
		borderRadius = newRadius;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el color del fons.
/// \param newColor: El color.
///
void Border::setBackgroundColor(
	const Color &newColor) {

	if (backgroundColor != newColor) {
		backgroundColor = newColor;
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
