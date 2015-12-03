#ifndef __EOS_FORMSMENUS_HPP
#define __EOS_FORMSMENUS_HPP


#include "eos.hpp"
#include "Services/Forms/eosForms.hpp"
#include "System/eosCallbacks.hpp"


#define MAX_LEVELS               10


namespace eos {
    
    class MenuForm;
    typedef MenuForm *MenuFormHandle;

    class MenuForm: public Form {
        private:
            typedef ICallbackP1<unsigned> IMenuFormCommandEvent;
            typedef ICallbackP1<unsigned> IMenuFormFormatTextEvent;
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
            IMenuFormFormatTextEvent *evFormatText;
            
        public:
            MenuForm(FormsServiceHandle service, FormHandle parent, uint8_t *resource);
            ~MenuForm();
            
            /// \brief Asigna el event evCommand.
            /// \param instance: La instancia on s'executa el metode.
            /// \param methid: El metode a executar.
            template <class cls>
            void setEvCommand(cls *instance, void (cls::*method)(unsigned)) { 
                
                evCommand = new CallbackP1<cls, unsigned>(instance, method); 
            }
            
            /// \brief Asigna el event evFormatText.
            /// \param instance: La instancia on s'executa el metode.
            /// \param methid: El metode a executar.
            template <class cls>
            void setEvFormatText(cls *instance, void (cls::*method)(unsigned)) { 
                
                evFormatText = new CallbackP1<cls, unsigned>(instance, method); 
            }

        private:
            void dispatchMessage(Message &message);
            void onActivate(FormHandle deactivatedForm);
            void onPaint(DisplayControllerHandle displayController);        
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
