#ifndef __EOS_FORMSMENUS_HPP
#define __EOS_FORMSMENUS_HPP


#include "eos.hpp"
#include "Services/Forms/eosDisplay.hpp"
#include "Services/Forms/eosForms.hpp"
#include "System/eosCallbacks.hpp"


#define MAX_LEVELS               10


namespace eos {

    class MenuForm: public Form {
        private:
            typedef ICallbackP1<unsigned> IMenuFormCommandEvent;
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
            IMenuFormCommandEvent *evCommand;
            
        public:
            MenuForm(FormsServiceHandle service, FormHandle parent, uint8_t *resource);
            ~MenuForm();
            
            template <class cls>
            void setEvCommand(cls *instance, void (cls::*method)(unsigned)) { 
                
                evCommand = new CallbackP1<cls, unsigned>(instance, method); 
            }
            
        private:
            void dispatchMessage(Message &message);
            void onActivate(FormHandle deactivatedForm);
            void onPaint(DisplayServiceHandle displayService);        
            void firstItem();
            void lastItem();
            void nextItem();
            void prevItem();
            void selectItem();
            void nextMenu();
            void prevMenu();
    };

}


#endif
