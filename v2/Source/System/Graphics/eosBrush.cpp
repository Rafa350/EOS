#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosBrush.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Brush::Brush() :
	_style(Style::null),
	_color(Colors::transparent) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    color: El color.
///
Brush::Brush(
	Color color):

	_style(Style::solid),
	_color(color) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de copia.
/// \param    brush: L'objecte a copiar.
///
Brush::Brush(
	const Brush &brush) :

	_style(brush._style),
	_color(brush._color) {
}


/// ----------------------------------------------------------------------
/// \brief    Operador d'asignacio.
/// \param    brush: L'objecte a asignar.
/// \return   El propi objecte.
///
Brush& Brush::operator = (
	const Brush &brush) {

	_style = brush._style;
	_color = brush._color;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador ==
/// \param    brush: El operand
/// \return   True si son iguals.
///
bool Brush::operator == (
	const Brush &brush) const {

	return
		(_style == brush._style) &&
		(_color == brush._color);
}
