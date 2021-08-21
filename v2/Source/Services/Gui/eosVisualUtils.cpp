#include "eos.h"
#include "Services/Gui/eosVisual.h"
#include "Services/Gui/eosVisualUtils.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosRect.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Converteix un punt a coordinades de pantalla.
/// \param    visual: El visual.
/// \param    p: El punt en coordinades relatives al visual.
/// \return   El punt en coordinades absolutes de pantalla.
///
Point VisualUtils::getPosition(
	Visual *visual) {

	int x = 0;
	int y = 0;

	while (visual != nullptr) {
		const Rect& bounds = visual->getBounds();
		x += bounds.getX();
		y += bounds.getY();

		visual = visual->getParent();
	}

	return Point(x, y);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el rectangle de retall d'un visual.
/// \param    visual: El visual.
/// \return   El rectangle de retall.
///
Rect VisualUtils::getClip(
	Visual *visual) {

	Rect clip(0, 0, INT32_MAX, INT32_MAX);

#if 0
	while (visual != nullptr) {
		const Rect& bounds(visual->getBounds());
		clip = clip.intersected(bounds.getSize());
		clip = clip.translated(bounds.getPosition());
		visual = visual->getParent();
	}
#else
	while (visual != nullptr) {
		const Rect& bounds(visual->getBounds());
		Rect clipRect(getPosition(visual), bounds.getSize());
		clip = clip.intersected(clipRect);
		visual = visual->getParent();
	}
#endif
	return clip;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el visual al que pertany el punt.
/// \param    pVisual: El visual.
/// \param    p: El punt.
/// \return   El visual. Si no el troba retorna nullptr.
///
Visual *VisualUtils::getVisual(
	Visual *visual,
	const Point& p) {

	if (visual->isVisible()) {

		Rect bounds = visual->getBounds();

		Rect testRect(bounds.getSize());
		Point testPoint = p.translated(-bounds.getX(), -bounds.getY());

		if (testRect.contains(testPoint)) {
			const Visual::VisualList& childs = visual->getChilds();
			for (auto child: childs) {
				Visual *result = getVisual(child, testPoint);
				if (result != nullptr)
					return result;
			}
			return visual;
		}
	}

	return nullptr;
}


Visual *VisualUtils::getVisual(
	Visual* visual,
	unsigned id) {

	if (visual->getId() == id)
		return visual;

	else {
		const Visual::VisualList& childs = visual->getChilds();
		for (auto child: childs) {
			Visual* result = VisualUtils::getVisual(child, id);
			if (result != nullptr)
				return result;
		}
	}

	return nullptr;
}
