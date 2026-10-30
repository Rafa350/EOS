export module Eos.System.Graphics.Rect;

import Eos.Math;
import Eos.System.Graphics.Point;
import Eos.System.Graphics.Size;
import Eos.Types;


export namespace eos {

    /// @brief Clase que representa un rectangle aliniat amb els eixos.
    ///
	class Rect {
		private:
			Int16 _x;
			Int16 _y;
			Int16 _width;
			Int16 _height;

		public:
			static constexpr Int16 absoluteMaxWidth = Math::maxI16;
            static constexpr Int16 absoluteMaxHeight = Math::maxI16;
            static constexpr Int16 absoluteMinWidth = 0;
            static constexpr Int16 absoluteMinHeight = 0;

        public:
			Rect();
            Rect(Int16 x, Int16 y, Int16 width, Int16 height);
            Rect(const Point &p1, const Point &p2);
            Rect(const Point &p, const Size &s);
            Rect(const Size &s);
            Rect(const Rect &r);
            Rect(const Rect &&r);

            inline Int16 getX() const { return _x; }
            inline Int16 getY() const { return _y; }
            inline Point getPosition() const { return Point(_x, _y); }
            inline Int16 getWidth() const { return _width; }
            inline Int16 getHeight() const { return _height; }
            inline Size getSize() const { return Size(_width, _height); }
            inline Int16 getMinX() const { return _x; };
            inline Int16 getMinY() const { return _y; }
            inline Int16 getMaxX() const { return _x + _width - 1; }
            inline Int16 getMaxY() const { return _y + _height - 1; }

            [[nodiscard]] Rect translated(Int16 x, Int16 y) const;
            [[nodiscard]] inline Rect translated(const Point &p) const { return translated(p.getX(), p.getY()); }
            [[nodiscard]] inline Rect inflated(Int16 i) const { return inflated(i, i, i, i); }
            [[nodiscard]] inline Rect inflated(Int16 h, Int16 v) const { return inflated(h, v, h, v); }
            [[nodiscard]] Rect inflated(Int16 left, Int16 top, Int16 right, Int16 bottom) const;
            [[nodiscard]] Rect intersected(const Rect &r) const;
            [[nodiscard]] Rect fusioned(const Rect &r) const;

            [[nodiscard]] bool contains(Int16 x, Int16 y) const;
            [[nodiscard]] inline bool contains(const Point &p) const { return contains(p.getX(), p.getY()); }
            [[nodiscard]] bool contains(const Rect &r) const;

            [[nodiscard]] bool isEmpty() const;

            Rect& operator = (const Rect &r);

            bool operator == (const Rect &r) const;
            inline bool operator != (const Rect &r) const { return !(*this == r); }
	};
}


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor de l'objecte. Crea un rectangle buit
///
Rect::Rect():
	_x {0},
	_y {0},
	_width {0},
	_height {0} {
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor de l'objecte.
/// @param    x: Posicio X.
/// @param    y: Posicio Y.
/// @param    width: Amplada.
/// @param    height: Alçada.
///
Rect::Rect(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height):

	_x {x},
	_y {y},
	_width {width},
	_height {height} {
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor de l'objecte.
/// @param    p: Posicio.
/// @param    s: Tamany.
///
Rect::Rect(
	const Point &p,
	const Size &s):

	_x {p.getX()},
	_y {p.getY()},
	_width {s.getWidth()},
	_height{s.getHeight()} {
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor del objecte.
/// @param    s: Tamany.
/// @remarks  La posicio es x=0, y=0.
///
Rect::Rect(
	const Size &s):

	_x {0},
	_y {0},
	_width {s.getWidth()},
	_height{s.getHeight()} {

}


/// ---------------------------------------------------------------------------
/// @brief    Constructor del objecte.
/// @param    p1: Primer punt.
/// @param    p2: Segon punt.
/// @remarks  El rectangle creat, SEMPRE estata normalitzat, independentment
///           dels punt inicials
///
Rect::Rect(
	const Point &p1,
	const Point &p2):

	_x(Math::min(p1.getX(), p2.getX())),
	_y(Math::min(p1.getY(), p2.getY())),
	_width(Math::abs(p2.getX() - p1.getX()) + 1),
	_height(Math::abs(p2.getY() - p1.getY()) + 1) {
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor copy
/// @param    r: L'objecte a copiar.
///
Rect::Rect(
	const Rect &r):

	_x(r._x),
	_y(r._y),
	_width(r._width),
	_height(r._height) {
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor move
/// @param    r: L'objecte a moure.
///
Rect::Rect(
	const Rect &&r) :

	_x(r._x),
	_y(r._y),
	_width(r._width),
	_height(r._height) {

}


/// ---------------------------------------------------------------------------
/// @brief    Infla un rectangle.
/// @param    left: Inflat per l'esquerra.
/// @param    top: Inflat per dalt.
/// @param    right: Inflat per la dreta.
/// @param    bottom: Inflat per avall.
/// @return   El resultat.
///
Rect Rect::inflated(
	Int16 left,
	Int16 top,
	Int16 right,
	Int16 bottom) const {

	return Rect(
		_x - left,
		_y - top,
		Math::max(0, _width + left + right),
		Math::max(0, _height + top + bottom));
}


/// ---------------------------------------------------------------------------
/// @brief    Obte un rectangle desplaçat.
/// @param    x: Desplaçament X.
/// @param    y: Desplaçament Y.
/// @return   El rectangle resultant de l'operacio.
///
Rect Rect::translated(
	Int16 x,
	Int16 y) const {

	return Rect(_x + x, _y + y, _width, _height);
}


/// ---------------------------------------------------------------------------
/// @brief    Obte un rectangle que es la interseccio d'aquest amb un altre.
/// @param    r: Rectangle per realitzar la interseccio.
/// @return   El resultat de la interseccio.
/// @remarks  El resultat SEMPRE sera un rectangle normalitzat.
///
Rect Rect::intersected(
	const Rect &r) const {

	auto x1 = Math::max(_x, r._x);
	auto y1 = Math::max(_y, r._y);
	auto x2 = Math::min(getMaxX(), r.getMaxX());
	auto y2 = Math::min(getMaxY(), r.getMaxY());

	if (x1 > x2)
		Math::swap(x1, x2);
	if (y1 > y2)
		Math::swap(y1, y2);

	if ((x2 < x1) || (y2 < y1))
		return Rect(x1, y1, 0, 0); // Rectangle buit
	else
		return Rect(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si el rectangle conte el punt especificat.
/// @param    x: Coordinada X del punt.
/// @param    y: Coordinada Y del punt.
/// @return   True si conte el punt.
///
bool Rect::contains(
	Int16 x,
	Int16 y) const {

	return
		(x >= _x) && (y >= _y) &&
		(x < _x + _width) && (y < _y + _height);
}


/// ---------------------------------------------------------------------------
/// @brief    Indica si es rectangle es buit.
/// @return   True si es buit.
///
bool Rect::isEmpty() const {

	return (_width == 0) && (_height == 0);
}


/// ---------------------------------------------------------------------------
/// @brief    Operador =
/// @param    r: L'objecte a asignar.
/// @return   Referencia al propi objecte.
///
Rect& Rect::operator = (
	const Rect &r) {

	_x = r._x;
	_y = r._y;
	_width = r._width;
	_height = r._height;

	return *this;
}


/// ---------------------------------------------------------------------------
/// @brief    Operador ==
/// @param    r: L'objecte a comparar.
/// @return   True si son ifguals, false en cas contrari.
///
bool Rect::operator == (
	const Rect &r) const {

	return
		(_x == r._x) &&
		(_y == r._y) &&
		(_width == r._width) &&
		(_height == r._height);
}
