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
            typedef ICallbackP2<NumericEditorFormHandle, int> IIncDecFormChangeEvent;
            
        private:
            int value;
            int minValue;
            int maxValue;
            int delta;
            const char *title;
            const char *prefix;
            const char *suffix;
            IIncDecFormChangeEvent *evChange;
            
        public:
            NumericEditorForm(FormsServiceHandle service, FormHandle parent);
            
            template <class cls>
            void setEvChange(cls *instance, void (cls::*method)(NumericEditorFormHandle, int)) { 
                
                evChange = new CallbackP2<cls, NumericEditorFormHandle, int>(instance, method);
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
        private:
            void incValue();
            void decValue();
    };
}


#endif
