#ifndef __EOS_FORMSLIST_HPP
#define __EOS_FORMSLIST_HPP


#include "eos.hpp"
#include "Services/Forms/eosForms.hpp"
#include "System/eosCallbacks.hpp"


namespace eos {
    
    class ListForm;
    typedef ListForm *ListFormhandle;
    
    class ListForm: public Form {
        private:
            const char *title;
            const char **items;
            unsigned currentItem;
            unsigned numItems;
    
        public:
            ListForm(FormsServiceHandle service, FormHandle parent);
            ~ListForm();
        private:
            void dispatchMessage(Message &message);
            void onActivate(FormHandle deactivateForm);
            void onPaint(DisplayControllerHandle displayController);
            void nextItem();
            void prevItem();       
            void selectItem();
    };    
}


#endif
