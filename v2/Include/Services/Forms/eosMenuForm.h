#ifndef __EOS_MENUFORM_H
#define __EOS_MENUFORM_H


#include "eos.h"
#include "System/Core/eosCallbacks.h"
#include "Services/Forms/eosForms.h"


#define MAX_LEVELS               10


namespace eos {
    
    typedef uint16_t ItemId;
    
    struct DrawItemEventParams {
        ItemId itemId;
        const char *title;
        FormsDisplay *display;
        int16_t x;
        int16_t y;
        int16_t width;
        int16_t height;
    };
    
    class MenuForm: public Form {
        private:
            typedef ICallbackP2<MenuForm*, ItemId> ISelectItemEvent;
            typedef ICallbackP2<MenuForm*, ItemId> IClickItemEvent;
            typedef ICallbackP2<MenuForm*, DrawItemEventParams*> IDrawItemEvent;
            struct MenuInfo {               // Informacio d'un menu
                unsigned offset;            // -Offset al menu
                unsigned numItems;          // -Numero de items
                unsigned firstItem;         // -Primer item a mostrar
                unsigned currentItem;       // -Item actual
            };
    
        private:
            uint8_t *resource;              // -Punter al recurs
            unsigned level;                 // -Nivell de submenus
            MenuInfo info[MAX_LEVELS];      // -Pila d'informacio del menu
            unsigned showItems;             // -Numero d'items a mostrar
            bool refreshBackground;         // -Indica si cal refrescar el fons
            ISelectItemEvent *evSelectItem;
            IClickItemEvent *evClickItem;
            IDrawItemEvent *evDrawItem;
            
        public:
            MenuForm(FormsService *service, Form *parent, uint8_t *resource);
            
            /// \brief Asigna el event evSelectItem.
            /// \param instance: La instancia on s'executa el metode.
            /// \param methid: El metode a executar.
            template <class cls>
            void setSelectItemEventHandler(cls *instance, void (cls::*method)(MenuForm*, ItemId)) {     
                if (evSelectItem != nullptr)
                    delete evSelectItem;
                evSelectItem = new CallbackP2<cls, MenuForm*, ItemId>(instance, method); 
            }
            
            /// \brief Asigna el event evClickItem.
            /// \param instance: La instancia on s'executa el metode.
            /// \param methid: El metode a executar.
            template <class cls>
            void setClickItemEventHandler(cls *instance, void (cls::*method)(MenuForm*, ItemId)) {     
                if (evClickItem != nullptr)
                    delete evClickItem;
                evClickItem = new CallbackP2<cls, MenuForm*, ItemId>(instance, method);
            }
            
            /// \brief Asigna el event evDrawItem.
            /// \param instance: La instancia on s'executa el metode.
            /// \param methid: El metode a executar.
            template <class cls>
            void setDrawItemEventHandler(cls *instance, void (cls::*method)(MenuForm*, DrawItemEventParams*)) {    
                if (evDrawItem != nullptr)
                    delete evDrawItem;
                evDrawItem = new CallbackP2<cls, MenuForm*, DrawItemEventParams*>(instance, method); 
            }

        protected:
            ~MenuForm();
            virtual void onSelectItem(ItemId itemId);
            virtual void onClickItem(ItemId itemId);
            virtual void onDrawItem(ItemId itemId, const char *title, 
                FormsDisplay *display, int16_t x, int16_t y, int16_t width, int16_t height);
            void onPaint(FormsDisplay *display);    
#ifdef eosFormsService_UseSelector            
            void onSelectorMove(SelectorPosition position, SelectorDirection direction);
            void onSelectorPress();
#endif
#ifdef eosFormsService_UseKeyboard            
            void onKeyPress(KeyCode key);
#endif            
        private:
            void firstItem();
            void lastItem();
            void nextItem();
            void prevItem();
            void clickItem();
            void backItem();
    };

}


#endif