#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosStackPanel.h"

#include <cmath>


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
StackPanel::StackPanel():
	_orientation(Orientation::vertical) {

}


/// ----------------------------------------------------------------------
/// \brief    Calcula les measures del panell i dels seus fills
/// \param    availableSize: Tamany maxim disponible.
/// \return   El tamany desitjat.
///
Size StackPanel::measureOverride(
	const Size& availableSize) const {

	bool isHorizontal = _orientation == Orientation::horizontal;

	Size childAvailableSize(
	    isHorizontal ? Size::absoluteMaxWidth : availableSize.getWidth(),
	    isHorizontal ? availableSize.getHeight() : Size::absoluteMaxHeight);

	int width = 0;
	int height = 0;

	const VisualList &childs = getChilds();
	for (auto it = childs.begin(); it != childs.end(); it++) {

		Visual* child = *it;
		eosAssert(child != nullptr);

		if (child->isVisible()) {

			child->measure(childAvailableSize);
			const Size& childDesiredSize = child->getDesiredSize();
			int childDesiredWidth = childDesiredSize.getWidth();
			int childDesiredHeight = childDesiredSize.getHeight();

			if (isHorizontal) {
				width += childDesiredWidth;
				height = std::max(height, childDesiredHeight);
			}
			else {
				width = std::max(width, childDesiredWidth);
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
	const Size& finalSize) const {

	bool isHorizontal = _orientation == Orientation::horizontal;

	int childX = 0;
	int childY = 0;
    int childWidth = finalSize.getWidth();
    int childHeight = finalSize.getHeight();

    const VisualList& childs = getChilds();
	for (auto it = childs.begin(); it != childs.end(); it++) {

		Visual* child = *it;
		eosAssert(child != nullptr);

		if (child->isVisible()) {

			const Size &childSize = child->getDesiredSize();
            if (isHorizontal)
                childWidth = childSize.getWidth();
            else
                childHeight = childSize.getHeight();
            
			child->arrange(Rect(childX, childY, childWidth, childHeight));

			if (isHorizontal)
				childX += childWidth;
			else
				childY += childHeight;
		}
	}

	return finalSize;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'orientacio del panell.
/// \param    value: El valor de la propietat.
///
void StackPanel::setOrientation(
	Orientation value) {

	if (_orientation != value) {
		_orientation = value;
		invalidate();
	}
}
