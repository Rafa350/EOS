#include "eos.h"
#include "eosAssert.h"
#include "System/eosString.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosFont.h"
#include "Controllers/Display/eosDisplayDriver.h"

#include <cmath>


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Selecciona la regio de retall.
/// \param    x1: Coordinada X esquerra.
/// \param    y1: Coodinada Y superior.
/// \param    x2: Coordinada X dreta.
/// \param    y2: Coordinada Y inferior.
/// \remarks  Utilitza les coordinades fisiques.
///
void Graphics::setClip(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2) {

	// Normalitzacio de coordinades
	//
    if (x1 > x2)
        std::swap(x1, x2);
    if (y1 > y2)
        std::swap(y1, y2);

    // Asigna la nova area de retall
    //
	_state.clipX1 = std::max((typeof(x1))0, x1);
	_state.clipY1 = std::max((typeof(y1))0, y1);
	_state.clipX2 = std::min(x2, _driver->getMaxX());
	_state.clipY2 = std::min(y2, _driver->getMaxY());
}


/// ----------------------------------------------------------------------
/// \brief    Elimina l'area de retall.
///
void Graphics::resetClip() {

	_state.clipX1 = 0;
	_state.clipY1 = 0;
	_state.clipX2 = _driver->getMaxX();
	_state.clipY2 = _driver->getMaxY();
}


/// ----------------------------------------------------------------------
/// \brief    Retalla un punt.
/// \param    x: Coordinada X del punt.
/// \param    y: Coordinada Y del punt.
/// \return   True si es visible.
///
bool Graphics::clipPoint(
    int16_t x,
    int16_t y) const {

	return
    	(x >= _state.clipX1) && (x <= _state.clipX2) &&
    	(y >= _state.clipY1) && (y <= _state.clipY2);
}


/// ----------------------------------------------------------------------
/// \brief    Retalla una linia horitzontal.
/// \param    x1: Coordinada X del primer punt.
/// \param    x2: Coordinada X del segon punt.
/// \param    y: Coordinada Y comu ambdos punts.
/// \return   True si es visible.
///
bool Graphics::clipHLine(
	int16_t &x1,
	int16_t &x2,
	int16_t y) const {

	// Descarta si es fora de l'area de visualitzacio
	//
	if ((y < _state.clipY1) || (y > _state.clipY2))
		return false;

	// Normalitza les coordinades
	//
	if (x1 > x2)
		std::swap(x1, x2);

	// Ajusta els punts d'interseccio
	//
	x1 = std::max(_state.clipX1, x1);
	x2 = std::min(x2, _state.clipX2);

	return x1 <= x2;
}


/// ----------------------------------------------------------------------
/// \brief    Retalla una linia vertical.
/// \param    x: Coordinada X comu ambdos punts.
/// \param    y1: Coordinada Y del primer punt.
/// \param    y2: Coordinada Y del segon punt.
/// \return   True si es visible.
///
bool Graphics::clipVLine(
	int16_t x,
	int16_t &y1,
	int16_t &y2) const {

	// Descarta si es fora de l'area de visualitzacio
	//
	if ((x < _state.clipX1) || (x > _state.clipX2))
		return false;

	// Normalitza les coordinades
	//
	if (y1 > y2)
		std::swap(y1, y2);

	// Ajusta els punts d'interseccio
	//
	y1 = std::max(_state.clipY1, y1);
	y2 = std::min(y2, _state.clipY2);

	return y1 <= y2;
}


/// ----------------------------------------------------------------------
/// \brief    Retalla una linia arbitraria. Amb l'algorisme Liang-Barsky.
/// \param    x1: Coordinada X del primer punt.
/// \param    y1: Coordinada Y del primer punt.
/// \param    x2: Coordinada X del segon punt.
/// \param    y2: Coordinada Y del segon punt.
/// \return   True si es visible.
///
bool Graphics::clipLine(
    int16_t &x1,
    int16_t &y1,
    int16_t &x2,
    int16_t &y2) const {

	// La descarta si es fora de l'area de visualitzacio
	//
    if (((x1 < _state.clipX1) && (x2 < _state.clipX1)) ||
        ((x1 > _state.clipX2) && (x2 > _state.clipX2)) ||
        ((y1 < _state.clipY1) && (y2 < _state.clipY1)) ||
        ((y1 > _state.clipY2) && (y2 > _state.clipY2)))
        return false;

    int32_t t1 = 0;
    int32_t t2 = 1 << 16;

    int16_t dx = x2 - x1;
    if (!clipTest(-dx, x1 - _state.clipX1, t1, t2))
        return false;
    if (!clipTest(dx, _state.clipX2 - x1, t1, t2))
        return false;

    int16_t dy = y2 - y1;
    if (!clipTest(-dy, y1 - _state.clipY1, t1, t2))
        return false;
    if (!clipTest(dy, _state.clipY2 - y1, t1, t2))
        return false;

    // Ajusta el punt d'interseccio x2, y2. La  funcio min
    // evita els errors d'arrodoniment.
    //
    if (t2 < (1 << 16)) {
        x2 = std::min(_state.clipX2, (int16_t)(x1 + ((t2 * dx) >> 16)));
        y2 = std::min(_state.clipY2, (int16_t)(y1 + ((t2 * dy) >> 16)));
    }

    // Ajusta el punt d'interseccio x1, y1. La funcio max
    // evita els errors d'errodoniment.
    //
    if (t1 > 0) {
        x1 = std::max(_state.clipX1, (int16_t)(x1 + ((t1 * dx) >> 16)));
        y1 = std::max(_state.clipY1, (int16_t)(y1 + ((t1 * dy) >> 16)));
    }

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Realitza el calcul de visibilitat per la funcio 'clipLine'
/// \param    p: Coordinada X o Y del punt inicial.
/// \param    q: Coordinada X o Y del puint final.
/// \param    t1: Correccio del punt inicial.
/// \param    t2: Correccio del punt final.
/// \return:  True si es visible, false en cas contrari.
///
bool Graphics::clipTest(
    int16_t p,
    int16_t q,
    int32_t &t1,
    int32_t &t2) {

    if (p < 0) {
        if (q < 0) {
            int32_t r = (q << 16) / p;
            if (r > t2)
                return false;
            else if (r > t1)
                t1 = r;
        }
    }

    else if (p > 0) {
        if (q < p) {
            int32_t r = (q << 16) / p;
            if (r < t1)
                return false;
            else if (r < t2)
                t2 = r;
        }
    }

    else if (q < 0) {
    	return false;
    }

   	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Retalla un area.
/// \param    x1: Coordinada X del primer punt.
/// \param    y1: Coordinada Y del primer punt.
/// \param    x2: Coordinada X del segon punt.
/// \param    y2: Coordinada Y del segon punt.
/// \return   True si es visible.
///
bool Graphics::clipRectangle(
    int16_t &x1,
    int16_t &y1,
    int16_t &x2,
    int16_t &y2) const {

	// Normalitza les coordinades
	//
	if (x1 > x2)
		std::swap(x1, x2);
	if (y1 > y2)
		std::swap(y1, y2);

	// Calcula la interseccio
	//
	x1 = std::max(x1, _state.clipX1);
	y1 = std::max(y1, _state.clipY1);
	x2 = std::min(x2, _state.clipX2);
	y2 = std::min(y2, _state.clipY2);

	return (x1 <= x2) && (y1 <= y2);
}
