#ifndef __EOS_NUMERICEDITORFORM_HPP
#define __EOS_NUMERICEDITORFORM_HPP


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
    
    class NumericEditorForm;
    typedef NumericEditorForm *NumericEditorFormHandle;
    
    class NumericEditorForm: public Form {
        private:
            typedef ICallbackP1<int> IIncDecFormChangeEvent;
            typedef ICallbackP1<int> IIncDecFormSetEvent;
            
        private:
            int value;
            int minValue;
            int maxValue;
            int delta;
            const char *title;
            const char *prefix;
            const char *suffix;
            IIncDecFormChangeEvent *evChange;
            IIncDecFormSetEvent *evSet;
            
        public:
            NumericEditorForm(FormsServiceHandle service, FormHandle parent);
            
            template <class cls>
            void setEvChange(cls *instance, void (cls::*method)(int)) { 
                
                evChange = new CallbackP1<cls, int>(instance, method);
            }
            
            template <class cls>
            void setEvSet(cls *instance, void (cls::*method)(int)) { 
                
                evSet = new CallbackP1<cls, int>(instance, method);
            }
            
            void setMinValue(int minValue);
            void setMaxValue(int maxValue);
            void setValue(int value);
            void setDelta(int delta);
            void setTitle(const char *title);
            void setPrefix(const char *prefix);
            void setSuffix(const char *suffix);
            
            /// \brief Retorna el valor actual.
            /// \return El valor actual.
            ///
            int getValue() const { return value; }
        protected:
            ~NumericEditorForm();            
            void onActivate(FormHandle deactivateForm);
            void onPaint(FormsDisplayHandle display);
            void onSelectorMove(int position, SelectorDirection direction);
            void onSelectorPress();
        private:
            void incValue();
            void decValue();
            void setValue();
    };
}


#endif
