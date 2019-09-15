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
///
Size StackPanel::measureCore(
	const Size &availableSize) const {

	int width = 0;
	int height = 0;
	for (ListIterator<Visual*> it(getChilds()); it.hasNext(); it.next()) {
		Visual *pChild = it.current();
		eosAssert(pChild != nullptr);
		if (pChild->isVisible()) {

			pChild->measure(availableSize);
			const Size& childSize = pChild->getDesiredSize();

			if (orientation == Orientation::horitzontal)
				height = Math::max(height, childSize.getHeight());
			else
				width = Math::max(width, childSize.getWidth());

		}
	}

	return Size(width, height);
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
