#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosItemsControl.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
ItemsControl::ItemsControl() :
	_activeItem(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un item a la llista.
/// \param    item: El item afeigit.
///
void ItemsControl::addItem(
	ControlItem* item) {

	eosAssert(item != nullptr);

	_items.push_front(item);
	onItemAdded(item);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina un item de la llista.
/// \param    item: El item a eliminar.
///
void ItemsControl::removeItem(
	ControlItem* item) {

	eosAssert(item != nullptr);

	int index = _items.indexOf(item);
	if (index >= 0) {
		if (item == _activeItem)
			_activeItem = nullptr;
		_items.removeAt(index);
		onItemRemoved(item);
	}
}


/// ----------------------------------------------------------------------
/// \brief
///
void ItemsControl::setActiveItem(
	ControlItem* item) {

	if (_activeItem != item) {
		_activeItem = item;
		onActiveItemChanged(item);
	}
}


void ItemsControl::onItemAdded(
	ControlItem* item) {

}

void ItemsControl::onItemRemoved(
	ControlItem* item) {

}

void ItemsControl::onActiveItemChanged(
	ControlItem* item) {

}
