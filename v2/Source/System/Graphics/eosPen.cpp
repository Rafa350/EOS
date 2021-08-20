#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosPoolAllocator.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosPen.h"


using namespace eos;


#ifdef EOS_DEBUG
static int __allocatedPenCount = 0;
static int __allocatedPenImplCount = 0;
#endif


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
#ifdef EOS_DEBUG
			__allocatedPenImplCount++;
#endif
		}

		/// \brief Destructor.
		///
		~Impl() {
#ifdef EOS_DEBUG
			__allocatedPenImplCount--;
#endif
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
	_impl(makeImpl(PenStyle::solid, COLOR_Transparent, 0)) {
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

#ifdef EOS_DEBUG
	__allocatedPenCount++;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de copia.
/// \param    pen: L'objecte a copiar.
///
Pen::Pen(
	const Pen& pen) :

	_impl(pen._impl) {

#ifdef EOS_DEBUG
	__allocatedPenCount++;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Destructor
///
Pen::~Pen() {

	auto& cache = ImplPtrCache::instance();

	if (_impl.uses() < 2) {
		for (int index = 0; index < cache.getSize(); index++) {
			if (cache[index] == _impl) {
				cache.removeAt(index);
				break;
			}
		}
	}

#ifdef EOS_DEBUG
	__allocatedPenCount--;
#endif
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

	auto& cache = ImplPtrCache::instance();

	// Si ja esta en el cache, el reutilitza.
	//
	for (auto it = cache.begin(); it != cache.end(); it++) {
		ImplPtr impl = *it;
		if ((impl->getStyle() == style) &&
			(impl->getColor() == color) &&
			(impl->getThickness() == thickness))
			return impl;
	}

	// Si no el troba, en crea un de nou
	//
	ImplPtr impl(new Impl(style, color, thickness));
	cache.pushBack(impl);
	return impl;
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

	return _impl->getColor().isTransparent();
}
