module;


#include "eos.h"


export module Eos.System.Graphics.Point;


import Eos.Math;


export namespace eos {

	/// \brief Clase que representa un punt.
	///
	class Point {
		private:
			int16_t _x;
			int16_t _y;

		public:
			static constexpr int16_t absoluteMaxX = Math::maxI16;
            static constexpr int16_t absoluteMaxY = Math::maxI16;
            static constexpr int16_t absoluteMinX = Math::minI16;
            static constexpr int16_t absoluteMinY = Math::minI16;

        public:
			constexpr Point(): _x {0}, _y {0} {}
            constexpr Point(int16_t x, int16_t y): _x {x}, _y {y} {}
            Point(const Point &p);
            Point(const Point &&p);

            inline int16_t getX() const { return _x; }
            inline int16_t getY() const { return _y; }

            Point& translate(int16_t dx, int16_t dy);
            Point& translate(const Point &d);
            [[nodiscard]] Point translated(int16_t dx, int16_t dy) const;
            [[nodiscard]] Point translated(const Point &p) const;

            Point& operator = (const Point &p);

            bool operator == (const Point &p) const;
            inline bool operator != (const Point &p) const { return !(*this == p); }
	};
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copy.
/// \param    p: El objecte a copiar.
///
eos::Point::Point(
	const Point &p):

	_x {p._x},
	_y {p._y} {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor move.
/// \param    p: L'objecte a moure.
///
eos::Point::Point(
	const Point&& p) :

	_x {p._x},
	_y {p._y} {

}


/// ----------------------------------------------------------------------
/// \brief    Desplaça el punt.
/// \param    dx: Desplaçament x.
/// \param    dy: Desplaçament y.
/// \return   Referencia al propi objecte.
///
eos::Point& eos::Point::translate(
	int16_t dx,
	int16_t dy) {

	_x += dx;
	_y += dy;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Desplaça el punt.
/// \param    p: El vector de desplaçament.
/// \return   Referencia al propi objecte.
///
eos::Point& eos::Point::translate(
	const Point & p) {

	_x += p._x;
	_y += p._y;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Obte un punt despla�at.
/// \param    dx: Increment X.
/// \param    dy: Increment Y.
/// \return   El punt despla�at.
///
eos::Point eos::Point::translated(
	int16_t dx,
	int16_t dy) const {

	return Point(_x + dx, _y + dy);
}


/// ----------------------------------------------------------------------
/// \brief    Obte un punt despla�at.
/// \param    d: Increment.
/// \return   El punt despla�at.
///
eos::Point eos::Point::translated(
	const Point &d) const {

	return Point(_x + d._x, _y + d._y);
}


/// ----------------------------------------------------------------------
/// \brief    Operador =
/// \param    p: L'objecte a asignar.
/// \return   Referencioa al propi objecte.
///
eos::Point& eos::Point::operator = (
	const Point &p) {

	_x = p._x;
	_y = p._y;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador ==
/// \param    p: Objecte a comparar.
/// \return   True si son iguals.
///
bool eos::Point::operator == (
	const Point &p) const {

	return (_x == p._x) && (_y == p._y);
}
