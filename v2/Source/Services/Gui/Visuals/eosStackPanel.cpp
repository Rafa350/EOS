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
/// \brief Calcula les mesures del control
/// \param availableSize: Tamany disponible.
/// \return El tamany requerit.
///
Size StackPanel::measureOverride(
	const Size &availableSize) const {

	int contentWidth = 0;
	int contentHeight = 0;
	for (ListIterator<Visual*> it(getChilds()); it.hasNext(); it.next()) {
		Visual *pChild = it.current();
		eosAssert(pChild != nullptr);
		if (pChild->isVisible()) {

			pChild->measure(availableSize);
			const Size& childSize = pChild->getDesiredSize();

			if (orientation == Orientation::horitzontal) {
				contentWidth += childSize.getWidth();
				contentHeight = Math::max(contentHeight, childSize.getHeight());
			}
			else {
				contentWidth = Math::max(contentWidth, childSize.getWidth());
				contentHeight += childSize.getHeight();
			}
		}
	}

	const Size& size = getSize();
	return Size(Math::max(size.getWidth(), contentWidth), Math::max(size.getHeight(), contentHeight));
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
