module;


#include "eos.h"
#include "eosAssert.h"


export module Eos.System.Graphics.Rect;


import Eos.Math;
import Eos.System.Graphics.Point;
import Eos.System.Graphics.Size;


export namespace eos {

    /// \brief Clase que representa un rectangle aliniat amb els eixos.
    ///
	class Rect {
		private:
			int16_t _x;
			int16_t _y;
			int16_t _width;
			int16_t _height;

		public:
			static constexpr int16_t absoluteMaxWidth = Math::maxI16;
            static constexpr int16_t absoluteMaxHeight = Math::maxI16;
            static constexpr int16_t absoluteMinWidth = 0;
            static constexpr int16_t absoluteMinHeight = 0;

        public:
			Rect();
            Rect(int16_t x, int16_t y, int16_t width, int16_t height);
            Rect(const Point &p1, const Point &p2);
            Rect(const Point &p, const Size &s);
            Rect(const Size &s);
            Rect(const Rect &r);
            Rect(const Rect &&r);

            inline int16_t getX() const { return _x; }
            inline int16_t getY() const { return _y; }
            inline Point getPosition() const { return Point(_x, _y); }
            inline int16_t getWidth() const { return _width; }
            inline int16_t getHeight() const { return _height; }
            inline Size getSize() const { return Size(_width, _height); }
            inline int16_t getMinX() const { return _x; };
            inline int16_t getMinY() const { return _y; }
            inline int16_t getMaxX() const { return _x + _width - 1; }
            inline int16_t getMaxY() const { return _y + _height - 1; }

            Rect translated(int16_t x, int16_t y) const;
            inline Rect translated(const Point &p) const { return translated(p.getX(), p.getY()); }
            Rect inflated(int16_t h, int16_t v) const { return inflated(h, v, h, v); }
            Rect inflated(int16_t left, int16_t top, int16_t right, int16_t bottom) const;
            Rect intersected(const Rect &r) const;
            Rect fusioned(const Rect &r) const;

            bool contains(int16_t x, int16_t y) const;
            inline bool contains(const Point &p) const { return contains(p.getX(), p.getY()); }
            bool contains(const Rect &r) const;

            bool isEmpty() const;

            Rect& operator = (const Rect &r);

            bool operator == (const Rect &r) const;
            inline bool operator != (const Rect &r) const { return !(*this == r); }
	};
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte. Crea un rectangle buit
///
eos::Rect::Rect():
	_x {0},
	_y {0},
	_width {0},
	_height {0} {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    x: Posicio X.
/// \param    y: Posicio Y.
/// \param    width: Amplada.
/// \param    height: Alçada.
///
eos::Rect::Rect(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height):

	_x {x},
	_y {y},
	_width {width},
	_height {height} {

	eosAssert(width >= 0);
	eosAssert(height >= 0);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    p: Posicio.
/// \param    s: Tamany.
///
eos::Rect::Rect(
	const Point &p,
	const Size &s):

	_x {p.getX()},
	_y {p.getY()},
	_width {s.getWidth()},
	_height{s.getHeight()} {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    s: Tamany.
/// \remarks  La posicio es x=0, y=0.
///
eos::Rect::Rect(
	const Size &s):

	_x {0},
	_y {0},
	_width {s.getWidth()},
	_height{s.getHeight()} {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    p1: Primer punt.
/// \param    p2: Segon punt.
/// \remarks  El rectangle creat, SEMPRE estata normalitzat, independentment
///           dels punt inicials
///
eos::Rect::Rect(
	const Point &p1,
	const Point &p2):

	_x(Math::min(p1.getX(), p2.getX())),
	_y(Math::min(p1.getY(), p2.getY())),
	_width(Math::abs(p2.getX() - p1.getX()) + 1),
	_height(Math::abs(p2.getY() - p1.getY()) + 1) {

	eosAssert(_width >= 0);
	eosAssert(_height >= 0);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copy
/// \param    r: L'objecte a copiar.
///
eos::Rect::Rect(
	const Rect &r):

	_x(r._x),
	_y(r._y),
	_width(r._width),
	_height(r._height) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor move
/// \param    r: L'objecte a moure.
///
eos::Rect::Rect(
	const Rect &&r) :

	_x(r._x),
	_y(r._y),
	_width(r._width),
	_height(r._height) {

}


/// ----------------------------------------------------------------------
/// \brief    Infla un rectangle.
/// \param    left: Inflat per l'esquerra.
/// \param    top: Inflat per dalt.
/// \param    right: Inflat per la dreta.
/// \param    bottom: Inflat per avall.
/// \return   El resultat.
///
eos::Rect eos::Rect::inflated(
	int16_t left,
	int16_t top,
	int16_t right,
	int16_t bottom) const {

	return Rect(
		_x - left,
		_y - top,
		Math::max(0, _width + left + right),
		Math::max(0, _height + top + bottom));
}


/// ----------------------------------------------------------------------
/// \brief    Obte un rectangle desplaçat.
/// \param    x: Desplaçament X.
/// \param    y: Desplaçament Y.
/// \return   El rectangle resultant de l'operacio.
///
eos::Rect eos::Rect::translated(
	int16_t x,
	int16_t y) const {

	return Rect(_x + x, _y + y, _width, _height);
}

/// ----------------------------------------------------------------------
/// \brief    Obte un rectangle que es la interseccio d'aquest amb un altre.
/// \param    r: Rectangle per realitzar la interseccio.
/// \return   El resultat de la interseccio.
/// \remarks  El resultat SEMPRE sera un rectangle normalitzat.
///
eos::Rect eos::Rect::intersected(
	const Rect &r) const {

	int x1 = Math::max(_x, r._x);
	int y1 = Math::max(_y, r._y);
	int x2 = Math::min(getMaxX(), r.getMaxX());
	int y2 = Math::min(getMaxY(), r.getMaxY());

	if (x1 > x2)
		Math::swap(x1, x2);
	if (y1 > y2)
		Math::swap(y1, y2);

	if ((x2 < x1) || (y2 < y1))
		return Rect(x1, y1, 0, 0); // Rectangle buit
	else
		return Rect(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rectangle conte el punt especificat.
/// \param    x: Coordinada X del punt.
/// \param    y: Coordinada Y del punt.
/// \return   True si conte el punt.
///
bool eos::Rect::contains(
	int16_t x,
	int16_t y) const {

	return
		(x >= _x) && (y >= _y) &&
		(x < _x + _width) && (y < _y + _height);
}


/// ----------------------------------------------------------------------
/// \brief    Indica si es rectangle es buit.
/// \return   True si es buit.
///
bool eos::Rect::isEmpty() const {

	return (_width == 0) && (_height == 0);
}


/// ----------------------------------------------------------------------
/// \brief    Operador =
/// \param    r: L'objecte a asignar.
/// \return   Referencia al propi objecte.
///
eos::Rect& eos::Rect::operator = (
	const Rect &r) {

	_x = r._x;
	_y = r._y;
	_width = r._width;
	_height = r._height;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador ==
/// \param    r: L'objecte a comparar.
/// \return   True si son ifguals, false en cas contrari.
///
bool eos::Rect::operator == (
	const Rect &r) const {

	return
		(_x == r._x) &&
		(_y == r._y) &&
		(_width == r._width) &&
		(_height == r._height);
}
