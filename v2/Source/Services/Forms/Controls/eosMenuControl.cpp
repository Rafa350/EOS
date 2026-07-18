#include "eos.h"
#include "Services/Forms/Controls/eosMenuControl.h"
#include "Services/Forms/eosForm.h"
#include "System/eosMath.h"
#include "System/Graphics/eosBrush.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosPen.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosRect.h"
#include "System/Graphics/eosText.h"


/// ----------------------------------------------------------------------
/// \brief    Contructor.
/// \param    position: La posicio.
/// \param    size: El tamany.
///
eos::MenuControl::MenuControl(
    const Point &position,
    const Size &size,
	const uint8_t *descriptor):

    Control {position, size},
    _textColor {Colors::white},
    _selectedTextColor {Colors::black},
	_selectedBackgroundColor {Colors::white},
	_descriptor {descriptor},
	_notifyEvent {nullptr},
	_commandEvent {nullptr} {

	_dataLevel = 0;
	_dataStack[0].menuDescriptorIndex = 0;
	_dataStack[0].numItems = getMenuNumItems(0);
	_dataStack[0].selectedItem = 0;
	_dataStack[0].firstVisibleItem = 0;

	_visibleItems = (size.getHeight() - _menuTitleHeight) / _itemTitleHeight;
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant un item ha estat activat.
/// \brief    id: Identificador del item.
///
void eos::MenuControl::onCommand(
	uint8_t id) {

	invalidate();

	if (_commandEvent != nullptr) {
		CommandEventArgs args = {
			.command {id}
		};
		_commandEvent->execute(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant un item ha estat seleccionat.
///
void eos::MenuControl::onItemSelected() {

	invalidate();

	if (_notifyEvent != nullptr) {
		NotifyEventArgs args = {
			.eventId {NotifyEventID::itemSelected}
		};
		_notifyEvent->execute(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els missatges
/// \param    message: El missatge a processar.
///
void eos::MenuControl::onMessage(
	FormMessage &message) {

	switch (message.id) {
		case FormMessageID::keyboard:
			switch (message.keyboard.id) {
				case KeyboardMessageID::up:
					prev();
					break;

				case KeyboardMessageID::down:
					next();
					break;

				case KeyboardMessageID::enter:
					action();
					break;

				default:
					Control::onMessage(message);
			}
			break;

		case FormMessageID::selector:
			switch (message.selector.id) {
				case SelectorMessageID::inc:
					next();
					break;

				case SelectorMessageID::dec:
					prev();
					break;

				case SelectorMessageID::press:
					action();
					break;

				default:
					Control::onMessage(message);
			}
			break;

		default:
			Control::onMessage(message);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els canvis en una propietat.
/// \param    ptr: Punter a la propietat que ha canviat.
///
void eos::MenuControl::onPropertyChanged(
	void *ptr) {

	Control::onPropertyChanged(ptr);
}


/// ----------------------------------------------------------------------
/// \brief    Renderitza la imatge del control.
/// \param    graphics: L'objecte per dibuixar.
///
void eos::MenuControl::onRender(
    Graphics *graphics) {

	Control::onRender(graphics);

	auto data = &_dataStack[_dataLevel];

	int16_t width = getSize().getWidth();

	Text text;
	text.setHorizontalAlign(eos::Text::HorizontalAlign::left);
	text.setForeground(Brush(_textColor));
	text.setBackground(Brush(getBackgroundColor()));

	auto menuTitleLength = getMenuTitleLength(data->menuDescriptorIndex);
	auto menuTitle = getMenuTitle(data->menuDescriptorIndex);
	text.setText(menuTitle, menuTitleLength);
	graphics->paintText(
		Rect(Point(2, 0), Size(width - 4, _menuTitleHeight)),
		text);
	graphics->paintLine(
		Pen(getBorderColor(), 1),
		Point(0, 10),
		Point(width - 1, 10));

	int16_t y = _menuTitleHeight;
	auto lastVisibleItem = data->firstVisibleItem + Math::min(data->numItems, _visibleItems) - 1;
	for (auto item = data->firstVisibleItem; item <= lastVisibleItem; item++) {

		auto itemDescriptorIndex = getMenuItemDescriptorIndex(data->menuDescriptorIndex, item);

		if (item == data->selectedItem)
			graphics->paintRectangle(
				Pen(_selectedBackgroundColor, 1),
				Brush(_selectedBackgroundColor),
				Rect(Point(2, y), Size(width - 4, _itemTitleHeight - 1)));

		if (item == data->selectedItem) {
			text.setBackground(Brush(_selectedBackgroundColor));
			text.setForeground(Brush(_selectedTextColor));
		}
		else {
			text.setBackground(Brush(getBackgroundColor()));
			text.setForeground(Brush(_textColor));
		}
		auto itemTitleLength = getItemTitleLength(itemDescriptorIndex);
		auto itemTitle = getItemTitle(itemDescriptorIndex);
		text.setText(itemTitle, itemTitleLength);
		graphics->paintText(
			Rect(Point(10, y), Size(width - 4, _itemTitleHeight)),
			text);

		if (getItemType(itemDescriptorIndex)) {
			const char *itemSubTitle;
			uint8_t itemSubTitleLength = 0;
            uint8_t itemId = getItemId(itemDescriptorIndex);
			if (requestText(itemId, itemSubTitle, itemSubTitleLength)) {
				text.setText(itemSubTitle, itemSubTitleLength);
				graphics->paintText(
					Rect(Point(60, y), Size(width - 4, _itemTitleHeight)),
					text);
			}
		}

		y += _itemTitleHeight;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el seguent item.
///
void eos::MenuControl::next() {

	auto data = &_dataStack[_dataLevel];

	if (data->selectedItem < data->numItems - 1) {
		data->selectedItem++;
        if (data->selectedItem >= data->firstVisibleItem + _visibleItems)
            data->firstVisibleItem++;
        onItemSelected();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Delecciona l'anterior item.
///
void eos::MenuControl::prev() {

	auto data = &_dataStack[_dataLevel];

	if (data->selectedItem > 0) {
		data->selectedItem--;
		if (data->selectedItem < data->firstVisibleItem)
			data->firstVisibleItem--;
        onItemSelected();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el primer item.
///
void eos::MenuControl::first() {

	auto data = &_dataStack[_dataLevel];

	if (data->selectedItem != 0) {
		data->selectedItem = 0;
		data->firstVisibleItem = 0;
        onItemSelected();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona l'ultim.
///
void eos::MenuControl::last() {

	auto data = &_dataStack[_dataLevel];

	if (data->selectedItem != (data->numItems - 1)) {
		data->selectedItem = data->numItems - 1;
		data->firstVisibleItem = data->numItems - _visibleItems;
        onItemSelected();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el item actual.
///
void eos::MenuControl::action() {

    auto data = &_dataStack[_dataLevel];
    auto itemDescriptorIndex = getMenuItemDescriptorIndex(data->menuDescriptorIndex, data->selectedItem);

    switch (getItemType(itemDescriptorIndex)) {
        case 0x00: // commandItem
            onCommand(getItemId(itemDescriptorIndex));
            break;

        case 0x01: // menuItem
            if (_dataLevel < (_dataStackSize - 1)) {
                _dataLevel++;

                auto menuDescriptorIndex = getItemSubMenuDescriptorIndex(itemDescriptorIndex);

                auto data = &_dataStack[_dataLevel];
                data->menuDescriptorIndex = menuDescriptorIndex;
                data->numItems = getMenuNumItems(menuDescriptorIndex);
                data->firstVisibleItem = 0;
                data->selectedItem = 0;

                onItemSelected();
            }
            break;

        case 0x02: // backItem
            if (_dataLevel > 0) {
                _dataLevel--;
                onItemSelected();
            }
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Reclama un text asociat a un item. La solicitut es fa
///           per mitja de l'event 'requestText'
/// \param    id: Identificador del item.
/// \param    text: Punter al text
/// \param    length: Longitut del text.
/// \return   True si es correcte.
/// \remarks  Els valors retornats en 'text' i 'length' nomes son valid en
///           el cas que la funcio retorni 'true'.
///
bool eos::MenuControl::requestText(
	uint8_t id,
	const char *&text,
	uint8_t &length) {

	if (_notifyEvent != nullptr) {
		NotifyEventArgs args = {
			.eventId {NotifyEventID::requestText},
			.requestText {
				.itemId {id},
				.text {nullptr},
				.length {0}
			}
		};
		_notifyEvent->execute(this, &args);

		text = args.requestText.text;
		length = args.requestText.length;
		return (text != nullptr) && (length != 0);
	}

	else {
		text = nullptr;
		length = 0;
		return false;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Obte el titol d'un menu.
/// \param    menuDescriptorIndex: El index del descriptor del menu.
/// \return   Punter a la cadena.
///
const char* eos::MenuControl::getMenuTitle(
	uint16_t menuDescriptorIndex) const {

	return reinterpret_cast<const char*>(&_descriptor[menuDescriptorIndex + 2]);
}


/// ----------------------------------------------------------------------
/// \brief    Obte la longitut del titol d'un menu.
/// \param    menuDescriptorIndex: El index del descriptor del menu.
/// \return   La longitut.
///
uint8_t eos::MenuControl::getMenuTitleLength(
	uint16_t menuDescriptorIndex) const {

	return _descriptor[menuDescriptorIndex + 1];
}


/// ----------------------------------------------------------------------
/// \brief    Obte el nombre d'items.
/// \param    menuDescriptorIndex: El index del descriptor del menu.
/// \return   El resultat
///
uint8_t eos::MenuControl::getMenuNumItems(
	uint16_t menuDescriptorIndex) const {

	return _descriptor[menuDescriptorIndex];
}


/// ----------------------------------------------------------------------
/// \brief    Obte el index del descriptor d'un item.
/// \param    menuDescriptorIndex: El index del descriptor del menu.
/// \param    item: El numero de item.
/// \return   El resultat
///
uint16_t eos::MenuControl::getMenuItemDescriptorIndex(
	uint16_t menuDescriptorIndex,
	uint8_t item) const {

    uint16_t idx =
   		menuDescriptorIndex +                   // Posicio del menu
		2 +                                     // Tamany del descriptor
		_descriptor[menuDescriptorIndex + 1] +  // Longitut del titol
		(item * 2);                             // Offset al item
    return _descriptor[idx] + _descriptor[idx + 1] * 256;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el titol d'un item.
/// \param    intemDescriptorIndex: El index del descriptor del item.
/// \return   Punter a la cadena.
///
const char* eos::MenuControl::getItemTitle(
	uint16_t itemDescriptorIndex) const {

	return reinterpret_cast<const char*>(&_descriptor[itemDescriptorIndex + 2]);
}


/// ----------------------------------------------------------------------
/// \brief    Obte la longitut del titol d'un item.
/// \param    itemDescriptorIndex: El index del descriptor del item.
/// \return   La longitut.
///
uint8_t eos::MenuControl::getItemTitleLength(
	uint16_t itemDescriptorIndex) const {

	return _descriptor[itemDescriptorIndex + 1];

}


/// ----------------------------------------------------------------------
/// \brief    Obte tipus d'item.
/// \param    itemOffset: El index del descriptor del item.
/// \return   El tipus.
///
uint8_t eos::MenuControl::getItemType(
	uint16_t itemDescriptorIndex) const {

	return _descriptor[itemDescriptorIndex] & 0x03;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el offset al submenu d'un item.
/// \param    itemOffset: El index del descriptor del item.
/// \return   El offset del submenu.
///
uint16_t eos::MenuControl::getItemSubMenuDescriptorIndex(
	uint16_t itemDescriptorIndex) const {

    return
    	itemDescriptorIndex +                 // Posicio del item
		2 +                                   // Tamany del descriptor
		_descriptor[itemDescriptorIndex + 1]; // Longitut del titol
}


/// ----------------------------------------------------------------------
/// \brief    Obte el ideitificador d'un item.
/// \param    itemOffset: El offset del item.
/// \return   El identitifacor.
///
uint8_t eos::MenuControl::getItemId(
	uint16_t itemOffset) const {

    return _descriptor[itemOffset + 2 + _descriptor[itemOffset + 1]];
}
