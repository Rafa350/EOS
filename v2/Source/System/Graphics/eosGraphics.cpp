#include "eos.h"
#include "eosAssert.h"
#include "System/eosString.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosFont.h"
#include "Controllers/Display/eosDisplayDriver.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    driver: Driver del display
///
Graphics::Graphics(
    IDisplayDriver *driver) :

    _driver(driver) {

	resetClip();
	resetTransformation();
}


/// ---------------------------------------------------------------------
/// \brief    Destructor.
///
Graphics::~Graphics() {

}


/// ----------------------------------------------------------------------
/// \brief    Asigna la transformacio.
/// \param    t: La transformacio.
/// \param    combine: True si cal combinar la transformacio amb l'actual.
///
void Graphics::setTransformation(
	const Transformation &t,
	bool combine) {

	// Asigna la nova transformacio
	//
	_state.ct = t;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza la transformacio.
///
void Graphics::resetTransformation() {

	_state.ct.identity();
}


/// ----------------------------------------------------------------------
/// \brief    Salva l'estat.
///
void Graphics::push() {

	//if (!stack.isFull())
		_stack.push(_state);
}


/// ----------------------------------------------------------------------
/// \brief    Recupera l'estat.
///
void Graphics::pop() {

	if (!_stack.isEmpty()) {
		_state = _stack.peek();
		_stack.pop();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Borrat de la pantalla al color especificat.
/// \param    color: El color per realitzar el borrat.
///
void Graphics::clear(
    Color color) const {

	int16_t x1 = 0;
	int16_t y1 = 0;
	int16_t x2 = _driver->getMaxX();
	int16_t y2 = _driver->getMaxY();

    if (clipRectangle(x1, y1, x2, y2))
        _driver->setPixels(x1, y1, x2 - x1 + 1, y2 - y1 + 1, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un pixel.
/// \param    x: Coordinada X del punt.
/// \param    y: Coordinada Y del punt.
/// \param    color: Colcor
///
void Graphics::drawPoint(
    int16_t x,
    int16_t y,
	Color color) const {

	// Transforma a coordinades fisiques
	//
	_state.ct.apply(x, y);

    if (clipPoint(x, y))
        _driver->setPixel(x, y, color);
}


/// ----------------------------------------------------------------------
/// \brief    Transforma les coordinades d'un punt.
/// \param    x: Coordinada X del punt.
/// \param    y: Coordinada Y del punt.
///
void Graphics::transform(
	int16_t &x,
	int16_t &y) const {

	_state.ct.apply(x, y);
}
