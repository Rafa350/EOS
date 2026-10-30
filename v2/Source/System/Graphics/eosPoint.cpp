export module Eos.System.Graphics.Point;


import Eos.Math;
import Eos.Types;


export namespace eos {

	/// @brief Clase que representa un punt.
	///
	class Point {
		private:
			Int16 _x;
			Int16 _y;

		public:
			static constexpr Int16 absoluteMaxX = Math::maxI16;
            static constexpr Int16 absoluteMaxY = Math::maxI16;
            static constexpr Int16 absoluteMinX = Math::minI16;
            static constexpr Int16 absoluteMinY = Math::minI16;

        public:
			constexpr Point(): _x {0}, _y {0} {}
            constexpr Point(Int16 x, Int16 y): _x {x}, _y {y} {}
            Point(const Point &p);
            Point(const Point &&p);

            inline Int16 getX() const { return _x; }
            inline Int16 getY() const { return _y; }

            Point& translate(Int16 dx, Int16 dy);
            Point& translate(const Point &d);
            [[nodiscard]] Point translated(Int16 dx, Int16 dy) const;
            [[nodiscard]] Point translated(const Point &p) const;

            Point& operator = (const Point &p);

            bool operator == (const Point &p) const;
            inline bool operator != (const Point &p) const { return !(*this == p); }
	};
}


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor copy.
/// @param    p: El objecte a copiar.
///
Point::Point(
	const Point &p):

	_x {p._x},
	_y {p._y} {
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor move.
/// @param    p: L'objecte a moure.
///
Point::Point(
	const Point&& p) :

	_x {p._x},
	_y {p._y} {

}


/// ---------------------------------------------------------------------------
/// @brief    Desplaça el punt.
/// @param    dx: Desplaçament x.
/// @param    dy: Desplaçament y.
/// @return   Referencia al propi objecte.
///
Point& Point::translate(
	Int16 dx,
	Int16 dy) {

	_x += dx;
	_y += dy;

	return *this;
}


/// ---------------------------------------------------------------------------
/// @brief    Desplaça el punt.
/// @param    p: El vector de desplaçament.
/// @return   Referencia al propi objecte.
///
Point& Point::translate(
	const Point & p) {

	_x += p._x;
	_y += p._y;

	return *this;
}


/// ---------------------------------------------------------------------------
/// @brief    Obte un punt despla�at.
/// @param    dx: Increment X.
/// @param    dy: Increment Y.
/// @return   El punt despla�at.
///
Point Point::translated(
	Int16 dx,
	Int16 dy) const {

	return Point(_x + dx, _y + dy);
}


/// ---------------------------------------------------------------------------
/// @brief    Obte un punt despla�at.
/// @param    d: Increment.
/// @return   El punt despla�at.
///
Point Point::translated(
	const Point &d) const {

	return Point(_x + d._x, _y + d._y);
}


/// ---------------------------------------------------------------------------
/// @brief    Operador =
/// @param    p: L'objecte a asignar.
/// @return   Referencioa al propi objecte.
///
Point& Point::operator = (
	const Point &p) {

	_x = p._x;
	_y = p._y;

	return *this;
}


/// ---------------------------------------------------------------------------
/// @brief    Operador ==
/// @param    p: Objecte a comparar.
/// @return   True si son iguals.
///
bool Point::operator == (
	const Point &p) const {

	return (_x == p._x) && (_y == p._y);
}
