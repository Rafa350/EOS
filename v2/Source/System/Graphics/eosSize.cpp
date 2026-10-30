export module Eos.System.Graphics.Size;

import Eos.Math;
import Eos.Types;


export namespace eos {

	/// @brief Clase que representa un tamany
    ///
	class Size {
		private:
			Int16 _width;
			Int16 _height;

		public:
			static constexpr Int16 absoluteMaxWidth = Math::maxU16;
            static constexpr Int16 absoluteMaxHeight = Math::maxU16;
            static constexpr Int16 absoluteMinWidth = 0;
            static constexpr Int16 absoluteMinHeight = 0;

		public:
			Size();
			Size(Int16 width, Int16 height);
			Size(const Size &s);
			Size(const Size &&s);

			/// @brief Obte l'amplada.
			inline Int16 getWidth() const { return _width; }

			/// @brief Obte l'alçada.
			inline Int16 getHeight() const { return _height; }

			[[nodiscard]] Size inflated(Int16 h, Int16 v) const;
			[[nodiscard]] Size inflated(Int16 left, Int16 top, Int16 right, Int16 bottom) const;
			[[nodiscard]] Size constrained(const Size &s) const;

			[[nodiscard]] bool isEmpty() const;

			Size& operator = (const Size &s);

			bool operator == (const Size &s) const;
            inline bool operator != (const Size &s) const { return !(*this == s); }
	};
}


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor del objecte. Crea un objecte de tamany zero.
///
Size::Size():

	_width {0},
	_height {0} {
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor del objecte.
/// @param    width: L'amplada.
/// @param    height: L'alçada.
///
Size::Size(
	Int16 width,
	Int16 height):

	_width {width},
	_height {height} {
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor copy.
/// @param    s: L'objecte a copiar.
///
Size::Size(
	const Size &s):

	_width {s._width},
	_height {s._height} {
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor move.
/// @param    s: L'objecte a copiar.
///
Size::Size(
	const Size &&s):

	_width {s._width},
	_height {s._height} {
}


/// ---------------------------------------------------------------------------
/// @brief    Retorna un objecte inflat.
/// @param    h: Inflat en horitzontal.
/// @param    v: Inflat en vertical
/// @return   El nou objecte.
/// \remarks  El increment tant en amplada com en alçada pot ser negatiu.
///
Size eos::Size::inflated(
	Int16 h,
	Int16 v) const {

	return Size(
		Math::max(0, _width + h),
		Math::max(0, _height + v));
}


/// ---------------------------------------------------------------------------
/// @brief    Retorna un objecte inflat.
/// @param    left: Inflat per l'esquerra.
/// @param    top: Inflat per dalt.
/// @param    right: Inflat per la dreta.
/// @param    bottom: Inflat per avall.
///
Size eos::Size::inflated(
	Int16 left,
	Int16 top,
	Int16 right,
	Int16 bottom) const {

	return Size(
		Math::max(0, _width + left + right),
		Math::max(0, _height + top + bottom));
}


/// ---------------------------------------------------------------------------
/// @brief    Retorna un tamany limitat.
/// @param    s: El tamany limit.
///
Size eos::Size::constrained(
	const Size &s) const {

	return Size(
		Math::min(_width, s._width),
		Math::min(_height, s._height));
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si el tamany es zero.
/// @return   True si es zero.
///
bool Size::isEmpty() const {

	return (_width == 0) && (_height == 0);
}


/// ---------------------------------------------------------------------------
/// @brief    Operador =
/// @param    s: L'objecte a asignar.
/// @return   Referencia al propi objecte.
///
Size& Size::operator = (
	const Size &s) {

	_width = s._width;
	_height = s._height;

	return *this;
}

/// ---------------------------------------------------------------------------
/// @brief    Operador ==
/// @param    s: Objecte a comparar.
/// @return   True si son iguals.
///
bool Size::operator == (
	const Size &s) const {

	return (_width == s._width) && (_height == s._height);
}
