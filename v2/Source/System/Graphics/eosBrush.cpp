#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosPoolAllocator.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosBrush.h"


using namespace eos;


#ifdef EOS_DEBUG
static int __allocatedBrushCount = 0;
static int __allocatedBrushImplCount = 0;
#endif


/// \brief Clase que implementa les dades internes del brush
///
class Brush::Impl: public PoolAllocatable<Brush::Impl, eosGraphics_MaxBrushes> {
	private:
		BrushStyle _style;
		Color _color;

	public:
		/// \brief Constructor del objecte.
		/// \param style: L'estil.
		/// \param color: El color.
		///
		Impl(BrushStyle style, Color color):
			_style(style),
			_color(color) {
#ifdef EOS_DEBUG
			__allocatedBrushImplCount++;
#endif
		}

		/// \brief Destructor.
		///
		~Impl() {
#ifdef EOS_DEBUG
			__allocatedBrushImplCount--;
#endif
		}

		/// \brief Operador ==
		/// \param other: L'altre objecte per comparar.
		/// \return True si son iguals.
		///
		bool operator == (const Impl& other) const {
			return
				(_style == other._style) &&
				(_color == other._color);
		}

		/// \brief Operador !=
		/// \param other: L'altre objecte per comparar.
		/// \return True si son diferents.
		///
		inline bool operator != (const Impl& other) const {
			return !(*this == other);
		}

		/// \brief Obte el estil
		/// \return El valor del estil.
		///
		inline BrushStyle getStyle() const {
			return _style;
		}

		/// \brief Obte el color.
		/// \return El valor del color.
		///
		inline Color getColor() const {
			return _color;
		}
};


Brush::ImplPtrCache Brush::_implCache;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Brush::Brush():
	_impl(makeImpl(BrushStyle::solid, COLOR_Transparent)) {

#ifdef EOS_DEBUG
	__allocatedBrushCount++;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    style: L'estil.
/// \param    color: El color.
///
Brush::Brush(
	BrushStyle style,
	Color color):

	_impl(makeImpl(style, color)) {

#ifdef EOS_DEBUG
	__allocatedBrushCount++;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de copia.
/// \param    brush: L'objecte a copiar.
///
Brush::Brush(
	const Brush& brush) :

	_impl(brush._impl) {

#ifdef EOS_DEBUG
	__allocatedBrushCount++;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
Brush::~Brush() {

	if (_impl.uses() < 2) {
		for (int index = 0; index < _implCache.getSize(); index++) {
			if (_implCache[index] == _impl) {
				_implCache.removeAt(index);
				break;
			}
		}
	}

#ifdef EOS_DEBUG
	__allocatedBrushCount--;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Operador d'asignacio.
/// \param    brush: L'objecte a asignar.
/// \return   El propi objecte.
///
Brush& Brush::operator = (
	const Brush& brush) {

	_impl = brush._impl;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador ==
/// \param    brush: El operand
/// \return   True si son iguals.
///
bool Brush::operator == (
	const Brush& brush) const {

	return *_impl == *brush._impl;
}


/// ----------------------------------------------------------------------
/// \brief    Crea l'estructura interna de dades.
/// \param    style: L'estil.
/// \param    color: EL color.
///
Brush::ImplPtr Brush::makeImpl(
	BrushStyle style,
	Color color) {

	// Si ja esta en el cache, el reutilitza.
	//
	for (auto it = _implCache.begin(); it != _implCache.end(); it++) {
		ImplPtr impl = *it;
		if ((impl->getStyle() == style) &&
			(impl->getColor() == color))
			return impl;
	}

	// Si no el troba, en crea un de nou
	//
	ImplPtr impl(new Impl(style, color));
	_implCache.pushBack(impl);
	return impl;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estil del brush.
/// \return   L'estil.
///
BrushStyle Brush::getStyle() const {

	return _impl->getStyle();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el color.
/// \return   El color.
/// \remarks  Nomes es valid per BrushStyle::solid
///
Color Brush::getColor() const {

	return _impl->getColor();
}


/// ----------------------------------------------------------------------
/// \brief    Indica si es nul.
/// \return   True si es nul, false en cas contrari.
///
bool Brush::isNull() const {

	return _impl->getColor().isTransparent();
}

