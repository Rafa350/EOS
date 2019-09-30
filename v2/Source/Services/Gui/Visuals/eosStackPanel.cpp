#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosStackPanel.h"
#include "System/eosMath.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
StackPanel::StackPanel():
	orientation(Orientation::vertical) {

}


/// ----------------------------------------------------------------------
/// \brief    Calcula les measures del panell i dels seus fills
/// \param    availableSize: Tamany maxim disponible.
/// \return   El tamany desitjat.
///
Size StackPanel::measureOverride(
	const Size &availableSize) const {

	bool isHorizontal = orientation == Orientation::horitzontal;

	Size childAvailableSize(
	    isHorizontal ? INT32_MAX : availableSize.getWidth(),
	    isHorizontal ? availableSize.getHeight() : INT32_MAX);

	int width = 0;
	int height = 0;

	for (VisualListIterator it(getChilds()); it.hasNext(); it.next()) {

		Visual *pChild = it.current();
		eosAssert(pChild != nullptr);

		if (pChild->isVisible()) {

			pChild->measure(childAvailableSize);
			const Size& childDesiredSize = pChild->getDesiredSize();
			int childDesiredWidth = childDesiredSize.getWidth();
			int childDesiredHeight = childDesitedSize.getHeight();

			if (isHorizontal) {
				width += childDesiredWidth;
				height = Math::max(height, childDesiredHeight);
			}
			else {
				width = Math::max(width, chilDesiredWidth);
				height += childDesiredHeight;
			}
		}
	}

	return Size(width, height);
}


/// ----------------------------------------------------------------------
/// \brief    Ajusta el tamany del panell i dels seus fills.
/// \param    finalSize: El tamany final a asignar.
/// \return   El tamany final obtingut.
///
Size StackPanel::arrangeOverride(
	const Size &finalSize) const {

	bool isHorizontal = orientation == Orientation::horitzontal;

	int childX = 0;
	int childY = 0;
    int childWidth = finalRect.getWidth();
    int childHeight = finalRect.getHeight();

	for (VisualListIterator it(getChilds()); it.hasNext(); it.next()) {

		Visual *pChild = it.current();
		eosAssert(pChild != nullptr);

		if (pChild->isVisible()) {

			const Size &childSize = pChild->getDesiredSize();
            if (isHorizontal)
                childWidth = childSize.getWidth();
            else
                childHeight = childSize.getHeight();
            
			pChild->arrange(Rect(childX, childY, childWidth, childHeight));

			if (isHorizontal)
				childX += chilWidth;
			else
				childY += childHeight;
		}
	}

	return finalSize;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'orientacio del panell.
/// \param    orientation: El valor de la propietat.
///
void StackPanel::setOrientation(
	Orientation orientation) {

	if (this->orientation != orientation) {
		this->orientation = orientation;
		invalidate();
	}
}
