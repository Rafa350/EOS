#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosBorder.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
///
Border::Border():
	backgroundColor(COLOR_Transparent),
	color(),
	thickness(1),
	radius(0),
	pContent(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief Calcula les mesures del control
/// \param availableSize: Tamany disponible.
///
Size Border::measureOverride(
	const Size &availableSize) const{

	return availableSize;
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
void Border::setColor(
	const Color &newColor) {

	if (this->color != newColor) {
		this->color = newColor;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna l'amplada del perfil.
/// \param newThickness: Amplada del perfil.
///
void Border::setThickness(
	int newThickness) {

	if (this->thickness != newThickness) {
		this->thickness = newThickness;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el radi de curvatura del perfil.
/// \param newRadius: Radi de curvatura.
///
void Border::setRadius(
	int newRadius) {

	if (this->radius != newRadius) {
		this->radius = newRadius;
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

	g.setColor(color);
	g.drawRectangle(r);

	context.endRender();
}
