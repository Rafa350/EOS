module;


#include "eos.h"
#include "eosAssert.h"


export module Eos.System.Graphics.Brush;


import Eos.System.Graphics.Color;
import Eos.System.Graphics.ColorDefinitions;


export namespace eos {

	class Brush final {
		public:
			enum class Style {
				null,
				solid,
				linearGradient,
				radialGradient
			};

		private:
			Style _style;
			Color _color;

		public:
			Brush();
			Brush(Color color);
			Brush(const Brush &brush);

			Brush& operator = (const Brush &brush);
			bool operator == (const Brush &brush) const;
			inline bool operator != (const Brush &brush) const { return !(*this == brush); }

			inline Color getColor() const { return _color; }
			inline Style getStyle() const { return _style; }

			inline bool isNull() const { return _style == Style::null; }
	};
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
eos::Brush::Brush() :
	_style(Style::null),
	_color(Colors::transparent) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    color: El color.
///
eos::Brush::Brush(
	Color color):

	_style(Style::solid),
	_color(color) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de copia.
/// \param    brush: L'objecte a copiar.
///
eos::Brush::Brush(
	const Brush &brush) :

	_style(brush._style),
	_color(brush._color) {
}


/// ----------------------------------------------------------------------
/// \brief    Operador d'asignacio.
/// \param    brush: L'objecte a asignar.
/// \return   El propi objecte.
///
eos::Brush& eos::Brush::operator = (
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
bool eos::Brush::operator == (
	const Brush &brush) const {

	return
		(_style == brush._style) &&
		(_color == brush._color);
}
