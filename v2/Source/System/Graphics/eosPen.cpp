#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosPoolAllocator.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosPen.h"


using namespace eos;


/// \brief Estructura que representa les dades internes del Pen
//
class Pen::Impl: public PoolAllocatable<Pen::Impl, eosGraphics_MaxPens> {
	private:
		PenStyle _style;
		Color _color;
		int _thickness;

	public:
		/// \brief Constructor.
		/// \param style: L'estil.
		/// \param color: El color.
		/// \param thickness: L'amplada de linmia.
		///
		Impl(PenStyle style, Color color, int thickness):
			_style(style),
			_color(color),
			_thickness(thickness) {
		}

		/// \brief Destructor.
		///
		~Impl() {
		}

		/// \brief Operador ==
		/// \param other: L'altre objecte per comparar.
		/// \return True si son iguals.
		///
		bool operator == (const Impl& other) const {
			return
				(_style == other._style) &&
				(_color == other._color) &&
				(_thickness == other._thickness);
		}

		/// \brief Operador !=
		/// \param other: L'altre objecte per comparar.
		/// \return True si son diferents.
		///
		inline bool operator != (const Impl& other) const {
			return !(*this == other);
		}

		/// \brief Obte l'estil.
		/// \return El valor de l'estil.
		///
		inline PenStyle getStyle() const {
			return _style;
		}

		/// \brief Obte el color.
		/// \return El valor del color.
		///
		inline Color getColor() const {
			return _color;
		}

		/// \brief Obte l'amplada de linia.
		/// \return El valor de l'amplada.
		///
		inline int getThickness() const {
			return _thickness;
		}
};


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Pen::Pen() :

	_impl(makeImpl(PenStyle::null, COLOR_Transparent, 1)) {
}



/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    style: Estil.
/// \param    color: El color de linia.
/// \param    thickness: Amplada de linia.
///
Pen::Pen(
	PenStyle style,
	Color color,
	int thickness):

	_impl(makeImpl(style, color, thickness)) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de copia.
/// \param    pen: L'objecte a copiar.
///
Pen::Pen(
	const Pen &pen) :

	_impl(pen._impl) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor
///
Pen::~Pen() {

}


/// ----------------------------------------------------------------------
/// \brief    Operador d'asignacio.
/// \param    pen L'objecte a asignar.
/// \return   El propi objecte.
///
Pen& Pen::operator = (
	const Pen& pen) {

	_impl = pen._impl;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operator ==
/// \param    pen: L'operand.
/// \return   True si son iguals.
///
bool Pen::operator == (
	const Pen& pen) const {

	return *_impl == *pen._impl;
}


/// ----------------------------------------------------------------------
/// \brief    Crea l'estructura interna de dades.
/// \param    style: L'estil.
/// \param    color: El color.
/// \param    thickness: Amplada de linia.
/// \return   El resultat.
///
Pen::ImplPtr Pen::makeImpl(
	PenStyle style,
	Color color,
	int thickness) {

	return ImplPtr(new Impl(style, color, thickness));
}


/// ----------------------------------------------------------------------
/// \brief    Obte el color.
/// \return   El valor obtingut.
///
Color Pen::getColor() const {

	return _impl->getColor();
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'amplada de linia.
/// \return   El valor obtingut.
///
int Pen::getThickness() const {

	return _impl->getThickness();
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estil.
/// \return   El valor obtingut.
///
PenStyle Pen::getStyle() const {

	return _impl->getStyle();
}


/// ----------------------------------------------------------------------
/// \brief    Indica si es nul.
/// \return   True si es nul.
///
bool Pen::isNull() const {

	return _impl->getStyle() == PenStyle::null;
}
