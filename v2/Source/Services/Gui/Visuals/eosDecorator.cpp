#include "eos.h"
#include "Services/Gui/Visuals/eosDecorator.h"


using namespace eos;


/// ---------------------------------------------------------------------
/// \brief    Constructor.
///
Decorator::Decorator() :
	_child(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Assigna el control fill del decorador.
/// \param    value: El conmtrol fill.
///
void Decorator::setChild(
	Visual *value) {

	if (_child != value) {

		if (_child != nullptr)
			removeVisual(_child);

		_child = value;

		if (_child != nullptr)
			addVisual(_child);
	}
}
