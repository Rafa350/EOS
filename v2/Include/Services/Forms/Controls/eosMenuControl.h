#pragma once


#include "eos.h"
#include "eosCallbacks.h"
#include "System/Graphics/eosColor.h"
#include "Services/Forms/eosControl.h"


namespace eos {

    class Graphics;

    class MenuControl: public Control {
    	private:
    		constexpr static uint32_t _dataStackSize = 5;
    		constexpr static int16_t _menuTitleHeight = 12;
    		constexpr static int16_t _itemTitleHeight = 12;

    	private:
    		struct Data {
    			uint16_t menuDescriptorIndex;
    			uint8_t selectedItem;
    			uint8_t firstVisibleItem;
    			uint8_t numItems;
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
    					uint8_t itemId;
    					const char *text;
    					uint8_t length;
    				} requestText;
    			};
    		};
    		using INotifyEvent = eos::ICallbackP2<MenuControl*, NotifyEventArgs*>;
    		template <typename Instance_> using NotifyEvent = eos::CallbackP2<Instance_, MenuControl*, NotifyEventArgs*>;

    		struct CommandEventArgs {
    			uint8_t command;
    		};
    		using ICommandEvent = eos::ICallbackP2<MenuControl*, CommandEventArgs*>;
    		template <typename Instance_> using CommandEvent = eos::CallbackP2<Instance_, MenuControl*, CommandEventArgs*>;

        private:
    		Color _textColor;
            Color _selectedTextColor;
            Color _selectedBackgroundColor;
            const uint8_t *_descriptor;
            Data _dataStack[_dataStackSize];
            uint8_t _dataLevel;
            uint8_t _visibleItems;
            INotifyEvent *_notifyEvent;
            ICommandEvent *_commandEvent;

        private:
            const char* getMenuTitle(uint16_t menuDescriptorIndex) const;
            uint8_t getMenuTitleLength(uint16_t menuDescriptorIndex) const;
            uint8_t getMenuNumItems(uint16_t menuDescriptorIndex) const;
            uint16_t getMenuItemDescriptorIndex(uint16_t menuDescriptorIndex, uint8_t item) const;

            const char* getItemTitle(uint16_t itemDescriptorIndex) const;
            uint8_t getItemTitleLength(uint16_t itemDescriptorIndex) const;
            uint8_t getItemType(uint16_t itemDescriptorIndex) const;
            uint16_t getItemSubMenuDescriptorIndex(uint16_t itemDescriptorIndex) const;
            uint8_t getItemId(uint16_t itemDescriptorIndex) const;

            bool requestText(uint8_t id, const char *&text, uint8_t &length);

        protected:
            void onMessage(FormMessage &message) override;
            void onRender(Graphics *graphics) override;
            void onPropertyChanged(void *ptr) override;
            virtual void onCommand(uint8_t id);
            virtual void onItemSelected();

        public:
            MenuControl(const Point &position, const Size &size, const uint8_t *descriptor);

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
