#ifndef __EOS_NUMERICEDITORFORM_HPP
#define __EOS_NUMERICEDITORFORM_HPP


#include "eos.hpp"
#include "System/Core/eosCallbacks.hpp"
#include "Services/Forms/eosForms.hpp"


namespace eos {
       
    class NumericEditorForm: public Form {
        private:
            typedef ICallbackP2<NumericEditorForm*, int> IIncDecFormChangeEvent;
            
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
            NumericEditorForm(FormsService *service, Form *parent);
            
            template <class cls>
            void setEvChange(cls *instance, void (cls::*method)(NumericEditorForm*, int)) { 
                
                evChange = new CallbackP2<cls, NumericEditorForm*, int>(instance, method);
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
            void onPaint(FormsDisplay *display);
#ifdef eosFormsService_UseSelector            
            void onSelectorMove(int position, SelectorDirection direction);
#endif            
#ifdef eosFormsService_UseKeyboard            
            void onKeyPress(KeyCode keyCode);
#endif            
        private:
            void incValue();
            void decValue();
    };
}


#endif
