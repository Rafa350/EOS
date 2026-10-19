export module Eos.Services.Forms.Controls.Menu;

import Eos.Callbacks;
import Eos.Math;
import Eos.Services.Forms;
import Eos.System.Graphics;
import Eos.System.Graphics.Color;
import Eos.System.Graphics.ColorDefinitions;
import Eos.Types;


export namespace eos {

	 class MenuControl: public Control {
    	private:
    		constexpr static UInt32 _dataStackSize = 5;
    		constexpr static UInt16 _menuTitleHeight = 12;
    		constexpr static UInt16 _itemTitleHeight = 12;

    	private:
    		struct Data {
    			UInt16 menuDescriptorIndex;
    			UInt8 selectedItem;
    			UInt8 firstVisibleItem;
    			UInt8 numItems;
    		};

    	public:
    		enum class NotifyEventID {
				itemSelected,
				requestText
    		};
    		struct NotifyEventArgs {
    			NotifyEventID eventId;
    			union {
    				struct {
    					UInt8 itemId;
    					const char *text;
    					UInt8 length;
    				} requestText;
    			};
    		};
    		using INotifyEvent = ICallbackP2<MenuControl*, NotifyEventArgs*>;
    		template <typename Instance_> using NotifyEvent = eos::CallbackP2<Instance_, MenuControl*, NotifyEventArgs*>;

    		struct CommandEventArgs {
    			UInt8 command;
    		};
    		using ICommandEvent = ICallbackP2<MenuControl*, CommandEventArgs*>;
    		template <typename Instance_> using CommandEvent = eos::CallbackP2<Instance_, MenuControl*, CommandEventArgs*>;

        private:
    		Color _textColor;
            Color _selectedTextColor;
            Color _selectedBackgroundColor;
            const UInt8 *_descriptor;
            Data _dataStack[_dataStackSize];
            UInt8 _dataLevel;
            UInt8 _visibleItems;
            INotifyEvent *_notifyEvent;
            ICommandEvent *_commandEvent;

        private:
            const char* getMenuTitle(UInt16 menuDescriptorIndex) const;
            UInt8 getMenuTitleLength(UInt16 menuDescriptorIndex) const;
            UInt8 getMenuNumItems(UInt16 menuDescriptorIndex) const;
            UInt16 getMenuItemDescriptorIndex(UInt16 menuDescriptorIndex, UInt8 item) const;

            const char* getItemTitle(UInt16 itemDescriptorIndex) const;
            UInt8 getItemTitleLength(UInt16 itemDescriptorIndex) const;
            UInt8 getItemType(UInt16 itemDescriptorIndex) const;
            UInt16 getItemSubMenuDescriptorIndex(UInt16 itemDescriptorIndex) const;
            UInt8 getItemId(UInt16 itemDescriptorIndex) const;

            bool requestText(UInt8 id, const char *&text, UInt8 &length);

        protected:
            void onMessage(FormMessage &message) override;
            void onRender(Graphics *graphics) override;
            void onPropertyChanged(void *ptr) override;
            virtual void onCommand(UInt8 id);
            virtual void onItemSelected();

        public:
            MenuControl(const Point &position, const Size &size, const UInt8 *descriptor);

            inline void setTextColor(Color value) { setProperty(_textColor, value); }
            inline void setSelectedTextColor(Color value) { setProperty(_selectedTextColor, value); }
            inline void setSelectedBackgroundColor(Color value) { setProperty(_selectedBackgroundColor, value); }

            inline void setNotifyEvent(INotifyEvent &event) {
            	_notifyEvent = &event;
            }
            inline void clearNotifyEvent() {
            	_notifyEvent = nullptr;
            }
            inline void setCommandEvent(ICommandEvent &event) {
            	_commandEvent = &event;
            }
            inline void clearCommandEvent() {
            	_commandEvent = nullptr;
            }

            void next();
            void prev();
            void first();
            void last();
            void action();
    };
}


using namespace eos;


/// ----------------------------------------------------------------------
/// @brief    Contructor.
/// @param    position: La posicio.
/// @param    size: El tamany.
///
MenuControl::MenuControl(
    const Point &position,
    const Size &size,
	const UInt8 *descriptor):

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
/// @brief    Es crida quant un item ha estat activat.
/// @brief    id: Identificador del item.
///
void MenuControl::onCommand(
	UInt8 id) {

	invalidate();

	if (_commandEvent != nullptr) {
		CommandEventArgs args = {
			.command {id}
		};
		_commandEvent->execute(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Es crida quant un item ha estat seleccionat.
///
void MenuControl::onItemSelected() {

	invalidate();

	if (_notifyEvent != nullptr) {
		NotifyEventArgs args = {
			.eventId {NotifyEventID::itemSelected}
		};
		_notifyEvent->execute(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Procesa els missatges
/// @param    message: El missatge a processar.
///
void MenuControl::onMessage(
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
/// @brief    Procesa els canvis en una propietat.
/// @param    ptr: Punter a la propietat que ha canviat.
///
void MenuControl::onPropertyChanged(
	void *ptr) {

	Control::onPropertyChanged(ptr);
}


/// ----------------------------------------------------------------------
/// @brief    Renderitza la imatge del control.
/// @param    graphics: L'objecte per dibuixar.
///
void MenuControl::onRender(
    Graphics *graphics) {

	Control::onRender(graphics);

	auto data = &_dataStack[_dataLevel];

	UInt16 width = getSize().getWidth();

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

	UInt16 y = _menuTitleHeight;
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
			UInt8 itemSubTitleLength = 0;
            UInt8 itemId = getItemId(itemDescriptorIndex);
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
/// @brief    Selecciona el seguent item.
///
void MenuControl::next() {

	auto data = &_dataStack[_dataLevel];

	if (data->selectedItem < data->numItems - 1) {
		data->selectedItem++;
        if (data->selectedItem >= data->firstVisibleItem + _visibleItems)
            data->firstVisibleItem++;
        onItemSelected();
	}
}


/// ----------------------------------------------------------------------
/// @brief    Delecciona l'anterior item.
///
void MenuControl::prev() {

	auto data = &_dataStack[_dataLevel];

	if (data->selectedItem > 0) {
		data->selectedItem--;
		if (data->selectedItem < data->firstVisibleItem)
			data->firstVisibleItem--;
        onItemSelected();
	}
}


/// ----------------------------------------------------------------------
/// @brief    Selecciona el primer item.
///
void MenuControl::first() {

	auto data = &_dataStack[_dataLevel];

	if (data->selectedItem != 0) {
		data->selectedItem = 0;
		data->firstVisibleItem = 0;
        onItemSelected();
	}
}


/// ----------------------------------------------------------------------
/// @brief    Selecciona l'ultim.
///
void MenuControl::last() {

	auto data = &_dataStack[_dataLevel];

	if (data->selectedItem != (data->numItems - 1)) {
		data->selectedItem = data->numItems - 1;
		data->firstVisibleItem = data->numItems - _visibleItems;
        onItemSelected();
	}
}


/// ----------------------------------------------------------------------
/// @brief    Selecciona el item actual.
///
void MenuControl::action() {

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
/// @brief    Reclama un text asociat a un item. La solicitut es fa
///           per mitja de l'event 'requestText'
/// @param    id: Identificador del item.
/// @param    text: Punter al text
/// @param    length: Longitut del text.
/// @return   True si es correcte.
/// \remarks  Els valors retornats en 'text' i 'length' nomes son valid en
///           el cas que la funcio retorni 'true'.
///
bool MenuControl::requestText(
	UInt8 id,
	const char *&text,
	UInt8 &length) {

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
/// @brief    Obte el titol d'un menu.
/// @param    menuDescriptorIndex: El index del descriptor del menu.
/// @return   Punter a la cadena.
///
const char* MenuControl::getMenuTitle(
	UInt16 menuDescriptorIndex) const {

	return reinterpret_cast<const char*>(&_descriptor[menuDescriptorIndex + 2]);
}


/// ----------------------------------------------------------------------
/// @brief    Obte la longitut del titol d'un menu.
/// @param    menuDescriptorIndex: El index del descriptor del menu.
/// @return   La longitut.
///
UInt8 MenuControl::getMenuTitleLength(
	UInt16 menuDescriptorIndex) const {

	return _descriptor[menuDescriptorIndex + 1];
}


/// ----------------------------------------------------------------------
/// @brief    Obte el nombre d'items.
/// @param    menuDescriptorIndex: El index del descriptor del menu.
/// @return   El resultat
///
UInt8 MenuControl::getMenuNumItems(
	UInt16 menuDescriptorIndex) const {

	return _descriptor[menuDescriptorIndex];
}


/// ----------------------------------------------------------------------
/// @brief    Obte el index del descriptor d'un item.
/// @param    menuDescriptorIndex: El index del descriptor del menu.
/// @param    item: El numero de item.
/// @return   El resultat
///
UInt16 MenuControl::getMenuItemDescriptorIndex(
	UInt16 menuDescriptorIndex,
	UInt8 item) const {

    UInt16 idx =
   		menuDescriptorIndex +                   // Posicio del menu
		2 +                                     // Tamany del descriptor
		_descriptor[menuDescriptorIndex + 1] +  // Longitut del titol
		(item * 2);                             // Offset al item
    return _descriptor[idx] + _descriptor[idx + 1] * 256;
}


/// ----------------------------------------------------------------------
/// @brief    Obte el titol d'un item.
/// @param    intemDescriptorIndex: El index del descriptor del item.
/// @return   Punter a la cadena.
///
const char* MenuControl::getItemTitle(
	UInt16 itemDescriptorIndex) const {

	return reinterpret_cast<const char*>(&_descriptor[itemDescriptorIndex + 2]);
}


/// ----------------------------------------------------------------------
/// @brief    Obte la longitut del titol d'un item.
/// @param    itemDescriptorIndex: El index del descriptor del item.
/// @return   La longitut.
///
UInt8 MenuControl::getItemTitleLength(
	UInt16 itemDescriptorIndex) const {

	return _descriptor[itemDescriptorIndex + 1];

}


/// ----------------------------------------------------------------------
/// @brief    Obte tipus d'item.
/// @param    itemOffset: El index del descriptor del item.
/// @return   El tipus.
///
UInt8 MenuControl::getItemType(
	UInt16 itemDescriptorIndex) const {

	return _descriptor[itemDescriptorIndex] & 0x03;
}


/// ----------------------------------------------------------------------
/// @brief    Obte el offset al submenu d'un item.
/// @param    itemOffset: El index del descriptor del item.
/// @return   El offset del submenu.
///
UInt16 MenuControl::getItemSubMenuDescriptorIndex(
	UInt16 itemDescriptorIndex) const {

    return
    	itemDescriptorIndex +                 // Posicio del item
		2 +                                   // Tamany del descriptor
		_descriptor[itemDescriptorIndex + 1]; // Longitut del titol
}


/// ----------------------------------------------------------------------
/// @brief    Obte el ideitificador d'un item.
/// @param    itemOffset: El offset del item.
/// @return   El identitifacor.
///
UInt8 MenuControl::getItemId(
	UInt16 itemOffset) const {

    return _descriptor[itemOffset + 2 + _descriptor[itemOffset + 1]];
}
