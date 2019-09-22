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

	int measuredWidth = 0;
	int measuredHeight = 0;

	bool isHorizontal = orientation == Orientation::horitzontal;

	Size childAvailableSize;
	if (isHorizontal)
		childAvailableSize = Size(INT32_MAX, availableSize.getHeight());
	else
		childAvailableSize = Size(availableSize.getWidth(), INT32_MAX);

	for (VisualListIterator it(getChilds()); it.hasNext(); it.next()) {
		Visual *pChild = it.current();
		eosAssert(pChild != nullptr);

		pChild->measure(childAvailableSize);
		const Size& childSize = pChild->getDesiredSize();

		if (isHorizontal) {
			measuredWidth += childSize.getWidth();
			measuredHeight = Math::max(measuredHeight, childSize.getHeight());
		}
		else {
			measuredWidth = Math::max(measuredWidth, childSize.getWidth());
			measuredHeight += childSize.getHeight();
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
	int childWidth = finalSize.getWidth();
	int childHeight = finalSize.getHeight();

	bool isHorizontal = orientation == Orientation::horitzontal;

	for (VisualListIterator it(getChilds()); it.hasNext(); it.next()) {
		Visual *pChild = it.current();
		eosAssert(pChild != nullptr);

		if (pChild->isVisible()) {

			if (isHorizontal)
				childWidth = pChild->getDesiredSize().getWidth();
			else
				childHeight = pChild->getDesiredSize().getHeight();

			pChild->arrange(Rect(childX, childY, childWidth, childHeight));

			if (isHorizontal)
				childX += childWidth;
			else
				childY += childHeight;
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
