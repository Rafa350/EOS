#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosPen.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Pen::Pen() :

	_style(PenStyle::null),
	_color(Colors::transparent),
	_thickness(0) {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    color: El color de linia.
/// \param    thickness: Amplada de linia.
///
Pen::Pen(
	Color color,
	int thickness):

	_style(PenStyle::solid),
	_color(color),
	_thickness(thickness) {

	eosAssert(thickness >= 0);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de copia.
/// \param    pen: L'objecte a copiar.
///
Pen::Pen(
	const Pen &pen):

	_style(pen._style),
	_color(pen._color),
	_thickness(pen._thickness) {

}


/// ----------------------------------------------------------------------
/// \brief    Operador d'asignacio.
/// \param    pen L'objecte a asignar.
/// \return   El propi objecte.
///
Pen& Pen::operator = (
	const Pen &pen) {

	_style = pen._style;
	_color = pen._color;
	_thickness = pen._thickness;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operator ==
/// \param    pen: L'operand.
/// \return   True si son iguals.
///
bool Pen::operator == (
	const Pen &pen) const {

	return
		(_style == pen._style) &&
		(_color == pen._color) &&
		(_thickness == pen._thickness);
}
