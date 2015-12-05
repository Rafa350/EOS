#ifndef __EOS_FORMSLIST_HPP
#define __EOS_FORMSLIST_HPP


#ifndef __EOS_HPP
#include "eos.hpp"
#endif

#ifndef __EOS_CALLBACKS_HPP
#include "System/Core/eosCallbacks.hpp"
#endif

#ifndef __EOS_FORMS_HPP
#include "Services/Forms/eosForms.hpp"
#endif


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
        protected:
            ~ListForm();
            void onActivate(FormHandle deactivateForm);
            void onPaint(DisplayControllerHandle displayController);
            void onSelectorMove(int position, bool forward);
            void onSelectorPress();
            void onDrawItem();
            void onSelectItem();
            void onClickItem();
        private:
            void nextItem();
            void prevItem();       
            void selectItem();
    };    
}


#endif
