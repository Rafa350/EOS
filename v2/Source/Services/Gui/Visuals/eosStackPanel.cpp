#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosStackPanel.h"
#include "System/eosMath.h"



using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
///
StackPanel::StackPanel():
	orientation(Orientation::vertical) {

}


/// ----------------------------------------------------------------------
/// \brief Calcula les mesures del panell i dels seus fills
/// \param availableSize: Tamany maxim disponible.
/// \return El tamany desitjat.
///
Size StackPanel::measureOverride(
	const Size &availableSize) const {

	bool isHorizontal = orientation == Orientation::horitzontal;

	Size childAvailableSize(
	    isHorizontal ? INT32_MAX : availableSize.getWidth(),
	    isHorizontal ? availableSize.getHeight() : INT32_MAX);

	int measuredWidth = 0;
	int measuredHeight = 0;

	for (VisualListIterator it(getChilds()); it.hasNext(); it.next()) {

		Visual *pChild = it.current();
		eosAssert(pChild != nullptr);

		if (pChild->isVisible()) {

			pChild->measure(childAvailableSize);
			const Size& childSize = pChild->getDesiredSize();
			int childWidth = childSize.getWidth();
			int childHeight = childSize.getHeight();

			if (isHorizontal) {
				measuredWidth += childWidth;
				measuredHeight = Math::max(measuredHeight, childHeight);
			}
			else {
				measuredWidth = Math::max(measuredWidth, childWidth);
				measuredHeight += childHeight;
			}
		}
	}

	return Size(measuredWidth, measuredHeight);
}


/// ----------------------------------------------------------------------
/// \brief Ajusta el tamany del panell i dels seus fills.
/// \param finalSize: El tamany final a asignar.
/// \return El tamany final obtingut.
///
Size StackPanel::arrangeOverride(
	const Size &finalSize) const {

	int childX = 0;
	int childY = 0;

	bool isHorizontal = orientation == Orientation::horitzontal;

	for (VisualListIterator it(getChilds()); it.hasNext(); it.next()) {

		Visual *pChild = it.current();
		eosAssert(pChild != nullptr);

		if (pChild->isVisible()) {

			const Size &childSize = pChild->getDesiredSize();

			pChild->arrange(Rect(Point(childX, childY), childSize));

			if (isHorizontal)
				childX += childSize.getWidth();
			else
				childY += childSize.getHeight();
		}
	}

	return finalSize;
}

/// ----------------------------------------------------------------------
/// \brief Asigna l'orientacio del panell.
/// \param orientation: El valor de la propietat.
///
void StackPanel::setOrientation(
	Orientation orientation) {

	if (this->orientation != orientation) {
		this->orientation = orientation;
		invalidate();
	}
}
