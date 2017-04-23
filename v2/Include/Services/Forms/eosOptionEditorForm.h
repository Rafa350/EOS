#ifndef __EOS_OPTIONEDITORFORM_HPP
#define __EOS_OPTIONEDITORFORM_HPP


#include "eos.hpp"
#include "System/Core/eosCallbacks.hpp"
#include "Services/Forms/eosForms.hpp"


namespace eos {
    
    class OptionEditorForm: public Form {
        private:
            const char *title;
            const char **items;
            unsigned currentItem;
            unsigned numItems;
    
        public:
            OptionEditorForm(FormsService *service, Form *parent);
        protected:
            ~OptionEditorForm();
            void onPaint(FormsDisplay *display);
#ifdef eosFormsService_UseSelector            
            void onSelectorMove(int position, SelectorDirection direction);
            void onSelectorPress();
#endif            
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
