#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosScreen.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosSize.h"
#include "System/Graphics/eosColorDefinitions.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
///
Screen::Screen() {

	setBackground(RGB(0x50, 0x50, 0x50));
	setSize(Size(DISPLAY_WIDTH, DISPLAY_HEIGHT));
}


/// ----------------------------------------------------------------------
/// \brief    Calcula la mida del visual i dels seus fills.
/// \param    availableSize: Indica el tamany disponible.
/// \return   El tamany requerit.
/// \remarks  En aquest cas sempre retorna el tamany disponible.
///
Size Screen::measureOverride(
	const Size& availableSize) const {

	if (isVisible()) {
		Panel::measureOverride(availableSize);
		return availableSize;
	}
	else
		return Size();
}
