module;


#include "eos.h"
#include "eosAssert.h"


export module Eos.System.Graphics.Size;


import Eos.Math;


export namespace eos {

	/// \brief Clase que representa un tamany
    ///
	class Size {
		private:
			int16_t _width;
			int16_t _height;

		public:
			static constexpr int16_t absoluteMaxWidth = Math::maxU16;
            static constexpr int16_t absoluteMaxHeight = Math::maxU16;
            static constexpr int16_t absoluteMinWidth = 0;
            static constexpr int16_t absoluteMinHeight = 0;

		public:
			Size();
			Size(int16_t width, int16_t height);
			Size(const Size &s);
			Size(const Size &&s);

			/// \brief Obte l'amplada.
			inline int16_t getWidth() const { return _width; }

			/// \brief Obte l'alçada.
			inline int16_t getHeight() const { return _height; }

			[[nodiscard]] Size inflated(int16_t h, int16_t v) const;
			[[nodiscard]] Size inflated(int16_t left, int16_t top, int16_t right, int16_t bottom) const;
			[[nodiscard]] Size constrained(const Size &s) const;

			[[nodiscard]] bool isEmpty() const;

			Size& operator = (const Size &s);

			bool operator == (const Size &s) const;
            inline bool operator != (const Size &s) const { return !(*this == s); }
	};
}


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte. Crea un objecte de tamany zero.
///
eos::Size::Size():

	_width {0},
	_height {0} {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    width: L'amplada.
/// \param    height: L'alçada.
///
eos::Size::Size(
	int16_t width,
	int16_t height):

	_width {width},
	_height {height} {

	eosAssert(width >= 0);
	eosAssert(height >= 0);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copy.
/// \param    s: L'objecte a copiar.
///
eos::Size::Size(
	const Size &s):

	_width {s._width},
	_height {s._height} {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor move.
/// \param    s: L'objecte a copiar.
///
eos::Size::Size(
	const Size &&s):

	_width {s._width},
	_height {s._height} {
}


/// ----------------------------------------------------------------------
/// \brief    Retorna un objecte inflat.
/// \param    h: Inflat en horitzontal.
/// \param    v: Inflat en vertical
/// \return   El nou objecte.
/// \remarks  El increment tant en amplada com en alçada pot ser negatiu.
///
eos::Size eos::Size::inflated(
	int16_t h,
	int16_t v) const {

	return Size(
		Math::max(0, _width + h),
		Math::max(0, _height + v));
}


/// ----------------------------------------------------------------------
/// \brief    Retorna un objecte inflat.
/// \param    left: Inflat per l'esquerra.
/// \param    top: Inflat per dalt.
/// \param    right: Inflat per la dreta.
/// \param    bottom: Inflat per avall.
///
eos::Size eos::Size::inflated(
	int16_t left,
	int16_t top,
	int16_t right,
	int16_t bottom) const {

	return Size(
		Math::max(0, _width + left + right),
		Math::max(0, _height + top + bottom));
}


/// ----------------------------------------------------------------------
/// \brief    Retorna un tamany limitat.
/// \param    s: El tamany limit.
///
eos::Size eos::Size::constrained(
	const Size &s) const {

	return Size(
		Math::min(_width, s._width),
		Math::min(_height, s._height));
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el tamany es zero.
/// \return   True si es zero.
///
bool eos::Size::isEmpty() const {

	return (_width == 0) && (_height == 0);
}


/// ----------------------------------------------------------------------
/// \brief    Operador =
/// \param    s: L'objecte a asignar.
/// \return   Referencia al propi objecte.
///
eos::Size& eos::Size::operator = (
	const Size &s) {

	_width = s._width;
	_height = s._height;

	return *this;
}

/// ----------------------------------------------------------------------
/// \brief    Operador ==
/// \param    s: Objecte a comparar.
/// \return   True si son iguals.
///
bool eos::Size::operator == (
	const Size &s) const {

	return (_width == s._width) && (_height == s._height);
}
