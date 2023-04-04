#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosBrush.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "Services/Gui/eosVisualUtils.h"
#include "Services/Gui/Visuals/eosStackPanel.h"
#include "Services/Gui/Visuals/eosTabControl.h"
#include "Services/Gui/Visuals/eosTabControlItem.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
TabControl::TabControl():
    _touchpadPressEventCallback(*this, &TabControl::touchpadPressEventHandler),
	_panel(nullptr),
	_header(nullptr),
	_content(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Handler del event 'TouchpadPress'
/// \param    args: Parametres del event.
///
void TabControl::touchpadPressEventHandler(
	const TouchpadPressEventArgs& args) {

	Visual* visual = VisualUtils::getVisual(this, args.position);
	if (visual != nullptr) {
		visual = nullptr;
	}
}


/// ----------------------------------------------------------------------
/// \build    Notifica que s'afegeix un item al control.
/// \param    item: El item a afeigir.
///
void TabControl::onItemAdded(
	ControlItem* item) {

	TabControlItem* tabItem = static_cast<TabControlItem*>(item);

	// Si cal, crea el panell base i l'afegeix al control
	//
	if (_panel == nullptr) {
		_panel = createPanel();
		addVisual(_panel);
	}

	// Si cal, crea el panell de la capcelera i l'afegeix al panell base
	//
	if (_header == nullptr) {
		_header = createHeaderPanel();
		_panel->addChild(_header);
	}

	// Afegeix l'element de la capcelera del item
	//
	Visual* headerItem = tabItem->getHeader();
	headerItem->setTouchpadPressEventCallback(&_touchpadPressEventCallback);
	_header->addChild(headerItem);

	// Afegeix l'element del contingut del item
	//
	_panel->addChild(tabItem->getContent());
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


Panel* TabControl::createPanel() {

	StackPanel* panel = new StackPanel();
	panel->setOrientation(Orientation::vertical);
	return panel;
}


/// ----------------------------------------------------------------------
/// \brief    Crea el panell de la capcelera.
/// \return   El panell creat.
///
Panel* TabControl::createHeaderPanel() {

	//TODO: Canviar a WarpPanel

	StackPanel* panel = new StackPanel();
	panel->setVerticalAlignment(VerticalAlignment::top);

	panel->setBackground(Colors::transparent);

	panel->setOrientation(Orientation::horizontal);

	return panel;
}
