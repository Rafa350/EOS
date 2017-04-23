#ifndef __EOS_NUMERICEDITORFORM_HPP
#define __EOS_NUMERICEDITORFORM_HPP


#include "eos.hpp"
#include "System/Core/eosCallbacks.hpp"
#include "Services/Forms/eosForms.hpp"
#include "Controllers/Display/eosColor.hpp"


namespace eos {
       
    class NumericEditorForm: public Form {
        private:
            typedef ICallbackP2<NumericEditorForm*, int> IIncDecFormChangeEvent;
            
        private:
            int value;
            int minValue;
            int maxValue;
            int delta;
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
            void setPrefix(const char *prefix);
            void setSuffix(const char *suffix);
            
            /// \brief Retorna el valor actual.
            /// \return El valor actual.
            inline int getValue() const { return value; }
            inline int getMinValue() const { return minValue; }
            inline int getMaxValue() const { return maxValue; }
            inline int getDelta() const { return delta; }

        protected:
            ~NumericEditorForm();            
            void onPaint(FormsDisplay *display);
#ifdef eosFormsService_UseSelector            
            void onSelectorMove(int position, SelectorDirection direction);
            void onSelectorPress();
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
