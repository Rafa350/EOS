#ifndef __EOS_MENUFORM_HPP
#define __EOS_MENUFORM_HPP


#include "eos.hpp"
#include "System/Core/eosCallbacks.hpp"
#include "Services/Forms/eosForms.hpp"


#define MAX_LEVELS               10


namespace eos {
    
    class MenuForm;
    typedef MenuForm *MenuFormHandle;
    
    class MenuForm: public Form {
        private:
            typedef ICallbackP2<MenuFormHandle, unsigned> ISelectItemEvent;
            typedef ICallbackP2<MenuFormHandle, unsigned> IClickItemEvent;
            typedef ICallbackP2<MenuFormHandle, unsigned> IDrawItemEvent;
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
            ISelectItemEvent *evSelectItem;
            IClickItemEvent *evClickItem;
            IDrawItemEvent *evDrawItem;
            
        public:
            MenuForm(FormsServiceHandle service, FormHandle parent, uint8_t *resource);
            
            /// \brief Asigna el event evSelectItem.
            /// \param instance: La instancia on s'executa el metode.
            /// \param methid: El metode a executar.
            template <class cls>
            void setSelectItemEvent(cls *instance, void (cls::*method)(MenuFormHandle, unsigned)) { 
                
                evSelectItem = new CallbackP2<cls, MenuFormHandle, unsigned>(instance, method); 
            }
            
            /// \brief Asigna el event evClickItem.
            /// \param instance: La instancia on s'executa el metode.
            /// \param methid: El metode a executar.
            template <class cls>
            void setClickItemEvent(cls *instance, void (cls::*method)(MenuFormHandle, unsigned)) {
                
                evClickItem = new CallbackP2<cls, MenuFormHandle, unsigned>(instance, method);
            }
            
            /// \brief Asigna el event evDrawItem.
            /// \param instance: La instancia on s'executa el metode.
            /// \param methid: El metode a executar.
            template <class cls>
            void setDrawItemEvent(cls *instance, void (cls::*method)(MenuFormHandle, unsigned)) { 
                
                evDrawItem = new CallbackP2<cls, MenuFormHandle, unsigned>(instance, method); 
            }

        protected:
            ~MenuForm();
            virtual void onSelectItem(unsigned itemId);
            virtual void onClickItem(unsigned itemId);
            virtual void onDrawItem(unsigned itemId);
            void onPaint(FormsDisplayHandle display);    
#ifdef eosFormsService_UseSelector            
            void onSelectorMove(int position, SelectorDirection direction);
            void onSelectorPress();
#endif
#ifdef eosFormsService_UseKeyboard            
            void onKeyPress(unsigned key);
#endif            
        private:
            void firstItem();
            void lastItem();
            void nextItem();
            void prevItem();
            void clickItem();
            void nextMenu();
            void prevMenu();
    };

}


#endif
