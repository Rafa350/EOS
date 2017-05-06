#ifndef __EOS_OPTIONEDITORFORM_H
#define __EOS_OPTIONEDITORFORM_H


#include "eos.h"
#include "System/Core/eosCallbacks.h"
#include "Services/Forms/eosForms.h"


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
