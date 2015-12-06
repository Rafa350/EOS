#ifndef __EOS_OPTIONEDITORFORM_HPP
#define __EOS_OPTIONEDITORFORM_HPP


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
    
    class OptionEditorForm;
    typedef OptionEditorForm *OptionEditorFormHandle;
    
    class OptionEditorForm: public Form {
        private:
            const char *title;
            const char **items;
            unsigned currentItem;
            unsigned numItems;
    
        public:
            OptionEditorForm(FormsServiceHandle service, FormHandle parent);
        protected:
            ~OptionEditorForm();
            void onActivate(FormHandle deactivateForm);
            void onPaint(FormsDisplayHandle display);
            void onSelectorMove(int position, SelectorDirection direction);
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
