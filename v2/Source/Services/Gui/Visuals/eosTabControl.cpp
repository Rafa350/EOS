#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosBrush.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "Services/Gui/Visuals/eosStackPanel.h"
#include "Services/Gui/Visuals/eosTabControl.h"
#include "Services/Gui/Visuals/eosTabControlItem.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
TabControl::TabControl():

	_header(nullptr),
	_content(nullptr) {

}


/// ----------------------------------------------------------------------
/// \build    Notifica que s'afegeix un item al control.
/// \param    item: El item a afeigir.
///
void TabControl::onItemAdded(
	ControlItem* item) {

	TabControlItem* tabItem = static_cast<TabControlItem*>(item);

	if (_header == nullptr) {
		_header = createHeaderPanel();
		addVisual(_header);
	}

	_header->addChild(tabItem->getHeader());
}


/// ----------------------------------------------------------------------
/// \brief    Notifica que s'ha eliminat un item del control.
/// \param    items: El item a eliminar.
///
void TabControl::onItemRemoved(
	ControlItem* item) {

	TabControlItem* tabItem = static_cast<TabControlItem*>(item);
}


/// ----------------------------------------------------------------------
/// \brief    Notifica que ha canviat l'item actiu.
/// \param    item: L'item activat.
///
void TabControl::onActiveItemChanged(
	ControlItem* item) {

	TabControlItem* tabItem = static_cast<TabControlItem*>(item);
}


/// ----------------------------------------------------------------------
/// \brief    Crea el panell de la capcelera.
/// \return   El panell creat.
///
Panel* TabControl::createHeaderPanel() {

	//TODO: Canviar a WarpPanel

	StackPanel* panel = new StackPanel();
	panel->setVerticalAlignment(VerticalAlignment::top);

	panel->setBackground(Brush(BrushStyle::solid, COLOR_Green));

	panel->setOrientation(Orientation::horizontal);

	return panel;
}
