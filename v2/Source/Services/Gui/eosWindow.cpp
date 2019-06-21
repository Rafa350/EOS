#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosWindow.h"
#include "System/Graphics/eosDisplay.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Asigna la posicio.
/// \param[in] x: Coordinada X de la posicio.
/// \param[in] y: Coordinada Y de la posicio.
///
void Window::setPosition(
	int x,
	int y) {

	if ((this->x != x) || (this->y != y)) {

		this->x = x;
		this->y = y;

		Visual *parent = getParent();
		if (parent)
			parent->invalidate();
		else
			invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el tamany.
/// \param[in] width: Amplada.
/// \param[in] height: Alçada.
///
void Window::setSize(
	int width,
	int height) {

    if ((this->width != width) || (this->height != height)) {

    	this->width = width;
    	this->height = height;

    	Visual *parent = getParent();
		if (parent)
			parent->invalidate();
		else
			invalidate();
    }
}
