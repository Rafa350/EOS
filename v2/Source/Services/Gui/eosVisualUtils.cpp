#include "eos.h"
#include "Services/Gui/eosVisual.h"
#include "Services/Gui/eosVisualUtils.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosRect.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Converteix un punt a coordinades de pantalla.
/// \param    pVisual: El visual.
/// \param    p: El punt en coordinades relatives al visual.
/// \return   El punt en coordinades absolutes de pantalla.
///
Point VisualUtils::getPosition(
	Visual *pVisual) {

	int x = 0;
	int y = 0;

	while (pVisual != nullptr) {
		const Rect& bounds = pVisual->getBounds();
		x += bounds.getX();
		y += bounds.getY();

		pVisual = pVisual->getParent();
	}

	return Point(x, y);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el rectangle de retall d'un visual.
/// \param    pVisual: El visual.
/// \return   El rectangle de retall.
///
Rect VisualUtils::getClip(
	Visual *pVisual) {

	Rect clip(0, 0, INT32_MAX, INT32_MAX);
	while (pVisual != nullptr) {
		const Rect& bounds(pVisual->getBounds());
		clip = clip.intersect(bounds.getSize());
		clip = clip.offset(bounds.getPosition());
		pVisual = pVisual->getParent();
	}

	return clip;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el visual al que pertany el punt.
/// \param    pVisual: El visual.
/// \param    p: El punt.
/// \return   El visual. Si no el troba retorna nullptr.
///
Visual *VisualUtils::getVisual(
	Visual *pVisual,
	const Point &p) {

	if (pVisual->isVisible()) {

		Rect bounds = pVisual->getBounds();

		Rect testRect(bounds.getSize());
		Point testPoint = p.offset(-bounds.getX(), -bounds.getY());

		if (testRect.contains(testPoint)) {
			for (VisualListIterator it(pVisual->getChilds()); it.hasNext(); it.next()) {
				Visual *pChild = it.current();

				Visual *pResult = getVisual(pChild, testPoint);
				if (pResult != nullptr)
					return pResult;
			}
			return pVisual;
		}
	}

	return nullptr;
}

