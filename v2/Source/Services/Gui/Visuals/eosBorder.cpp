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
	backgroundColor(COLOR_Transparent),
	color(),
	thickness(1),
	radius(0),
	content(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Calcula les mesures del control
/// \param    availableSize: Tamany disponible.
///
Size Border::measureOverride(
	const Size &availableSize) const{

	return availableSize;
}


/// ----------------------------------------------------------------------
/// \brief    Assigna el contingut.
/// \param    value: El contingut.
///
void Border::setContent(
	Visual *value) {

	if (content != value) {

		if (content != nullptr)
			removeVisual(content);

		content = value;

		if (content != nullptr)
			addVisual(content);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el color del perfil.
/// \param    value: El color.
///
void Border::setColor(
	const Color &value) {

	if (color != value) {
		color = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'amplada del perfil.
/// \param    value: Amplada del perfil.
///
void Border::setThickness(
	int value) {

	if (thickness != value) {
		thickness = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el radi de curvatura del perfil.
/// \param    value: Radi de curvatura.
///
void Border::setRadius(
	int value) {

	if (radius != value) {
		radius = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el color del fons.
/// \param    value: El color.
///
void Border::setBackgroundColor(
	const Color &value) {

	if (backgroundColor != value) {
		backgroundColor = value;
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
	int x2 = s.getWidth() - 1;
	int y2 = s.getHeight() - 1;

	g.fillRectangle(0, 0, x2, y2, backgroundColor);
	g.drawRectangle(0, 0, x2, y2, color);

	context->endRender();
}
