#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/eosBorder.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
///
Border::Border():
	backgroundColor(),
	borderColor(),
	borderThickness(1),
	borderRadius(0),
	content(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief Assigna el contingut.
/// \param visual: El contingut.
///
void Border::setContent(
	Visual *visual) {

	if (content != visual) {

		if (content != nullptr)
			removeVisual(content);

		content = visual;

		if (content != nullptr)
			addVisual(content);

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
/// \param graphics: L'bjecte 'Graphics' per dibuixar.
///
void Border::onRender(
	RenderContext *context) {

	Graphics *g = context->beginRender(this);

	int x1 = 0;
	int y1 = 0;
	int x2 = getWidth() - 1;
	int y2 = getHeight() - 1;

	g->setColor(backgroundColor);
	g->fillRectangle(x1, y1, x2, y2);

	g->setColor(borderColor);
	g->drawRectangle(x1, y1, x2, y2);

	context->endRender();
}
