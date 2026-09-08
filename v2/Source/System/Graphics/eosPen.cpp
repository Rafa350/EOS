module;


#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"


export module Eos.System.Graphics.Pen;


export namespace eos {

	class Pen final {
		public:
			enum class Style {
				null,
				solid
			};

			enum class CapStyle {

			};

			enum class JoinStyle {

			};

		private:
			Style _style;
			Color _color;
			int16_t _thickness;

		public:
			Pen();
			Pen(Color color, int thickness);
			Pen(const Pen &pen);

			Pen& operator = (const Pen &pen);
			bool operator == (const Pen &pen) const;
			inline bool operator != (const Pen &pen) const { return !(*this == pen); }

			inline Color getColor() const { return _color; }
			inline int16_t getThickness() const { return _thickness; }
			inline Style getStyle() const { return _style; }

			inline bool isNull() const { return _style == Style::null; }
	};
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
eos::Pen::Pen() :

	_style(Style::null),
	_color(Colors::transparent),
	_thickness(0) {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    color: El color de linia.
/// \param    thickness: Amplada de linia.
///
eos::Pen::Pen(
	Color color,
	int thickness):

	_style(Style::solid),
	_color(color),
	_thickness(thickness) {

	eosAssert(thickness >= 0);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de copia.
/// \param    pen: L'objecte a copiar.
///
eos::Pen::Pen(
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
eos::Pen& eos::Pen::operator = (
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
bool eos::Pen::operator == (
	const Pen &pen) const {

	return
		(_style == pen._style) &&
		(_color == pen._color) &&
		(_thickness == pen._thickness);
}
