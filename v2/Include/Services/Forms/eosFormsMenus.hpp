#ifndef __EOS_FORMSMENUS_HPP
#define __EOS_FORMSMENUS_HPP


#include "eos.hpp"
#include "Services/Forms/eosDisplay.hpp"
#include "Services/Forms/eosForms.hpp"


#define MAX_LEVELS               10

                                       // Notificacions MSG_NOTIFY
#define EV_MENU_GETVALUE          1    // -Obte el valor del item
#define EV_MENU_PAINT_BACKGROUND  2    // -Dibuixa el fons
#define EV_MENU_PAINT_TITLE       3    // -Dibuixa el titol
#define EV_MENU_PAINT_ITEM        4    // -Dibuixa un item


namespace eos {

    typedef struct {                       // Parametres de notificacio GETVALUE
        unsigned command;
        char *itemValue;
    } eosMenuNotifyGetValue;

    typedef struct {                       // Parametres de notificacio PAINT
        char *title;                       // -Titol del menu/item
        unsigned firstItem;                // -Numero del primer item que es dibuixa
        unsigned numItem;                  // -Numero d'item
        unsigned command;                  // -Comanda del item
    } eosMenuNotifyPaint;
    
    class IMenuOwner {
        public:
            virtual void onCommand(uint8_t cmd) = 0;
    };

    class MenuForm: public Form {
        private:
            struct MenuInfo {               // Informacio d'un menu
                unsigned offset;            // -Offset al menu
                unsigned numItems;          // -Numero de items
                unsigned firstItem;         // -Primer item a mostrar
                unsigned currentItem;       // -Item actual
            };
    
        private:
            IMenuOwner *owner;
            uint8_t *resource;
            unsigned level;                 // -Nivell de submenus
            MenuInfo info[MAX_LEVELS];      // -Pila d'informacio del menu
            unsigned showItems;    
            
        public:
            MenuForm(FormsServiceHandle service, FormHandle parent, IMenuOwner *owner, uint8_t *resource);
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
