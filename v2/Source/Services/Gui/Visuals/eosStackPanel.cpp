#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosStackPanel.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
///
StackPanel::StackPanel():
	orientation(Orientation::vertical),
	desiredSize(0, 0) {

}


void StackPanel::measure(
	const Size &availableSize) {

	int width = 0;
	int height = 0;
	for (ListIterator<Visual*> it(getChilds()); it.hasNext(); it.next()) {
		Visual *pChild = it.current();
		eosAssert(pChild != nullptr);
		if (pChild->isVisible()) {

		}
	}

	desiredSize = Size(width, height);
}


void StackPanel::setOrientation(
	Orientation orientation) {

	if (this->orientation != orientation) {
		this->orientation = orientation;
		invalidate();
	}
}

